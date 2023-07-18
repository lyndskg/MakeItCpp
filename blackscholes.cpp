//
//  main.cpp
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

#include "blackscholes.h"
#include "inputReader.h"

using namespace std;


// ----------------------------------------------------------------------------
//                      Class Member Function Implementations
// ----------------------------------------------------------------------------

// Default constructor
blackScholesModel::blackScholesModel() : inputMode("") {}

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

// Processes the command line arguments.
void blackScholesModel::get_options(int argc, char* argv[]) {
    int optIndex = 0, option = 0;
    
    // Define an array of the structures describing each long option.
    struct option longOpts[] = {{"mode", required_argument, nullptr, 'm'},
                                {"help", no_argument, nullptr, 'h'},
                                {nullptr, no_argument, nullptr, '\0'}};
    
    // Loop over all of the options.
    while ((option = getopt_long(argc, argv, "m:h", longOpts, &optIndex))
           != -1) {
        switch (option) {
            case 'm':
                // Set the program mode to MODE.
                inputMode = optarg;
                
                // If an invalid mode is specified, print to standard error
                // and exit.
                if (inputMode != "USER" && inputMode != "FILE" && inputMode != "DB" && inputMode != "API") {
                    cerr << "Invalid mode\n";
                    exit(1);
                } // if
                
                
                // Call the corresponding function based on the input mode.
                if (inputMode == "USER") {
                    // TODO: WTF??
                    blackScholesModel model;
                    InputReader inputReader;
                    inputReader.readInputFromUser(model);
                    
                } else if (inputMode == "FILE") {
                    string filename = "input.txt"; // Example filename
                    blackScholesModel::readInputFromFile(filename);
                    
                } else if (inputMode == "DB") {
                    blackScholesModel::readInputFromDB(); // Implement this function for database input
                    
                } else if (inputMode == "API") {
                    blackScholesModel::readInputFromAPI(); // Implement this function for API input
                } // if-elif-elif-elif

                break;
                
                
            case 'h':
                // Print a helpful message and exit.
                printHelp(argv);
                exit(0);
                
            default:
                cerr << "Invalid command line option\n";
                exit(1);
        } // switch
    } // while
    
    // If no mode is specified, print to standard error and exit.
    if (inputMode.empty()) {
        cerr << "Error: no mode specified\n";
        exit(1);
    }
}

// Prints a helpful message about how to use the program for the user when requested.
// TODO: FINISH IMPLEMENTATION
void blackScholesModel::printHelp(char* argv[]) {
    // argv[0] is the name of the currently executing program.
    cout << "Usage: " << argv[0] << " [-m TODO1|TODO2]|-h" << endl;
    cout << "This program is to" << endl;
}

// Defines the option pricing function and calculates the option price using the Black-Scholes formula.
double blackScholesModel::calculateOptionPrice(double underlyingPrice, double strikePrice, double timeToExpiration,
                                               double riskFreeRate, double volatility, char optionType) {
        
    // Calculate the intermediate variables.
    double d1 = (log(underlyingPrice / strikePrice) + (riskFreeRate + pow(volatility, 2) / 2.0) * timeToExpiration) * (1.0 / volatility * sqrt(timeToExpiration));
    
    double d2 = d1 - volatility * sqrt(timeToExpiration);
    
//
//    double optionPrice = 0.0;
//
//    // Calculate the option price using the Black-Scholes formula.
//    double optionPrice = underlyingPrice * normalCDF(d1) - strikePrice * exp(-riskFreeRate * timeToExpiration) * normalCDF(d2);
//
    
    // TODO: decide if switch or ternary operator
    switch (optionType) {
        case 'c':
            return underlyingPrice * normalCDF(d1) - strikePrice * exp(-riskFreeRate * timeToExpiration) * normalCDF(d2);
            
        case 'p':
            return strikePrice * exp(-riskFreeRate * timeToExpiration) * normalCDF(-d2) - underlyingPrice * normalCDF(-d1);
            
        default:
            cerr << "Error: Option type does not exist!";
            return -1;
    }
//
//    return optionPrice;
}


// Approximate the CDF of a normal distribution. 
double blackScholesModel::normalCDF(double d) {
    // Abramowitz & Stegun's (1964) approximation.
                
    /* Refer to https://www.ijser.org/researchpaper/Approximations-to-Standard-Normal-Distribution-Function.pdf
       for potentially more efficient approximations wrt M.A.E. and corresponding z-score */

    double result = 0.0;
    
    const double a[] = {0.2316419, 0.31938153, -0.356563782, 1.781477937, -1.821255978, 1.330274429};
    
    double L, K = 0.0;
    
    L = abs(d);
    K = 1.0 / (1.0 + a[0] * L);
    
    result = 1.0 - 1.0 / sqrt(2 * std::numbers::pi) * exp(-L * L / 2.0) * (a[1] * K + a[2] * K * K + a[3] * pow(K, 3.0) + a[4] * pow(K, 4.0) + a[5] + pow(K, 5.0));
    
    return d < 0 ? 1.0 - result : result; // Should ternary operator be used here? Or if-else statement (below)?
    
    /* if (d < 0)
        {
        return 1.0 - result;
        }
        else
        {
            return result;
        } */
}

// Launches the algorithm.
void blackScholesModel::launchAlgo() {
        // TODO: IMPLEMENT
}



// Setter methods
void blackScholesModel::setUnderlyingPrice(const double& value) {
    underlyingPrice = value;
}


void blackScholesModel::setStrikePrice(const double& value) {
    strikePrice = value;
}

void blackScholesModel::setTTE(const double& value) {
    timeToExpiration = value;
}

void blackScholesModel::setRFR(const double& value) {
    riskFreeRate = value;
}

void blackScholesModel::setVolatility(const double& value) {
    volatility = value;
}

void blackScholesModel::setOptionType(const char& value) {
    optionType = value;
}



// Getter methods
const double& blackScholesModel::getUnderlyingPrice() const {
    return underlyingPrice;
}

const double& blackScholesModel::getStrikePrice() const {
    return strikePrice;
}

const double& blackScholesModel::getTTE() const {
    return timeToExpiration;
}


const double& blackScholesModel::getRFR() const {
    return riskFreeRate;
}


const double& blackScholesModel::getVolatility() const {
    return volatility;
}

const char& blackScholesModel::getOptionType() const {
    return optionType;
}




