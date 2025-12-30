#include "Elementharta.h"
#include <iostream>

Elementharta::Elementharta(sf::Vector2f pos, sf::Color culoare)
    {
      forma.setRadius(15.f);
      forma.setOrigin(15.f,15.f);
      forma.setPosition(pos);
      forma.setFillColor(culoare);
    }
    // cppcheck-suppress unusedFunction
    void Elementharta::afisare(std::ostream& os) const{
        os << "[Element]";
        afisareVirtuala(os);
       }
    void Elementharta::draw(sf::RenderWindow& window) const{
      window.draw(forma);
    }
    sf::FloatRect Elementharta::getBounds() const{
      return forma.getGlobalBounds();
    }