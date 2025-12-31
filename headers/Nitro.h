#ifndef NITRO_H
#define NITRO_H

#include "Elementharta.h"

class Nitro : public Elementharta {
private:
    float putereBoost;
protected:
  void afisareVirtuala(std::ostream& os) const override;
public:
    explicit Nitro(sf::Vector2f pos);
    void aplicaefect(Masina& masina) override;
    void draw(sf::RenderWindow& window) override;
    std::unique_ptr<Elementharta> clone() const override;
};

#endif