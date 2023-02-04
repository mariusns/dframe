/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * participant.c
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#include "participant.h"
#include "worker.h"
#include <dds/dds.h>
/* Only allocation */



static dds_return_t dfparticipant_init(dfparticipant_t *part)
{
	if(part == NULL)
	{
		if((part = dds_alloc(sizeof(*part)))== NULL)
		{
			return DDS_RETCODE_ALREADY_DELETED;
		}

	}
	else if( sizeof(*part) < sizeof(dfparticipant_t))
	{
		return DDS_RETCODE_BAD_PARAMETER;
	}

	if(part->enable)
	{
		return DDS_RETCODE_OK;
	}

	part->type = DF_TYPE_PARTICIPANT;
	part->status = DDS_RETCODE_NOT_ENABLED;
	part->entity = NULL;
	part->workers = NULL;
	part->n = 0;
	part->enable = false;

}



dds_return_t dfparticipant_alloc(dfparticipant_t *part, int32_t numwork)
{
	return dfparticipant_alloc_l(part, numwork, NULL);
}

dds_return_t dfparticipant_alloc_l(dfparticipant_t *part, int32_t numwork, dfconfig_t *config)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	size_t nw = 1;

	if(part->type != DF_TYPE_PARTICIPANT)
	{
		return ret;
	}


	part->entity = dfentity_alloc(NULL,DDS_DOMAIN_DEFAULT, DF_TYPE_PARTICIPANT, config->participant);
	if(part->entity != NULL && part->entity->status == DDS_RETCODE_OK)
	{
		part->status = DDS_RETCODE_OK;
		part->enable = true;
	}


	/*Only allocate*/
	if(numwork ==0)
	{
		 nw = 1;
	}
	else
	{
		nw = numwork;
	}

	part->workers = dds_alloc(sizof(*part->workers)*nw);
	if(part->workers != NULL)
		part->n = nw;

	/* Default number of reader/writers is 1, for system  */
	for(int i= 0; i< part->n; i++)
	{

		part->entity->status = dfworker_alloc_l(&part->workers[i], 1, 1, DF_MODE_WR, config);
		if(part->entity->status != DDS_RETCODE_OK)
		{
			break;
		}

	}

	if(part->entity->status  == DDS_RETCODE_OK)
	{
		/* Enable the entity since allocation is ok, but wait with the dfparticipant, until a worker is started */
		part->n = nw;
		part->status = DDS_RETCODE_OK;
		part->entity->enable = true;

	}
	else{
		part->n = 0;
		part->status = part->entity->status;
		part->entity->enable = false;
	}

	return ret;
}

dds_return_t dfparticipant_free(dfparticipant_t *part)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	if(part == NULL)
	{
		return ret;
	}
	else if(part->type != DF_TYPE_PARTICIPANT)
	{

		return ret;
	}
	else if(part->status ==  DDS_RETCODE_ALREADY_DELETED)
	{
		ret = DDS_RETCODE_OK;
		return ret;
	}



	for(int i= 0; i < part->n; i++)
	{
		ret  = dfworker_free(&part->workers[i]);
		if(ret != DDS_RETCODE_OK)
		{
			part->status = ret;
			break;
		}
	}
	if(ret == DDS_RETCODE_OK)
	{
		part->n = 0;
		part->enable = false;
		dds_free(part->workers);
		part->workers = NULL;
		ret = dfentity_free(part->entity);
		if(ret == DDS_RETCODE_OK)
		{
			part->entity = NULL;
		}
	}

	if(ret != DDS_RETCODE_OK)
	{
		/* Error handler*/

	}


	return ret;
}


