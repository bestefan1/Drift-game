#include "Meniujoc.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
Meniujoc::Meniujoc()
    : window(sf::VideoMode(800, 600), "Drift Game"),
        gameState(GameState::MainMenu),
       masina(Masina::TipMasina::Street, 0.0f,
             { Pneu(Pneu::TipPneu::Standard, 0.0f), Pneu(Pneu::TipPneu::Standard, 0.0f),
               Pneu(Pneu::TipPneu::Standard, 0.0f), Pneu(Pneu::TipPneu::Standard, 0.0f) })

{

    if (!font.loadFromFile("G:/clion/Drift-game/fonts/arial.ttf")) {
        std::cerr << "Fontul nu a fost incarcat\n";
        gameState = GameState::Exiting;
        return;
    }
    //titlu
    gameTitleText.setFont(font);
    gameTitleText.setString("Drift Game");
    gameTitleText.setCharacterSize(60);
    gameTitleText.setFillColor(sf::Color::Yellow);
    gameTitleText.setStyle(sf::Text::Bold | sf::Text::Underlined);


    sf::FloatRect titleRect = gameTitleText.getLocalBounds();
    gameTitleText.setOrigin(titleRect.left + titleRect.width / 2.0f,
                            titleRect.top + titleRect.height / 2.0f);
    gameTitleText.setPosition(window.getSize().x / 2.0f, 100.f);

    //timer joc
    timerText.setFont(font);
    timerText.setString("Timp: 0.0s");
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 10.f);


    setupMenu();
    tirewarningtxt.setFont(font);
    tirewarningtxt.setString("PNEURI UZATE!");
    tirewarningtxt.setCharacterSize(40);
    tirewarningtxt.setFillColor(sf::Color::Red);
    tirewarningtxt.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = tirewarningtxt.getLocalBounds();
    tirewarningtxt.setOrigin(textRect.left + textRect.width / 2.0f,
                              textRect.top + textRect.height / 2.0f);
    tirewarningtxt.setPosition(static_cast<float>(window.getSize().x) / 2.0f, 50.f);

    masina.initGraphics({400, 300}, sf::Color::Red);
}

void Meniujoc::setupMenu() {
    sf::Vector2f buttonSize(200, 50);
    
    // buton start
    startButton.setSize(buttonSize);
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300, 200);
    
    startButtonText.setFont(font);
    startButtonText.setString("START");
    startButtonText.setCharacterSize(24);
    startButtonText.setFillColor(sf::Color::Black);
    // centrare
    sf::FloatRect textRect = startButtonText.getLocalBounds();
    startButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    startButtonText.setPosition(startButton.getPosition() + buttonSize / 2.f);

    // buton exit
    exitButton.setSize(buttonSize);
    exitButton.setFillColor(sf::Color(180, 180, 180)); // Gri
    exitButton.setPosition(300, 300);
    
    exitButtonText.setFont(font);
    exitButtonText.setString("EXIT");
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::Black);
    textRect = exitButtonText.getLocalBounds();
    exitButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    exitButtonText.setPosition(exitButton.getPosition() + buttonSize / 2.f);
}

// bucla principala
void Meniujoc::run() {
    if (gameState == GameState::Exiting) return;

    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        
        processEvents();
        update(dt);
        render();
    }
}


void Meniujoc::processEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        switch (gameState) {
            case GameState::MainMenu:

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        handleMenuClick({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
                    }
                }
                break;
            
            case GameState::Playing:
                if (event.type == sf::Event::KeyPressed)
                    masina.handleInput(event.key.code, true);
                if (event.type == sf::Event::KeyReleased)
                    masina.handleInput(event.key.code, false);
                break;
            
            case GameState::Exiting:
                window.close();
                break;
        }
    }
}


void Meniujoc::update(sf::Time dt) {
    if (gameState == GameState::Playing) {
        masina.update(dt, window.getSize());
        sf::Time elapsed = gameClock.getElapsedTime();

        std::stringstream ss;
        ss << "Timp: " << std::fixed << std::setprecision(1) << elapsed.asSeconds() << "s";
        timerText.setString(ss.str());
    }
}


void Meniujoc::render() {
    window.clear(sf::Color(50, 50, 50));

    switch (gameState) {
        case GameState::MainMenu:
            window.draw(gameTitleText);
            window.draw(startButton);
            window.draw(startButtonText);
            window.draw(exitButton);
            window.draw(exitButtonText);
            break;
            
        case GameState::Playing:
            masina.draw(window);
            window.draw(timerText);
            if (masina.verificarepneu()) {
                window.draw(tirewarningtxt);
            }
            break;
        
        case GameState::Exiting:
            break;
    }

    window.display();
}


void Meniujoc::handleMenuClick(sf::Vector2f mousePos) {
    if (startButton.getGlobalBounds().contains(mousePos)) {
        std::cout << "START!\n";
        setupMasinaFromConsole();
        gameClock.restart();
        gameState = GameState::Playing;
    }

    if (exitButton.getGlobalBounds().contains(mousePos)) {
        std::cout << "exit...\n";
        window.close();
    }
}



void Meniujoc::setupMasinaFromConsole() {
    int alege;
    std::cout<<"alege tip masina: 1=Street, 2=Stock, 3=Drift ";
    std::cin >> alege;

    Masina::TipMasina tipMasina;
    std::vector<Pneu> pneuri;
    sf::Color masinaColor; // culoare implicita

    switch (alege) {
        case 1:
            tipMasina=Masina::TipMasina::Street;
            pneuri={ Pneu(Pneu::TipPneu::Standard,0.0f), /*...*/ };
           masinaColor = sf::Color::Blue;
            break;
        case 2:
            tipMasina=Masina::TipMasina::Stock;
            pneuri={ Pneu(Pneu::TipPneu::Slick,0.0f), /*...*/ };
            masinaColor = sf::Color::Yellow;
            break;
        case 3:
            tipMasina=Masina::TipMasina::Drift;
            pneuri={ Pneu(Pneu::TipPneu::SemiS,0.0f), /*...*/ };
            masinaColor = sf::Color::Magenta;
            break;
        default:
            std::cout<<"invalid\n";
            tipMasina=Masina::TipMasina::Street;
            pneuri={ Pneu(Pneu::TipPneu::Standard,0.0f), /*...*/ };
            masinaColor = sf::Color::Red;
            break;
    }
    masina= Masina(tipMasina,0.0f,pneuri);
    masina.initGraphics(sf::Vector2f(window.getSize() / 2u), masinaColor);
}

void Meniujoc::afisare() const {
    masina.afisare();
}