#ifndef __VANILLA_OPTION_CPP
#define __VANILLA_OPTION_CPP
#define _USE_MATH_DEFINES

#include<iostream>
#include <math.h>
#include <cmath>
#include "vanilla-option.hpp"

// Inicializa os dados membros

void VanillaOption::init() {

    K = 100.0;
    r = 0.1275; //5% interest rate
    T = 1.0; //Um ano até a maturidade
    S = 100.0; // Opção está ITM quando o preço spot for igual ao preço de strike
    sigma = 0.2; // Volatilidade é 20%
}

//Copia os dados dos membros
void VanillaOption::copy(const VanillaOption& rhs) {
    
    K = rhs.getK();
    r = rhs.getr();
    T = rhs.getT();
    S = rhs.getS();
    sigma = rhs.getsigma();
}

VanillaOption::VanillaOption(){init(); }

VanillaOption::VanillaOption(const double& _K, const double& _r,
                            const double& _T, const double& _S,
                            const double& _sigma) {
    
    K = _K;
    r = _r;
    T = _T;
    S = _S;
    sigma = _sigma;

}

//Copy constructor
VanillaOption::VanillaOption(const VanillaOption& rhs){
    copy(rhs);
}

//Assignment operator
VanillaOption& VanillaOption::operator=(const VanillaOption& rhs){

    if (this == &rhs) return *this;
    copy(rhs);
    return *this;

}

//Destructor
VanillaOption::~VanillaOption() {
    //Vázio, pois o compilador faz todo o trabalho de limpeza dos tipos simples
}

//Acesso público para o preço de strike, K

double VanillaOption::getK() const { return K; }
double VanillaOption::getr() const { return r; }
double VanillaOption::getT() const { return T; }
double VanillaOption::getS() const { return S; }
double VanillaOption::getsigma() const { return sigma; }


// Uma aproximação para a função de distribuição cumulativa
// para a distribuição normal

double N (const double x ){
    double k = 1.0 / ( 1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

    if (x >= 0.0) {
        
        return (1.0 - (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5*x*x) * k_sum);
    }

    else {

        return 1.0 - N(-x); //Recursão

    }
}

double VanillaOption::calc_call_price() const{
    double sigma_sqrt_T = sigma * sqrt(T);
    double d_1 = (log(S / K) + (r + sigma * sigma * 0.5) * T) / sigma_sqrt_T;
    double d_2 = d_1 - sigma_sqrt_T;
    return S * N(d_1) - K * exp(-r*T) * N(d_2);
}

double VanillaOption::calc_put_price() const{
   double sigma_sqrt_T = sigma * sqrt(T);
   double d_1 = (log(S / K) + (r + sigma * sigma * 0.5) * T) / sigma_sqrt_T;
   double d_2 = d_1 - sigma_sqrt_T;
   return K * exp(-r*T) * N(-d_2) - S * N(-d_1);
}

int main (int argc, char **argv) {
    VanillaOption option; 

    //calcular call e put
    double call = option.calc_call_price();
    double put = option.calc_call_price();

    //Parametros de Output
    std::cout<<"Strike, K: " << option.getK() << std::endl;
    std::cout<<"Risk-Free rate, r: " << option.getr() << std::endl;
    std::cout<<"Time to maturity, T:" <<option.getT() << std::endl;
    std::cout<<"Spot price, S: "<<option.getS() << std::endl;
    std::cout<<"Volatility of asset, sigma: "<<option.getsigma() <<std::endl;

    //Output preço das opções
    std::cout << "Call price: " << call << std::endl;
    std::cout << "Put price: " << put << std::endl;

    std::cin.get();

    return 0;
}

#endif