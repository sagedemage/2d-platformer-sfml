#include "engine/entities.hpp"

void Gravity(sf::Sprite *player, float accel);

void JumpPhysics(sf::Sprite *player, MotionState *motion_state,
                 PlayerSpeed player_speed);
