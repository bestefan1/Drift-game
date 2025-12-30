//
// Created by Stefan King on 10/26/2025.
//
#include "Pneu.h"
#include <ostream>
#include <iomanip>
Pneu::Pneu( TipPneu tip_parametru, float uzura_parametru)
:tip(tip_parametru),uzura(uzura_parametru){}

//Pneu::Pneu(const Pneu &alte)
  //  :tip(alte.tip),uzura(alte.uzura){}

Pneu &Pneu::operator=(const Pneu &alte) {
    if (this != &alte){
        tip = alte.tip;
        uzura = alte.uzura;
    }
    return *this;
}
//Pneu::~Pneu(){}
std::string Pneu::getTipAsString() const {
    switch (tip) {
        case TipPneu::Slick:    return "Slick";
        case TipPneu::Standard: return "Standard";
        case TipPneu::SemiS:    return "SemiS";
    }
    return "Necunoscut";
}
// cppcheck-suppress unusedFunction
void Pneu::degradare(float distanta) {
    float coef=1.0f;
    switch (tip) {
        case TipPneu::Slick: coef=0.015f; break;
        case TipPneu::Standard: coef=0.003f; break;
        case TipPneu::SemiS: coef=0.001f; break;
    }
    uzura+=distanta*coef;
    if (uzura>100.0f) uzura=100.0f;
}
// cppcheck-suppress unusedFunction
bool Pneu::uzat() const {
    return uzura >=100.0f;
}
/*void Pneu::afisare() const {
    std::cout<<"Tip: ";
    switch (tip) {
        case TipPneu::Slick: std::cout<<"Slick "; break;
        case TipPneu::Standard: std::cout<<"Standard "; break;
        case TipPneu::SemiS: std::cout<<"SemiS "; break;
    }
    std::cout<<" uzura: "<<uzura<<"%"<<std::endl;
}
*/
std::ostream& operator<<(std::ostream& os, const Pneu& p) {
    os << "Pneu: ";
    switch (p.tip) {
        case Pneu::TipPneu::Slick:    os << "Slick"; break;
        case Pneu::TipPneu::Standard: os << "Standard"; break;
        case Pneu::TipPneu::SemiS:    os << "SemiS"; break;
    }
    os << " (Uzura: " << std::fixed << std::setprecision(1) << p.uzura << "%)";
    return os;
}

