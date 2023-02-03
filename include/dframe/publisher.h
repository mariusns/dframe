/*
 * publisher.h
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#ifndef INCLUDE_DFRAME_PUBLISHER_H_
#define INCLUDE_DFRAME_PUBLISHER_H_
#include "dftypes.h"


dds_return_t dfpublisher_alloc(dfpublisher_t * pub, dds_entity_t parent, dfconfig_t *config);
dds_return_t dfpublisher_free(dfpublisher_t * pub);
dds_return_t dfpublisher_enable(dfpublisher_t * pub);
dds_return_t dfpublisher_enabled(dfpublisher_t * pub);
#endif /* INCLUDE_DFRAME_PUBLISHER_H_ */
