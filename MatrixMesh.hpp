//
//  MatrixMesh.hpp
//  Ex 1
//
//  Created by Ronny on 28/06/21.
//

#ifndef MatrixMesh_hpp
#define MatrixMesh_hpp

#include <vector>
#include <iostream>
#include <map>
#include "EuropeanOption.hpp"
#include "PerpAmericanOption.hpp"
#include "Greeks.hpp"
using namespace std;


class MatrixMesh{
private:
    template <typename T>
    void CreateMesh();
    
    vector<vector<double>> Mesh_Values;
public:
    vector <double> S_vec; //vector for Spot values
    vector<double> sig_vec; //vector for sigma values
    vector<double> K_vec; //vector for strike values
    vector <double> T_vec; //vector for time to expiries
    vector <double> r_vec; //vector for risk free rate
    map<vector<double>,double> Matrix_Map; //output map

    
public:
    MatrixMesh();
    MatrixMesh(EuropeanOption& op);
    MatrixMesh(PerpAmericanOption& op);
    virtual ~MatrixMesh();
    
    template <typename T>
    void CalculateMesh(T Opt, string func = "Price"); //calculates option price/delta/gamma as a function of paramters value matrix
//    void CalculateMesh(PerpAmericanOption Opt);
    void DisplayMatrix() const;
    void DisplayVec(const vector<double>& vec) const;

};


#endif /* MatrixMesh_hpp */
