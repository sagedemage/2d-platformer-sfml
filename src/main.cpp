#include <iostream>

#define LEVEL_WIDTH 750
#define LEVEL_HEIGHT 500

struct CollisionState {
    bool on_the_floor;
    bool on_the_platform;
};

sf::Vector2f player_boundary(sf::Vector2f position) {
    if (position.x + 25 >= 750.f) {
        /* Right boundary */
        position.x = float(LEVEL_WIDTH - 25);
    } else if (position.x <= 0.f) {
        /* Left  boundary */
        position.x = 0.f;
    }
    if (position.y <= 0.f) {
        /* Top boudnary */
        position.y = 0.f;
    } else if (position.y + 25 >= LEVEL_HEIGHT) {
        /* Bottom boudnary */
        position.y = float(LEVEL_HEIGHT - 25);
    }
    return position;
}

void movePlayer(sf::Sprite& player, float speed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        // move player left
        player.move(-speed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        // move player right
        player.move(speed, 0.f);
    }
}

CollisionState playerWallCollision(sf::Sprite& player, sf::Sprite& wall,
                                   CollisionState collisionState, float accel,
                                   float speed) {
    sf::Vector2f p_position = player.getPosition();
    int offset = 5;
    /* X Axis Collision */
    if (player.getPosition().y > wall.getPosition().y + offset &&
        player.getPosition().y < wall.getPosition().y + 25 - offset) {
        if (player.getPosition().x + 25 > wall.getPosition().x &&
            player.getPosition().x + 25 < wall.getPosition().x + 25) {
            // left collision
            p_position.x -= speed;
            player.setPosition(p_position);
        } else if (player.getPosition().x < wall.getPosition().x + 25 &&
                   player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x += speed;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().y + 25 > wall.getPosition().y + offset &&
             player.getPosition().y + 25 < wall.getPosition().y + 25 - offset) {
        if (player.getPosition().x + 25 > wall.getPosition().x &&
            player.getPosition().x + 25 < wall.getPosition().x + 25) {
            // left collision
            p_position.x -= speed;
            player.setPosition(p_position);
        } else if (player.getPosition().x < wall.getPosition().x + 25 &&
                   player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x += speed;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().y + 25 / 2 > wall.getPosition().y &&
             player.getPosition().y + 25 / 2 < wall.getPosition().y + 25) {
        if (player.getPosition().x + 25 > wall.getPosition().x &&
            player.getPosition().x + 25 < wall.getPosition().x + 25) {
            // left collision
            p_position.x -= speed;
            player.setPosition(p_position);
        } else if (player.getPosition().x < wall.getPosition().x + 25 &&
                   player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x += speed;
            player.setPosition(p_position);
        }
    }

    /* Y Axis Collision */
    if (player.getPosition().x > wall.getPosition().x &&
        player.getPosition().x < wall.getPosition().x + 25) {
        if (player.getPosition().y + 25 > wall.getPosition().y &&
            player.getPosition().y + 25 < wall.getPosition().y + 25) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collisionState.on_the_floor = true;
        } else if (player.getPosition().y < wall.getPosition().y + 25 &&
                   player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y += accel;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().x + 25 > wall.getPosition().x &&
             player.getPosition().x + 25 < wall.getPosition().x + 25) {
        if (player.getPosition().y + 25 > wall.getPosition().y &&
            player.getPosition().y + 25 < wall.getPosition().y + 25) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collisionState.on_the_floor = true;
        } else if (player.getPosition().y < wall.getPosition().y + 25 &&
                   player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y += accel;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().x + 25 / 2 > wall.getPosition().x &&
             player.getPosition().x + 25 / 2 < wall.getPosition().x + 25) {
        if (player.getPosition().y + 25 > wall.getPosition().y &&
            player.getPosition().y + 25 < wall.getPosition().y + 25) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collisionState.on_the_floor = true;
        } else if (player.getPosition().y < wall.getPosition().y + 25 &&
                   player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y += accel;
            player.setPosition(p_position);
        }
    }
    return collisionState;
}

CollisionState playerPlatformCollision(sf::Sprite& player, sf::Sprite& platform,
                                       CollisionState collisionState,
                                       float accel) {
    sf::Vector2f p_position = player.getPosition();

    /* Y Axis Collision */
    if (player.getPosition().x > platform.getPosition().x &&
        player.getPosition().x < platform.getPosition().x + 25) {
        if (player.getPosition().y + 25 > platform.getPosition().y &&
            player.getPosition().y + 25 <
                platform.getPosition().y + 2 * accel) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collisionState.on_the_floor = true;
            collisionState.on_the_platform = true;
        }
    }

    else if (player.getPosition().x + 25 > platform.getPosition().x &&
             player.getPosition().x + 25 < platform.getPosition().x + 25) {
        if (player.getPosition().y + 25 > platform.getPosition().y &&
            player.getPosition().y + 25 <
                platform.getPosition().y + 2 * accel) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collisionState.on_the_floor = true;
            collisionState.on_the_platform = true;
        }
    }

    else if (player.getPosition().x + 25 / 2 > platform.getPosition().x &&
             player.getPosition().x + 25 / 2 < platform.getPosition().x + 25) {
        if (player.getPosition().y + 25 > platform.getPosition().y &&
            player.getPosition().y + 25 <
                platform.getPosition().y + 2 * accel) {
            // top collision
            p_position.y -= accel;
            player.setPosition(p_position);
            collisionState.on_the_floor = true;
            collisionState.on_the_platform = true;
        }
    }
    return collisionState;
}

float gravity(sf::Vector2f position, float accel) {
    position.y += accel;

    return position.y;
}

CollisionState playerSpriteCollisions(sf::Sprite& player, sf::Sprite walls[45],
                                      sf::Sprite platforms[12],
                                      CollisionState collisionState,
                                      float accel, float speed) {
    collisionState =
        playerWallCollision(player, walls[0], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[1], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[2], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[3], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[4], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[5], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[6], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[7], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[8], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[9], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[10], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[11], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[12], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[13], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[14], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[15], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[16], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[17], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[18], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[19], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[20], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[21], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[22], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[23], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[24], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[25], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[26], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[27], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[28], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[29], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[30], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[31], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[32], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[33], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[34], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[35], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[36], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[37], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[38], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[39], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[40], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[41], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[42], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[43], collisionState, accel, speed);
    collisionState =
        playerWallCollision(player, walls[44], collisionState, accel, speed);

    collisionState =
        playerPlatformCollision(player, platforms[0], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[1], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[2], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[3], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[4], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[5], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[6], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[7], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[8], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[9], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[10], collisionState, accel);
    collisionState =
        playerPlatformCollision(player, platforms[11], collisionState, accel);

    return collisionState;
}

void drawAllSprites(sf::RenderWindow& window, sf::Sprite& player,
                    sf::Sprite walls[45], sf::Sprite platforms[12]) {
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
    sf::Sprite walls[45] = {
        wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall,
        wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall,
        wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall,
        wall, wall, wall, wall, wall, wall, wall, wall, wall};

    sf::Sprite platforms[12] = {platform, platform, platform, platform,
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

    const float speed = 1.25;
    const float accel = 5;

    CollisionState collisionState;
    collisionState.on_the_floor = false;
    collisionState.on_the_platform = false;

    sf::Music music;
    if (!music.openFromFile("assets/music/free_from_hell.ogg")) {
        return -1;
    }

    const int volume = 50;
    music.setVolume(volume);

    music.setLoop(true);
    music.play();

#pragma unroll
    while (window.isOpen()) {
        sf::Event event;
#pragma unroll
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
                    collisionState.on_the_floor == true) {
                    // jump
                    player.move(0.f, -accel * 8);
                    collisionState.on_the_floor = false;
                    collisionState.on_the_platform = false;
                }
                if (event.key.code == sf::Keyboard::Down and
                    collisionState.on_the_floor == true and
                    collisionState.on_the_platform == true) {
                    // drop down
                    player.move(0.f, accel);
                    collisionState.on_the_floor = false;
                    collisionState.on_the_platform = false;
                }
            }
        }

        movePlayer(player, speed);

        // Player Boundary
        sf::Vector2f player_position = player_boundary(player.getPosition());
        player.setPosition(player_position);

        // Render Sprites
        drawAllSprites(window, player, walls, platforms);

        // Gravity
        player_position.y = gravity(player.getPosition(), accel);
        player.setPosition(player_position);

        // Sprite Collisions
        collisionState = playerSpriteCollisions(player, walls, platforms,
                                                collisionState, accel, speed);
    }

    return 0;
}
