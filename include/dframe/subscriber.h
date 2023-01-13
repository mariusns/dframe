/*
 * subscriber.h
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#ifndef INCLUDE_DFRAME_SUBSCRIBER_H_
#define INCLUDE_DFRAME_SUBSCRIBER_H_
#include "dftypes.h"


dds_return_t dfsubscriber_alloc(dfsubscriber_t * sub, dds_entity_t parent, ecfg_t *cfg)
dds_return_t dfsubscriber_free(dfsubscriber_t * sub);

dds_return_t dfsubscriber_enable(dfsubscriber_t * sub);
dds_return_t dfsubscriber_enabled(dfsubscriber_t * pub);

#endif /* INCLUDE_DFRAME_SUBSCRIBER_H_ */
