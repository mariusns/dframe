/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * entity.c
 *
 *  Created on: 21. nov. 2022
 *      Author: marius
 */


#include <dframe/entity.h>
#include <dds/ddsc/dds_public_entity.h>


/* DDS interface layer */

static dds_return_t valid_type(df_type_t type)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;

	switch (type)
	{
		case DF_TYPE_PARTICIPANT:
		case DF_TYPE_WORKER:
		case DF_TYPE_PUBLISHER:
		case DF_TYPE_WRITER:
		case DF_TYPE_SUBSCRIBER:
		case DF_TYPE_READER:
		case DF_TYPE_TOPIC:
			ret = DDS_RETCODE_OK;
	}

	return ret;

}


//static dds_return_t dfent

dfentity_t* dfentity_alloc(dds_entity_t parent, dds_domainid_t domain, df_type_t type , ecfg_t *cfg)
{

	dfentity_t *e = NULL;
	dds_qos_t *qos = NULL;
	dds_listener_t *list = NULL;

	if(!valid_type(type))
	{
		return e;
	}


	if(parent<= 0 && type != DF_TYPE_PARTICIPANT)
	{
		return e;
	}

	if((e = dds_alloc(sizeof(*e))) == NULL)
	{
		return NULL;
	}
	/* Set default */

	e->e = DDS_RETCODE_UNSUPPORTED;
	e->list = NULL;
	e->qos = NULL;
	e->type = DF_TYPE_DONTCARE;
	e->enable = false;
	e->status = DDS_RETCODE_NOT_ENABLED;

	if(cfg != NULL )
	{
		if(sizeof(cfg->qos.data) >= sizeof(dds_qos_t) && (e->qos = dds_alloc(sizeof(*e->qos)))!= NULL)
		{
			if(dds_copy_qos(e->qos,cfg->qos.data) != DDS_RETCODE_OK)
			{

				e->status = DDS_RETCODE_ERROR;
				return e;
			}

		}else
		{
			e->status = DDS_RETCODE_ERROR;
			return e;
		}


		if(sizeof(cfg->qos.data(e->list) >= sizeof(dds_listener_t) && (e->list = dds_alloc(sizeof(*e->list)))) != NULL)
		{
			if(dds_copy_listener(e->list, cfg->listener.data) != DDS_RETCODE_OK)
			{
				e->status = DDS_RETCODE_ERROR;
				return e;
			}
		}else
		{
			e->status = DDS_RETCODE_ERROR;
			return e;
		}


	}

	df_type_t ptype = (df_type_t)dds_get_kind(parent);

	if(cfg != NULL && cfg->type == DF_TYPE_CFG )
	{
		if(type == DF_TYPE_WRITER || type== DF_TYPE_READER)
		{
			if( (df_type_t)dds_get_kind(cfg->topic.e) != DF_TYPE_TOPIC)
			{
				e->status = DDS_RETCODE_BAD_PARAMETER;
				return e;
			}
		}else if(type ==  DF_TYPE_TOPIC)
		{
			if(cfg->topic.desc == NULL ||  cfg->topic.name == NULL )
			{
				e->status = DDS_RETCODE_BAD_PARAMETER;
				return e;
			}
		}
	}

	switch (type)
	{
		case DF_TYPE_PARTICIPANT:

			e->e = dds_create_participant(((cfg != NULL && cfg->domain != NULL ) ? cfg->domain: DDS_DOMAIN_DEFAULT), e->qos, e->list);
			break;
		case DF_TYPE_PUBLISHER:
			if(ptype != DF_TYPE_PARTICIPANT)
			{
				e->status = DDS_RETCODE_BAD_PARAMETER;
				return e;
			}

			e->e = dds_create_publisher(parent, e->qos, e->list);

			break;

		case DF_TYPE_WRITER:

			if(ptype != DF_TYPE_PARTICIPANT || ptype !=  DF_TYPE_PUBLISHER)
			{
				e->status = DDS_RETCODE_BAD_PARAMETER;
				return e;
			}

			e->e = dds_create_writer(parent, cfg->topic.e, e->qos, e->list);

			break;
		case DF_TYPE_SUBSCRIBER:
			if(ptype != DF_TYPE_PARTICIPANT)
			{
				e->status = DDS_RETCODE_BAD_PARAMETER;
				return e;
			}

			e->e = dds_create_subscriber(parent, e->qos, e->list);

			break;
		case DF_TYPE_READER:
			if(ptype != DF_TYPE_PARTICIPANT && ptype != DF_TYPE_SUBSCRIBER)
			{
				e->status = DDS_RETCODE_BAD_PARAMETER;
				return e;
			}

			e->e = dds_create_reader(parent, cfg->topic.e, e->qos, e->list);

			break;
		case DF_TYPE_TOPIC:
			if(ptype != DF_TYPE_PARTICIPANT && ptype != DF_TYPE_SUBSCRIBER && ptype != DF_TYPE_PUBLISHER)
			{
				e->status = DDS_RETCODE_BAD_PARAMETER;
			}

			e->e = dds_create_topic(parent,cfg->topic.desc, cfg->topic.name, e->qos, e->list);

			break;
		default:
			e->type = DF_TYPE_DONTCARE;

	}

	if(e->e > DDS_RETCODE_OK)
	{
		e->status = DDS_RETCODE_OK;
		e->type = type;
		if(dds_enabled(e->e) == DDS_RETCODE_OK)
		{
			e->enable = true;
		}
	}

	return e;
}

dds_return_t dfentity_enable(dfentity_t *entity)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;

	if(entity == NULL)
	{
		return ret;
	}

	if(valid_type(entity->type) != DDS_RETCODE_OK)
	{
		return ret;
	}

	if(entity->enable == false)
	{
		ret = dds_enable(entity->e);
	}else
	{
		ret = DDS_RETCODE_OK;
	}

	if(ret == DDS_RETCODE_OK)
	{
		entity->enable = true;
	}
	else
	{
		entity->enable = false;
	}

	return ret;
}

inline dds_return_t dfentity_enabled(dfentity_t *entity)
{

	if(entity == NULL){ return DDS_RETCODE_BAD_PARAMETER;}
	return entity->enable ? DDS_RETCODE_OK:DDS_RETCODE_NOT_ENABLED;
}

dds_return_t dfentity_free(dfentity_t *entity)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	if(entity == NULL || valid_type(entity->type) != DDS_RETCODE_OK)
	{
		return ret;
	}

	if(entity->status == DDS_RETCODE_ALREADY_DELETED)
	{
		return DDS_RETCODE_OK;
	}

	/* Set default */
	entity->enable = false;
	entity->type = DF_TYPE_DONTCARE;
	ret = dds_delete(entity->e);
	if(ret != DDS_RETCODE_OK)
	{
		return ret;
	}

	dds_delete_listener(entity->list);
	entity->list = NULL;
	dds_delete_qos(entity->qos);
	entity->qos = NULL;
	entity->status = DDS_RETCODE_ALREADY_DELETED;

	return DDS_RETCODE_OK;
}

df_type_t dfentity_get_type(dfentity_t *entity)
{
	df_type_t ret = DF_TYPE_DONTCARE;
	if (entity == NULL)
	{
		return ret;
	}

	if(entity->enable && entity->e > DDS_RETCODE_OK )
	{

		if(valid_type(entity))
		{
			ret = entity->type;
		}
		else if( entity->type == DF_TYPE_DONTCARE)
		{
			ret = dds_get_type(entity->e);
		}

	}

	return ret;

}



