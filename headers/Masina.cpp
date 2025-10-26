//
// Created by Stefan King on 10/26/2025.
//

#include "Masina.h"
#include <iostream>

Masina::Masina(TipMasina tip_parametru, float viteza_parametru, const std::vector<Pneu> &pneuri_parametru):
tip(tip_parametru), viteza(viteza_parametru), pneuri(pneuri_parametru)
{}

void Masina::deplasarep(float distanta) {
    for (auto& p : pneuri) {
        p.degradare(distanta);
    }
}
void Masina::afisare()const {
    std::cout<<"Tip masina: ";
    switch (tip) {
        case TipMasina::Street: std::cout<<"Street: ";break;
        case TipMasina::Stock: std::cout<<"Stock: ";break;
        case TipMasina::Drift: std::cout<<"Drift: ";break;
    }
    std::cout<<"Viteza: "<<viteza<<std::endl;

    std::cout<<"Pneuri:\n ";
    for (const auto& p : pneuri) {
        p.afisare();
    }
}
bool Masina::verificarepneu() const {
    for (const auto& p : pneuri) {
        if (p.uzat()) return true;
    }
    return false;
}
void Masina::acceleratie(float coeficient) {
    viteza+=coeficient;
}
void Masina::franare(float coeficient) {
    viteza-=coeficient;
    if (viteza<0) viteza=0;
}


