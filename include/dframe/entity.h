/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/
/*
 * entity.h
 *
 *  Created on: 21. nov. 2022
 *      Author: marius
 */

#ifndef INCLUDE_DFRAME_ENTITY_H_
#define INCLUDE_DFRAME_ENTITY_H_
#include <dframe/dftypes.h>

/* DDS interface layer */


dds_return_t dfentity_alloc(dfentity_t *entity , dds_entity_t parent, df_type_t type , ecfg_t *cfg);

dds_return_t dfentity_enable(dfentity_t *entity);

dds_return_t dfentity_enabled(dfentity_t *entity);

dds_return_t dfentity_free(dfentity_t *entity);

df_type_t dfentity_get_type(dfentity_t *entity);

#endif /* INCLUDE_DFRAME_ENTITY_H_ */
