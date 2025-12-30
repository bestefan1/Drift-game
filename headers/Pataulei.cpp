#include "Pataulei.h"
#include "Masina.h"
#include <iostream>

Pataulei::Pataulei(sf::Vector2f pos):Elementharta(pos,sf::Color(50,50,50))
{
 forma.setRadius(25.f);
 forma.setOrigin(25.f,25.f);
}
std::unique_ptr<Elementharta> Pataulei::clone() const{
  return std::make_unique<Pataulei>(*this);
  }
void Pataulei::afisareVirtuala(std::ostream& os) const{
  os << "Pataulei";
}
void Pataulei::aplicaefect(Masina& masina){
  std::cout<<"Pataulei/derapaj"<<std::endl;
  masina.setGrip(0.1f);
}