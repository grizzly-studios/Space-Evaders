/* 
 * File:   main.cpp
 * Author: WP
 *
 * Created on September 25, 2013, 12:29 AM
 */

#include "BuildConfig.hpp"

#ifdef RUN_TESTS
	#include "gtest/gtest.h"
	#include "gmock/gmock.h"
#endif

#include "app/Application.h"
#include "util/Logger.h"

using namespace gs;

/*
 * 
 */
int main(int argc, char** argv) {
	#ifdef RUN_TESTS
		// The following line must be executed to initialize Google Mock
		// (and Google Test) before running the tests.
		::testing::InitGoogleMock(&argc, argv);
		return RUN_ALL_TESTS();
	#endif

	//No point in INFO, WARN or DEBUG messages before this point
	Application *app = new Application(argc, argv); 
	INFO << "Initialising application" << std::endl;
	app->init();
	INFO << "Running application" << std::endl;
	app->run();

	delete app;

	return 0;
}
