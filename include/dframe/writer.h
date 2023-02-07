/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

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

typedef struct dfwriter_drv
{
	void (*write)();
	void (*loan)();
	void (*release)();
	void (*lock)();
	void (*unlock)();
	void (*status)();
}dfwriter_drv_t;

#endif /* INCLUDE_DFRAME_WRITER_H_ */
