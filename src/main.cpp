#include <array>
#include <iostream>

constexpr unsigned LEVEL_WIDTH = 750;
constexpr unsigned LEVEL_HEIGHT = 500;

typedef struct CollisionState {
    bool on_the_floor;
    bool on_the_platform;
} CollisionState;

typedef struct PlayerSpeed {
    float speed;
    float accel;
} PlayerSpeed;

sf::Vector2f PlayerBoundary(sf::Vector2f position, sf::FloatRect global_bounds) {
    if (position.x + global_bounds.width >= 750.F) {
        /* Right boundary */
        position.x = static_cast<float>(LEVEL_WIDTH - global_bounds.width);
    } else if (position.x <= 0.F) {
        /* Left  boundary */
        position.x = 0.F;
    }
    if (position.y <= 0.F) {
        /* Top boudnary */
        position.y = 0.F;
    } else if (position.y + global_bounds.height >= LEVEL_HEIGHT) {
        /* Bottom boudnary */
        position.y = static_cast<float>(LEVEL_HEIGHT - global_bounds.height);
    }
    return position;
}

void MovePlayer(sf::Sprite& player, float speed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        // move player left
        player.move(-speed, 0.F);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        // move player right
        player.move(speed, 0.F);
    }
}

void PlayerWallCollision(sf::Sprite& player, sf::Sprite& wall,
                         CollisionState* collision_state, PlayerSpeed player_speed) {
    sf::Vector2f p_position = player.getPosition();
    float offset = 5;
    float player_width = player.getGlobalBounds().width;
    float player_height = player.getGlobalBounds().height;
    /* X Axis Collision */
    if (player.getPosition().y > wall.getPosition().y + offset &&
        player.getPosition().y < wall.getPosition().y + player_height - offset) {
        if (player.getPosition().x + player_width > wall.getPosition().x &&
            player.getPosition().x + player_width < wall.getPosition().x + player_width) {
            // left collision
            p_position.x -= player_speed.speed;
            player.setPosition(p_position);
        } else if (player.getPosition().x < wall.getPosition().x + player_width &&
                   player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x += player_speed.speed;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().y + player_height > wall.getPosition().y + offset &&
             player.getPosition().y + player_height < wall.getPosition().y + player_height - offset) {
        if (player.getPosition().x + player_width > wall.getPosition().x &&
            player.getPosition().x + player_width < wall.getPosition().x + player_width) {
            // left collision
            p_position.x -= player_speed.speed;
            player.setPosition(p_position);
        } else if (player.getPosition().x < wall.getPosition().x + player_width &&
                   player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x += player_speed.speed;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().y + player_height / 2 > wall.getPosition().y &&
             player.getPosition().y + player_height / 2 < wall.getPosition().y + player_height) {
        if (player.getPosition().x + player_width > wall.getPosition().x &&
            player.getPosition().x + player_width < wall.getPosition().x + player_width) {
            // left collision
            p_position.x -= player_speed.speed;
            player.setPosition(p_position);
        } else if (player.getPosition().x < wall.getPosition().x + player_width &&
                   player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x += player_speed.speed;
            player.setPosition(p_position);
        }
    }

    /* Y Axis Collision */
    if (player.getPosition().x > wall.getPosition().x &&
        player.getPosition().x < wall.getPosition().x + player_width) {
        if (player.getPosition().y + player_height > wall.getPosition().y &&
            player.getPosition().y + player_height < wall.getPosition().y + player_height) {
            // top collision
            p_position.y -= player_speed.accel;
            player.setPosition(p_position);
            collision_state->on_the_floor = true;
        } else if (player.getPosition().y < wall.getPosition().y + player_height &&
                   player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y += player_speed.accel;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().x + player_width > wall.getPosition().x &&
             player.getPosition().x + player_width < wall.getPosition().x + player_width) {
        if (player.getPosition().y + player_height > wall.getPosition().y &&
            player.getPosition().y + player_height < wall.getPosition().y + player_height) {
            // top collision
            p_position.y -= player_speed.accel;
            player.setPosition(p_position);
            collision_state->on_the_floor = true;
        } else if (player.getPosition().y < wall.getPosition().y + player_height &&
                   player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y += player_speed.accel;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().x + player_width / 2 > wall.getPosition().x &&
             player.getPosition().x + player_width / 2 < wall.getPosition().x + player_width) {
        if (player.getPosition().y + player_height > wall.getPosition().y &&
            player.getPosition().y + player_height < wall.getPosition().y + player_height) {
            // top collision
            p_position.y -= player_speed.accel;
            player.setPosition(p_position);
            collision_state->on_the_floor = true;
        } else if (player.getPosition().y < wall.getPosition().y + player_height &&
                   player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y += player_speed.accel;
            player.setPosition(p_position);
        }
    }
}

void PlayerPlatformCollision(sf::Sprite& player, sf::Sprite& platform,
                             CollisionState* collision_state, float accel) {
    sf::Vector2f p_position = player.getPosition();
    float player_width = player.getGlobalBounds().width;
    float player_height = player.getGlobalBounds().height;

    /* Y Axis Collision */
    if (player.getPosition().x > platform.getPosition().x &&
        player.getPosition().x < platform.getPosition().x + player_width) {
        if (player.getPosition().y + player_height > platform.getPosition().y &&
            player.getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }

    else if (player.getPosition().x + player_width > platform.getPosition().x &&
             player.getPosition().x + player_width < platform.getPosition().x + player_width) {
        if (player.getPosition().y + player_height > platform.getPosition().y &&
            player.getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }

    else if (player.getPosition().x + player_width / 2 > platform.getPosition().x &&
             player.getPosition().x + player_width / 2 < platform.getPosition().x + player_width) {
        if (player.getPosition().y + player_height > platform.getPosition().y &&
            player.getPosition().y + player_height <
                platform.getPosition().y + 2 * accel) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collision_state->on_the_floor = true;
            collision_state->on_the_platform = true;
        }
    }
}

float Gravity(sf::Vector2f position, float accel) {
    position.y += accel;

    return position.y;
}

void PlayerSpriteCollisions(sf::Sprite& player, std::array<sf::Sprite, 45> walls,
                                      std::array<sf::Sprite, 12> platforms,
                                      CollisionState* collision_state,
                                      PlayerSpeed player_speed) {
    PlayerWallCollision(player, walls[0], collision_state, player_speed);
    PlayerWallCollision(player, walls[1], collision_state, player_speed);
    PlayerWallCollision(player, walls[2], collision_state, player_speed);
    PlayerWallCollision(player, walls[3], collision_state, player_speed);
    PlayerWallCollision(player, walls[4], collision_state, player_speed);
    PlayerWallCollision(player, walls[5], collision_state, player_speed);
    PlayerWallCollision(player, walls[6], collision_state, player_speed);
    PlayerWallCollision(player, walls[7], collision_state, player_speed);
    PlayerWallCollision(player, walls[8], collision_state, player_speed);
    PlayerWallCollision(player, walls[9], collision_state, player_speed);
    PlayerWallCollision(player, walls[10], collision_state, player_speed);
    PlayerWallCollision(player, walls[11], collision_state, player_speed);
    PlayerWallCollision(player, walls[12], collision_state, player_speed);
    PlayerWallCollision(player, walls[13], collision_state, player_speed);
    PlayerWallCollision(player, walls[14], collision_state, player_speed);
    PlayerWallCollision(player, walls[15], collision_state, player_speed);
    PlayerWallCollision(player, walls[16], collision_state, player_speed);
    PlayerWallCollision(player, walls[17], collision_state, player_speed);
    PlayerWallCollision(player, walls[18], collision_state, player_speed);
    PlayerWallCollision(player, walls[19], collision_state, player_speed);
    PlayerWallCollision(player, walls[20], collision_state, player_speed);
    PlayerWallCollision(player, walls[21], collision_state, player_speed);
    PlayerWallCollision(player, walls[22], collision_state, player_speed);
    PlayerWallCollision(player, walls[23], collision_state, player_speed);
    PlayerWallCollision(player, walls[24], collision_state, player_speed);
    PlayerWallCollision(player, walls[25], collision_state, player_speed);
    PlayerWallCollision(player, walls[26], collision_state, player_speed);
    PlayerWallCollision(player, walls[27], collision_state, player_speed);
    PlayerWallCollision(player, walls[28], collision_state, player_speed);
    PlayerWallCollision(player, walls[29], collision_state, player_speed);
    PlayerWallCollision(player, walls[30], collision_state, player_speed);
    PlayerWallCollision(player, walls[31], collision_state, player_speed);
    PlayerWallCollision(player, walls[32], collision_state, player_speed);
    PlayerWallCollision(player, walls[33], collision_state, player_speed);
    PlayerWallCollision(player, walls[34], collision_state, player_speed);
    PlayerWallCollision(player, walls[35], collision_state, player_speed);
    PlayerWallCollision(player, walls[36], collision_state, player_speed);
    PlayerWallCollision(player, walls[37], collision_state, player_speed);
    PlayerWallCollision(player, walls[38], collision_state, player_speed);
    PlayerWallCollision(player, walls[39], collision_state, player_speed);
    PlayerWallCollision(player, walls[40], collision_state, player_speed);
    PlayerWallCollision(player, walls[41], collision_state, player_speed);
    PlayerWallCollision(player, walls[42], collision_state, player_speed);
    PlayerWallCollision(player, walls[43], collision_state, player_speed);
    PlayerWallCollision(player, walls[44], collision_state, player_speed);

    PlayerPlatformCollision(player, platforms[0], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[1], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[2], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[3], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[4], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[5], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[6], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[7], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[8], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[9], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[10], collision_state, player_speed.accel);
    PlayerPlatformCollision(player, platforms[11], collision_state, player_speed.accel);
}

void DrawAllSprites(sf::RenderWindow& window, sf::Sprite& player,
                    std::array<sf::Sprite, 45> walls, std::array<sf::Sprite, 12> platforms) {
    window.clear(sf::Color(84, 193, 255, 255));

    window.draw(walls[0]);
    window.draw(walls[1]);
    window.draw(walls[2]);
    window.draw(walls[3]);
    window.draw(walls[4]);
    window.draw(walls[5]);
    window.draw(walls[6]);
    window.draw(walls[7]);
    window.draw(walls[8]);
    window.draw(walls[9]);
    window.draw(walls[10]);
    window.draw(walls[11]);
    window.draw(walls[12]);
    window.draw(walls[13]);
    window.draw(walls[14]);
    window.draw(walls[15]);
    window.draw(walls[16]);
    window.draw(walls[17]);
    window.draw(walls[18]);
    window.draw(walls[19]);
    window.draw(walls[20]);
    window.draw(walls[21]);
    window.draw(walls[22]);
    window.draw(walls[23]);
    window.draw(walls[24]);
    window.draw(walls[25]);
    window.draw(walls[26]);
    window.draw(walls[27]);
    window.draw(walls[28]);
    window.draw(walls[29]);
    window.draw(walls[30]);
    window.draw(walls[31]);
    window.draw(walls[32]);
    window.draw(walls[33]);
    window.draw(walls[34]);
    window.draw(walls[35]);
    window.draw(walls[36]);
    window.draw(walls[37]);
    window.draw(walls[38]);
    window.draw(walls[39]);
    window.draw(walls[40]);
    window.draw(walls[41]);
    window.draw(walls[42]);
    window.draw(walls[43]);
    window.draw(walls[44]);
    window.draw(platforms[0]);
    window.draw(platforms[1]);
    window.draw(platforms[2]);
    window.draw(platforms[3]);
    window.draw(platforms[4]);
    window.draw(platforms[5]);
    window.draw(platforms[6]);
    window.draw(platforms[7]);
    window.draw(platforms[8]);
    window.draw(platforms[9]);
    window.draw(platforms[10]);
    window.draw(platforms[11]);
    window.draw(player);

    window.display();
}

int main() {
    // window
    sf::RenderWindow window(sf::VideoMode(LEVEL_WIDTH, LEVEL_HEIGHT),
                            "2D Platformer");
    window.setFramerateLimit(60);

    // player
    sf::Texture player_texture;
    if (!player_texture.loadFromFile("./assets/player/player.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }
    sf::Sprite player;
    player.setTexture(player_texture);
    player.scale(sf::Vector2f(25 / player.getLocalBounds().width,
                              25 / player.getLocalBounds().height));

    player.setPosition(0, LEVEL_HEIGHT - 250);

    sf::Texture wall_texture;
    if (!wall_texture.loadFromFile("./assets/tiles/tile1.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }

    sf::Sprite wall;
    wall.setTexture(wall_texture);
    wall.scale(sf::Vector2f(25 / wall.getLocalBounds().width,
                            25 / wall.getLocalBounds().height));

    sf::Texture platform_texture;
    if (!platform_texture.loadFromFile("./assets/tiles/tile2.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }

    sf::Sprite platform;
    platform.setTexture(platform_texture);
    platform.scale(sf::Vector2f(25 / platform.getLocalBounds().width,
                                25 / platform.getLocalBounds().height));

    // Scene Layout
    std::array<sf::Sprite, 45> walls = {
        wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall,
        wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall,
        wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall,
        wall, wall, wall, wall, wall, wall, wall, wall, wall};

    std::array<sf::Sprite, 12> platforms = {platform, platform, platform, platform,
                                platform, platform, platform, platform,
                                platform, platform, platform, platform};

    walls[0].setPosition(LEVEL_WIDTH - 25, LEVEL_HEIGHT - 25);
    walls[1].setPosition(LEVEL_WIDTH - 50, LEVEL_HEIGHT - 25);
    walls[2].setPosition(LEVEL_WIDTH - 75, LEVEL_HEIGHT - 25);
    walls[3].setPosition(LEVEL_WIDTH - 100, LEVEL_HEIGHT - 25);
    walls[4].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 25);
    walls[5].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 25);
    walls[6].setPosition(LEVEL_WIDTH - 175, LEVEL_HEIGHT - 25);
    walls[7].setPosition(LEVEL_WIDTH - 200, LEVEL_HEIGHT - 25);
    walls[8].setPosition(LEVEL_WIDTH - 225, LEVEL_HEIGHT - 25);
    walls[9].setPosition(LEVEL_WIDTH - 250, LEVEL_HEIGHT - 25);
    walls[10].setPosition(LEVEL_WIDTH - 275, LEVEL_HEIGHT - 25);
    walls[11].setPosition(LEVEL_WIDTH - 300, LEVEL_HEIGHT - 25);
    walls[12].setPosition(LEVEL_WIDTH - 325, LEVEL_HEIGHT - 25);
    walls[13].setPosition(LEVEL_WIDTH - 350, LEVEL_HEIGHT - 25);
    walls[14].setPosition(LEVEL_WIDTH - 375, LEVEL_HEIGHT - 25);
    walls[15].setPosition(LEVEL_WIDTH - 400, LEVEL_HEIGHT - 25);
    walls[16].setPosition(LEVEL_WIDTH - 425, LEVEL_HEIGHT - 25);
    walls[17].setPosition(LEVEL_WIDTH - 450, LEVEL_HEIGHT - 25);
    walls[18].setPosition(LEVEL_WIDTH - 475, LEVEL_HEIGHT - 25);
    walls[19].setPosition(LEVEL_WIDTH - 500, LEVEL_HEIGHT - 25);
    walls[20].setPosition(LEVEL_WIDTH - 525, LEVEL_HEIGHT - 25);
    walls[21].setPosition(LEVEL_WIDTH - 550, LEVEL_HEIGHT - 25);
    walls[22].setPosition(LEVEL_WIDTH - 575, LEVEL_HEIGHT - 25);
    walls[23].setPosition(LEVEL_WIDTH - 600, LEVEL_HEIGHT - 25);
    walls[24].setPosition(LEVEL_WIDTH - 625, LEVEL_HEIGHT - 25);
    walls[25].setPosition(LEVEL_WIDTH - 650, LEVEL_HEIGHT - 25);
    walls[26].setPosition(LEVEL_WIDTH - 675, LEVEL_HEIGHT - 25);
    walls[27].setPosition(LEVEL_WIDTH - 700, LEVEL_HEIGHT - 25);
    walls[28].setPosition(LEVEL_WIDTH - 725, LEVEL_HEIGHT - 25);
    walls[29].setPosition(LEVEL_WIDTH - 750, LEVEL_HEIGHT - 25);
    walls[30].setPosition(LEVEL_WIDTH - 550, LEVEL_HEIGHT - 100);
    walls[31].setPosition(LEVEL_WIDTH - 525, LEVEL_HEIGHT - 100);
    walls[32].setPosition(LEVEL_WIDTH - 500, LEVEL_HEIGHT - 100);
    walls[33].setPosition(LEVEL_WIDTH - 475, LEVEL_HEIGHT - 100);
    walls[34].setPosition(LEVEL_WIDTH - 450, LEVEL_HEIGHT - 100);
    walls[35].setPosition(LEVEL_WIDTH - 425, LEVEL_HEIGHT - 125);
    walls[36].setPosition(LEVEL_WIDTH - 400, LEVEL_HEIGHT - 125);
    walls[37].setPosition(LEVEL_WIDTH - 375, LEVEL_HEIGHT - 125);
    walls[38].setPosition(LEVEL_WIDTH - 350, LEVEL_HEIGHT - 125);
    walls[39].setPosition(LEVEL_WIDTH - 325, LEVEL_HEIGHT - 150);
    walls[40].setPosition(LEVEL_WIDTH - 300, LEVEL_HEIGHT - 175);
    walls[41].setPosition(LEVEL_WIDTH - 275, LEVEL_HEIGHT - 200);
    walls[42].setPosition(LEVEL_WIDTH - 250, LEVEL_HEIGHT - 200);
    walls[43].setPosition(LEVEL_WIDTH - 225, LEVEL_HEIGHT - 200);
    walls[44].setPosition(LEVEL_WIDTH - 200, LEVEL_HEIGHT - 200);

    platforms[0].setPosition(LEVEL_WIDTH - 600, LEVEL_HEIGHT - 50);
    platforms[1].setPosition(LEVEL_WIDTH - 575, LEVEL_HEIGHT - 75);
    platforms[2].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 175);
    platforms[3].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 175);
    platforms[4].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 150);
    platforms[5].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 150);
    platforms[6].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 125);
    platforms[7].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 125);
    platforms[8].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 100);
    platforms[9].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 100);
    platforms[10].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 75);
    platforms[11].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 75);

    PlayerSpeed player_speed{};
    player_speed.speed = 1.25;
    player_speed.accel = 5;

    CollisionState collision_state{};
    collision_state.on_the_floor = false;
    collision_state.on_the_platform = false;

    sf::Music music;
    if (!music.openFromFile("assets/music/free_from_hell.ogg")) {
        return -1;
    }

    const int volume = 50;
    music.setVolume(volume);

    music.setLoop(true);
    music.play();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up and
                    collision_state.on_the_floor) {
                    // jump
                    player.move(0.F, -player_speed.accel * 8);
                    collision_state.on_the_floor = false;
                    collision_state.on_the_platform = false;
                }
                if (event.key.code == sf::Keyboard::Down and
                    collision_state.on_the_floor and
                    collision_state.on_the_platform) {
                    // drop down
                    player.move(0.F, player_speed.accel);
                    collision_state.on_the_floor = false;
                    collision_state.on_the_platform = false;
                }
            }
        }

        MovePlayer(player, player_speed.speed);

        // Player Boundary
        sf::Vector2f player_position = PlayerBoundary(player.getPosition(), player.getGlobalBounds());
        player.setPosition(player_position);

        // Render Sprites
        DrawAllSprites(window, player, walls, platforms);

        // Gravity
        player_position.y = Gravity(player.getPosition(), player_speed.accel);
        player.setPosition(player_position);

        // Sprite Collisions
        PlayerSpriteCollisions(player, walls, platforms, &collision_state, player_speed);
    }

    return 0;
}
