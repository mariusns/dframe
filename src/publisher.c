/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * publisher.c
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#include <dframe/publisher.h>


static dds_return_t dfpubliser_init(dfpublisher_t * pub)
{
	if(pub == NULL)
	{
		if((pub = dds_alloc(sizeof(*pub)))== NULL)
		{
			return DDS_RETCODE_ALREADY_DELETED;
		}

	}
	else if(sizeof(*pub) < sizeof(dfpublisher_t))
	{
		return DDS_RETCODE_BAD_PARAMETER;
	}

	if(pub->enable)
	{
		return DDS_RETCODE_OK;
	}

	pub->type = DF_TYPE_PUBLISHER;
	pub->status = DDS_RETCODE_NOT_ENABLED;
	pub->n = 0;
	pub->writers = NULL;
	pub->enable = false;

	return DDS_RETCODE_OK;
}



dds_return_t dfpublisher_alloc(dfpublisher_t * pub, dds_entity_t parent, dfconfig_t *config)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;

	ret = dfpubliser_init(pub);
	if(ret != DDS_RETCODE_OK)
	{
		return ret;
	}

	pub->entity = dfentity_alloc(parent, DDS_DOMAIN_DEFAULT, DF_TYPE_PUBLISHER, config->publisher);

	if(pub->entity == NULL)
	{
		ret = DDS_RETCODE_ALREADY_DELETED;
	}
	else
	{
		pub->status = pub->entity->status;

		if(pub->entity->enable)
		{
			pub->enable = true;
			ret = DDS_RETCODE_OK;
		}
		else
		{
			pub->enable = false;
			ret = DDS_RETCODE_NOT_ENABLED;
		}
	}
	return ret;
}


dds_return_t dfpublisher_enable(dfpublisher_t * pub)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	if(pub == NULL)
	{
		return ret;
	}
	else if(pub->enable == false)
	{
		if((ret=dfentity_enabled(pub->entity)) != DDS_RETCODE_OK)
		{
			if (ret == DDS_RETCODE_NOT_ENABLED)
			{
				ret = dfentity_enable(pub->entity);
			}
			pub->enable = (ret == DDS_RETCODE_OK)? true:false;
		}
		else
		{
			pub->enable = true;
			ret = DDS_RETCODE_OK;
		}
	}
	else
	{
		ret = DDS_RETCODE_OK;
	}
	return pub->status = ret;
}


dds_return_t dfpublisher_enabled(dfpublisher_t * pub)
{
	dds_return_t ret = DDS_RETCODE_NOT_ENABLED;

	if(pub == NULL)
	{
		ret = DDS_RETCODE_ALREADY_DELETED ;
	}
	else if(pub->enable && pub->status == DDS_RETCODE_OK)
	{
		ret = DDS_RETCODE_OK;
	}

	return ret;
}

dds_return_t dfpublisher_free(dfpublisher_t * pub)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;

	return ret;
}

