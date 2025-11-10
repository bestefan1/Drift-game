//
// Created by Stefan King on 11/10/2025.
//

#include "Motor.h"

Motor::Motor(TipMotor tip_parametru): tip(tip_parametru) {
    switch (tip) {
        case TipMotor::Stock:
            CP=150;
            cuplu=200.0f;
            break;
        case TipMotor::Sport:
            CP=300;
            cuplu=350.0f;
            break;
        case TipMotor::Drift:
            CP=500;
            cuplu=600.0f;
            break;
    }
}
float Motor::getCoefAcceleratie() const {
    return(static_cast<float>(CP)*cuplu)/10000.0f;
}
std::string Motor::getTipAsString() const {
    switch (tip) {
        case TipMotor::Stock: return "Stock";
        case TipMotor::Sport: return "Sport";
        case TipMotor::Drift: return "Drift";
    }
    return "unknown";
}
std::ostream& operator<<(std::ostream& os, const Motor& m) {
    os <<"Motor"<< m.getTipAsString()<<",CP= "<<m.CP<<",Cuplu= "<<m.cuplu;
    return os;
}


