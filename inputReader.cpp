//
//  inputReader.cpp
//  black-scholes
//
//  Created by lyndskg on 7/18/23.
//
#include <iostream>
#include <fstream>
#include <stdexcept> // For exception handling
#include <limits> // For numeric_limits
#include <curl/curl.h> // Example library for making HTTP requests
// Include necessary database libraries

#include "blackscholes.h"
#include "inputReader.h"

using namespace std;


// ----------------------------------------------------------------------------
//                             Helper Functions
// ----------------------------------------------------------------------------

// Validates and retrieves a valid numerical input from the user.
//
// @param prompt: The prompt message to display for the user
// @return: The valid numerical input value.
//
// Time complexity: O(1)
// Space complexity: O(1)
double InputReader::getValidInput(const string& prompt) {
    double value;
    
    // Continue looping until a valid input is provided
    while (true) { 
        cout << prompt; // Prompt the user to enter input
        
        // Read input from the user and check if it's a valid number and greater than 0
        if (cin >> value && value > 0.0) {
            break; // Valid input, exit the loop
        }
        
        cin.clear(); // Clear the error state of cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input from the input stream
        
        cout << "Invalid input. Please enter a valid value: ";
    }
    
    return value;
} // getValidInput()


// Prompts the user for an option type input and validates its correctness.
//
// @param prompt: The prompt message to display for the user
// @return: The validated option type represented as a char.
//
// Time complexity: O(1)
// Space complexity: O(1)
char InputReader::getValidOptionType(const string& prompt) {
    char optionType;
    
    // Continue looping until a valid input is provided
    while (true) {
        cout << prompt; // Prompt the user to enter the option type
        
        // Read the user input and validate its correctness
        if (cin >> optionType && (optionType == 'C' || optionType == 'P')) {
            break; // Break the loop if the input is valid
        }
        
        cin.clear(); // Clear the error state of the input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        
        cout << "Invalid input. Please enter a valid Option Type (C/P): ";
    }
    
    return optionType; // Return the validated option type
    
} // getValidOptionType()


// Validates and sets the input values for the blackScholesModel.
//
// Time complexity: O(1)
// Space complexity: O(1)
void InputReader::validateAndSetInputValues(blackScholesModel& model, double underlyingPrice, double strikePrice, double timeToExpiration, double riskFreeRate, double volatility, char optionType) {

    // Validate the retrieved input values
    
    // Check if the underlying price is positive
    if (underlyingPrice <= 0.0) {
        throw runtime_error("Invalid underlying price: must be greater than 0.");
    }

    // Check if strike price is positive
    if (strikePrice <= 0.0) {
        throw runtime_error("Invalid strike price: must be greater than 0.");
    }

    // Check if time to expiration is positive
    if (timeToExpiration <= 0.0) {
        throw runtime_error("Invalid time to expiration: must be greater than 0.");
    }

    // Check if risk-free rate is non-negative
    if (riskFreeRate < 0.0) {
        throw runtime_error("Invalid risk-free rate: must be non-negative.");
    }

    // Check if volatility is non-negative
    if (volatility < 0.0) {
        throw runtime_error("Invalid volatility: must be non-negative.");
    }

    // Check if option type is valid ('C' for call or 'P' for put)
    if (optionType != 'C' && optionType != 'P') {
        throw runtime_error("Invalid option type: must be 'C' or 'P'.");
    }
    
    // Additional consistency validations
    if (strikePrice > underlyingPrice) {
        throw runtime_error("Strike price cannot be greater than underlying price.");
    }
    
    // Set the validated input values
    model.setUnderlyingPrice(underlyingPrice);
    model.setStrikePrice(strikePrice);
    model.setTTE(timeToExpiration);
    model.setRFR(riskFreeRate);
    model.setVolatility(volatility);
    model.setOptionType(optionType);
    
} // validateAndSetInputValues()



// Serves as a callback for receiving the API response during an HTTP request.
// It is typically used with a library like 'libcurl' to handle the response data.
//
// Time complexity: O(1)
// Space complexity: O(1)
size_t responseCallback(void* contents, size_t size, size_t nmemb, string* response) {
    // Calculate the total size of the response data
    size_t totalSize = size * nmemb;
    
    // Append the received data to the response string
    response->append(static_cast<char*>(contents), totalSize);
    
    return totalSize;
    
} // responseCallback()



// ----------------------------------------------------------------------------
//                     Class Member Function Implementations
// ----------------------------------------------------------------------------

// Reads input values from the user interactively.
//
// Time complexity: O(1) per input prompt
//          i.e. time complexity depends on the number of input prompts and the time it takes for the user the              provide valid input
// Space complexity: O(1)
void InputReader::readInputFromUser(blackScholesModel& model) {
    try {
        // Prompt user via the CLI
        cout << "Please enter the input values:" << endl;

        // Get all relevant input values from user
        model.setUnderlyingPrice(getValidInput("Underlying Price: "));
        model.setStrikePrice(getValidInput("Strike Price: "));
        model.setTTE(getValidInput("Time to Expiration: "));
        model.setRFR(getValidInput("Risk-Free Rate: "));
        model.setVolatility(getValidInput("Volatility: "));
        model.setOptionType(getValidOptionType("Option Type (C/P): "));

        cout << "Input values entered successfully." << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    } // try-catch
    
} // readInputFromUser()




// Reads input parameters from a file (e.g. JSON or CSV).
//
// Time complexity: O(1) per input read from the file
// Space complexity: O(1)
void InputReader::readInputFromFile(blackScholesModel& model, const string& filename) {
    
    // Open the input file
    ifstream inputFile(filename);
    
    if (inputFile.is_open()) {
        
        // Declare variables to store the input values
        double underlyingPrice;
        double strikePrice;
        double timeToExpiration;
        double riskFreeRate;
        double volatility;
        char optionType;
        
        // Read input data from the file and populate the class members.
        // You can use a JSON or CSV parsing library to simplify this process.
        
        
        // Example: Reading input from a CSV file
       //        string line;
       //        if (getline(file, line)) {
       //            // Parse the line to extract input parameters
       //            // and populate the class members accordingly.
       //        }
        
        
        // Read the input values from the file
        if (inputFile >> underlyingPrice >> strikePrice >> timeToExpiration >> riskFreeRate >> volatility >> optionType) {
            
            // Check if the read input values are valid
            
            // Check if the underlying price is positive
            if (underlyingPrice <= 0.0) {
                cerr << "Invalid underlying price: must be greater than 0." << endl;
            } // if
            
            // Check if the strike price is positive
            if (strikePrice <= 0.0) {
                cerr << "Invalid strike price: must be greater than 0." << endl;
            } // if
            
            // Check if the time to expiration is positive
            if (timeToExpiration <= 0.0) {
                cerr << "Invalid time to expiration: must be greater than 0." << endl;
            } // if
            
            // Check if the risk-free rate is non-negative
            if (riskFreeRate < 0.0) {
                cerr << "Invalid risk-free rate: must be non-negative." << endl;
            } // if
            
            // Check if the volatility is non-negative
            if (volatility < 0.0) {
                cerr << "Invalid volatility: must be non-negative." << endl;
            } // if
            
            // Check if the option type is valid ('C' for call or 'P' for put)
            if (optionType != 'C' && optionType != 'P') {
                cerr << "Invalid option type: must be 'C' or 'P'." << endl;
            } // if
            
            // If all input values are valid, validate and set the retrieved input values.
            if (underlyingPrice > 0.0 && strikePrice > 0.0 && timeToExpiration > 0.0 && riskFreeRate >= 0.0 &&
                volatility >= 0.0 && (optionType == 'C' || optionType == 'P')) {
                
                validateAndSetInputValues(model, underlyingPrice, strikePrice, timeToExpiration, riskFreeRate, volatility, optionType);
                
                cout << "Input values retrieved from the file." << endl;
            } // if

        } else {
            cerr << "Error reading input values from the file." << endl;
        } // if-else
         
        inputFile.close();
        
    } else {
        cerr << "Failed to open input file: " << filename << endl;
    } // if-else
    
} // readInputFromFile()


     

// Reads input values from a database.
//      It connects to the database, retrieves the input data, validates the retrieved values, and sets
//      them in the blackScholesModel object.
//
// Time complexity: O(1) [per input retrieval from the database]
// Space complexity: O(1)
//
// TODO: IMPLEMENT
void InputReader::readInputFromDB(blackScholesModel& model) {
    
    try {
        // Connect to the database and retrieve the input data
        
        // Example code:
        cout << "Connecting to the database..." << endl;
        
        // Perform database query to retrieve the input values
        double retrievedUnderlyingPrice = 0.0;
        double retrievedStrikePrice = 0.0;
        double retrievedTimeToExpiration = 0.0;
        double retrievedRiskFreeRate = 0.0;
        double retrievedVolatility = 0.0;
        char retrievedOptionType = 'C';
        
        // Handle any exceptions that may occur during database operations
        
        // Example code:
        // throw std::runtime_error("Failed to connect to the database.");
        
        
        // Validate and set the retrieved input values
        validateAndSetInputValues(model, retrievedUnderlyingPrice, retrievedStrikePrice, retrievedTimeToExpiration, retrievedRiskFreeRate, retrievedVolatility, retrievedOptionType);
        
        cout << "Input values retrieved from the database." << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    } // try-catch
    
} // readInputFromDB()




// Reads input values from an API by making an HTTP request.
//      It initializes libcurl, sets up the HTTP request w/ the API endpoint URL, and performs the request.
//      The received response is stored in the 'response' string and then parsed to extract the input values.
//      Finally, the retrieved input values are validated and set in the blackScholesModel object.
//
// Time complexity: O(1) [per input retrieval from the API]
// Space complexity: O(1)
void InputReader::readInputFromAPI(blackScholesModel& model) {
    cout << "Making API request..." << endl;
    
    // Initialize libcurl
    CURL* curl = curl_easy_init();
    
    if (curl) {
        string url = "https://api.example.com/data"; // Example API endpoint URL
        
        // Set up the HTTP request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // Specify the URL of the API endpoint to which the request will be sent
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseCallback); // Handle the received data and append it to the 'response' string
        
        string response; // Store the API response
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); // Specify the address of the 'response' string as the data storage location for the received response
        
        // Perform the HTTP request
        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            // The API request was successful, and the response is stored in the 'response' string
            
            // Example: Parse the API response and extract the input values
            double retrievedUnderlyingPrice = 100.0;
            double retrievedStrikePrice = 110.0;
            double retrievedTimeToExpiration = 30.0;
            double retrievedRiskFreeRate = 0.05;
            double retrievedVolatility = 0.2;
            char retrievedOptionType = 'C';
            
            // Validate and set the retrieved input values
            validateAndSetInputValues(model, retrievedUnderlyingPrice, retrievedStrikePrice, retrievedTimeToExpiration, retrievedRiskFreeRate,
                                         retrievedVolatility, retrievedOptionType);
            
            cout << "Input values retrieved from the API." << endl;
        } else {
            // An error occurred during the API request
            cerr << "Failed to retrieve input values from the API. Error: " << curl_easy_strerror(res) << endl;
        } // if-else
        
        // Clean up libcurl resources
        curl_easy_cleanup(curl);
        
    } else {
        // Failed to initialize libcurl
        cerr << "Failed to initialize libcurl" << endl;
    } // if-else
     
    
} // readInputFromAPI()

