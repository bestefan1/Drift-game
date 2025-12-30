#include "Exceptiijoc.h"

Driftgameerror::Driftgameerror(const std::string& m) : message(std::move(m)) {}

const char* Driftgameerror::what() const noexcept {
  return message.c_str();
}
Mapboundserror::Mapboundserror():Driftgameerror("Mapboundserror: //limite harta//") {}
Vehicledamageerror::Vehicledamageerror(const std::string& Componenta): Driftgameerror("Vehicledamageerror: //" + Componenta) {}
Assetnotfounderror::Assetnotfounderror(const std::string& Numeresursa): Driftgameerror("Assetnotfounderror: //" + Numeresursa) {}