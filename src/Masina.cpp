#include "Masina.h"
#include "Exceptiijoc.h"
#include <iostream>
#include <cmath>
#include <ranges>
Masina::Masina(TipMasina tip_parametru, float viteza_parametru, const std::vector<Pneu> &pneuri_parametru, Motor::TipMotor tip_motor_parametru):
tip(tip_parametru), viteza(viteza_parametru), pneuri(pneuri_parametru), motor(tip_motor_parametru),steeringAngle(0.0f), velocity{0.f, 0.f}, isMovingUp(false), isMovingDown(false), isMovingLeft(false), isMovingRight(false), scor(0),lateralGrip(0.94f)
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
    //sf::Vector2f movement(0.f, 0.f);
    //float steeringspeed=150.f;
    float seconds=dt.asSeconds();
    float multiplicatorPower=(nitroActiv)? 2.0f:1.0f;
    if (nitroActiv) {
        //multiplicatorPower = 1.8f;
        nitroTimer-=seconds;
        if (nitroTimer <= 0) {
            nitroTimer = false;
        }
    }
    if (isMovingLeft) {
        steeringAngle-=steerSpeed*seconds;
    }
    else if (isMovingRight) {
        steeringAngle+=steerSpeed*seconds;
    } else {
        if (steeringAngle > 2.0f) steeringAngle -= steerSpeed*seconds;
        else if (steeringAngle < -2.0f) steeringAngle += steerSpeed*seconds;
        else steeringAngle = 0;
    }
    if (steeringAngle > maxSteer) steeringAngle = maxSteer;
    if (steeringAngle < -maxSteer) steeringAngle = -maxSteer;

    float speed=std::sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
    if (speed>10.f) {
        float factorRotatie=(steeringAngle*(speed/450.f));
        shape.rotate(factorRotatie*seconds*15.f);
    }
    float angleRad=(shape.getRotation()-90.f)*3.14159f/180.f;
    sf::Vector2f facingDir(std::cos(angleRad), std::sin(angleRad));

    //sf::Vector2f accelerationForce(0.f,0.f);
    float enginePower=motor.getCoefAcceleratie()*300.0f;

    if (isMovingUp)
        velocity += facingDir*(enginePower*multiplicatorPower)*seconds;
    if (isMovingDown)
        velocity -= facingDir*(enginePower*0.5f)*seconds;
    updateTrail(seconds);
    //aceleratie
    //velocity += accelerationForce*dt.asSeconds();
    float forwardSpeed= velocity.x*facingDir.x+velocity.y*facingDir.y;
    sf::Vector2f sideDir(-facingDir.y,facingDir.x);
    float sidewaysSpeed=velocity.x*sideDir.x+velocity.y*sideDir.y;

    velocity = facingDir * forwardSpeed + sideDir * (sidewaysSpeed * lateralGrip);
    if (this->lateralGrip<0.94f) {
        this->lateralGrip+=0.15f*seconds;
        if (this->lateralGrip>0.94f) this->lateralGrip=0.94f;
    }
    velocity -= velocity*dragFactor*dt.asSeconds();

    sf::Vector2f frameMovement=velocity*dt.asSeconds();
    shape.move(frameMovement);

    float distance=std::sqrt(frameMovement.x*frameMovement.x+frameMovement.y*frameMovement.y);
    deplasarep(distance);

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
    updateTrail(seconds);
}
void Masina::draw(sf::RenderWindow &window) const {
    for(const auto& p : trail) {
        window.draw(p);
    }
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
    for (const auto& p : pneuri) {
        if (p.uzat()) return true;
    }
    return false;
}
void Masina::acceleratie(float coeficient) {
    viteza+=coeficient;
}
void Masina::franare(float coeficient) {
    viteza-=coeficient;
    if (viteza<0) viteza=0;
}
sf::Vector2f Masina::getPosition() const {
    return shape.getPosition();
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
void Masina::adaugaScor(int puncte) {
    this->scor+=(puncte);
}
void Masina::modificaViteza(float factor) {
    this->velocity*=factor;
    this->viteza*=factor;
}
sf::FloatRect Masina::getBounds() const {
    return shape.getGlobalBounds();
}
void Masina::setGrip(float noulGrip) {
    this->lateralGrip=noulGrip;
}
void Masina::actualizareInterfata(sf::Text &textscor) const {
    textscor.setString("Scor: "+std::to_string(scor));
}
void Masina::aplicaMediu(sf::Vector2f fortaVant, float modFrecare) {
    velocity+=fortaVant;
    this->lateralGrip=0.94f*modFrecare;
}
void Masina::activeazaNitro(float putere, float durata) {
    this->nitroActiv = true;
    this->nitroTimer = durata;
    this->velocity *= putere;
}

void Masina::updateTrail(float dt) {
    if (nitroActiv) {
        sf::CircleShape punct(5.f);
        punct.setPosition(shape.getPosition());
        punct.setFillColor(sf::Color(0, 255, 255, 180));
        trail.push_back(punct);

        nitroTimer -= dt;
        if (nitroTimer <= 0) nitroActiv = false;
    }

    for (auto it = trail.begin(); it != trail.end(); ) {
        sf::Color c = it->getFillColor();
        if (c.a > 10) {
            c.a -= static_cast<sf::Uint8>(150 * dt);
            it->setFillColor(c);
            ++it;
        } else {
            it = trail.erase(it);
        }
    }
}
