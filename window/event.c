/* event.c  -  Window library events  -  Public Domain  -  2014 Mattias Jansson / Rampant Pixels
 * 
 * This library provides a cross-platform window library in C11 providing basic support data types and
 * functions to create and manage windows in a platform-independent fashion. The latest source code is
 * always available at
 *
 * https://github.com/rampantpixels/window_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.
 *
 */

#include <foundation/foundation.h>

#include <window/window.h>
#include <window/internal.h>


static event_stream_t* _window_stream = 0;


int _window_event_initialize( void )
{
	if( !_window_stream )
		_window_stream = event_stream_allocate( 1024 );
	return 0;
}


void _window_event_shutdown( void )
{
	if( _window_stream )
		event_stream_deallocate( _window_stream );
	_window_stream = 0;
}


void window_event_process( void )
{
}


event_stream_t* window_event_stream( void )
{
	return _window_stream;
}


void window_event_handle_foundation( event_t* event )
{
#if FOUNDATION_PLATFORM_IOS
	if( event->id == FOUNDATIONEVENT_START )
	{
		_window_app_started = true;
		_window_app_paused = false;
	}
	else if( event->id == FOUNDATIONEVENT_PAUSE )
		_window_app_paused = true;
	else if( event->id == FOUNDATIONEVENT_RESUME )
		_window_app_paused = false;
#endif
}
