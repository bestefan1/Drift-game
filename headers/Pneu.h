//
// Created by Stefan King on 10/26/2025.
//

#ifndef PNEU_H
#define PNEU_H
#include <string>


class Pneu {
    public:
    enum class TipPneu{Slick,Standard,SemiS};
    Pneu(TipPneu tip, float uzura);
    Pneu(const Pneu &alte) = default;
    Pneu &operator=(const Pneu &alte);
    ~Pneu() = default;
    void degradare(float distanta);
   [[nodiscard]] bool uzat() const;
   // void afisare() const;
    std::string getTipAsString() const;
    private:
    TipPneu tip;
    float uzura;
    friend std::ostream& operator<<(std::ostream& os, const Pneu& p);
};



#endif //PNEU_H
