#include "engine/entities.hpp"

void PlayerWallCollision(sf::Sprite *player_sprite, sf::Sprite &wall,
                         CollisionState *collision_state,
                         MotionSpeed motion_speed);

void PlayerPlatformCollision(sf::Sprite *player_sprite, sf::Sprite &platform,
                             CollisionState *collision_state, float accel);
