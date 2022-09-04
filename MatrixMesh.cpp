//
//  MatrixMesh.cpp
//  Ex 1
//
//  Created by Ronny on 28/06/21.
//

#include "MatrixMesh.hpp"

MatrixMesh::MatrixMesh(){
    S_vec.push_back(100);
    sig_vec.push_back(0.2);
    K_vec.push_back(110);
    r_vec.push_back(0.05);
    T_vec.push_back(1);
        
    cout << "Initialized Matrix Mesh Array with default values for option attribute vectors" << endl;
}

MatrixMesh::MatrixMesh(EuropeanOption& op){
    S_vec.push_back(op.S);
    K_vec.push_back(op.K);
    sig_vec.push_back(op.sig);
    r_vec.push_back(op.r);
    T_vec.push_back(op.T);
}

MatrixMesh::MatrixMesh(PerpAmericanOption& op){
    S_vec.push_back(op.S);
    K_vec.push_back(op.K);
    sig_vec.push_back(op.sig);
    r_vec.push_back(op.r);
}


MatrixMesh::~MatrixMesh(){
}

void MatrixMesh::DisplayVec(const vector<double>& vec) const{
    for (int i = 0; i < vec.size() - 1 ; i++){
        cout << vec[i] << ", ";
    }
    cout << vec[vec.size()-1] << endl;
}

template<>
void MatrixMesh::CreateMesh<EuropeanOption>(){
//    cout << "Creating Mesh"<< endl;
        for (int i = 0; i < S_vec.size(); i++){
            for (int j = 0; j < K_vec.size(); j++){
                for (int k = 0; k < sig_vec.size(); k++){
                    for (int l = 0; l < r_vec.size(); l++){
                        for (int m = 0; m < T_vec.size(); m++){
                            vector<double> combination;
                            combination.push_back(S_vec[i]);
                            combination.push_back(K_vec[j]);
                            combination.push_back(sig_vec[k]);
                            combination.push_back(r_vec[l]);
                            combination.push_back(T_vec[m]);
                            Mesh_Values.push_back(combination);
                        }
                    }
                }
            }
        }
}

template<>
void MatrixMesh::CreateMesh<PerpAmericanOption>(){
//    cout << "Creating Mesh"<< endl;
        for (int i = 0; i < S_vec.size(); i++){
            for (int j = 0; j < K_vec.size(); j++){
                for (int k = 0; k < sig_vec.size(); k++){
                    for (int l = 0; l < r_vec.size(); l++){
                            vector<double> combination;
                            combination.push_back(S_vec[i]);
                            combination.push_back(K_vec[j]);
                            combination.push_back(sig_vec[k]);
                            combination.push_back(r_vec[l]);
                            Mesh_Values.push_back(combination);
                        
                    }
                }
            }
        }
}

template<>
void MatrixMesh::CalculateMesh(EuropeanOption Opt,string func){
//    cout << "Calculating Mesh" << endl;
    CreateMesh<EuropeanOption>();
    vector<vector<double>>::const_iterator iter = Mesh_Values.begin();
    if (func == "Price"){
        for(; iter != Mesh_Values.end() ; ++iter){
            Opt.S = (*iter)[0];
            Opt.K = (*iter)[1];
            Opt.sig = (*iter)[2];
            Opt.r = (*iter)[3];
            Opt.T = (*iter)[4];
            Matrix_Map.insert(make_pair(*iter,Opt.Price()));
        }
    }
    else{
        Greeks EuroOption;
        for(; iter != Mesh_Values.end() ; ++iter){
            Opt.S = (*iter)[0];
            Opt.K = (*iter)[1];
            Opt.sig = (*iter)[2];
            Opt.r = (*iter)[3];
            Opt.T = (*iter)[4];
            if (func == "Delta") Matrix_Map.insert(make_pair(*iter,EuroOption.Delta(Opt)));
            else if (func == "Gamma") Matrix_Map.insert(make_pair(*iter,EuroOption.Gamma(Opt)));
    }
}
}

template<>
void MatrixMesh::CalculateMesh(PerpAmericanOption Opt,string func){
    CreateMesh<PerpAmericanOption>();
    vector<vector<double>>::const_iterator iter = Mesh_Values.begin();
    for(; iter != Mesh_Values.end(); ++iter){
        Opt.S = (*iter)[0];
        Opt.K = (*iter)[1];
        Opt.sig = (*iter)[2];
        Opt.r = (*iter)[3];
        Opt.b = 0; //Assuming underlying as a Stock
        Matrix_Map.insert(make_pair(*iter,Opt.Price()));
    }
}

void MatrixMesh::DisplayMatrix() const{
//    cout << "Printing Mesh" << endl;
    map<vector<double>,double>::const_iterator iter = Matrix_Map.begin();
    if ((iter->first).size() == 4) cout << "(Spot,Strike,Volatility,Interest Rate)" << endl << endl;
    else cout << "(Spot,Strike,Volatility,Interest Rate,Time to Expiry)" << endl << endl;
    for(; iter!= Matrix_Map.end(); ++iter){
        cout << "(";
        for (int i = 0; i < (iter->first).size()-1 ; i++){
            cout << (iter->first)[i] << ",";
    }
    cout << (iter->first)[(iter->first).size()-1] << ") : " << (iter->second) << endl;
}
}


