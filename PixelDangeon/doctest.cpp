/*
 * doctest_main.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: KZ
 */

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Menu.h"

namespace unit_doctest {

    int main(int argc, char** argv) {
        doctest::Context context;



        // defaults
    //    context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
    //    context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
    //    context.setOption("order-by", "name");            // sort the test cases by their name

        context.applyCommandLine(argc, argv);

        // overrides
    //    context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail

        int res = context.run(); // run

        if (context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
            return res;          // propagate the result of the tests

        int client_stuff_return_code = 0;
        // your program - if the testing framework is integrated in your production code

        srand(time(NULL));
        sf::RenderWindow window(sf::VideoMode(1000, 800), "PixelDangeon");
        Menu(window);

        return res + client_stuff_return_code; // the result from doctest is propagated here as well
    }

}