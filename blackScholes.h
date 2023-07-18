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
    // Default constructor.
    blackScholesModel();
  
    // Custom constructor.
    blackScholesModel(double underlyingPrice, double strikePrice, double timeToExpiration,
                      double riskFreeRate, double volatility, char optionType);
    
    // Processes the command line arguments.
    void get_options(int argc, char* argv[]);
    
    // Prints a helpful message about how to use the program for the user when requested.
    void printHelp(char* argv[]);
    
    void readInputFromFile(const string& filename);
    
    void readInputFromUser();
    
    void readInputFromDB();
    
    void readInputFromAPI();
    
    // Launches the algorithm.
    void launchAlgo();
    
    // Setter methods
    void setUnderlyingPrice(const double& value);
    
    void setStrikePrice(const double& value);
    
    void setTTE(const double& value);
    
    void setRFR(const double& value);
    
    void setVolatility(const double& value);
    
    void setOptionType(const char& value);
    
    // Getter methods
    const double& getUnderlyingPrice() const;
    
    const double& getStrikePrice() const;
    
    const double& getTTE() const;
    
    const double& getRFR() const;

    const double& getVolatility() const;
  
    const char& getOptionType() const;
    
 
    // Defines the option pricing function and calculates the option price using the Black-Scholes formula.
    double calculateOptionPrice(double underlyingPrice, double strikePrice, double timeToExpiration, double riskFreeRate,
                                double volatility, char optionType);

    // Approximate the CDF of a normal distribution. 
    double normalCDF(double d);
    
    
private:
    double underlyingPrice;
    double strikePrice;
    double timeToExpiration;
    double riskFreeRate;
    double volatility;
    
    char optionType;
    
    string inputMode;
    
//    enum OptionContractType {
//        Call = 1,
//        Put = 2
//    };
    // Declare other member variables.
};

#endif /* blackscholes_h */
