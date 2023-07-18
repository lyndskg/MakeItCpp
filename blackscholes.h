//
//  blackscholes.h
//  black-scholes
//
//  Created by lyndskg on 7/12/23.
//

#ifndef blackscholes_h
#define blackscholes_h

#include <stdio.h>
#include <algorithm>

using namespace std;

class blackScholesModel {
public:
    string inputMode; // Program mode (USER, FILE, DB, API)
    
    // Default constructor.
    blackScholesModel();
  
    // Custom constructor.
    blackScholesModel(double underlyingPrice, double strikePrice, double timeToExpiration,
                      double riskFreeRate, double volatility, char optionType);
    
    
    
    // Processes the command line arguments.
    //     Uses getopt_long to parse the options and their arguments.
    //      Based on the specified mode, it calls the corresponding functions to read input values from different sources (e.g. user
    //      input, a file, a database, or an API).
    //
    // Time complexity: O(n), where n = # of command line options
    // Space complexity: O(1)
    void get_options(int argc, char* argv[]);
    
    
    // Prints a helpful message about how to use the program for the user when requested.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void printHelp(char* argv[]);
    
    
    
    // Defines the option pricing function and calculates the option price using the Black-Scholes formula.
    //      The function takes in the underlying price, strike price, time to expiration, risk-free rate,
    //      volatility, and option type as input parameters and returns the calculated option price.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    double calculateOptionPrice(double underlyingPrice, double strikePrice, double timeToExpiration, double riskFreeRate,
                                double volatility, char optionType);

    
    
    // Approximates the cumulative distribution function (CDF) of a normal distribution.
    //      The function calculates an approximation of the CDF of a standard normal distribution given a value 'd' as input.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    double normalCDF(double d);
    
    // Launches the algorithm.
    void launchAlgo();
    
  
    // ----------------------------------------------------------------------------
    //                            Setter Methods
    // ----------------------------------------------------------------------------

    // Setter method for the underlying price of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void setUnderlyingPrice(const double& value);
    
    
    // Setter method for the strike price of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void setStrikePrice(const double& value);
    
    
    // Setter method for the time until expiration of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void setTTE(const double& value);
    
    
    // Setter method for the risk-free rate of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void setRFR(const double& value);
    
    
    // Setter method for the volatility of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void setVolatility(const double& value);
    
    
    // Setter method for the option type of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    void setOptionType(const char& value);
    
    
    
    
    // ----------------------------------------------------------------------------
    //                            Getter Methods
    // ----------------------------------------------------------------------------

    
    // Getter method for the underlying price of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    const double& getUnderlyingPrice() const;
    
    
    // Getter method for the strike price of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    const double& getStrikePrice() const;
    
    
    // Getter method for the time until expiration of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    const double& getTTE() const;
    
    
    // Getter method for the risk-free rate of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    const double& getRFR() const;

    
    // Getter method for the volatility of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    const double& getVolatility() const;
  
    
    // Getter method for the option type of the Black-Scholes model.
    //
    // Time complexity: O(1)
    // Space complexity: O(1)
    const char& getOptionType() const;

    
private:
    double underlyingPrice;
    double strikePrice;
    double timeToExpiration;
    double riskFreeRate;
    double volatility;
    
    char optionType;
    
    
//    enum OptionContractType {
//        Call = 1,
//        Put = 2
//    };
    
    // TODO: Declare other member variables.
    
}; // blackScholesModel

#endif /* blackscholes_h */
