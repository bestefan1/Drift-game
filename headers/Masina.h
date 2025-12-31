//
// Created by Stefan King on 10/26/2025.
//

#ifndef MASINA_H
#define MASINA_H
#pragma once
#include "Pneu.h"
#include "Motor.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Masina {
    public:
    enum class TipMasina{Street,Stock,Drift};
    Masina(TipMasina tip_parametru,float viteza_parametru,const std::vector<Pneu>& pneuri_parametru, Motor::TipMotor tip_motor_parametru);

    void deplasarep(float distanta);
    //void afisare() const;
    bool verificarepneu() const;
    void acceleratie(float coeficient);
    void franare(float coeficient);
    void initGraphics(sf::Vector2f pozitie, sf::Color culoare, const sf::Font& font);
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time dt, sf::Vector2u windowBounds);
    void draw(sf::RenderWindow& window) const;
    //[[nodiscard]] bool isMoving() const;
    [[nodiscard]] std::string getTipAsString() const;
    sf::Vector2f getPosition() const;
    void adaugaScor(int puncte);
    void actualizareInterfata(sf::Text& textscor) const;
    void modificaViteza(float factor);
    sf::FloatRect getBounds() const;
    void setGrip(float noulGrip);
    sf::Vector2f getVelocity() const {return velocity;}
    private:
    TipMasina tip;
    float viteza;
    std::vector<Pneu> pneuri;
    Motor motor;
    float steeringAngle=0;
    static constexpr float maxSteer=25.0f;
    static constexpr float steerSpeed=120.0f;
    //vizual + fizici
    sf::RectangleShape shape;
    sf::Vector2f velocity;        // directie+viteza
    //float accelerationRate = 200.0f;
    float dragFactor = 1.2f;         // coef incetinire

    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    sf::Text masinaTipText;
    sf::Text pneuriTipText;
    friend std::ostream& operator<<(std::ostream& os, const Masina& m);
    int scor=0;
    float lateralGrip=0.94f;
};



#endif //MASINA_H
