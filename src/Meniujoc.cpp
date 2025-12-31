#include "Meniujoc.h"
#include "Exceptiijoc.h"
#include "Elementharta.h"
#include "Banut.h"
#include "Jalon.h"
#include "Pataulei.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <random>
#include <ctime>
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
    genereazaHarta();
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

    errormsgtext.setFont(font);
    errormsgtext.setCharacterSize(20);
    errormsgtext.setFillColor(sf::Color::Transparent);
    errormsgtext.setStyle(sf::Text::Bold);
    errormsgtext.setPosition(300.f,400.f);

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

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(650.f,10.f);

    collisionMsgText.setFont(font);
    collisionMsgText.setCharacterSize(40);
    collisionMsgText.setFillColor(sf::Color::Transparent);
    collisionMsgText.setStyle(sf::Text::Bold);
    collisionMsgText.setPosition(250.f,70.f);
    fundalharta.setFillColor(sf::Color(60,60,60));
    fundalharta.setOutlineThickness(20.f);
    fundalharta.setOutlineColor(sf::Color::Red);

    gameOverTitle.setFont(font);
    gameOverTitle.setString("Cursa terminata!");
    gameOverTitle.setCharacterSize(60);
    gameOverTitle.setFillColor(sf::Color::Red);
    gameOverTitle.setStyle(sf::Text::Bold);

    weatherText.setFont(font);
    weatherText.setCharacterSize(20);
    weatherText.setPosition(10.f,40.f);
    weatherText.setFillColor(sf::Color::White);

    weatherOverlay.setSize(hartaLimite);
    weatherOverlay.setPosition(0,0);

    shopText.setFont(font);
    shopText.setCharacterSize(22);
    shopText.setFillColor(sf::Color::Yellow);
    shopText.setPosition(100.f, 450.f);

    sf::FloatRect goRect=gameOverTitle.getLocalBounds();
    gameOverTitle.setOrigin(goRect.left + goRect.width / 2.0f,goRect.top+goRect.height/2.0f);
    gameOverTitle.setPosition(400.f,200.f);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(40);
    finalScoreText.setFillColor(sf::Color::White);

    restartInfoText.setFont(font);
    restartInfoText.setString("Apasa R pentru rastart/M pentru meniu principal/ESC pentru exit");
    restartInfoText.setCharacterSize(20);
    restartInfoText.setFillColor(sf::Color::Yellow);
    restartInfoText.setPosition(220.f,450.f);
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
                handleShopInput(event);
                break;
            case GameState::Paused:
                break;
            case GameState::Exiting:
                window.close();
                break;
            case GameState::Gameover:
                if (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::R) {
                    restartGame();
                    gameState = GameState::Playing;
                }
                else if (event.key.code==sf::Keyboard::M) {
                    restartGame();
                    gameState = GameState::MainMenu;
                }
                break;
            default:
                break;
        }
    }
}


void Meniujoc::update(sf::Time dt) {
    if (gameState == GameState::Playing) {
       try {
           env.update(dt);
           if (nitroDeblocat && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
               masina.activeazaNitro(1.8f, 3.0f);
               nitroDeblocat = false;
           }
           masina.aplicaMediu(env.getWindForce()*dt.asSeconds(),env.getFrictionModifier());
           weatherText.setString("Vreme:"+ env.getWeatherName());
           weatherOverlay.setFillColor(env.getWeatherColor());
           masina.update(dt, sf::Vector2u(static_cast<unsigned int>(hartaLimite.x),
            static_cast<unsigned int>(hartaLimite.y)));
           stats.update(masina.getVelocity(),dt.asSeconds());
           updateObiecte();
           masina.actualizareInterfata(scoreText);
           if (msgClock.getElapsedTime().asSeconds()>1.5f) {
               collisionMsgText.setFillColor(sf::Color::Transparent);
           }
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
          /* bool Banutiexista=false;
           for (const auto& el:elementeHarta) {
               if (dynamic_cast<Banut*>(el.get())){}
               Banutiexista=true;
               break;
           }*/
           if (elapsed.asSeconds() > 70.0f) {
               gameState= GameState::Gameover;
           }
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
              // restartGame();
               gameState = GameState::Gameover;
               stats.salveazaProgres();
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
            if (!nitroDeblocat) {
            shopText.setString("Nitro Upgrade: 700 Banuti (Ai: " + std::to_string(stats.getBanut()) + ")\n[N] - Cumpara");
            }
            window.draw(shopText);
            if (errorClock.getElapsedTime().asSeconds()<2.0f) {
                window.draw(errormsgtext);
            } else {
                errormsgtext.setFillColor(sf::Color::Transparent);
            }
            break;
        case GameState::Playing:
        case GameState::Paused:
            window.setView(gameView);
            window.draw(fundalharta);
            window.draw(weatherOverlay);
            for (const auto& el: elementeHarta) {
                el->draw(window);
            }
            masina.draw(window);
        window.setView(window.getDefaultView());
        window.draw(weatherText);
        window.draw(timerText);
        window.draw(scoreText);
        window.draw(collisionMsgText);
        if (masina.verificarepneu()) {
            window.draw(tirewarningtxt);
        }
        if (gameState == GameState::Paused) {
            window.draw(pauseText);
        }
        break;
        case GameState::Gameover: {
            window.setView(window.getDefaultView());
            window.draw(gameOverTitle);
            masina.actualizareInterfata(finalScoreText);
            finalScoreText.setPosition(320.f,300.f);
            window.draw(finalScoreText);
            window.draw(restartInfoText);

            sf::Text statsText;
            statsText.setFont(font);
            statsText.setString(stats.getRezumatSesiune());
            statsText.setCharacterSize(18);
            statsText.setPosition(320.f,350.f);
            window.draw(statsText);
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
       int nextCar=(selectedCar%3)+1;
        if (nextCar==3) {
            if (stats.esteDriftDeblocat()) {
                selectedCar=3;
            } else {
                if (stats.deblocheazaMasinaDrift()) {
                    std::cout<<"Masina Drift deblocata:";
                    selectedCar=3;
                    errormsgtext.setString("Masina Drift deblocata:");
                    errormsgtext.setFillColor(sf::Color::Green);
                    errorClock.restart();
                } else {
                    std::cout<<"Bani insuficienti, ai nevoie de 500.\n";
                    errormsgtext.setString("Bani insuficienti, ai nevoie de 500.");
                    errormsgtext.setFillColor(sf::Color::Red);
                    errorClock.restart();
                    selectedCar=1;

                }

            }
        }
            else {
                selectedCar=nextCar;
            }
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
    stats.resetSesiune();
    stats.salveazaProgres();
    gameClock.restart();
    genereazaHarta();
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
Meniujoc::Meniujoc(const Meniujoc &alte):
    gameView(alte.gameView),
    hartaLimite(alte.hartaLimite),
    fundalharta(alte.fundalharta),
    window(),
    font(alte.font),
    gameState(alte.gameState),
    masina(alte.masina)
{
    for (const auto& el:alte.elementeHarta) {
     this->elementeHarta.push_back(el->clone());
    }
}
void swap(Meniujoc& prima,Meniujoc& adoua) noexcept {
    using std::swap;
    swap(prima.elementeHarta,adoua.elementeHarta);
    swap(prima.gameState, adoua.gameState);
    swap(prima.masina, adoua.masina);
    swap(prima.hartaLimite, adoua.hartaLimite);
}
Meniujoc& Meniujoc::operator=(Meniujoc alte) {
    swap(*this,alte);
    return *this;
}
void Meniujoc::updateObiecte() {
    for (auto it=elementeHarta.begin(); it!=elementeHarta.end();) {
        if (masina.getBounds().intersects((*it)->getBounds())) {
            if (dynamic_cast<Banut*>(it->get())) {
                collisionMsgText.setString("colectat");
                collisionMsgText.setFillColor(sf::Color::Green);
                stats.adaugaBanut();
            }
            else if (dynamic_cast<Jalon*>(it->get())) {
                collisionMsgText.setString("ai lovit un jalon");
                collisionMsgText.setFillColor(sf::Color::Red);
            }
            else if (dynamic_cast<Pataulei*>(it->get())) {
                collisionMsgText.setString("derapaj");
                collisionMsgText.setFillColor(sf::Color::Cyan);
            }
            msgClock.restart();
            (*it)->aplicaefect(masina);
            it=elementeHarta.erase(it);
        }
        else {
            ++it;
        }
    }
}
void Meniujoc::genereazaHarta() {
    elementeHarta.clear();
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribX(100.f,2400.f);
    std::uniform_real_distribution<float> distribY(100.f,2400.f);

    std::uniform_int_distribution<int> distribTip(0,2);
    std::uniform_int_distribution<int> distribCantitate(40,60);
    int nrObiecte=distribCantitate(generator);
    for (int i=0;i<nrObiecte;++i) {
        sf::Vector2f pos(distribX(generator),distribY(generator));
        switch(distribTip(generator)) {
            case 0:
                elementeHarta.push_back(std::make_unique<Banut>(pos));
                break;
            case 1:
                elementeHarta.push_back(std::make_unique<Jalon>(pos));
                break;
            case 2:
                elementeHarta.push_back(std::make_unique<Pataulei>(pos));
                break;
            default:
                break;
        }
    }
    std::cout<<"Nr. obiecte generate"<<nrObiecte;
}
void Meniujoc::handleShopInput(sf::Event& event) {
    if (gameState == GameState::Configuration && event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::N) {
            int baniCurenti = stats.getBanut();
            if (baniCurenti >= 700 && !nitroDeblocat) {
                stats.scadeBani(700);
                nitroDeblocat = true;
                shopText.setString("Nitro: DEBLOCAT (Apasati SPACE in joc)");
                shopText.setFillColor(sf::Color::Green);
            }
        }
    }
}