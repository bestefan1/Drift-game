//
// Created by Stefan King on 10/26/2025.
//

#ifndef MASINA_H
#define MASINA_H
#include "Pneu.h"
#include <iostream>
#include <vector>

class Masina {
    public:
    enum class Tip{Street,Stock,Drift};
    private:
    Tip tip;
    float viteza;
    std::vector<Pneu> pneuri;



};



#endif //MASINA_H
