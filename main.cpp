//
//  main.cpp
//  black-scholes
//
//  Created by lyndskg on 7/18/23.
//

#include <stdio.h>
#include <iomanip>

#include "Program.h"
#include "blackScholes.h"
#include "inputReader.h"
#include "xcode_redirect.hpp"

using namespace std;

// ----------------------------------------------------------------------------
//                               Driver
// ----------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    // To speed up I/O
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    cout << setprecision(20);  // Always show 20 decimal places
    cout << fixed; // Disable scientific notation for large numbers
    
    // Create an instance of Program.
    Program program;
    
    program.get_options(argc, argv);
    
    // Create an instance of blackScholesModel.
    blackScholesModel model;
    
    program.launchAlgo(model);
    
    return 0;
    
} // main()
