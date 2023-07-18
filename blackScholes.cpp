//
//  blackScholes.cpp
//  black-scholes
//
//  Created by lyndskg on 7/12/23.
//

#include <iostream>
#include <stdio.h>
#include <iostream>
#include <getopt.h>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>
#include <numbers>

#include "blackScholes.h"
#include "inputReader.h"

using namespace std;


// ----------------------------------------------------------------------------
//           "blackScholesModel" Class Member Function Implementations
// ----------------------------------------------------------------------------

// Default constructor.
blackScholesModel::blackScholesModel() : optionType('C') {}

// Custom constructor: IS THIS NECESSARY?
blackScholesModel::blackScholesModel(double underlyingPrice, double strikePrice, double timeToExpiration,
                                         double riskFreeRate, double volatility, char optionType) {
//        this->underlyingPrice = underlyingPrice;
//        this->strikePrice = strikePrice;
//        this->TimeToExpiration = timeToExpiration;
//        this->RiskFreeRate = riskFreeRate;
//        this->Volatility = volatility;
//        this->Option = option;
        
}
//
//// Processes the command line arguments.
//void blackScholesModel::get_options(int argc, char* argv[]) {
//    int optIndex = 0, option = 0;
//    bool invalidMode = false; // Tracks invalid mode provision(s)
//
//    // Define an array of the structures describing each long option.
//    struct option longOpts[] = {{"mode", required_argument, nullptr, 'm'}, // Option: --mode or -m
//                                {"help", no_argument, nullptr, 'h'},       // Option: --help or -h
//                                {nullptr, no_argument, nullptr, '\0'}};    // End of options
//
//    // Loop over all of the options.
//    while (true) {
//        option = getopt_long(argc, argv, "m:h", longOpts, &optIndex);
//
//        if (option == -1) {
//            break; // Break out of the loop if no more options are found
//        } // if
//
//        switch (option) {
//
//            // If the "mode" option is flagged
//            case 'm':
//                // Set the program mode to the provided argument.
//                inputMode = optarg;
//
//                // If an invalid mode is specified, print to standard error and set invalidMode to true.
//                if (inputMode != "USER" && inputMode != "FILE" && inputMode != "DB" && inputMode != "API") {
//                    cerr << "Invalid mode.\n";
//                    invalidMode = true; // Set invalidMode to true
//                } // if
//                break; // Break out of the switch statement
//
//            // If the "help" option is flagged
//            case 'h':
//                // Print a helpful message and exit.
//                printHelp(argv);
//                exit(0);
//
//            // Default case
//            default:
//                cerr << "Invalid command line option.\n";
//                invalidMode = true; // Set invalidMode to true
//                break; // Break out of the switch statement
//        } // switch
//    } // while
//
//    // Check if an invalid mode was encountered
//    if (invalidMode) {
//        cerr << "Invalid mode was provided as a command line option.\n";
//        exit(1); // Exit with an error code
//    } // if
//
//    // Check if a mode was specified
//    if (inputMode.empty()) {
//        cerr << "Error: no mode specified.\n";
//        exit(1); // Exit with an error code
//    } // if
//} // get_options()



// Prints a helpful message about how to use the program for the user when requested.
void blackScholesModel::printHelp(char* argv[]) {
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




// Defines the option pricing function and calculates the option price using the Black-Scholes formula.
double blackScholesModel::calculateOptionPrice(double underlyingPrice, double strikePrice, double timeToExpiration,
                                               double riskFreeRate, double volatility, char optionType) {
        
    // Calculate the intermediate variables (i.e. d1 and d2)
    double d1 = (log(underlyingPrice / strikePrice) + (riskFreeRate + pow(volatility, 2) / 2.0) * timeToExpiration)
                    * (1.0 / volatility * sqrt(timeToExpiration));
    
    double d2 = d1 - volatility * sqrt(timeToExpiration);
    
    
    // TODO: Decide if switch, if-elif-else, or ternary operator
    // Calculate the option price based on the option type
    switch (optionType) {
        // If the option type is 'C' (call), calculate and return the call option price using the Black-Scholes formula
        case 'C':
            return underlyingPrice * normalCDF(d1) - strikePrice * exp(-riskFreeRate * timeToExpiration) * normalCDF(d2);
            
        // If the option type is 'P' (put), calculate and return the put option price using the Black-Scholes formula
        case 'P':
            return strikePrice * exp(-riskFreeRate * timeToExpiration) * normalCDF(-d2) - underlyingPrice * normalCDF(-d1);
            
        // If neither option type is specified, display an error message and return -1
        default:
            cerr << "Error: Option type does not exist!";
            return -1;
    } // switch
    
} // calculateOptionPrice()


// Approximates the cumulative distribution function (CDF) of a normal distribution.
double blackScholesModel::normalCDF(double d) {
    // Abramowitz & Stegun's (1964) approximation.
                
    /* Refer to https://www.ijser.org/researchpaper/Approximations-to-Standard-Normal-Distribution-Function.pdf
       for potentially more efficient approximations wrt M.A.E. and corresponding z-score */

    double result = 0.0;
    
    // The array 'a' contains pre-defined coefficients used in the approximation formula.
    const double a[] = {0.2316419, 0.31938153, -0.356563782, 1.781477937, -1.821255978, 1.330274429};
    
    double L, K = 0.0;
    
    L = abs(d); // Calculate the absolute value of 'd'
    K = 1.0 / (1.0 + a[0] * L); // Calculate the intermediate value 'K' using the first coefficient from 'a' and 'L'
    
    // Calculate the approximation of the CDF based on the coefficients and intermediate values
    result = 1.0 - 1.0 / sqrt(2 * std::numbers::pi) * exp(-L * L / 2.0) * (a[1] * K + a[2] * K * K + a[3] * pow(K, 3.0) + a[4] * pow(K, 4.0) + a[5] + pow(K, 5.0));
    
    // Return the result based on the sign of 'd'
    return d < 0 ? 1.0 - result : result; // Should ternary operator be used here? Or if-else statement (below)?
    
    // The ternary operator is used to return 1.0 minus the result if 'd' is negative, or the result itself if 'd' is non-negative.
    // Alternatively, an if-else statement can be used to achieve the same result.
    
} // normalCDF()


//
//// Launches the algorithm.
//void blackScholesModel::launchAlgo() {
//    blackScholesModel model;
//    InputReader inputReader;
//
//    // Call the corresponding function based on the input mode.
//    if (inputMode == "USER") { // User input
//        inputReader.readInputFromUser(model);
//    } else if (inputMode == "FILE") { // File input
//        string filename = "input.txt"; // Example filename
//        inputReader.readInputFromFile(model, filename);
//    } else if (inputMode == "DB") { // Database input
//        inputReader.readInputFromDB(model);
//    } else if (inputMode == "API") { // External data feed (e.g. API) input
//        inputReader.readInputFromAPI(model);
//    } else {
//        cerr << "Error: invalid or non-existing mode.\n";
//        exit(-1);
//    } // if-elif-else
//
//} // launchAlgo()


// ----------------------------------------------------------------------------
//                            Setter Methods
// ----------------------------------------------------------------------------

// Setter method for the underlying price of the Black-Scholes model.
void blackScholesModel::setUnderlyingPrice(const double& value) {
    underlyingPrice = value;
} // setUnderlyingPrice()


// Setter method for the strike price of the Black-Scholes model.
void blackScholesModel::setStrikePrice(const double& value) {
    strikePrice = value;
}// setStrikePrice()


// Setter method for the time until expiration of the Black-Scholes model.
void blackScholesModel::setTTE(const double& value) {
    timeToExpiration = value;
} // setTTE()


// Setter method for the risk-free rate of the Black-Scholes model.
void blackScholesModel::setRFR(const double& value) {
    riskFreeRate = value;
} // setRFR()


// Setter method for the volatility of the Black-Scholes model.
void blackScholesModel::setVolatility(const double& value) {
    volatility = value;
} // setVolatility()


// Setter method for the option type of the Black-Scholes model.
void blackScholesModel::setOptionType(const char& value) {
    optionType = value;
} // setOptionType()



// ----------------------------------------------------------------------------
//                            Getter Methods
// ----------------------------------------------------------------------------


// Getter method for the underlying price of the Black-Scholes model.
const double& blackScholesModel::getUnderlyingPrice() const {
    return underlyingPrice;
} // getUnderlyingPrice()



// Getter method for the strike price of the Black-Scholes model.
const double& blackScholesModel::getStrikePrice() const {
    return strikePrice;
} // getStrikePrice()


// Getter method for the time until expiration of the Black-Scholes model.
const double& blackScholesModel::getTTE() const {
    return timeToExpiration;
} // getTTE()



// Getter method for the risk-free rate of the Black-Scholes model.
const double& blackScholesModel::getRFR() const {
    return riskFreeRate;
} // getRFR()



// Getter method for the volatility of the Black-Scholes model.
const double& blackScholesModel::getVolatility() const {
    return volatility;
} // getVolatility()


// Getter method for the option type of the Black-Scholes model.
const char& blackScholesModel::getOptionType() const {
    return optionType;
} // getOptionType()




