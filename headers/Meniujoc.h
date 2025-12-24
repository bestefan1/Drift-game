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
    enum class GameState{MainMenu,Playing,Paused,Configuration,Exiting};
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

    sf::RectangleShape configButton;
    sf::Text configButtonText;

    sf::RectangleShape exitButton;
    sf::Text exitButtonText;

    sf::Text configTitle;
    sf::Text carOptionText;
    sf::Text tireOptionText;
    sf::Text motorOptionText;
    sf::RectangleShape backButton;
    sf::Text backButtonText;
    int selectedCar=1;
    int selectedTire=1;
    int selectedMotor=1;

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
    void setupConfigMenu();
    void handleMenuClick(sf::Vector2f mousePos);
    void handleConfigClick(sf::Vector2f mousePos);
    void updateConfigStrings();
    void setupMasinaFromSelection();
    void restartGame();
    //void afisare() const;
    friend std::ostream& operator<<(std::ostream& os, const Meniujoc& joc);
};



#endif //MENIUJOC_H
