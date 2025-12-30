//
// Created by Stefan King on 11/10/2025.
//

#ifndef MOTOR_H
#define MOTOR_H
#include <string>
#include <ostream>


class Motor {
public:
    enum class TipMotor {Stock,Sport,Drift};
    explicit Motor(TipMotor tip=TipMotor::Stock);
    [[nodiscard]]float getCoefAcceleratie() const;
    [[nodiscard]] std::string getTipAsString() const;
private:
    TipMotor tip;
    int CP;
    float cuplu;
    friend std::ostream& operator<<(std::ostream& os, const Motor& m);
};



#endif //MOTOR_H
