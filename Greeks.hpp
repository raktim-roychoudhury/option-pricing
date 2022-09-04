//
//  Greeks.hpp
//  Ex 1
//
//  Created by Ronny on 01/07/21.
//

#ifndef Greeks_hpp
#define Greeks_hpp

#include "EuropeanOption.hpp"
#include <math.h>
#include <boost/math/distributions/normal.hpp>

class Greeks{

private:
public:
    Greeks();
    ~Greeks();
    
    //
    double Delta(const EuropeanOption& op) const; //calculate delta for an european option
    double Gamma(const EuropeanOption& op) const; //calculate gamma for an european option
    double NumericalDelta (const EuropeanOption& op,double h = 0.001) const; //calculate delta using numerical approximation with default step size 0.001
    double NumericalGamma(const EuropeanOption& op,double h = 0.001) const;//calculate gamma using numerical approximation with default step size 0.001

};

#endif /* Greeks_hpp */
