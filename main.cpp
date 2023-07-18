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

#include "Program.h"
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
    
    // Create an instance of Program.
    Program program;
    
    program.get_options(argc, argv);
    
    // Create an instance of blackScholesModel.
    blackScholesModel model;
    
    program.launchAlgo(model);
    
    return 0;
}


// ----------------------------------------------------------------------------
//                      Class Member Function Implementations
// ----------------------------------------------------------------------------


// Default constructor.
Program::Program() {}


// Processes the command line arguments.
void Program::get_options(int argc, char* argv[]) {
    int optIndex = 0, option = 0;
    bool invalidMode = false; // Tracks invalid mode provision(s)
    
    // Define an array of the structures describing each long option.
    struct option longOpts[] = {{"mode", required_argument, nullptr, 'm'}, // Option: --mode or -m
                                {"help", no_argument, nullptr, 'h'},       // Option: --help or -h
                                {nullptr, no_argument, nullptr, '\0'}};    // End of options
    
    // Loop over all of the options.
    while (true) {
        option = getopt_long(argc, argv, "m:h", longOpts, &optIndex);
        
        if (option == -1) {
            break; // Break out of the loop if no more options are found
        } // if
        
        switch (option) {
                
            // If the "mode" option is flagged
            case 'm':
                // Set the program mode to the provided argument.
                inputMode = optarg;
                
                // If an invalid mode is specified, print to standard error and set invalidMode to true.
                if (inputMode != "USER" && inputMode != "FILE" && inputMode != "DB" && inputMode != "API") {
                    cerr << "Invalid mode.\n";
                    invalidMode = true; // Set invalidMode to true
                } // if
                break; // Break out of the switch statement
                
            // If the "help" option is flagged
            case 'h':
                // Print a helpful message and exit.
                printHelp(argv);
                exit(0);
            
            // Default case
            default:
                cerr << "Invalid command line option.\n";
                invalidMode = true; // Set invalidMode to true
                break; // Break out of the switch statement
        } // switch
    } // while
    
    // Check if an invalid mode was encountered
    if (invalidMode) {
        cerr << "Invalid mode was provided as a command line option.\n";
        exit(1); // Exit with an error code
    } // if
    
    // Check if a mode was specified
    if (inputMode.empty()) {
        cerr << "Error: no mode specified.\n";
        exit(1); // Exit with an error code
    } // if
} // get_options()



// Prints a helpful message about how to use the program for the user when requested.
void Program::printHelp(char* argv[]) {
    // Usage:
    cout << "Usage: " << argv[0] << " [-m USER|FILE|DB|API]|-h" << endl; // argv[0] is the name of the currently executing program
    cout << "This program is designed to calculate European options pricing " << endl;
    cout << "using the Black-Scholes formula." << endl;
    // Options:
    cout << "Options:" << endl;
    cout << "-m, --mode <mode>: Specify the mode of operation." << endl;
    cout << "Valid modes are: USER, FILE, DB, API." << endl;
    cout << "-h, --help: Print this help message." << endl;
    // Additional details:
    cout << "Based on the specified mode of operation, the program can read " << endl;
    cout << "input from its user(s), file(s), database(s), and/or external data feeds (e.g. APIs)." << endl;
} // printHelp()
 


// Launches the algorithm.
void Program::launchAlgo(blackScholesModel &model) {
    InputReader inputReader;
    
    // Call the corresponding function based on the input mode.
    if (inputMode == "USER") { // User input
        inputReader.readInputFromUser(model);
    } else if (inputMode == "FILE") { // File input
        string filename = "input.txt"; // Example filename
        inputReader.readInputFromFile(model, filename);
    } else if (inputMode == "DB") { // Database input
        inputReader.readInputFromDB(model);
    } else if (inputMode == "API") { // External data feed (e.g. API) input
        inputReader.readInputFromAPI(model);
    } else {
        cerr << "Error: invalid or non-existing mode.\n";
        exit(-1);
    } // if-elif-else
} // launchAlgo()


