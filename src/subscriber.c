/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * subscriber.c
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */


#include <dframe/subscriber.h>

static dds_return_t dfsubscriber_init(dfsubscriber_t * sub)
{

	if(sub == NULL)
	{
		if((sub = dds_alloc(sizeof(*sub)))== NULL)
		{
			return DDS_RETCODE_ALREADY_DELETED;
		}

	}
	else if(sizeof(*sub) < sizeof(dfsubscriber_t))
	{
		return DDS_RETCODE_BAD_PARAMETER;
	}

	if(sub->enable)
	{
		return DDS_RETCODE_OK;
	}

	sub->type = DF_TYPE_SUBSCRIBER;
	sub->status = DDS_RETCODE_NOT_ENABLED;
	sub->n = 0;
	sub->readers = NULL;
	sub->enable = false;

	return DDS_RETCODE_OK;
}



dds_return_t dfsubscriber_alloc(dfsubscriber_t * entity, dds_entity_t parent, ecfg_t *cfg)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;

	ret = dfsubscriber_init(entity);
	if(ret != DDS_RETCODE_OK)
	{
		return ret;
	}

	entity->entity = dfentity_alloc(parent, DDS_DOMAIN_DEFAULT, DF_TYPE_PUBLISHER, cfg);

	if(entity->entity == NULL)
	{
		ret = DDS_RETCODE_ALREADY_DELETED;
	}
	else
	{
		entity->status = entity->entity->status;
		if(entity->entity->enable)
		{
			entity->enable = true;
			ret = DDS_RETCODE_OK;
		}
		else
		{
			entity->enable = false;
			ret = DDS_RETCODE_NOT_ENABLED;
		}
	}
	return ret;
}


dds_return_t dfsubscriber_enable(dfsubscriber_t * entity)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	if(entity == NULL)
	{
		return ret;
	}
	else if(entity->enable== false)
	{
		if((ret=dfentity_enabled(entity->entity)) != DDS_RETCODE_OK)
		{
			if (ret == DDS_RETCODE_NOT_ENABLED)
			{
				ret = dfentity_enable(entity->entity);
			}
			entity->enable = (ret == DDS_RETCODE_OK)? true:false;
		}
		else
		{
			entity->enable = true;
			ret = DDS_RETCODE_OK;
		}
	}
	else
	{
		ret = DDS_RETCODE_OK;
	}
	return entity->status = ret;
}



dds_return_t dfsubscriber_enabled(dfsubscriber_t * entity)
{
	dds_return_t ret = DDS_RETCODE_NOT_ENABLED;

	if(entity == NULL)
	{
		ret = DDS_RETCODE_ALREADY_DELETED ;
	}
	else if(entity->enable && entity->status == DDS_RETCODE_OK)
	{
		ret = DDS_RETCODE_OK;
	}

	return ret;
}

dds_return_t dfsubscriber_free(dfpublisher_t * pub)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;

	return ret;
}
