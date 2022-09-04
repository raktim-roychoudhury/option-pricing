//
//  PerpAmericanOption.hpp
//  Ex 1
//
//  Created by Ronny on 29/06/21.
//

#ifndef PerpAmericanOption_hpp
#define PerpAmericanOption_hpp
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

class PerpAmericanOption{
    
private:
    double CallPrice() const;
    double PutPrice() const;
    
public:
    double K; //strike
    double S; //spot
    double sig; //volatility
    double r; //risk free rate
    double b; //cost of carry
    string optype; //Call or Put
    
    PerpAmericanOption();
    virtual ~PerpAmericanOption();
    PerpAmericanOption(const PerpAmericanOption& source);
    PerpAmericanOption(string optiontype);
    
    PerpAmericanOption& operator = (const PerpAmericanOption& source);
    PerpAmericanOption toggle(); //toggle between call and put
    
    double Price() const; //option price
};



#endif /* PerpAmericanOption_hpp */
