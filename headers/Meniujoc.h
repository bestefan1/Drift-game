//
// Created by Stefan King on 10/26/2025.
//

#ifndef MENIUJOC_H
#define MENIUJOC_H
#include "Masina.h"
#include "Pneu.h"
//#include <vector>

class Meniujoc {
private:
    Masina masina;
public:
    Masina& getMasina()
{return masina;}
    Meniujoc();
    void start();
    void afisare() const;
};



#endif //MENIUJOC_H
