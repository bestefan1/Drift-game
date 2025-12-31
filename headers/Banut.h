#ifndef BANUT_H
#define BANUT_H
#include "Elementharta.h"


class Banut: public Elementharta {
  protected:
    void afisareVirtuala(std::ostream& os) const override;
  public:
    void draw(sf::RenderWindow& window) override;
   explicit Banut(sf::Vector2f pos);
    std::unique_ptr<Elementharta> clone() const override;
    void aplicaefect(Masina& masina) override;
};



#endif //BANUT_H
