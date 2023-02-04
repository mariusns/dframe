/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * typeless.c
 *
 *  Created on: 7. des. 2022
 *      Author: marius
 */

#include <typeless.h>
#include <dds/dds.h>

/* Default type */

#ifndef DF_TYPE_T
#undef DF_TYPE_T entity_t
//#else
//#define DF_TYPE_T entity_t
#endif /**/

#define DF_TYPE_T entity_t







dds_return_t df_init(DF_TYPE_T * e)
{

	DF_TYPE_T *entity =(DF_TYPE_T*)e;
	if(e == NULL)
	{
		if((e = dds_alloc(sizeof(entity)))== NULL)
		{
			return DDS_RETCODE_ALREADY_DELETED;
		}

	}
	else if(sizeof(*entity) < sizeof(DF_TYPE_T))
	{
		return DDS_RETCODE_BAD_PARAMETER;
	}

	if(e->enable)
	{
		return DDS_RETCODE_OK;
	}

	entity->type = DF_TYPE_T;
	entity->status = DDS_RETCODE_NOT_ENABLED;
	entity->enable = false;

	return DDS_RETCODE_OK;
}

dds_return_t df_alloc(DF_TYPE_T * sub, dds_entity_t parent, ecfg_t *cfg);



dds_return_t df_free(DF_TYPE_T * sub);

dds_return_t df_enable(DF_TYPE_T * sub);
dds_return_t df_enabled(DF_TYPE_T * pub);


