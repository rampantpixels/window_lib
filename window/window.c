/* window.c  -  Window library  -  Public Domain  -  2014 Mattias Jansson / Rampant Pixels
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


static bool _window_initialized = false;


int window_initialize( void )
{
	if( _window_initialized )
		return 0;
	
	if( _window_event_initialize() < 0 )
		return -1;
	
	_window_initialized = true;
	
#if FOUNDATION_PLATFORM_MACOSX || FOUNDATION_PLATFORM_IOS
	_window_class_reference();
#endif

	return 0;
}


void window_shutdown( void )
{
	_window_event_shutdown();
	
	_window_initialized = false;
}


bool window_is_initialized( void )
{
	return _window_initialized;
}
