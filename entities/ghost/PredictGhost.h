//
// Created by stan1 on 09/11/2025.
//

#ifndef PREDICTGHOST_H
#define PREDICTGHOST_H
#include "entities/ghost/Ghost.h"

namespace entities {
class PredictGhost : public Ghost {
public:
  PredictGhost(float x, float y, std::shared_ptr<Pacman> pacman,
               const std::vector<std::vector<bool>> &wallgrid, int id,
               float chasetime);

  float distanceTurn(std::vector<int> direction, float dt) override;
  void CalculateNextTurn(float dt) override;
};
} // namespace entities

#endif // PREDICTGHOST_H
