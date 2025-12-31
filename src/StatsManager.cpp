#include "StatsManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

StatsManager::StatsManager()
    {
        resetSesiune();
        incarcaProgres();
    }
void StatsManager::resetSesiune(){
  distantaSesiune=0.f;
  vitezaMaximaSesiune=0.f;
  banutiSesiune=0;
}
void StatsManager::update(sf::Vector2f velocity, float dt) {
    float vitezaCurenta=std::sqrt(velocity.x*velocity.x+velocity.y*velocity.y);
    distantaSesiune+=vitezaCurenta*dt;
    if (vitezaCurenta>vitezaMaximaSesiune) {
        vitezaMaximaSesiune=vitezaCurenta;
    }
}
void StatsManager::adaugaBanut() {
    banutiSesiune++;
    baniTotali+=10;
    salveazaProgres();
}
void StatsManager::incarcaProgres() {
    std::ifstream f(saveFile);
    if (f.is_open()) {
        f>>baniTotali>>masinaDriftDeblocata;
        f.close();
    } else {
        baniTotali=0;
        masinaDriftDeblocata=false;
    }
}
// cppcheck-suppress functionStatic
void StatsManager::salveazaProgres() {
    std::ofstream f(saveFile);
    if (f.is_open()) {
        f<<baniTotali<<" "<<masinaDriftDeblocata;
        f.close();
    }
}
bool StatsManager::deblocheazaMasinaDrift() {
    if (!masinaDriftDeblocata && baniTotali >=500) {
        baniTotali=baniTotali-500;
        masinaDriftDeblocata=true;
        salveazaProgres();
        return true;
    }
    return false;
}
std::string StatsManager::getRezumatSesiune() const {
    std::stringstream ss;
    ss <<"Statistici\n"
        <<"Distanta: "<<std::fixed<<std::setprecision(1)<<distantaSesiune/100.f<<"m\n"
        <<"Viteza max:"<<static_cast<int>(vitezaMaximaSesiune)<<"unit\n"
        <<"Bani colectati/sesiune curenta:"<<banutiSesiune*10<<"\n"
        <<"Bani totali:"<<baniTotali;
    return ss.str();
}
int StatsManager::getBanut() const {
    return baniTotali;
}
void StatsManager::scadeBani(int suma) {
    if (baniTotali>=suma) {
        baniTotali-=suma;
        salveazaProgres();
    }
}

