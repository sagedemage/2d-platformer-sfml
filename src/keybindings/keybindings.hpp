#include "engine/entities.hpp"

void HoldKeybindings(sf::Sprite *player_sprite, MotionSpeed motion_speed,
                     unsigned int joystick_num);

void ClickKeybindings(sf::Event event, sf::Sprite *player_sprite,
                      MotionState *motion_state,
                      CollisionState *collision_state, MotionSpeed motion_speed,
                      unsigned int joystick_num);
