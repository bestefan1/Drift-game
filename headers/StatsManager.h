#ifndef STATSMANAGER_H
#define STATSMANAGER_H
#include <SFML/Graphics.hpp>
#include <string>


class StatsManager {
  private:
    float distantaSesiune;
    float vitezaMaximaSesiune;
    int banutiSesiune;
    int baniTotali;
    bool masinaDriftDeblocata;
    const std::string saveFile="save.txt";

   public:
     StatsManager();
     void update(sf::Vector2f velocity, float dt);
     void adaugaBanut();
     void incarcaProgres();
     void salveazaProgres();

     bool deblocheazaMasinaDrift();
     int getBaniTotali() const {return baniTotali;}
     bool esteDriftDeblocat() const{return masinaDriftDeblocata;}
     int getBanut() const;
     void scadeBani(int suma);
     std::string getRezumatSesiune() const;
     void resetSesiune();
};



#endif //STATSMANAGER_H
