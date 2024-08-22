#include "engine/entities.hpp"

void HoldKeybindings(sf::Sprite *player, PlayerSpeed player_speed,
                     unsigned int joystick_num);

void ClickKeybindings(sf::Event event, sf::Sprite *player,
                      MotionState *motion_state,
                      CollisionState *collision_state, PlayerSpeed player_speed,
                      unsigned int joystick_num);
