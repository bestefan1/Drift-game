//
// Created by Stefan King on 10/26/2025.
//

#ifndef MASINA_H
#define MASINA_H
#include "Pneu.h"
#include <iostream>
#include <vector>

class Masina {
    public:
    enum class TipMasina{Street,Stock,Drift};
    private:
    TipMasina tip;
    float viteza;
    std::vector<Pneu> pneuri;
    public:
    Masina(TipMasina tip_parametru,float viteza_parametru,const std::vector<Pneu>& pneuri_parametru);

    void deplasarep(float distanta);
    void afisare() const;
    bool verificarepneu() const;
    void acceleratie(float coeficient);
    void franare(float coeficient);


};



#endif //MASINA_H
