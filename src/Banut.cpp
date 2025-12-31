#include "Banut.h"
#include "Masina.h"
#include <iostream>

Banut::Banut(sf::Vector2f pos):Elementharta(pos,sf::Color::Yellow){
  forma.setOutlineThickness(2.f);
  forma.setOutlineColor(sf::Color::White);
}
std::unique_ptr<Elementharta> Banut::clone() const {
  return std::make_unique<Banut>(*this);
}
void Banut::afisareVirtuala(std::ostream& os) const {
  os<<"Banut";
}
void Banut::aplicaefect(Masina& masina) {
  masina.adaugaScor(10);
  std::cout << "Banut colectat" << std::endl;
}
void Banut::draw(sf::RenderWindow& window) {
  window.draw(forma);
}