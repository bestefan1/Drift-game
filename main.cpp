#include <iostream>
#include <fstream>
#include "headers/Meniujoc.h"
int main() {
    Meniujoc joc;
    joc.start();
    std::cout<<"\nMasina: \n";
    joc.afisare();

    std::ifstream fin("headers/input.txt");
    if (!fin) {
        std::cerr<<"err\n";
        return 1;
    }
    int distanta;
    float acceleratie;
    while (fin >> distanta>>acceleratie) {
        std::cout<<"distanta: "<<distanta<<" acceleratie= "<<acceleratie<<"\n";
    }

    return 0;
}
