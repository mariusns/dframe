/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * datatypes.h
 *
 *  Created on: 16. sep. 2022
 *      Author: marius
 */

#ifndef INCLUDE_DATATYPES_H_
#define INCLUDE_DATATYPES_H_
#include <dds/ddsc/dds_public_impl.h>
#include <stdint.h>
#include <stdbool.h>


#define DFDESC(X) "Descriptor "##X
#define DF_MODE_R	1
#define DF_MODE_W	2
#define DF_MODE_WR	3
#define DF_MODE_READ 4
#define DF_MODE_READ_THREAD 5
#define DF_MODE_READ_THREAD_SINGLE 6


typedef enum df_type {
	DF_TYPE_DONTCARE			= DDS_KIND_DONTCARE,
	DF_TYPE_TOPIC	 			= DDS_KIND_TOPIC,
	DF_TYPE_PARTICIPANT			= DDS_KIND_PARTICIPANT,
	DF_TYPE_READER 				= DDS_KIND_READER,
	DF_TYPE_WRITER		 		= DDS_KIND_WRITER,
	DF_TYPE_SUBSCRIBER  		= DDS_KIND_SUBSCRIBER,
	DF_TYPE_PUBLISHER	 		= DDS_KIND_PUBLISHER,
	DF_TYPE_COND_READ			= DDS_KIND_COND_READ,
	DF_TYPE_COND_QUERY			= DDS_KIND_COND_QUERY,
	DF_TYPE_COND_GUARD			= DDS_KIND_COND_GUARD,
	DF_TYPE_WAITSET				= DDS_KIND_WAITSET,
	DF_TYPE_DOMAIN				= DDS_KIND_DOMAIN,
	DF_TYPE_PROCESSOR	 		= 13,
	DF_TYPE_WORKER,
	DF_TYPE_EVENT,
	DF_TYPE_DATA,
	DF_TYPE_ENTITY,
	DF_TYPE_CONFIG,
	DF_TYPE_CFG,
	DF_TYPE_VECTOR,
}df_type_t;



#define DF_NO_NUMBER (-1)






#endif /* INCLUDE_DATATYPES_H_ */

