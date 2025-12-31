#ifndef PATAULEI_H
#define PATAULEI_H
#include "Elementharta.h"


class Pataulei : public Elementharta {
  protected:
    void afisareVirtuala(std::ostream& os) const override;
    public:
    void draw(sf::RenderWindow& window) override;
      explicit Pataulei(sf::Vector2f pos);
      std::unique_ptr<Elementharta> clone() const override;
      void aplicaefect(Masina& masina) override;
};



#endif //PATAULEI_H
