//
//  Program.h
//  black-scholes
//
//  Created by lyndskg on 7/18/23.
//

#ifndef Program_h
#define Program_h

#include "blackScholes.h"
#include "inputReader.h"


// ----------------------------------------------------------------------------
//                      "Program" Class Declarations
// ----------------------------------------------------------------------------


class Program {
public:
    string inputMode; // Program mode (USER, FILE, DB, API)
    
    // Default constructor.
    Program();
    
    // Processes the command line arguments.
    void get_options(int argc, char* argv[]);
    
    // Prints a helpful message about how to use the program for the user when requested.
    void printHelp(char* argv[]);
    
    
    // Launches the algorithm.
    void launchAlgo(blackScholesModel &model);
    
private:
    // TODO: Implement any missing member variables
}; // Program


#endif /* Program_h */
