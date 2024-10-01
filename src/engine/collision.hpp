#include "engine/entities.hpp"

void PlayerBlockCollision(sf::Sprite *player_sprite, sf::Sprite &block_sprite,
                          CollisionState *collision_state,
                          MotionSpeed motion_speed);

void PlayerPlatformCollision(sf::Sprite *player_sprite,
                             sf::Sprite &platform_sprite,
                             CollisionState *collision_state, float accel);
