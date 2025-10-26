//
// Created by Stefan King on 10/26/2025.
//

#ifndef PNEU_H
#define PNEU_H
#include <iostream>
#include <string>


class Pneu {
    public:
    enum class TipPneu{Slick,Standard,SemiS};
    private:
    TipPneu tip;
    float uzura;
    public:
    Pneu(TipPneu tip, float uzura);
    Pneu(const Pneu &alte);
    Pneu &operator=(const Pneu &alte);
    ~Pneu();
    void degradare(float distanta);
    bool uzat() const;
    void afisare() const;
};



#endif //PNEU_H
