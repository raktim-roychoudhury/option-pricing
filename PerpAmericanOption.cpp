//
//  PerpAmericanOption.cpp
//  Ex 1
//
//  Created by Ronny on 29/06/21.
//

#include "PerpAmericanOption.hpp"

PerpAmericanOption::PerpAmericanOption(){
    K = 100;
    S = 110;
    sig = 0.1;
    r = 0.1;
    b = 0.02;
    optype = "C";
}

PerpAmericanOption::PerpAmericanOption(const PerpAmericanOption& source){
    K = source.K;
    S = source.S;
    sig = source.sig;
    r = source.r;
    b = source.b;
    optype = source.optype;
}

PerpAmericanOption::PerpAmericanOption(string optiontype){
    PerpAmericanOption();
    optype = optiontype;
}

PerpAmericanOption::~PerpAmericanOption(){
}

double PerpAmericanOption::Price() const{
    if (optype == "C") return CallPrice();
    return PutPrice();
}

double PerpAmericanOption::CallPrice() const{
    double price,y1;
    y1 = 0.5 - (b/pow(sig,2)) + sqrt(pow(((b/pow(sig,2)) - 0.5),2) + ((2*r)/pow(sig,2)));
    price = (K/(y1-1))*pow((((y1-1)*S)/(y1*K)),y1);
    return price;
}

double PerpAmericanOption::PutPrice() const{
    double price,y2;
    y2 = 0.5 - (b/pow(sig,2)) - sqrt(pow(((b/pow(sig,2)) - 0.5),2) + ((2*r)/pow(sig,2)));
    price = (K/(1-y2))*pow((((y2-1)*S)/(y2*K)),y2);
    return price;
}

PerpAmericanOption& PerpAmericanOption::operator = (const PerpAmericanOption& source){
    if (this == &source) return *this;
    K = source.K;
    S = source.S;
    sig = source.sig;
    r = source.r;
    b = source.b;
    optype = source.optype;
    return *this;
}

PerpAmericanOption PerpAmericanOption::toggle(){
    PerpAmericanOption temp(*this);
    if (temp.optype == "C") temp.optype = "P";
    else temp.optype = "C";
    return temp;
}
