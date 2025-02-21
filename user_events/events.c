/*
 * events.c
 *
 *  Created on: 8 мая 2020 г.
 *      Author: IVSop
 */
#include "callback.h"
#include "cmsis_os.h"

static osEventFlagsId_t _periph_event_id;

/**
 * \brief
 *
 */
void init_periph_events(void)
{
	_periph_event_id = osEventFlagsNew(NULL);
	if (_periph_event_id == NULL)
	{
		/// \\todo printf
	}
	else
	{
		set_cb_periph_event_id(_periph_event_id);
	}
}

/**
 * \brief
 *
 */
osEventFlagsId_t  get_periph_event_id(void)
{
	return _periph_event_id;
}


