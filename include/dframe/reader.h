/*
 * reader.h
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#ifndef INCLUDE_DFRAME_READER_H_
#define INCLUDE_DFRAME_READER_H_

#include <dframe/dftypes.h>

dds_return_t dfreader_alloc(dfreader_t *reader, dfentity_t *parent, ecfg_t *cfg);
dds_return_t dfreader_free(dfreader_t *reader);
dds_return_t dfreader_enable(dfreader_t *reader);

#endif /* INCLUDE_DFRAME_READER_H_ */
