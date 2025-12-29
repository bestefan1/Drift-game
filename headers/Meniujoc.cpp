#include "Meniujoc.h"
#include "Exceptiijoc.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ostream>
int Meniujoc::nrAccidente=0;
Meniujoc::Meniujoc()
    :   gameView(sf::FloatRect(0,0,800.f,600.f)),
        hartaLimite(2500.f,2500.f),
        fundalharta(hartaLimite),
        window(sf::VideoMode(800, 600), "Drift Game"),
        gameState(GameState::MainMenu),
       masina(Masina::TipMasina::Street, 0.0f,
             { Pneu(Pneu::TipPneu::Standard, 0.0f), Pneu(Pneu::TipPneu::Standard, 0.0f),
               Pneu(Pneu::TipPneu::Standard, 0.0f), Pneu(Pneu::TipPneu::Standard, 0.0f)}, Motor::TipMotor::Stock)

{
    window.setFramerateLimit(30);
    if (!font.loadFromFile("fonts/arial.ttf")) {
        throw Assetnotfounderror("fonts/arial.ttf");
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
    gameTitleText.setPosition(static_cast<float>(window.getSize().x)/ 2.0f, 100.f);

    //timer joc
    timerText.setFont(font);
    timerText.setString("Timp: 0.0s");
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 10.f);


    setupMenu();
    setupConfigMenu();
    tirewarningtxt.setFont(font);
    tirewarningtxt.setString("PNEURI UZATE!");
    tirewarningtxt.setCharacterSize(40);
    tirewarningtxt.setFillColor(sf::Color::Red);
    tirewarningtxt.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = tirewarningtxt.getLocalBounds();
    tirewarningtxt.setOrigin(textRect.left + textRect.width / 2.0f,
                              textRect.top + textRect.height / 2.0f);
    tirewarningtxt.setPosition(static_cast<float>(window.getSize().x) / 2.0f, 50.f);
    fadeOverlay.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),static_cast<float> (window.getSize().y)));
    fadeOverlay.setFillColor(sf::Color(0, 0, 0, 15));

    pauseText.setFont(font);
    pauseText.setString("PAUZA");
    pauseText.setCharacterSize(70);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold);

    sf::FloatRect pauseRect = pauseText.getLocalBounds();
    pauseText.setOrigin(pauseRect.left + pauseRect.width / 2.0f,
                        pauseRect.top + pauseRect.height / 2.0f);
    pauseText.setPosition(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f);
    fundalharta.setFillColor(sf::Color(60,60,60));
    fundalharta.setOutlineThickness(20.f);
    fundalharta.setOutlineColor(sf::Color::Red);

    masina.initGraphics({400, 300}, sf::Color::Red,font);
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

    //buton configmasina
    configButton.setSize(buttonSize);
    configButton.setFillColor(sf::Color(100,100,250));
    configButton.setPosition(300,270);
    configButtonText.setFont(font);
    configButtonText.setString("CONFIG");
    configButtonText.setCharacterSize(24);
    configButtonText.setFillColor(sf::Color::White);
    sf::FloatRect configRect = configButton.getLocalBounds();
    configButtonText.setOrigin(configRect.left+configRect.width/ 2.0f,configRect.top + configRect.height / 2.0f);
    configButtonText.setPosition(configButton.getPosition() + buttonSize / 2.f);
    // buton exit
    exitButton.setSize(buttonSize);
    exitButton.setFillColor(sf::Color(180, 180, 180)); // Gri
    exitButton.setPosition(300, 340);
    
    exitButtonText.setFont(font);
    exitButtonText.setString("EXIT");
    exitButtonText.setCharacterSize(24);
    exitButtonText.setFillColor(sf::Color::Black);
    textRect = exitButtonText.getLocalBounds();
    exitButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    exitButtonText.setPosition(exitButton.getPosition() + buttonSize / 2.f);
}
void Meniujoc::setupConfigMenu() {
    configTitle.setFont(font);
    configTitle.setString("CONFIGURATIE MASINA");
    configTitle.setCharacterSize(45);
    configTitle.setFillColor(sf::Color::Cyan);
    configTitle.setPosition(260, 50);

    carOptionText.setFont(font);
    carOptionText.setCharacterSize(30);
    carOptionText.setPosition(250, 180);

    tireOptionText.setFont(font);
    tireOptionText.setCharacterSize(30);
    tireOptionText.setPosition(250, 250);

    motorOptionText.setFont(font);
    motorOptionText.setCharacterSize(30);
    motorOptionText.setPosition(250, 320);

    backButton.setSize({200,50});
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(300, 450);

    backButtonText.setFont(font);
    backButtonText.setString("SAVE");
    backButtonText.setCharacterSize(24);
    backButtonText.setPosition(345, 460);

    updateConfigStrings();
}
void Meniujoc::updateConfigStrings() {
    static const std::string masini[]={"Street","Stock","Drift"};
    static const std::string pneuri[]={"Standard","Slick","SemiS"};
    static const std::string motoare[]={"Stock", "Sport","Drift"};

    carOptionText.setString("Masina: <"+ masini[selectedCar-1]+">");
    tireOptionText.setString("Pneuri: <"+ pneuri[selectedTire-1]+">");
    motorOptionText.setString("Motor: <"+ motoare[selectedMotor-1]+">");
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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                restartGame();
            }
            if (event.key.code == sf::Keyboard::P) {
                if (gameState == GameState::Playing) {
                    gameState = GameState::Paused;
                } else if (gameState == GameState::Paused) {
                    gameState = GameState::Playing;
                }
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
            case GameState::Configuration:
                if (event.type==sf::Event::MouseButtonPressed && event.mouseButton.button==sf::Mouse::Left) {
                    handleConfigClick({static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)});
                }
                break;
            case GameState::Paused:
                break;
            case GameState::Exiting:
                window.close();
                break;
            default:
                break;
        }
    }
}


void Meniujoc::update(sf::Time dt) {
    if (gameState == GameState::Playing) {
       try {
           masina.update(dt, sf::Vector2u(static_cast<unsigned int>(hartaLimite.x),
            static_cast<unsigned int>(hartaLimite.y)));
           if (masina.verificarepneu()) {
               throw Vehicledamageerror("Pneuri");
           }
           sf::Vector2f pos=masina.getPosition();
           if (pos.x<-100 || pos.y<-100 || pos.x>hartaLimite.x+100 || pos.y>hartaLimite.y+100) {
               throw Mapboundserror();
           }
           gameView.setCenter(masina.getPosition());
           sf::Time elapsed = gameClock.getElapsedTime();
           std::stringstream ss;
           ss << "Timp: " << std::fixed << std::setprecision(1) << elapsed.asSeconds() << "s";
           timerText.setString(ss.str());
       }
           catch (const Mapboundserror& e) {
                nrAccidente++;
               std::cerr <<"Accident:"<< e.what()<<std::endl;
               restartGame();
           }
           catch (const Vehicledamageerror& e) {
               std::cerr<<"Eroare:"<<e.what()<<std::endl;
               nrAccidente++;
               render();
               sf::sleep(sf::seconds(3.0f));
               gameState = GameState::MainMenu;
               gameClock.restart();
           }
       }
}


void Meniujoc::render() {
    window.clear(sf::Color(50, 50, 50));

    switch (gameState) {
        case GameState::MainMenu:
            window.draw(gameTitleText);
        window.draw(startButton);
        window.draw(startButtonText);
        window.draw(configButton);
        window.draw(configButtonText);
        window.draw(exitButton);
        window.draw(exitButtonText);
        break;
        case GameState::Configuration:
            window.draw(configTitle);
            window.draw(carOptionText);
            window.draw(tireOptionText);
            window.draw(motorOptionText);
            window.draw(backButton);
            window.draw(backButtonText);
            break;
        case GameState::Playing:
        case GameState::Paused:
            window.setView(gameView);
            window.draw(fundalharta);
            masina.draw(window);
        window.setView(window.getDefaultView());
        window.draw(timerText);
        if (masina.verificarepneu()) {
            window.draw(tirewarningtxt);
        }
        if (gameState == GameState::Paused) {
            window.draw(pauseText);
        }
        break;
        
        case GameState::Exiting:
        default:
            break;

    }

    window.display();
}


void Meniujoc::handleMenuClick(sf::Vector2f mousePos) {
    if (startButton.getGlobalBounds().contains(mousePos)) {
        std::cout << "START!\n";
        setupMasinaFromSelection();
        gameClock.restart();
        gameState = GameState::Playing;
    }
    if (configButton.getGlobalBounds().contains(mousePos)) {
        gameState = GameState::Configuration;
    }

    if (exitButton.getGlobalBounds().contains(mousePos)) {
        std::cout << "exit...\n";
        window.close();
    }
}
void Meniujoc::handleConfigClick(sf::Vector2f mousePos) {
    if (carOptionText.getGlobalBounds().contains(mousePos)) {
        selectedCar=(selectedCar%3)+1;
    }
    if (tireOptionText.getGlobalBounds().contains(mousePos)) {
        selectedTire=(selectedTire%3)+1;
    }
    if (motorOptionText.getGlobalBounds().contains(mousePos)) {
        selectedMotor=(selectedMotor%3)+1;
    }
    if (backButton.getGlobalBounds().contains(mousePos)) {
        gameState = GameState::MainMenu;
    }

    updateConfigStrings();
}

void Meniujoc::restartGame() {
    std::cout << "Restart"<<std::endl;
    setupMasinaFromSelection();
    gameClock.restart();
}

//actual setup din file
void Meniujoc::setupMasinaFromSelection() {

    int alegemasina = selectedCar;
    int alegepneu = selectedTire;
    int alegemotor = selectedMotor;
    /*std::cout<<"Alege tip masina: 1=Street, 2=Stock, 3=Drift\n";
    std::cout << "Alege tip pneuri: 1=Standard, 2=Slick, 3=SemiS\n";
    std::ifstream file("tastatura.txt");
    if (!file.is_open()) {
        std::cerr<<"err"<<std::endl;
        alegemasina = 1;
        alegepneu = 1;
        alegemotor = 1;
    } else {
        if (file>>alegemasina>>alegepneu>>alegemotor) {
            std::cout<<"config masina:"<<alegemasina<<"  "<<alegepneu<<"  "<<alegemotor<<std::endl;
        }
        else {
            std::cerr<<"err"<<std::endl;
            alegemasina = 1;
            alegepneu = 1;
            alegemotor = 1;
        }
        file.close();
    }
    */
    Masina::TipMasina tipMasina;
    std::vector<Pneu> pneuri;
    sf::Color masinaColor; // culoare implicita

    switch (alegemasina) {
        case 1:
            tipMasina=Masina::TipMasina::Street;
           // pneuri={ Pneu(Pneu::TipPneu::Standard,0.0f), /*...*/ };
           masinaColor = sf::Color::Blue;
            break;
        case 2:
            tipMasina=Masina::TipMasina::Stock;
           // pneuri={ Pneu(Pneu::TipPneu::Slick,0.0f), /*...*/ };
            masinaColor = sf::Color::Yellow;
            break;
        case 3:
            tipMasina=Masina::TipMasina::Drift;
           // pneuri={ Pneu(Pneu::TipPneu::SemiS,0.0f), /*...*/ };
            masinaColor = sf::Color::Magenta;
            break;
        default:
            std::cout<<"invalid\n";
            tipMasina=Masina::TipMasina::Street;
           // pneuri={ Pneu(Pneu::TipPneu::Standard,0.0f), /*...*/ };
            masinaColor = sf::Color::Red;
            break;
    }
    Pneu::TipPneu tipPneu;

    switch (alegepneu) {
        case 1:
            tipPneu = Pneu::TipPneu::Standard;
        break;
        case 2:
            tipPneu = Pneu::TipPneu::Slick;
        break;
        case 3:
            tipPneu = Pneu::TipPneu::SemiS;
        break;
        default:
            std::cout << "invalid\n";
        tipPneu = Pneu::TipPneu::Standard;
        break;
    }
    Motor::TipMotor tipMotor;
    switch (alegemotor) {
        case 1: tipMotor = Motor::TipMotor::Stock; break;
        case 2: tipMotor = Motor::TipMotor::Sport; break;
        case 3: tipMotor = Motor::TipMotor::Drift; break;
        default:
            std::cout << "invalid\n";
            tipMotor = Motor::TipMotor::Stock;
            break;
    }

    for (int i = 0; i < 4; ++i) {
        pneuri.emplace_back(tipPneu, 0.0f);
    }
    masina = Masina(tipMasina,0.0f,pneuri,tipMotor);
    masina.initGraphics(sf::Vector2f(window.getSize() / 2u), masinaColor,font);
    std::cout<<"setup actual:"<<alegemasina<<alegepneu<<alegemotor<<std::endl;
}

/*void Meniujoc::afisare() const {
    masina.afisare();
}
*/
std::ostream& operator<<(std::ostream& os, const Meniujoc& joc) {
    os<<"STARE JOC:\n";
    os<<"Starea curenta:";
    switch (joc.gameState) {
        case Meniujoc::GameState::MainMenu:
            os<<"Meniujoc::GameState::MainMenu";
            break;
        case Meniujoc::GameState::Playing:
            os<<"Meniujoc::GameState::Playing";
            break;
        case Meniujoc::GameState::Paused:
            os<<"Meniujoc::GameState::Paused";
            break;
        case Meniujoc::GameState::Exiting:
            os<<"Meniujoc::GameState::Exiting";
            break;
        default:
            os<<"invalid\n";
            break;
    }
    os<<"\n\n";
    os<<joc.masina;
return os;
}
int Meniujoc::getNrAccidente() {
    return nrAccidente;
}