//
// Created by Stefan King on 10/26/2025.
//
#include <iostream>
#include "Pneu.h"
Pneu::Pneu( Tip tip_parametru, float uzura_parametru)
:tip(tip_parametru),uzura(uzura_parametru){}

Pneu::Pneu(const Pneu &alte)
    :tip(alte.tip),uzura(alte.uzura){}

Pneu &Pneu::operator=(const Pneu &alte) {
    if (this != &alte){
        tip = alte.tip;
        uzura = alte.uzura;
    }
    return *this;
}
Pneu::~Pneu(){}

void Pneu::degradare(float distanta) {
    float coef=1.0f;
    switch (tip) {
        case Tip::Slick: coef=2.0f; break;
        case Tip::Standard: coef=1.0f; break;
        case Tip::SemiS: coef=1.5f; break;
    }
    uzura+=distanta*coef;
    if (uzura>100.0f) uzura=100.0f;
}
bool Pneu::uzat() const {
    return uzura >=100.0f;
}
void Pneu::afisare() const {
    std::cout<<"Tip: ";
    switch (tip) {
        case Tip::Slick: std::cout<<"Slick"; break;
        case Tip::Standard: std::cout<<"Standard"; break;
        case Tip::SemiS: std::cout<<"SemiS"; break;
    }
    std::cout<<"uzura: "<<uzura<<"%"<<std::endl;
}


