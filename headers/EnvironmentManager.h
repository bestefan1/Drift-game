#ifndef ENVIRONMENTMANAGER_H
#define ENVIRONMENTMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

enum class WeatherState { Sunny, Rainy, Icy, Windy };

class EnvironmentManager {
private:
    WeatherState currentState;
    sf::Vector2f windForce;
    float frictionMultiplier;
    float timer;
    float nextChangeTime;

    void updateWeatherEffects();

public:
    EnvironmentManager();
    void update(sf::Time dt);

    sf::Vector2f getWindForce() const;
    float getFrictionModifier() const;
    std::string getWeatherName() const;
    sf::Color getWeatherColor() const;
};

#endif //ENVIRONMENTMANAGER_H
