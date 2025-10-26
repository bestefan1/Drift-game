
#include "Pneu.h"
#include "Masina.h"
#include "Meniujoc.h"
#include <iostream>
#include <vector>
Meniujoc::Meniujoc()
    :masina(Masina::TipMasina::Street,0.0f,std::vector<Pneu>
        { Pneu(Pneu::TipPneu::Standard,0.0f),
          Pneu(Pneu::TipPneu::Standard,0.0f),
            Pneu(Pneu::TipPneu::Standard,0.0f),
            Pneu(Pneu::TipPneu::Standard,0.0f)
        })
{}
void Meniujoc::start() {
    int alege;
    std::cout<<"alege tip masina: 1=Street, 2=Stock, 3=Drift ";
    std::cin >> alege;

    Masina::TipMasina tipMasina;
    std::vector<Pneu> pneuri;
    switch (alege) {
        case 1:
            tipMasina=Masina::TipMasina::Street;
        pneuri={ Pneu(Pneu::TipPneu::Standard,0.0f),
                 Pneu(Pneu::TipPneu::Standard,0.0f),
                 Pneu(Pneu::TipPneu::Standard,0.0f),
                 Pneu(Pneu::TipPneu::Standard,0.0f),
        };
        break;
        case 2:
            tipMasina=Masina::TipMasina::Stock;
        pneuri={ Pneu(Pneu::TipPneu::Slick,0.0f),
        Pneu(Pneu::TipPneu::Slick,0.0f),
        Pneu(Pneu::TipPneu::Slick,0.0f),
        Pneu(Pneu::TipPneu::Slick,0.0f),
        };
        break;
        case 3:
            tipMasina=Masina::TipMasina::Drift;
        pneuri={ Pneu(Pneu::TipPneu::SemiS,0.0f),
        Pneu(Pneu::TipPneu::SemiS,0.0f),
        Pneu(Pneu::TipPneu::SemiS,0.0f),
        Pneu(Pneu::TipPneu::SemiS,0.0f),
        };
        break;
        default:
            std::cout<<"invalid\n";
        tipMasina=Masina::TipMasina::Street;
        pneuri={ Pneu(Pneu::TipPneu::Standard,0.0f),
        Pneu(Pneu::TipPneu::Standard,0.0f),
        Pneu(Pneu::TipPneu::Standard,0.0f),
        Pneu(Pneu::TipPneu::Standard,0.0f),
        };
        break;
    }
    masina= Masina(tipMasina,0.0f,pneuri);
}
void Meniujoc::afisare() const {
    masina.afisare();
}
