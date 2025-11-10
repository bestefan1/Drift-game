#include "headers/Meniujoc.h"
#include <iostream>
int main() {
    Meniujoc joc;
    joc.run();
    std::cout<<"Joc terminat.\n";
    std::cout<<joc;
    //pentru alegere masina/pneuri se alege din consola
    //escape pentru iesire, R-pentru restart, P-pentru pauza
    //wasd controale joc
    return 0;
}