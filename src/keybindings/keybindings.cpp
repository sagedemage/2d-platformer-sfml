#include "keybindings.hpp"

void HoldKeybindings(sf::Sprite *player_sprite, MotionSpeed motion_speed,
                     unsigned int joystick_num) {
    /* Keyboard */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // move player left
        player_sprite->move(-motion_speed.speed, 0.F);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // move player right
        player_sprite->move(motion_speed.speed, 0.F);
    }

    /* Controller */
    if (sf::Joystick::getAxisPosition(joystick_num, sf::Joystick::PovX) ==
        -100) {
        // move player left
        // Left D-pad: sf::Joystick::PovX equal to -100
        player_sprite->move(-motion_speed.speed, 0.F);
    } else if (sf::Joystick::getAxisPosition(joystick_num,
                                             sf::Joystick::PovX) == 100) {
        // move player right
        // Right D-pad: sf::Joystick::PovX equal to 100
        player_sprite->move(motion_speed.speed, 0.F);
    }
}

void ClickKeybindings(sf::Event event, sf::Sprite *player,
                      MotionState *motion_state,
                      CollisionState *collision_state, MotionSpeed motion_speed,
                      unsigned int joystick_num) {
    /* Keyboard */
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::K and
            collision_state->on_the_floor) {
            // jump
            motion_state->jump = true;
            collision_state->on_the_floor = false;
            collision_state->on_the_platform = false;
        } else if (event.key.code == sf::Keyboard::S and
                   collision_state->on_the_floor and
                   collision_state->on_the_platform) {
            // drop down
            player->move(0.F, motion_speed.accel);
            collision_state->on_the_floor = false;
            collision_state->on_the_platform = false;
        }
    }

    /* Controller */
    if (sf::Joystick::isButtonPressed(joystick_num, 0) and
        collision_state->on_the_floor) {
        // jump
        // Button 0: A Button on the Xbox One Controller
        motion_state->jump = true;
        collision_state->on_the_floor = false;
        collision_state->on_the_platform = false;
    }

    if (sf::Joystick::getAxisPosition(joystick_num, sf::Joystick::PovY) ==
            100 and
        collision_state->on_the_floor and collision_state->on_the_platform) {
        // drop down
        // Down D-pad: sf::Joystick::PovY equal to 100
        player->move(0.F, motion_speed.accel);
        collision_state->on_the_floor = false;
        collision_state->on_the_platform = false;
    }
}
