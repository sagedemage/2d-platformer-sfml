#include "engine/entities.hpp"

float Gravity(sf::Vector2f position, float accel);

void JumpPhysics(sf::Sprite *player, MotionState *motion_state,
                 PlayerSpeed player_speed);
