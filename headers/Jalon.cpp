#include "Jalon.h"
#include "Masina.h"
#include <iostream>

Jalon::Jalon(sf::Vector2f pos):Elementharta(pos,sf::Color(255,165,0)){}
std::unique_ptr<Elementharta> Jalon::clone() const {
return std::make_unique<Jalon>(*this);
}
void Jalon::afisareVirtuala(std::ostream& os) const{
  os<<"Jalon:"<<std::endl;
  }
void Jalon::aplicaefect(Masina& masina){
  std::cout<<"Jalon lovit"<<std::endl;
  masina.modificaViteza(0.7f);
}