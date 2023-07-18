//
//  inputReader.h
//  black-scholes
//
//  Created by lyndskg on 7/18/23.
//

#ifndef inputReader_h
#define inputReader_h

#include <string>

#include <curl/curl.h>
#include "blackScholes.h"

using namespace std;


class blackScholesModel; // Forward declaration of blackScholesModel class

// ----------------------------------------------------------------------------
//                  "InputReader" Class Declarations
// ----------------------------------------------------------------------------
class InputReader {
public:
    // Default constructor.
    InputReader();
    
    void readInputFromUser(blackScholesModel& model);
    void readInputFromFile(blackScholesModel& model, const string& filename);
    void readInputFromDB(blackScholesModel& model);
    void readInputFromAPI(blackScholesModel& model);
    
private:
    double getValidInput(const string& prompt);

    char getValidOptionType(const string& prompt);
    
    void validateAndSetInputValues(blackScholesModel& model, double underlyingPrice, double strikePrice,double timeToExpiration, double riskFreeRate, double volatility, char optionType);
}; // class InputReader


#endif /* inputReader_h */
