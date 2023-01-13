/*
 * reader.c
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#include <dframe/reader.h>


//dds_return_t dfreader_alloc(dfreader_t *reader, const char *desc)

dds_return_t dfreader_alloc(dfreader_t *reader, dfentity_t *parent, ecfg_t *cfg)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	if(reader == NULL || parent == NULL)
	{
		return ret;
	}

	if(dfentity_enabled(reader->entity) == DDS_RETCODE_OK)
	{

		if(reader->status != DDS_RETCODE_OK)
			reader->enable =  true;
		return DDS_RETCODE_OK;
	}


	if(parent->enable == false && dfentity_enable(parent) != DDS_RETCODE_OK)
	{

		return ret = DDS_RETCODE_NOT_ENABLED;
	}


	ret = dfentity_alloc(reader->entity , parent->e, DF_TYPE_READER , cfg);


	return ret;
}


dds_return_t dfreader_free(dfreader_t *reader)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;



	return ret;
}


dds_return_t dfreader_enable(dfreader_t *reader)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	if(reader == NULL)
	{
		return ret;
	}
	else if(reader->enable == false)
	{
		if((ret=dfentity_enabled(reader->entity)) != DDS_RETCODE_OK)
		{
			if (ret == DDS_RETCODE_NOT_ENABLED)
			{
				ret = dfentity_enable(reader->entity);
			}
			reader->enable = (ret == DDS_RETCODE_OK)? true:false;
		}
		else
		{
			reader->enable = true;
			ret = DDS_RETCODE_OK;
		}
	}
	else
	{
		ret = DDS_RETCODE_OK;
	}
	return reader->status = ret;
}

