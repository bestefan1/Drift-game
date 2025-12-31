#ifndef JALON_H
#define JALON_H
#include "Elementharta.h"


class Jalon:public Elementharta {
  protected:
    void afisareVirtuala(std::ostream& os) const override;
    public:
      void draw(sf::RenderWindow& window) override;
      explicit Jalon(sf::Vector2f pos);
      std::unique_ptr<Elementharta> clone() const override;
      void aplicaefect(Masina& masina) override;
};



#endif //JALON_H
