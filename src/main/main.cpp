/* 
 * File:   main.cpp
 * Author: WP
 *
 * Created on September 25, 2013, 12:29 AM
 */

#include <cstdlib>
#include "app/Application.h"
#include "util/logger.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
        logger *loge = new logger();
		
        Application *app = new Application(argc, argv, loge);
		
        
        app->init();
        
        app->run();

        return 0;
}

