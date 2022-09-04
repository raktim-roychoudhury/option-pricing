//
//  main.cpp
//  Ex 1
//
//  Created by Ronny on 27/06/21.
//

#include <iostream>
#include "EuropeanOption.hpp"
#include "PerpAmericanOption.hpp"
#include "MatrixMesh.hpp"
#include "Mesh.hpp"
#include "Greeks.hpp"
#include <vector>
using namespace std;

int main(){
    EuropeanOption call_b1,call_b2,call_b3,call_b4;
    //Batch 1
    call_b1.T = 0.25;
    call_b1.K = 65;
    call_b1.sig = 0.30;
    call_b1.r = 0.08;
    call_b1.S = 60;
    call_b1.optype = "C";

    //Batch 2
    call_b2.T = 1;
    call_b2.K = 100;
    call_b2.sig = 0.2;
    call_b2.r = 0.0;
    call_b2.S = 100;
    call_b2.optype = "C";

    //Batch 3
    call_b3.T = 1;
    call_b3.K = 10;
    call_b3.sig = 0.5;
    call_b3.r = 0.12;
    call_b3.S = 5;
    call_b3.optype = "C";

    //Batch 4
    call_b4.T = 30;
    call_b4.K = 100;
    call_b4.sig = 0.3;
    call_b4.r = 0.08;
    call_b4.S = 100;
    call_b4.optype = "C";
    
//    calculating call and put prices for batches 1-4

    cout << "Batch 1 : Call Price = " << call_b1.Price() << ", Put Price = " << call_b1.toggle().Price() << endl;
    cout << "Batch 2 : Call Price = " << call_b2.Price() << ", Put Price = " << call_b2.toggle().Price() << endl;
    cout << "Batch 3 : Call Price = " << call_b3.Price() << ", Put Price = " << call_b3.toggle().Price() << endl;
    cout << "Batch 4 : Call Price = " << call_b4.Price() << ", Put Price = " << call_b4.toggle().Price() << endl <<endl;
//
//  calculating call and put price for batches 1-4, but using put call parity
    cout << "Batch 1 : Call Price = " << call_b1.Price() << ", Put Price = " << call_b1.ParityPrice() << endl;
    cout << "Batch 2 : Call Price = " << call_b2.Price() << ", Put Price = " << call_b2.ParityPrice() << endl;
    cout << "Batch 3 : Call Price = " << call_b3.toggle().ParityPrice() << ", Put Price = " << call_b3.toggle().Price() << endl;
    cout << "Batch 4 : Call Price = " << call_b4.toggle().ParityPrice() << ", Put Price = " << call_b4.toggle().Price() << endl << endl;

    EuropeanOption put_b1(call_b1.toggle());
// checking if put call parity is satisfied
    cout << "Checking is put call parity is satisfied : " << CheckParity(call_b1,put_b1) << endl;

//Creating a range of spot prices and calculating the option price as a function of spot price;
    vector<double> SpotPrice = CreateMesh(50,150,10); //creating a vector from 50 to 150 with step size 10
    vector<double> PriceVec1 = CalculateSpotMesh(call_b1,SpotPrice); //outputs a vector of option pricees in SpoPrice
    vector<double> PriceVec2 = CalculateSpotMesh(call_b1,50,150,10); //overloaded version
    PrintMesh(PriceVec1);
    PrintMesh(PriceVec2);
    
//Matrix Pricer
    {
    
    MatrixMesh EuropeanMesh(call_b1); //initilazing a MatrixMesh object

    EuropeanMesh.S_vec = CreateMesh(50,100,10); //assigning SpotVec to S_vec
    EuropeanMesh.sig_vec = CreateMesh(0.05,0.2,0.05);

    EuropeanMesh.CalculateMesh<EuropeanOption>(call_b1); //calculates a matrix of option prices as a function of S_vec and sig_vec combinations
    EuropeanMesh.DisplayMatrix(); //Prints Output matrix prices as a map
    }
    
// Greeks
    Greeks EuroOption; //defining an instance of class Greeks
    EuropeanOption Call_Option;
    Call_Option.S = 105;
    Call_Option.K = 100;
    Call_Option.T = 0.5;
    Call_Option.sig = 0.36;
    Call_Option.r = 0.1;
    Call_Option.underlying = "Futures";
    EuropeanOption Put_Option(Call_Option.toggle());
    cout << "Call Delta = " << EuroOption.Delta(Call_Option) << " , " << "Put Delta = "<<EuroOption.Delta(Put_Option) << endl; //delta of call option
    cout << "Call Gamma = " << EuroOption.Gamma(Call_Option) << " , " << "Put Gamma = " <<EuroOption.Gamma(Put_Option) << endl; //Gamma of call option


    //Calculates and prints delta values for call option as a function of spot prices
    vector<double> Call_Delta = CalculateSpotMesh(call_b1,50,100,5,"Delta");
    vector<double> Put_Delta = CalculateSpotMesh(call_b1.toggle(),50,100,5,"Delta");
    PrintMesh(Call_Delta);
    PrintMesh(Put_Delta);
    
    //Similar matrix pricer but output option delta as a function of parameter value vectors
// Greeks (Matrix Pricer)
    MatrixMesh EuropeanMesh(call_b1);
    EuropeanMesh.S_vec = CreateMesh(50,100,10);
    EuropeanMesh.sig_vec = CreateMesh(0.05,0.2,0.05);

//    EuropeanMesh.CalculateMesh<EuropeanOption>(call_b1,"Delta");
    EuropeanMesh.CalculateMesh<EuropeanOption>(call_b1.toggle(),"Delta");
    EuropeanMesh.DisplayMatrix();
    
//    Numerical Greeks
  
//Greek calculations but using numerical methods instead of explicit formulae and checking accuracy
    
    cout << EuroOption.NumericalDelta(Call_Option) << " , " << EuroOption.NumericalDelta(Put_Option) << endl;
    cout << EuroOption.NumericalGamma(Call_Option) << " , " << EuroOption.NumericalGamma(Put_Option) << endl;

    cout << "Delta Accuracy = " << (EuroOption.NumericalDelta(Call_Option,1)/EuroOption.Delta(Call_Option))*100 << "% "<<endl; //h = 1;
    cout << "Gamma Accuracy = " << (EuroOption.NumericalGamma(Call_Option,1)/EuroOption.Gamma(Call_Option))*100 << "% "<<endl; //h = 0.1;
    cout << "Delta Accuracy = " << (EuroOption.NumericalDelta(Call_Option,0.1)/EuroOption.Delta(Call_Option))*100 << "% "<<endl; //h = 0.1;
    cout << "Gamma Accuracy = " << (EuroOption.NumericalGamma(Call_Option,0.1)/EuroOption.Gamma(Call_Option))*100 << "% "<<endl; //h = 0.1;

//    Perp American Option
    
    PerpAmericanOption PerpACall;
    PerpACall.K = 100;
    PerpACall.sig = 0.1;
    PerpACall.r = 0.1;
    PerpACall.b = 0.02;
    PerpACall.S = 110;
    
    
    cout << "Perpetual American Option : Call Price = " << PerpACall.Price() << " Put Price = " << PerpACall.toggle().Price() << endl;

    
//    calcaulting perp american option prices as a function of spot prices AmerSpotVec
    vector<double> AmerSpotVec = CreateMesh(50,150,10);
    vector<double> AmerSpotMesh = CalculateSpotMesh(PerpACall,AmerSpotVec);
//    vector<double> AmerSpotMesh1 = CalculateSpotMesh(PerpACall,50,150,10);
    PrintMesh(AmerSpotMesh);
//    PrintMesh(AmerSpotMesh1);

//    Matrix pricer for perp amer call option as a function of S_vec and K_vec parameter combinations.
    MatrixMesh AmerMatrix(PerpACall);
    AmerMatrix.S_vec = CreateMesh(100,130,10);
    AmerMatrix.K_vec = CreateMesh(110,150,10);
    AmerMatrix.CalculateMesh<PerpAmericanOption>(PerpACall);
    AmerMatrix.DisplayMatrix();
    return 0;
}
