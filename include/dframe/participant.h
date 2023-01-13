/*
 * participant.h
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#ifndef INCLUDE_DFRAME_PARTICIPANT_H_
#define INCLUDE_DFRAME_PARTICIPANT_H_
#include "dftypes.h"


/* Allocation functions  */
dds_return_t dfparticipant_alloc(dfparticipant_t *part, int32_t numwork);
dds_return_t dfparticipant_alloc_l(dfparticipant_t *part, int32_t numwork, dfconfig_t *config);
dds_return_t dfparticipant_free(dfparticipant_t *part);







#endif /* INCLUDE_DFRAME_PARTICIPANT_H_ */
