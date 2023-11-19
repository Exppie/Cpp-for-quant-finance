#ifndef __VANILLA_OPTION_H
#define __VANILLA_OPTION_H

#define _USE_MATH_DEFINES
#include<cmath>

class VanillaOption {

private:

    void init();
    void copy(const VanillaOption& rhs); // pass-by-reference-to-const = não copiar e não modificar o parametro rhs 

    double K; //Preço de Strike
    double r; //Taxa de juros livre de risco
    double T; //Tempo de maturidade
    double S; //Preço do ativo subjacente
    double sigma; //Volatilidade do ativo subjacente

public:

    VanillaOption(); // Default constructor - não possui parametros
    VanillaOption(const double& _K, const double& _r,
                const double& _T, const double& _S,
                const double& _sigma); //Parameter constructor

    VanillaOption(const VanillaOption& rhs); //Copiar constructor
    VanillaOption& operator = (const VanillaOption& rhs); //Assignment Operator
    virtual ~VanillaOption(); //Destructor é virtual

    //Selector ("getter") metodos para os parametros da opção
    double getK() const; // const no final representa que os metódos são incapazes de modificar dados
    double getr() const;
    double getT() const;
    double getS() const;
    double getsigma() const;

    // Metodos de calcular preços das opções
    double calc_call_price() const;
    double calc_put_price() const;
};

#endif