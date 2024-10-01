#include "collision.hpp"

void PlayerWallCollision(sf::Sprite *player_sprite, sf::Sprite &wall,
                         CollisionState *collision_state,
                         MotionSpeed motion_speed) {
    float offset = 5;
    float player_width = player_sprite->getGlobalBounds().width;
    float player_height = player_sprite->getGlobalBounds().height;
    /* X Axis Collision */
    if (player_sprite->getPosition().y > wall.getPosition().y + offset &&
        player_sprite->getPosition().y <
            wall.getPosition().y + player_height - offset) {
        if (player_sprite->getPosition().x + player_width >
                wall.getPosition().x &&
            player_sprite->getPosition().x + player_width <
                wall.getPosition().x + player_width) {
            // left collision
            player_sprite->move(-motion_speed.speed, 0);
        } else if (player_sprite->getPosition().x <
                       wall.getPosition().x + player_width &&
                   player_sprite->getPosition().x > wall.getPosition().x) {
            // right collision
            player_sprite->move(motion_speed.speed, 0);
        }
    }

    else if (player_sprite->getPosition().y + player_height >
                 wall.getPosition().y + offset &&
             player_sprite->getPosition().y + player_height <
                 wall.getPosition().y + player_height - offset) {
        if (player_sprite->getPosition().x + player_width >
                wall.getPosition().x &&
            player_sprite->getPosition().x + player_width <
                wall.getPosition().x + player_width) {
            // left collision
            player_sprite->move(-motion_speed.speed, 0);
        } else if (player_sprite->getPosition().x <
                       wall.getPosition().x + player_width &&
                   player_sprite->getPosition().x > wall.getPosition().x) {
            // right collision
            player_sprite->move(motion_speed.speed, 0);
        }
    }

    else if (player_sprite->getPosition().y + player_height / 2 >
                 wall.getPosition().y &&
             player_sprite->getPosition().y + player_height / 2 <
                 wall.getPosition().y + player_height) {
        if (player_sprite->getPosition().x + player_width >
                wall.getPosition().x &&
            player_sprite->getPosition().x + player_width <
                wall.getPosition().x + player_width) {
            // left collision
            player_sprite->move(-motion_speed.speed, 0);
        } else if (player_sprite->getPosition().x <
                       wall.getPosition().x + player_width &&
                   player_sprite->getPosition().x > wall.getPosition().x) {
            // right collision
            player_sprite->move(motion_speed.speed, 0);
        }
    }

    /* Y Axis Collision */
    if (player_sprite->getPosition().x > wall.getPosition().x &&
        player_sprite->getPosition().x < wall.getPosition().x + player_width) {
        if (player_sprite->getPosition().y + player_height >
                wall.getPosition().y &&
            player_sprite->getPosition().y + player_height <
                wall.getPosition().y + player_height) {
            // top collision
            player_sprite->move(0, -motion_speed.accel);
            collision_state->on_the_floor = true;
        } else if (player_sprite->getPosition().y <
                       wall.getPosition().y + player_height &&
                   player_sprite->getPosition().y > wall.getPosition().y) {
            // bottom collision
            player_sprite->move(0, motion_speed.accel);
        }
    }

    else if (player_sprite->getPosition().x + player_width >
                 wall.getPosition().x &&
             player_sprite->getPosition().x + player_width <
                 wall.getPosition().x + player_width) {
        if (player_sprite->getPosition().y + player_height >
                wall.getPosition().y &&
            player_sprite->getPosition().y + player_height <
                wall.getPosition().y + player_height) {
            // top collision
            player_sprite->move(0, -motion_speed.accel);
            collision_state->on_the_floor = true;
        } else if (player_sprite->getPosition().y <
                       wall.getPosition().y + player_height &&
                   player_sprite->getPosition().y > wall.getPosition().y) {
            // bottom collision
            player_sprite->move(0, motion_speed.accel);
        }
    }

    else if (player_sprite->getPosition().x + player_width / 2 >
                 wall.getPosition().x &&
             player_sprite->getPosition().x + player_width / 2 <
                 wall.getPosition().x + player_width) {
        if (player_sprite->getPosition().y + player_height >
                wall.getPosition().y &&
            player_sprite->getPosition().y + player_height <
                wall.getPosition().y + player_height) {
            // top collision
            player_sprite->move(0, -motion_speed.accel);
            collision_state->on_the_floor = true;
        } else if (player_sprite->getPosition().y <
                       wall.getPosition().y + player_height &&
                   player_sprite->getPosition().y > wall.getPosition().y) {
            // bottom collision
            player_sprite->move(0, motion_speed.accel);
        }
    }
}

void PlayerPlatformCollision(sf::Sprite *player_sprite, sf::Sprite &platform,
                             CollisionState *collision_state, float accel) {
    float player_width = player_sprite->getGlobalBounds().width;
    float player_height = player_sprite->getGlobalBounds().height;

    /* Y Axis Collision */
    if (player_sprite->getPosition().x > platform.getPosition().x &&
        player_sprite->getPosition().x <
            platform.getPosition().x + player_width) {
        if (player_sprite->getPosition().y + player_height >
                platform.getPosition().y &&
            player_sprite->getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            player_sprite->move(0, -accel);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }

    else if (player_sprite->getPosition().x + player_width >
                 platform.getPosition().x &&
             player_sprite->getPosition().x + player_width <
                 platform.getPosition().x + player_width) {
        if (player_sprite->getPosition().y + player_height >
                platform.getPosition().y &&
            player_sprite->getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            player_sprite->move(0, -accel);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }

    else if (player_sprite->getPosition().x + player_width / 2 >
                 platform.getPosition().x &&
             player_sprite->getPosition().x + player_width / 2 <
                 platform.getPosition().x + player_width) {
        if (player_sprite->getPosition().y + player_height >
                platform.getPosition().y &&
            player_sprite->getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            player_sprite->move(0, -accel);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }
}