#include "Nitro.h"
#include "Masina.h"

Nitro::Nitro(sf::Vector2f pos) : Elementharta(pos, sf::Color::Cyan), putereBoost(1.8f) {
    forma.setPointCount(3);
    forma.setRadius(18.f);
    forma.setOutlineThickness(2.f);
    forma.setOutlineColor(sf::Color::White);
    forma.setOrigin(18.f, 18.f);
    forma.setPosition(pos);
}

void Nitro::afisareVirtuala(std::ostream& os) const {
    os << "Nitro Boost activat la pozitia (" << forma.getPosition().x << ", " << forma.getPosition().y << ")";
}

void Nitro::aplicaefect(Masina& masina) {
    masina.activeazaNitro(putereBoost, 3.0f);
    masina.adaugaScor(150);
}

void Nitro::draw(sf::RenderWindow& window) {
    window.draw(forma);
}

std::unique_ptr<Elementharta> Nitro::clone() const {
    return std::make_unique<Nitro>(*this);
}