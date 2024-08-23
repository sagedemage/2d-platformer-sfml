#include "collision.hpp"

void PlayerWallCollision(sf::Sprite *player, sf::Sprite &wall,
                         CollisionState *collision_state,
                         PlayerSpeed player_speed) {
    float offset = 5;
    float player_width = player->getGlobalBounds().width;
    float player_height = player->getGlobalBounds().height;
    /* X Axis Collision */
    if (player->getPosition().y > wall.getPosition().y + offset &&
        player->getPosition().y <
            wall.getPosition().y + player_height - offset) {
        if (player->getPosition().x + player_width > wall.getPosition().x &&
            player->getPosition().x + player_width <
                wall.getPosition().x + player_width) {
            // left collision
            player->move(-player_speed.speed, 0);
        } else if (player->getPosition().x <
                       wall.getPosition().x + player_width &&
                   player->getPosition().x > wall.getPosition().x) {
            // right collision
            player->move(player_speed.speed, 0);
        }
    }

    else if (player->getPosition().y + player_height >
                 wall.getPosition().y + offset &&
             player->getPosition().y + player_height <
                 wall.getPosition().y + player_height - offset) {
        if (player->getPosition().x + player_width > wall.getPosition().x &&
            player->getPosition().x + player_width <
                wall.getPosition().x + player_width) {
            // left collision
            player->move(-player_speed.speed, 0);
        } else if (player->getPosition().x <
                       wall.getPosition().x + player_width &&
                   player->getPosition().x > wall.getPosition().x) {
            // right collision
            player->move(player_speed.speed, 0);
        }
    }

    else if (player->getPosition().y + player_height / 2 >
                 wall.getPosition().y &&
             player->getPosition().y + player_height / 2 <
                 wall.getPosition().y + player_height) {
        if (player->getPosition().x + player_width > wall.getPosition().x &&
            player->getPosition().x + player_width <
                wall.getPosition().x + player_width) {
            // left collision
            player->move(-player_speed.speed, 0);
        } else if (player->getPosition().x <
                       wall.getPosition().x + player_width &&
                   player->getPosition().x > wall.getPosition().x) {
            // right collision
            player->move(player_speed.speed, 0);
        }
    }

    /* Y Axis Collision */
    if (player->getPosition().x > wall.getPosition().x &&
        player->getPosition().x < wall.getPosition().x + player_width) {
        if (player->getPosition().y + player_height > wall.getPosition().y &&
            player->getPosition().y + player_height <
                wall.getPosition().y + player_height) {
            // top collision
            player->move(0, -player_speed.accel);
            collision_state->on_the_floor = true;
        } else if (player->getPosition().y <
                       wall.getPosition().y + player_height &&
                   player->getPosition().y > wall.getPosition().y) {
            // bottom collision
            player->move(0, player_speed.accel);
        }
    }

    else if (player->getPosition().x + player_width > wall.getPosition().x &&
             player->getPosition().x + player_width <
                 wall.getPosition().x + player_width) {
        if (player->getPosition().y + player_height > wall.getPosition().y &&
            player->getPosition().y + player_height <
                wall.getPosition().y + player_height) {
            // top collision
            player->move(0, -player_speed.accel);
            collision_state->on_the_floor = true;
        } else if (player->getPosition().y <
                       wall.getPosition().y + player_height &&
                   player->getPosition().y > wall.getPosition().y) {
            // bottom collision
            player->move(0, player_speed.accel);
        }
    }

    else if (player->getPosition().x + player_width / 2 >
                 wall.getPosition().x &&
             player->getPosition().x + player_width / 2 <
                 wall.getPosition().x + player_width) {
        if (player->getPosition().y + player_height > wall.getPosition().y &&
            player->getPosition().y + player_height <
                wall.getPosition().y + player_height) {
            // top collision
            player->move(0, -player_speed.accel);
            collision_state->on_the_floor = true;
        } else if (player->getPosition().y <
                       wall.getPosition().y + player_height &&
                   player->getPosition().y > wall.getPosition().y) {
            // bottom collision
            player->move(0, player_speed.accel);
        }
    }
}

void PlayerPlatformCollision(sf::Sprite *player, sf::Sprite &platform,
                             CollisionState *collision_state, float accel) {
    float player_width = player->getGlobalBounds().width;
    float player_height = player->getGlobalBounds().height;

    /* Y Axis Collision */
    if (player->getPosition().x > platform.getPosition().x &&
        player->getPosition().x < platform.getPosition().x + player_width) {
        if (player->getPosition().y + player_height >
                platform.getPosition().y &&
            player->getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            player->move(0, -accel);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }

    else if (player->getPosition().x + player_width >
                 platform.getPosition().x &&
             player->getPosition().x + player_width <
                 platform.getPosition().x + player_width) {
        if (player->getPosition().y + player_height >
                platform.getPosition().y &&
            player->getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            player->move(0, -accel);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }

    else if (player->getPosition().x + player_width / 2 >
                 platform.getPosition().x &&
             player->getPosition().x + player_width / 2 <
                 platform.getPosition().x + player_width) {
        if (player->getPosition().y + player_height >
                platform.getPosition().y &&
            player->getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            player->move(0, -accel);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }
}
