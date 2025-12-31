//
// Created by Stefan King on 10/26/2025.
//

#ifndef MENIUJOC_H
#define MENIUJOC_H
#pragma once
#include "Masina.h"
#include "Elementharta.h"
#include "StatsManager.h"
#include "Exceptiijoc.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Meniujoc {
public:
    enum class GameState{MainMenu,Playing,Paused,Configuration,Gameover,Exiting};
    Meniujoc();
    void run();
    static int getNrAccidente();
    Meniujoc(const Meniujoc& alte);
    Meniujoc& operator=(Meniujoc alte);
    friend void swap(Meniujoc& prima,Meniujoc& adoua) noexcept;
    void genereazaHarta();
    void updateObiecte();
    //Masina& getMasina()
    //{return masina;}
//    void afisare() const;
private:
    sf::View gameView;
    sf::Vector2f hartaLimite;
    sf::RectangleShape fundalharta;
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
    sf::Text scoreText;
    sf::Text collisionMsgText;
    sf::Clock msgClock;
    static int nrAccidente;
    sf::Text gameOverTitle;
    sf::Text finalScoreText;
    sf::Text restartInfoText;
    StatsManager stats;
    sf::Text errormsgtext;
    sf::Clock errorClock;
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
    std::vector<std::unique_ptr<Elementharta>> elementeHarta;
};



#endif //MENIUJOC_H
