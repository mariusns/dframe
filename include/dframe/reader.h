/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

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

typedef struct dfreader_drv
{
	void (*read)();
	void (*take)();
	void (*load)();
	void (*lock)();
	void (*unlock)();
	void (*status)();
}dfreader_drv_t;




#endif /* INCLUDE_DFRAME_READER_H_ */
