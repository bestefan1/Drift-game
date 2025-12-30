#ifndef ELEMENTHARTA_H
#define ELEMENTHARTA_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
class Masina;
class Elementharta {
  protected:
    sf::CircleShape forma;
    virtual void afisareVirtuala(std::ostream& os) const=0;
    public:
      Elementharta(sf::Vector2f pos,sf::Color culoare);
      virtual ~Elementharta()=default;
      virtual std::unique_ptr<Elementharta> clone() const=0;
      void afisare(std::ostream& os) const;
      virtual void aplicaefect(Masina& masina)=0;
      void draw(sf::RenderWindow& window) const;
      sf::FloatRect getBounds() const;
};



#endif //ELEMENTHARTA_H
