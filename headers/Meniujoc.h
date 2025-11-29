//
// Created by Stefan King on 10/26/2025.
//

#ifndef MENIUJOC_H
#define MENIUJOC_H
#pragma once
#include "Masina.h"
#include <SFML/Graphics.hpp>
//#include <vector>

class Meniujoc {
public:
    enum class GameState{MainMenu,Playing,Paused,Exiting};
    Meniujoc();
    void run();
    //Masina& getMasina()
    //{return masina;}
//    void afisare() const;
private:
    sf::RenderWindow window;
    sf::Font font;
    GameState gameState;
    //elemente meniu
    sf::RectangleShape startButton;
    sf::Text startButtonText;

    sf::RectangleShape exitButton;
    sf::Text exitButtonText;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Text tirewarningtxt;
    sf::RectangleShape fadeOverlay;
    sf::Text gameTitleText;
    sf::Text timerText;
    sf::Clock gameClock;
    sf::Text pauseText;
    Masina masina;
    void processEvents();

    //functie loop
    void update(sf::Time dt);

    //functie loop render
    void render();
    void setupMenu(); // init
    void handleMenuClick(sf::Vector2f mousePos);
    void setupMasinaFromConsole();
    void restartGame();
    //void afisare() const;
    friend std::ostream& operator<<(std::ostream& os, const Meniujoc& joc);
};



#endif //MENIUJOC_H
