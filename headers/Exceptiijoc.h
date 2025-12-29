#ifndef EXCEPTIIJOC_H
#define EXCEPTIIJOC_H

#include <exception>
#include <string>


class Driftgameerror : public std::exception
{
  protected:
    std::string message;
   public:
     explicit Driftgameerror(const std::string m);
     virtual ~Driftgameerror() noexcept = default;
     const char* what() const noexcept override;
};
class Mapboundserror : public Driftgameerror{
  public:
    Mapboundserror();
  };
class Vehicledamageerror: public Driftgameerror{
  public:
    explicit Vehicledamageerror(const std::string& Componenta);
};
class Assetnotfounderror: public Driftgameerror{
  public:
    explicit Assetnotfounderror(const std::string& Numeresursa);
};



#endif //EXCEPTIIJOC_H
