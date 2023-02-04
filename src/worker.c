/*
'
* Distributed under the terms of the GNU General Public License v2
* Copyright 2023 Marius Norvoll Sletten
*
*/

/*
 * worker.c
 *
 *  Created on: 9. nov. 2022
 *      Author: marius
 */

#include "dframe/worker.h"
#include <dframe/publisher.h>

dds_return_t dfworker_alloc(dfworker_t *worker, dds_entity_t participant, int32_t nw, int32_t nr, uint8_t mode)
{
	dds_return_t ret = dfworker_alloc_l(worker,participant, nw, nr,mode,NULL);

	return ret;
}

dds_return_t dfworker_alloc_l(dfworker_t *worker, dds_entity_t participant ,int32_t nw, int32_t nr, uint8_t mode, dfconfig_t *config)
/*
 * Only put pointers and allocate pointers, aslong as we dont have topics designated to writers/readers.
 *
 *
 */
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;
	ecfg_t *cfg = NULL;


	if(worker == NULL || worker->type != DF_TYPE_WORKER)
	{
		return ret;
	}


	/* Publisher */

	if(config != NULL && config->publisher != NULL)
	{
		cfg = config->participant;
	}

	ret = DDS_RETCODE_ALREADY_DELETED;
	worker->publisher = dfentity_alloc(participant, NULL, DF_TYPE_PUBLISHER, cfg);

	if(worker->publisher == NULL)
	{
		return ret;
	}
	else if(worker->publisher->status != DDS_RETCODE_OK)
	{
		return worker->publisher->status;
	}

	/* Subscriber */

	if(config != NULL && config->subscriber != NULL)
	{
		cfg = config->subscriber;
	}

	worker->subscriber = dfentity_alloc(participant, NULL, DF_TYPE_SUBSCRIBER, cfg);

	if(worker->subscriber->status != DDS_RETCODE_OK)
	{
		return worker->subscriber->status;
	}
	/* Default topics for worker "SYSTEM" */


	return ret;
}

dds_return_t dfworker_free(dfworker_t *worker)
{
	dds_return_t ret = DDS_RETCODE_BAD_PARAMETER;


	return ret;
}



