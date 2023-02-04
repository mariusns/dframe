/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * typeless.h
 *
 *  Created on: 7. des. 2022
 *      Author: marius
 */

#ifndef TYPELESS_H_
#define TYPELESS_H_
#include <dframe/dftypes.h>

/*

typedef struct df_functions_s
{
	dds_return_t (*init)(entity_t * e);
	dds_return_t (*alloc)(entity_t * e, dds_entity_t p, ecfg_t *cfg);
	dds_return_t (*free)(entity_t * e);

	dds_return_t (*enable)(entity_t * e);
	dds_return_t (*enabled)(entity_t * e);

}df_functions_t;




dds_return_t df_init(entity_t * e);
dds_return_t df_alloc(entity_t * e, dds_entity_t p, ecfg_t *cfg);
dds_return_t df_free(entity_t * e);

dds_return_t df_enable(entity_t * e);
dds_return_t df_enabled(entity_t * e);


extern const df_functions_t functions =
{
		.init = df_init,
		.alloc = df_alloc,
		.free = df_free,
		.enable = df_enable,
		.enabled = df_enabled
};

*/


#endif /* TYPELESS_H_ */
