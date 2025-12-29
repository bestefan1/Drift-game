#include "headers/Meniujoc.h"
#include <iostream>
int main() {
    try {
        Meniujoc joc;
        joc.run();
    }
    catch (const Assetnotfounderror& e) {
        std::cerr<<"Eroare"<<e.what()<<std::endl;
        return 1;
    }
    catch (const Driftgameerror& e) {
        std::cerr<<"Eroare"<<e.what()<<std::endl;
    }
    std::cout<<"Joc terminat.\n";

    //pentru alegere masina/pneuri se alege din consola
    //escape pentru iesire, R-pentru restart, P-pentru pauza
    //wasd controale joc
    return 0;
}