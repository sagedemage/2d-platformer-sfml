#include <iostream>

#define LEVEL_WIDTH 750
#define LEVEL_HEIGHT 500

sf::Vector2f player_boundary(sf::Vector2f position) {
    if (position.x+25 >= 750.f)
    {
        /* Right boundary */
        position.x = float(LEVEL_WIDTH - 25);
    }
    else if (position.x <= 0.f)
    {
        /* Left  boundary */
        position.x = 0.f;
    }
    if (position.y <= 0.f)
    {
        /* Top boudnary */
        position.y = 0.f;
    }
    else if (position.y+25 >= LEVEL_HEIGHT)
    {
        /* Bottom boudnary */
        position.y = float(LEVEL_HEIGHT - 25);
    }
    return position;
}

void movePlayer(sf::Sprite& player, int speed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // move player left
        player.move(-speed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // move player right
        player.move(speed, 0.f);
    }
}

bool playerWallCollision(sf::Sprite& player, sf::Sprite& wall, bool on_the_floor, int accel) {

    sf::Vector2f p_position = player.getPosition();
    int offset = 2;
    /* X Axis Collision */
    if (player.getPosition().y > wall.getPosition().y+offset &&
        player.getPosition().y < wall.getPosition().y + 25-offset) {
        if (player.getPosition().x+25 >= wall.getPosition().x &&
            player.getPosition().x+25 < wall.getPosition().x +25) {
            // left collision
            p_position.x-=2;
            player.setPosition(p_position);
        }
        else if (player.getPosition().x <= wall.getPosition().x+25 &&
            player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x+=2;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().y + 25 > wall.getPosition().y+offset &&
        player.getPosition().y + 25 < wall.getPosition().y + 25-offset) {
        if (player.getPosition().x+25 >= wall.getPosition().x &&
            player.getPosition().x+25 < wall.getPosition().x +25) {
            // left collision
            p_position.x-=2;
            player.setPosition(p_position);
        }
        else if (player.getPosition().x <= wall.getPosition().x+25 &&
            player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x+=2;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().y + 25/2 > wall.getPosition().y &&
        player.getPosition().y + 25/2 < wall.getPosition().y + 25) {
        if (player.getPosition().x+25 >= wall.getPosition().x &&
            player.getPosition().x+25 < wall.getPosition().x +25) {
            // left collision
            p_position.x-=2;
            player.setPosition(p_position);
        }
        else if (player.getPosition().x <= wall.getPosition().x+25 &&
            player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x+=2;
            player.setPosition(p_position);
        }
    }

    /* Y Axis Collision */
    if (player.getPosition().x > wall.getPosition().x &&
        player.getPosition().x < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y+25) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
        else if (player.getPosition().y <= wall.getPosition().y+25 &&
            player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y+=accel;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().x + 25 > wall.getPosition().x &&
        player.getPosition().x + 25 < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y +25) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
        else if (player.getPosition().y <= wall.getPosition().y+25 &&
            player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y+=accel;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().x + 25/2 > wall.getPosition().x &&
        player.getPosition().x + 25/2 < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y +25) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
        else if (player.getPosition().y <= wall.getPosition().y+25 &&
            player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y+=accel;
            player.setPosition(p_position);
        }
    }
    return on_the_floor;
}

bool playerPlatformCollision(sf::Sprite& player, sf::Sprite& platform, bool on_the_floor, int accel) {

    sf::Vector2f p_position = player.getPosition();

    /* Y Axis Collision */
    if (player.getPosition().x > platform.getPosition().x &&
        player.getPosition().x < platform.getPosition().x + 25) {
        if (player.getPosition().y+25 >= platform.getPosition().y &&
            player.getPosition().y+25 < platform.getPosition().y+accel) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
    }

    else if (player.getPosition().x + 25 > platform.getPosition().x &&
        player.getPosition().x + 25 < platform.getPosition().x + 25) {
        if (player.getPosition().y+25 >= platform.getPosition().y &&
            player.getPosition().y+25 < platform.getPosition().y+accel) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
    }

    else if (player.getPosition().x + 25/2 > platform.getPosition().x &&
        player.getPosition().x + 25/2 < platform.getPosition().x + 25) {
        if (player.getPosition().y+25 >= platform.getPosition().y &&
            player.getPosition().y+25 < platform.getPosition().y+accel) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
    }
    return on_the_floor;
}

int gravity(sf::Vector2f position, int accel) {
    position.y += accel;

    return position.y;
}

bool drawAllRegions(sf::RenderWindow& window, sf::Sprite& player, sf::Sprite& wall,
    sf::Sprite& platform, bool on_the_floor, int accel) {

    sf::Sprite wall1 = wall, wall2 = wall, wall3 = wall, wall4 = wall, wall5 = wall;
    sf::Sprite wall6 = wall, wall7 = wall, wall8 = wall, wall9 = wall, wall10 = wall;
    sf::Sprite wall11 = wall, wall12 = wall, wall13 = wall, wall14 = wall, wall15 = wall;
    sf::Sprite wall16 = wall, wall17 = wall, wall18 = wall, wall19 = wall, wall20 = wall;
    sf::Sprite wall21 = wall, wall22 = wall, wall23 = wall, wall24 = wall, wall25 = wall;
    sf::Sprite wall26 = wall, wall27 = wall, wall28 = wall, wall29 = wall, wall30 = wall;
    sf::Sprite wall31 = wall, wall32 = wall, wall33 = wall, wall34 = wall, wall35 = wall;
    sf::Sprite wall36 = wall, wall37 = wall, wall38 = wall, wall39 = wall, wall40 = wall;
    sf::Sprite wall41 = wall, wall42 = wall, wall43 = wall, wall44 = wall, wall45 = wall;

    sf::Sprite platform1 = platform, platform2 = platform, platform3 = platform, platform4 = platform;
    sf::Sprite platform5 = platform, platform6 = platform, platform7 = platform, platform8 = platform;
    sf::Sprite platform9 = platform, platform10 = platform, platform11 = platform, platform12 = platform;

    wall1.setPosition(LEVEL_WIDTH-25, LEVEL_HEIGHT-25);
    wall2.setPosition(LEVEL_WIDTH-50, LEVEL_HEIGHT-25);
    wall3.setPosition(LEVEL_WIDTH-75, LEVEL_HEIGHT-25);
    wall4.setPosition(LEVEL_WIDTH-100, LEVEL_HEIGHT-25);
    wall5.setPosition(LEVEL_WIDTH-125, LEVEL_HEIGHT-25);
    wall6.setPosition(LEVEL_WIDTH-150, LEVEL_HEIGHT-25);
    wall7.setPosition(LEVEL_WIDTH-175, LEVEL_HEIGHT-25);
    wall8.setPosition(LEVEL_WIDTH-200, LEVEL_HEIGHT-25);
    wall9.setPosition(LEVEL_WIDTH-225, LEVEL_HEIGHT-25);
    wall10.setPosition(LEVEL_WIDTH-250, LEVEL_HEIGHT-25);
    wall11.setPosition(LEVEL_WIDTH-275, LEVEL_HEIGHT-25);
    wall12.setPosition(LEVEL_WIDTH-300, LEVEL_HEIGHT-25);
    wall13.setPosition(LEVEL_WIDTH-325, LEVEL_HEIGHT-25);
    wall14.setPosition(LEVEL_WIDTH-350, LEVEL_HEIGHT-25);
    wall15.setPosition(LEVEL_WIDTH-375, LEVEL_HEIGHT-25);
    wall16.setPosition(LEVEL_WIDTH-400, LEVEL_HEIGHT-25);
    wall17.setPosition(LEVEL_WIDTH-425, LEVEL_HEIGHT-25);
    wall18.setPosition(LEVEL_WIDTH-450, LEVEL_HEIGHT-25);
    wall19.setPosition(LEVEL_WIDTH-475, LEVEL_HEIGHT-25);
    wall20.setPosition(LEVEL_WIDTH-500, LEVEL_HEIGHT-25);
    wall21.setPosition(LEVEL_WIDTH-525, LEVEL_HEIGHT-25);
    wall22.setPosition(LEVEL_WIDTH-550, LEVEL_HEIGHT-25);
    wall23.setPosition(LEVEL_WIDTH-575, LEVEL_HEIGHT-25);
    wall24.setPosition(LEVEL_WIDTH-600, LEVEL_HEIGHT-25);
    wall25.setPosition(LEVEL_WIDTH-625, LEVEL_HEIGHT-25);
    wall26.setPosition(LEVEL_WIDTH-650, LEVEL_HEIGHT-25);
    wall27.setPosition(LEVEL_WIDTH-675, LEVEL_HEIGHT-25);
    wall28.setPosition(LEVEL_WIDTH-700, LEVEL_HEIGHT-25);
    wall29.setPosition(LEVEL_WIDTH-725, LEVEL_HEIGHT-25);
    wall30.setPosition(LEVEL_WIDTH-750, LEVEL_HEIGHT-25);
    wall31.setPosition(LEVEL_WIDTH-550, LEVEL_HEIGHT-100);
    wall32.setPosition(LEVEL_WIDTH-525, LEVEL_HEIGHT-100);
    wall33.setPosition(LEVEL_WIDTH-500, LEVEL_HEIGHT-100);
    wall34.setPosition(LEVEL_WIDTH-475, LEVEL_HEIGHT-100);
    wall35.setPosition(LEVEL_WIDTH-450, LEVEL_HEIGHT-100);
    wall36.setPosition(LEVEL_WIDTH-425, LEVEL_HEIGHT-125);
    wall37.setPosition(LEVEL_WIDTH-400, LEVEL_HEIGHT-125);
    wall38.setPosition(LEVEL_WIDTH-375, LEVEL_HEIGHT-125);
    wall39.setPosition(LEVEL_WIDTH-350, LEVEL_HEIGHT-125);
    wall40.setPosition(LEVEL_WIDTH-325, LEVEL_HEIGHT-150);
    wall41.setPosition(LEVEL_WIDTH-300, LEVEL_HEIGHT-175);
    wall42.setPosition(LEVEL_WIDTH-275, LEVEL_HEIGHT-200);
    wall43.setPosition(LEVEL_WIDTH-250, LEVEL_HEIGHT-200);
    wall44.setPosition(LEVEL_WIDTH-225, LEVEL_HEIGHT-200);
    wall45.setPosition(LEVEL_WIDTH-200, LEVEL_HEIGHT-200);

    platform1.setPosition(LEVEL_WIDTH-600, LEVEL_HEIGHT-50);
    platform2.setPosition(LEVEL_WIDTH-575, LEVEL_HEIGHT-75);
    platform3.setPosition(LEVEL_WIDTH-150, LEVEL_HEIGHT-175);
    platform4.setPosition(LEVEL_WIDTH-125, LEVEL_HEIGHT-175);
    platform5.setPosition(LEVEL_WIDTH-150, LEVEL_HEIGHT-150);
    platform6.setPosition(LEVEL_WIDTH-125, LEVEL_HEIGHT-150);
    platform7.setPosition(LEVEL_WIDTH-150, LEVEL_HEIGHT-125);
    platform8.setPosition(LEVEL_WIDTH-125, LEVEL_HEIGHT-125);
    platform9.setPosition(LEVEL_WIDTH-150, LEVEL_HEIGHT-100);
    platform10.setPosition(LEVEL_WIDTH-125, LEVEL_HEIGHT-100);
    platform11.setPosition(LEVEL_WIDTH-150, LEVEL_HEIGHT-75);
    platform12.setPosition(LEVEL_WIDTH-125, LEVEL_HEIGHT-75);

    window.clear(sf::Color(84, 193, 255, 255));

    window.draw(wall1);
    window.draw(wall2);
    window.draw(wall3);
    window.draw(wall4);
    window.draw(wall5);
    window.draw(wall6);
    window.draw(wall7);
    window.draw(wall8);
    window.draw(wall9);
    window.draw(wall10);
    window.draw(wall11);
    window.draw(wall12);
    window.draw(wall13);
    window.draw(wall14);
    window.draw(wall15);
    window.draw(wall16);
    window.draw(wall17);
    window.draw(wall18);
    window.draw(wall19);
    window.draw(wall20);
    window.draw(wall21);
    window.draw(wall22);
    window.draw(wall23);
    window.draw(wall24);
    window.draw(wall25);
    window.draw(wall26);
    window.draw(wall27);
    window.draw(wall28);
    window.draw(wall29);
    window.draw(wall30);
    window.draw(wall31);
    window.draw(wall32);
    window.draw(wall33);
    window.draw(wall34);
    window.draw(wall35);
    window.draw(wall36);
    window.draw(wall37);
    window.draw(wall38);
    window.draw(wall39);
    window.draw(wall40);
    window.draw(wall41);
    window.draw(wall42);
    window.draw(wall43);
    window.draw(wall44);
    window.draw(wall45);
    window.draw(platform1);
    window.draw(platform2);
    window.draw(platform3);
    window.draw(platform4);
    window.draw(platform5);
    window.draw(platform6);
    window.draw(platform7);
    window.draw(platform8);
    window.draw(platform9);
    window.draw(platform10);
    window.draw(platform11);
    window.draw(platform12);
    window.draw(player);

    window.display();

    on_the_floor = playerWallCollision(player, wall1, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall2, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall3, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall4, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall5, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall6, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall7, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall8, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall9, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall10, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall11, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall12, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall13, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall14, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall15, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall16, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall17, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall18, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall19, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall20, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall21, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall22, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall23, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall24, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall25, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall26, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall27, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall28, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall29, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall30, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall31, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall32, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall33, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall34, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall35, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall36, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall37, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall38, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall39, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall40, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall41, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall42, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall43, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall44, on_the_floor, accel);
    on_the_floor = playerWallCollision(player, wall45, on_the_floor, accel);

    on_the_floor = playerPlatformCollision(player, platform1, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform2, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform3, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform4, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform5, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform6, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform7, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform8, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform9, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform10, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform11, on_the_floor, accel);
    on_the_floor = playerPlatformCollision(player, platform12, on_the_floor, accel);

    return on_the_floor;
}

int main()
{
    // window
    sf::RenderWindow window(sf::VideoMode(LEVEL_WIDTH, LEVEL_HEIGHT), "2D Platformer");
    window.setFramerateLimit(60);

    // player
    sf::Texture player_texture;
    if(!player_texture.loadFromFile("./assets/player/player.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }
    sf::Sprite player;
    player.setTexture(player_texture);
    player.scale(sf::Vector2f(25/player.getLocalBounds().width, 25/player.getLocalBounds().height));

    player.setPosition(0, LEVEL_HEIGHT-250);

    sf::Texture wall_texture;
    if(!wall_texture.loadFromFile("./assets/tiles/tile1.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }

    sf::Sprite wall;
    wall.setTexture(wall_texture);
    wall.scale(sf::Vector2f(25/wall.getLocalBounds().width, 25/wall.getLocalBounds().height));

    sf::Texture platform_texture;
    if(!platform_texture.loadFromFile("./assets/tiles/tile2.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }

    sf::Sprite platform;
    platform.setTexture(platform_texture);
    platform.scale(sf::Vector2f(25/platform.getLocalBounds().width, 25/platform.getLocalBounds().height));

    const float speed = 2.f;
    const int accel = 5;
    bool on_the_floor = false;

    sf::Music music;
    if (!music.openFromFile("assets/music/empty.ogg")) {
        return -1;
    }

    const int volume = 50;
    music.setVolume(volume);

    music.setLoop(true);
    music.play();

#pragma unroll
    while (window.isOpen())
    {
        sf::Event event;
#pragma unroll
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up and on_the_floor == true)
                {
                    // jump
                    player.move(0.f, -accel*8);
                    on_the_floor = false;
                }
                if (event.key.code == sf::Keyboard::Down and on_the_floor == true)
                {
                    // drop down
                    player.move(0.f, accel);
                    on_the_floor = false;
                }
            }
        }

        movePlayer(player, speed);

        // Player Boundary
        sf::Vector2f player_position = player_boundary(player.getPosition());
        player.setPosition(player_position);

        // Gravity
        player_position.y = gravity(player.getPosition(), accel);
        player.setPosition(player_position);

        on_the_floor = drawAllRegions(window, player, wall, platform, on_the_floor, accel);
    }

    return 0;
}
