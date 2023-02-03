/*
 * writer.h
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#ifndef INCLUDE_DFRAME_WRITER_H_
#define INCLUDE_DFRAME_WRITER_H_
#include <dframe/dftypes.h>

dds_return_t dfwriter_alloc(dfwriter_t *writer, dfentity_t *parent, ecfg_t *cfg);
dds_return_t dfwriter_free(dfwriter_t *writer);
dds_return_t dfwriter_enable(dfwriter_t *writer);


#endif /* INCLUDE_DFRAME_WRITER_H_ */
