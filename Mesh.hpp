//
//  Mesh.hpp
//  Ex 1
//
//  Created by Ronny on 27/06/21.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#include "Greeks.hpp"
#include "EuropeanOption.hpp"

using namespace std;

//creates a vector of doubles starting from min to max with step size = mesh_size;
vector<double> CreateMesh(double min, double max, double mesh_size){
    vector<double> OptionMesh;
//    cout << "Creating option mesh" << endl;
    for (double i = min; i <= max ; i += mesh_size){
        OptionMesh.push_back(i);
    }
    return OptionMesh;
}

//function which outputs the price of an european option for each spot value in the range from min to max separated by mesh_size
vector<double> CalculateSpotMesh(EuropeanOption op, double min, double max, double mesh_size,string func = "Price"){
    vector<double> EuropeanOptionMesh;
    
    if (func == "Price"){
    for (double i = min; i <= max ; i += mesh_size){
        op.S = i;
        EuropeanOptionMesh.push_back(op.Price());
    }}
    else {
        Greeks EuroOption;
        for (double i = min; i <= max; i+= mesh_size){
            op.S = i;
            if (func == "Delta") EuropeanOptionMesh.push_back(EuroOption.Delta(op));
            else if(func == "Gamma") EuropeanOptionMesh.push_back(EuroOption.Gamma(op));
        }
    }
    return EuropeanOptionMesh;
}

//calculates option price for each spot price in vector SpotVec

vector<double> CalculateSpotMesh(EuropeanOption op, vector<double>& SpotVec,string func = "Price"){
    vector<double> EuropeanOptionMesh;
    if (func == "Price"){
        for (int i = 0; i < SpotVec.size(); i++){
            op.S = SpotVec[i];
            EuropeanOptionMesh.push_back(op.Price());
        }
    }
    else {
        Greeks EuroOption;
        for (int i = 0; i < SpotVec.size(); i++){
            op.S = SpotVec[i];
            if (func == "Delta") EuropeanOptionMesh.push_back(EuroOption.Delta(op));
            else if(func == "Gamma") EuropeanOptionMesh.push_back(EuroOption.Gamma(op));
        }
    }
    return EuropeanOptionMesh;
}


vector<double> CalculateSpotMesh(PerpAmericanOption op, double min, double max, int mesh_size){
    vector<double> OptionMesh;
    for (double i = min; i <= max ; i += mesh_size){
        op.S = i;
        OptionMesh.push_back(op.Price());
    }
    return OptionMesh;
}

vector<double> CalculateSpotMesh(PerpAmericanOption op, vector<double> SpotVec){
    vector<double> OptionMesh;
    for (int i = 0; i < SpotVec.size() ; i++){
        op.S = SpotVec[i];
        OptionMesh.push_back(op.Price());
    }
    return OptionMesh;
}

//function to print the optionmesh
void PrintMesh(vector<double> OptionMesh){
    for (int i = 0; i < OptionMesh.size() - 1 ; i++){
        cout << OptionMesh[i] << ", ";
    }
    cout << OptionMesh[OptionMesh.size()-1] << endl;
}



#endif /* Mesh_hpp */
