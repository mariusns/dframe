/*
 * writer.c
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#include <dframe/writer.h>
#include <dframe/entity.h>
#include "dds/ddsrt/sync.h"
#include "dds/ddsrt/threads.h"







static dds_return_t dfwriter_init(dfwriter_t * writer)
{
	if(writer == NULL)
	{
		if((writer = dds_alloc(sizeof(*writer)))== NULL)
		{
			return DDS_RETCODE_ALREADY_DELETED;
		}

	}
	else if(sizeof(*writer) < sizeof(dfpublisher_t))
	{
		return DDS_RETCODE_BAD_PARAMETER;
	}

	if(writer->enable)
	{
		return DDS_RETCODE_OK;
	}

	writer->type = DF_TYPE_WRITER;
	writer->status = DDS_RETCODE_NOT_ENABLED;
	writer->enable = false;

	return DDS_RETCODE_OK;
}




dds_return_t dfwriter_alloc(dfwriter_t *writer, dfentity_t *parent, ecfg_t *cfg)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;

	ret = dfwriter_init(writer);
	if(ret != DDS_RETCODE_OK)
	{
		return ret;
	}

	writer->entity = dfentity_alloc(parent, DDS_DOMAIN_DEFAULT, DF_TYPE_WRITER, cfg);

	if(writer->entity == NULL)
	{
		ret = DDS_RETCODE_ALREADY_DELETED;
	}
	else
	{
		writer->status = writer->entity->status;

		if(writer->entity->enable)
		{
			writer->enable = true;
			ret = DDS_RETCODE_OK;
		}
		else
		{
			writer->enable = false;
			ret = DDS_RETCODE_NOT_ENABLED;
		}
	}
	return ret;
}

dds_return_t dfwriter_free(dfwriter_t *writer)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;

	return ret;
}


dds_return_t dfwriter_enable(dfwriter_t *writer)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	if(writer == NULL)
	{
		return ret;
	}
	else if(writer->enable == false)
	{
		if((ret=dfentity_enabled(writer->entity)) != DDS_RETCODE_OK)
		{
			if (ret == DDS_RETCODE_NOT_ENABLED)
			{
				ret = dfentity_enable(writer->entity);
			}
			writer->enable = (ret == DDS_RETCODE_OK)? true:false;
		}
		else
		{
			writer->enable = true;
			ret = DDS_RETCODE_OK;
		}
	}
	else
	{
		ret = DDS_RETCODE_OK;
	}
	return writer->status = ret;
}
