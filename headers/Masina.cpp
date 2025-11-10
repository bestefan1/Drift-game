//
// Created by Stefan King on 10/26/2025.
//

#include "Masina.h"
#include <iostream>
#include <cmath>
#include <ranges>
Masina::Masina(TipMasina tip_parametru, float viteza_parametru, const std::vector<Pneu> &pneuri_parametru, Motor::TipMotor tip_motor_parametru):
tip(tip_parametru), viteza(viteza_parametru), pneuri(pneuri_parametru), motor(tip_motor_parametru), velocity{0.f, 0.f}, isMovingUp(false), isMovingDown(false), isMovingLeft(false), isMovingRight(false)
{
}

void Masina::initGraphics(sf::Vector2f pozitie, sf::Color culoare, const sf::Font& font) {
    shape.setSize({40.f, 60.f}); // dimensiuni masina
    shape.setFillColor(culoare);
    shape.setOrigin(shape.getSize() / 2.f); // origine in centru
    shape.setPosition(pozitie);

    masinaTipText.setFont(font);
    masinaTipText.setString("Masina: " + getTipAsString());
    masinaTipText.setCharacterSize(18);
    masinaTipText.setFillColor(sf::Color::White);

    pneuriTipText.setFont(font);
    if (!pneuri.empty()) { // Verificăm să nu fie gol vectorul
        pneuriTipText.setString("Pneuri: " + pneuri[0].getTipAsString());
    }
    pneuriTipText.setCharacterSize(18);
    pneuriTipText.setFillColor(sf::Color::White);

}
void Masina::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) {
        isMovingUp = isPressed;
        if (isPressed) acceleratie(1.0f);
    }
    else if (key == sf::Keyboard::S) {
        isMovingDown = isPressed;
        if (isPressed) franare(1.0f);
    }
    else if (key == sf::Keyboard::A)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        isMovingRight = isPressed;
}
void Masina::update(sf::Time dt, sf::Vector2u windowBounds) {
    sf::Vector2f movement(0.f, 0.f);
    if (isMovingUp)
        movement.y -= 1.f;
    if (isMovingDown)
        movement.y += 1.f;
    if (isMovingLeft)
        movement.x -= 1.f;
    if (isMovingRight)
        movement.x += 1.f;

    // incetinire pe diagonala
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length != 0)
        movement /= length;

    //aceleratie
    velocity += movement * accelerationRate * dt.asSeconds();
    sf::Vector2f frameMovement = velocity * dt.asSeconds();
    float distance = std::sqrt(frameMovement.x * frameMovement.x + frameMovement.y * frameMovement.y);
    deplasarep(distance);
    //drag
    velocity -= velocity * dragFactor * dt.asSeconds();

    shape.move(velocity * dt.asSeconds());

    // respectare margini
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f halfSize = shape.getSize() / 2.f;

    //limita stanga
    if (pos.x - halfSize.x < 0) {
        pos.x = halfSize.x;
        velocity.x = 0;
    }
    //dreapta
    if (pos.x + halfSize.x >static_cast<float>(windowBounds.x)) {
        pos.x = static_cast<float> (windowBounds.x) - halfSize.x;
        velocity.x = 0;
    }
    //sus
    if (pos.y - halfSize.y < 0) {
        pos.y = halfSize.y;
        velocity.y = 0;
    }
    //jos
    if (pos.y + halfSize.y > static_cast<float>(windowBounds.y)) {
        pos.y = static_cast<float>(windowBounds.y) - halfSize.y;
        velocity.y = 0;
    }
    shape.setPosition(pos);
    halfSize = shape.getSize() / 2.f;
    masinaTipText.setPosition(pos.x - halfSize.x, pos.y - halfSize.y - 45);
    pneuriTipText.setPosition(pos.x - halfSize.x, pos.y - halfSize.y - 25);
}
void Masina::draw(sf::RenderWindow &window) const {
    window.draw(shape);
    window.draw(masinaTipText);
    window.draw(pneuriTipText);
}
//bool Masina::isMoving() const {
 //   return isMovingUp || isMovingDown || isMovingLeft || isMovingRight;
//}
// cppcheck-suppress functionCanBeConst
void Masina::deplasarep(float distanta) {
    for (auto& p : pneuri) {
        p.degradare(distanta);
    }
}
std::string Masina::getTipAsString() const {
    switch (tip) {
        case TipMasina::Street: return "Street";
        case TipMasina::Stock:  return "Stock";
        case TipMasina::Drift:  return "Drift";
    }
    return "Necunoscut";
}
/*void Masina::afisare()const {
    std::cout<<"Tip masina: ";
    switch (tip) {
        case TipMasina::Street: std::cout<<"Street: ";break;
        case TipMasina::Stock: std::cout<<"Stock: ";break;
        case TipMasina::Drift: std::cout<<"Drift: ";break;
    }
    std::cout<<"Viteza: "<<viteza<<std::endl;

    std::cout<<"Pneuri:\n ";
    for (const auto& p : pneuri) {
        p.afisare();
    }
}
*/
bool Masina::verificarepneu() const {
    return std::ranges::any_of(pneuri,&Pneu::uzat);
}
void Masina::acceleratie(float coeficient) {
    viteza+=coeficient;
}
void Masina::franare(float coeficient) {
    viteza-=coeficient;
    if (viteza<0) viteza=0;
}
std::ostream& operator<<(std::ostream& os, const Masina& m) {
    os<<"Masina tip: "<<m.getTipAsString()<<"\n";
    os<<m.motor<<"\n";
    os<<"Pneuri tip: "<<m.pneuri.size()<<"\n";
    for (const auto& pneu : m.pneuri) {
        os<<" "<<pneu<<"\n";
    }
    return os;
}


