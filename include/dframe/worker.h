/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * worker.h
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#ifndef INCLUDE_DFRAME_WORKER_H_
#define INCLUDE_DFRAME_WORKER_H_
#include "dftypes.h"

dds_return_t dfworker_alloc(dfworker_t *worker, dds_entity_t participant, int32_t nw, int32_t nr, uint8_t mode);
dds_return_t dfworker_alloc_l(dfworker_t *worker, dds_entity_t participant, int32_t nw, int32_t nr, uint8_t mode, dfconfig_t *config);
dds_return_t dfworker_free(dfworker_t *worker);

#endif /* INCLUDE_DFRAME_WORKER_H_ */
