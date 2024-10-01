#include "engine/entities.hpp"

void Gravity(sf::Sprite *player_sprite, float accel);

void JumpPhysics(sf::Sprite *player_sprite, MotionState *motion_state,
                 MotionSpeed motion_speed);
