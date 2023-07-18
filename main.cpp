//
//  main.cpp
//  black-scholes
//
//  Created by lyndskg on 7/17/23.
//

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <getopt.h>


#include "blackscholes.h"
#include "inputReader.h"
#include "xcode_redirect.hpp"



// ----------------------------------------------------------------------------
//                               Driver
// ----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
    // To speed up I/O
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    cout << setprecision(20);  // Always show 20 decimal places
    cout << fixed; // Disable scientific notation for large numbers
    
    
    // Create an instance of blackScholesModel.
    blackScholesModel model;
    
    // Process the commamnd line arguments.
    model.get_options(argc, argv);
    
    // based on inputmode, set parameters
    /*
     
     CASE 1: USER INPUT
     
     
     CASE 2: FILE INPUT
     
     
     CASE 3: DB INPUT
     
     
     CASE 4: API / DATA FEED
     
     */
//
//    // Use other member functions as needed.
//    double optionPrice = model.calculateOptionPrice(1, 1, 1, 1, 2, 'c');
//
    
//    cout << optionPrice << endl;
    // TODO: Further calculations or operations
    
    
//    // Read input from market data.
//    model.readInput();

    // Launch the algo ____.
    model.launchAlgo();
    
    return 0;
}


