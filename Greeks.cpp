//
//  Greeks.cpp
//  Ex 1
//
//  Created by Ronny on 01/07/21.
//

#include "Greeks.hpp"


Greeks::Greeks(){
    
}

Greeks::~Greeks(){
    
}

double Greeks::Delta(const EuropeanOption& op) const{
    double delta,d1,N1;
    d1 = 0;
    delta = 0;
    using namespace boost::math;
    normal_distribution<> myNorm(0,1);
    if (op.underlying == "Stock") {
    d1 = (log(op.S/op.K) + ((op.r + 0.5*pow(op.sig,2))*op.T)) / (op.sig*sqrt(op.T));
    }
    else if(op.underlying =="Futures"){
    d1 = (log(op.S/op.K) + ((0.5*pow(op.sig,2))*op.T)) / (op.sig*sqrt(op.T));
    }
    N1 = cdf(myNorm,d1);
    if (op.optype == "C"){
        if (op.underlying == "Stock") delta = N1;
        else if(op.underlying == "Futures") delta = exp(-op.r*op.T)*N1;
    }
    else
        if (op.underlying == "Stock") delta = (N1-1);
        else if (op.underlying =="Futures") delta = exp(-op.r*op.T)*(N1-1);
        
    return delta;
}

double Greeks::Gamma(const EuropeanOption& op) const{
    double gamma,d1,n1;
    d1 = 0;
    gamma = 0;
    using namespace boost::math;
    normal_distribution<> myNorm(0,1);
    
    if (op.underlying == "Stock") d1 = (log(op.S/op.K) + ((op.r + 0.5*pow(op.sig,2))*op.T)) / (op.sig*sqrt(op.T));
    else if (op.underlying == "Futures") d1 = (log(op.S/op.K) + ((0.5*pow(op.sig,2))*op.T)) / (op.sig*sqrt(op.T));
    n1 = pdf(myNorm,d1);
    if (op.underlying == "Stock") gamma = (n1)/(op.S*op.sig*sqrt(op.T));
    else if (op.underlying =="Futures") gamma = (exp(-op.r*op.T)*n1)/(op.S*op.sig*sqrt(op.T));
    return gamma;
}

double Greeks::NumericalDelta(const EuropeanOption& op,double h) const{
    EuropeanOption op1(op), op2(op);
    op1.S += h;
    op2.S -= h;
    return 0.5*((op1.Price() - op2.Price())/h);
}

double Greeks::NumericalGamma(const EuropeanOption& op,double h) const{
    EuropeanOption op1(op), op2(op);
    op1.S += h;
    op2.S -= h;
    return (op1.Price() - (2*(op.Price())) + op2.Price())/pow(h,2);
}
