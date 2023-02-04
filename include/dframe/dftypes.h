/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/
/*
 * topic.h
 *
 *  Created on: 16. sep. 2022
 *  Author: marius
 */

#ifndef DFTYPES_H_
#define DFTYPES_H_

#include <dds/dds.h>
#include <dframe/datatypes.h>


/*API accessable datatypes */




typedef struct dfvector_s
{
	const df_type_t type:DF_TYPE_VECTOR;
	void *data:NULL; // Cast this to what you need
	int32_t n;
}dfvector_t;

/* Sufficient structure to contain config for all entity types */
typedef struct ecfg_s{
	const df_type_t type:DF_TYPE_CFG;
	dds_domainid_t domain;
	struct {
		dds_entity_t e;
		const dds_topic_descriptor_t *desc;
		const char *name;
	}topic;
	dfvector_t qos;
	dfvector_t listener;
}ecfg_t;


/* Use this type for setting up qos and listeners, then we have one type for everything */
typedef struct dfconfig_s
{
	const df_type_t type: DF_TYPE_CONFIG;
	ecfg_t *participant:NULL;
	ecfg_t *worker:NULL;
	ecfg_t *publisher:NULL;
	ecfg_t *subscriber:NULL;
	ecfg_t *writer:NULL;
	ecfg_t *reader:NULL;
	ecfg_t *topic:NULL;
	ecfg_t *writer:NULL;
}dfconfig_t;



typedef struct dfentity_s{
	const df_type_t type:DF_TYPE_ENTITY;
	dds_entity_t e:DDS_RETCODE_BAD_PARAMETER;
	dds_qos_t	*qos:NULL;
	dds_listener_t *list:NULL;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
}dfentity_t;


typedef struct dfdata_s{
	const df_type_t type:DF_TYPE_DATA;
	const void **buffer;
	dds_sample_info_t *info:NULL;
	int32_t length:DF_NO_NUMBER;
	int32_t tsize:DF_NO_NUMBER;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
}dfdata_t;

/* Single event data-handle */
typedef struct dfevent_s
{
	const df_type_t type:DF_TYPE_EVENT;
	ddsrt_mutex_t lock;
	ddsrt_cond_t cond;
	ddsrt_threadattr_t tattr;
	ddsrt_thread_t tid;
	bool stop;
	dfdata_t *data;
	dds_return_t mode:DF_MODE_READ;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
}dfevent_t;

typedef struct dfprocessor_s
{
	const df_type_t type:DF_TYPE_PROCESSOR;
	void (* processor)(void *data);
	dfevent_t ev;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
}dfprocessor_t;

typedef struct entity_s
{
	const df_type_t type;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
	dfentity_t *entity;
}entity_t;

typedef struct dftopic_s
{
	const df_type_t type;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
	dfentity_t *entity;
	const char *name;
	const char *desc;

}dftopic_t;

typedef struct dfreader_s
{
	const df_type_t type;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
	dfentity_t *entity;
	uint8_t history:5;
	dfdata_t *data: NULL;
	dfprocessor_t processor;
}dfreader_t;

typedef struct dfwriter_s {
	const df_type_t type;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
	dfentity_t *entity;
	uint8_t history:5;
}dfwriter_t;

typedef struct dfsubscriber_s{
	const df_type_t type;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
	dfentity_t *entity;
	dfreader_t *readers:NULL;
	int32_t n:DF_NO_NUMBER;
}dfsubscriber_t;

typedef struct dfpublisher_s{
	const df_type_t type;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
	dfentity_t *entity;
	dfwriter_t *writers:NULL;
	int32_t n:DF_NO_NUMBER;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
}dfpublisher_t;

typedef struct dfworker_s {
	const df_type_t type:DF_TYPE_WORKER;
	const dftopic_t *topic:NULL;
	const dfpublisher_t *publisher:NULL;
	const dfsubscriber_t *subscriber:NULL;
	struct{
		int32_t t:0;
		int32_t p:0;
		int32_t s:0;
	}dim;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
}dfworker_t;


typedef struct dfparticipant_s{
	const df_type_t type:DF_TYPE_PARTICIPANT;
	dfentity_t *entity;
	const dfworker_t *workers; //??
	int32_t 	n:DF_NO_NUMBER;
	bool enable:false;
	dds_return_t status:DDS_RETCODE_ALREADY_DELETED;
}dfparticipant_t;

#endif /* DFTYPES_H_ */

