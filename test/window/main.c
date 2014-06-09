/* main.c  -  Window test  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
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
#include <foundation/delegate.h>
#include <window/window.h>
#include <test/test.h>


static application_t test_window_application( void )
{
	application_t app = {0};
	app.name = "Window tests";
	app.short_name = "test_window";
	app.config_dir = "test_window";
	return app;
}


static memory_system_t test_window_memory_system( void )
{
	return memory_system_malloc();
}


static int test_window_initialize( void )
{
	return 0;
}


static void test_window_shutdown( void )
{
}


DECLARE_TEST( window, createdestroy )
{
	window_t* window;
#if FOUNDATION_PLATFORM_MACOSX
	window = window_allocate_from_nswindow( delegate_nswindow() );
#elif FOUNDATION_PLATFORM_IOS
	window = window_allocate_from_uiwindow( delegate_uiwindow() );
#endif
	
	EXPECT_NE( window, 0 );
	EXPECT_TRUE( window_is_open( window ) );
	
	window_deallocate( window );
	window = 0;

	EXPECT_FALSE( window_is_open( window ) );
	
	return 0;
}


DECLARE_TEST( window, sizemove )
{
	window_t* window;
#if FOUNDATION_PLATFORM_MACOSX
	window = window_allocate_from_nswindow( delegate_nswindow() );
#elif FOUNDATION_PLATFORM_IOS
	window = window_allocate_from_uiwindow( delegate_uiwindow() );
#endif
	
	EXPECT_NE( window, 0 );
	EXPECT_TRUE( window_is_open( window ) );

	thread_sleep( 1000 );
	
#if FOUNDATION_PLATFORM_IOS || FOUNDATION_PLATFORM_ANDROID
	EXPECT_TRUE( window_is_maximized( window ) );
#else
	EXPECT_FALSE( window_is_maximized( window ) );
#endif
	
	EXPECT_TRUE( window_is_visible( window ) );
	EXPECT_TRUE( window_has_focus( window ) );
	
	window_maximize( window );
	thread_sleep( 1000 );
	EXPECT_TRUE( window_is_maximized( window ) );
	EXPECT_TRUE( window_has_focus( window ) );

#if !FOUNDATION_PLATFORM_IOS && !FOUNDATION_PLATFORM_ANDROID
	window_restore( window );
	thread_sleep( 1000 );
	EXPECT_FALSE( window_is_maximized( window ) );
	EXPECT_TRUE( window_has_focus( window ) );
#endif
	
	window_maximize( window );
	thread_sleep( 1000 );
	EXPECT_TRUE( window_is_maximized( window ) );
		
#if !FOUNDATION_PLATFORM_IOS && !FOUNDATION_PLATFORM_ANDROID
	window_resize( window, 150, 100 );
	thread_sleep( 1000 );
	EXPECT_EQ( window_width( window ), 150 );
	EXPECT_EQ( window_height( window ), 100 );
	EXPECT_FALSE( window_is_maximized( window ) );
	EXPECT_TRUE( window_has_focus( window ) );
	
	window_move( window, 10, 20 );
	thread_sleep( 1000 );
	EXPECT_EQ( window_position_x( window ), 10 );
	EXPECT_EQ( window_position_y( window ), 20 );
	EXPECT_FALSE( window_is_maximized( window ) );
	EXPECT_TRUE( window_has_focus( window ) );
	
	window_minimize( window );
	thread_sleep( 1000 );
	EXPECT_FALSE( window_is_maximized( window ) );
	EXPECT_FALSE( window_has_focus( window ) );

	window_restore( window );
	thread_sleep( 1000 );
	EXPECT_FALSE( window_is_maximized( window ) );
	EXPECT_FALSE( window_is_minimized( window ) );
	EXPECT_TRUE( window_has_focus( window ) );
	
	window_minimize( window );
	thread_sleep( 1000 );
	EXPECT_FALSE( window_is_maximized( window ) );
	EXPECT_TRUE( window_is_minimized( window ) );
#endif
		
	window_deallocate( window );
	window = 0;
	
	EXPECT_FALSE( window_is_open( window ) );
	
	return 0;
}


static void test_window_declare( void )
{
	ADD_TEST( window, createdestroy );
	ADD_TEST( window, sizemove );
}


test_suite_t test_window_suite = {
	test_window_application,
	test_window_memory_system,
	test_window_declare,
	test_window_initialize,
	test_window_shutdown
};


#if FOUNDATION_PLATFORM_ANDROID || FOUNDATION_PLATFORM_IOS

int test_window_run( void );
int test_window_run( void )
{
	test_suite = test_window_suite;
	return test_run_all();
}

#else

test_suite_t test_suite_define( void );
test_suite_t test_suite_define( void )
{
	return test_window_suite;
}

#endif

