/* 
 * File:   main.cpp
 * Author: WP
 *
 * Created on September 25, 2013, 12:29 AM
 */

#include <cstdlib>
#include "event/EventManager.hpp"
#include "logic/Logic.hpp"
#include "view/View.hpp"
#include "app/Application.h"
#include "util/logger.h"

using namespace std;
using namespace gs;

/*
 * 
 */
int main(int argc, char** argv) {
    logger *loge = logger::getInstance();
		
    Application *app = new Application(argc, argv, loge);
    app->init();
    app->run();
    return 0;
}
