#include "engine/entities.hpp"

void PlayerWallCollision(sf::Sprite *player, sf::Sprite &wall,
                         CollisionState *collision_state,
                         PlayerSpeed player_speed);

void PlayerPlatformCollision(sf::Sprite *player, sf::Sprite &platform,
                             CollisionState *collision_state, float accel);
