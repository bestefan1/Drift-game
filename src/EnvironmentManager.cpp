#include "EnvironmentManager.h"
#include <random>

EnvironmentManager::EnvironmentManager() : currentState(WeatherState::Sunny) {
    updateWeatherEffects();
    nextChangeTime = 15.0f;
}

void EnvironmentManager::updateWeatherEffects() {
    std::random_device rd;
    std::mt19937 gen(rd());

    switch (currentState) {
        case WeatherState::Sunny:
            frictionMultiplier = 1.0f;
            windForce = {0.f, 0.f};
            break;
        case WeatherState::Rainy:
            frictionMultiplier = 0.7f;
            windForce = {0.f, 0.f};
            break;
        case WeatherState::Icy:
            frictionMultiplier = 0.3f;
            windForce = {0.f, 0.f};
            break;
        case WeatherState::Windy:
            std::uniform_real_distribution<float> dist(-50.f, 50.f);
            frictionMultiplier = 0.9f;
            windForce = {dist(gen), dist(gen)};
            break;
    }
}

void EnvironmentManager::update(sf::Time dt) {
    timer+=dt.asSeconds();
    if (timer >= nextChangeTime) {
      int next=rand()%4;
      currentState=static_cast<WeatherState>(next);
      updateWeatherEffects();
      timer=0.0f;
    }
}

sf::Vector2f EnvironmentManager::getWindForce() const { return windForce; }
float EnvironmentManager::getFrictionModifier() const { return frictionMultiplier; }

std::string EnvironmentManager::getWeatherName() const {
    switch (currentState) {
        case WeatherState::Sunny: return "SENIN";
        case WeatherState::Rainy: return "PLOAIE (Grip scazut)";
        case WeatherState::Icy:   return "GHEATA (Atentie!)";
        case WeatherState::Windy: return "VANT LATERAL";
    }
    return "Unknown";
}

sf::Color EnvironmentManager::getWeatherColor() const {
    if (currentState == WeatherState::Rainy) return sf::Color(100, 100, 255, 100);
    if (currentState == WeatherState::Icy)   return sf::Color(200, 200, 255, 100);
    return sf::Color::Transparent;
}