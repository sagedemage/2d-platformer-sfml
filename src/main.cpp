/* Standard libraries */
#include <array>
#include <iostream>

/* Global header files */
#include "engine/entities.hpp"

/* Local header files */
#include "engine/collision.hpp"
#include "engine/physics.hpp"
#include "keybindings/keybindings.hpp"

constexpr unsigned LEVEL_WIDTH = 750;
constexpr unsigned LEVEL_HEIGHT = 500;

/* Function Declarations */
sf::Vector2f PlayerBoundary(sf::Vector2f position, sf::FloatRect global_bounds);

void PlayerSpriteCollisions(sf::Sprite *player,
                            std::array<sf::Sprite, 45> walls,
                            std::array<sf::Sprite, 12> platforms,
                            CollisionState *collision_state,
                            MotionSpeed motion_speed);

void DrawAllSprites(sf::RenderWindow &window, sf::Sprite &player,
                    std::array<sf::Sprite, 45> walls,
                    std::array<sf::Sprite, 12> platforms);

int main() {
    const float player_speed = 1.25;
    const float player_accel = 2.5;

    // window
    sf::RenderWindow window(sf::VideoMode(LEVEL_WIDTH, LEVEL_HEIGHT),
                            "2D Platformer");
    window.setFramerateLimit(60);

    // player
    sf::Texture player_texture;
    if (!player_texture.loadFromFile("./assets/player/player.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }
    sf::Sprite player_sprite;
    player_sprite.setTexture(player_texture);
    player_sprite.scale(
        sf::Vector2f(25 / player_sprite.getLocalBounds().width,
                     25 / player_sprite.getLocalBounds().height));

    player_sprite.setPosition(0, LEVEL_HEIGHT - 250);

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

    std::array<sf::Sprite, 12> platforms = {
        platform, platform, platform, platform, platform, platform,
        platform, platform, platform, platform, platform, platform};

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

    MotionState motion_state;
    motion_state.jump = false;
    motion_state.jump_frames = 0;

    MotionSpeed motion_speed{};
    motion_speed.speed = player_speed;
    motion_speed.accel = player_accel;

    CollisionState collision_state{};
    collision_state.on_the_floor = false;
    collision_state.on_the_platform = false;

    Player player;
    player.motion_state = motion_state;
    player.collision_state = collision_state;
    player.motion_speed = motion_speed;
    player.sprite = player_sprite;

    unsigned int joystick_num = 0;
    if (sf::Joystick::isConnected(joystick_num)) {
        std::cout << "Joystick number " + std::to_string(joystick_num) +
                         " is connected!"
                  << std::endl;
    }

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

            ClickKeybindings(event, &player.sprite, &player.motion_state,
                             &player.collision_state, player.motion_speed,
                             joystick_num);
        }

        HoldKeybindings(&player.sprite, player.motion_speed, joystick_num);

        // Player Boundary
        sf::Vector2f player_position = PlayerBoundary(
            player.sprite.getPosition(), player_sprite.getGlobalBounds());
        player.sprite.setPosition(player_position);

        // Render Sprites
        DrawAllSprites(window, player.sprite, walls, platforms);

        // Gravity
        Gravity(&player.sprite, player.motion_speed.accel);

        // Jump physics
        JumpPhysics(&player.sprite, &player.motion_state, player.motion_speed);

        // Sprite Collisions
        PlayerSpriteCollisions(&player.sprite, walls, platforms,
                               &player.collision_state, player.motion_speed);
    }

    return 0;
}

sf::Vector2f PlayerBoundary(sf::Vector2f position,
                            sf::FloatRect global_bounds) {
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

void PlayerSpriteCollisions(sf::Sprite *player_sprite,
                            std::array<sf::Sprite, 45> walls,
                            std::array<sf::Sprite, 12> platforms,
                            CollisionState *collision_state,
                            MotionSpeed motion_speed) {
    PlayerWallCollision(player_sprite, walls[0], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[1], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[2], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[3], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[4], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[5], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[6], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[7], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[8], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[9], collision_state, motion_speed);
    PlayerWallCollision(player_sprite, walls[10], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[11], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[12], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[13], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[14], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[15], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[16], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[17], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[18], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[19], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[20], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[21], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[22], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[23], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[24], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[25], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[26], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[27], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[28], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[29], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[30], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[31], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[32], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[33], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[34], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[35], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[36], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[37], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[38], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[39], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[40], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[41], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[42], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[43], collision_state,
                        motion_speed);
    PlayerWallCollision(player_sprite, walls[44], collision_state,
                        motion_speed);

    PlayerPlatformCollision(player_sprite, platforms[0], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[1], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[2], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[3], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[4], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[5], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[6], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[7], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[8], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[9], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[10], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platforms[11], collision_state,
                            motion_speed.accel);
}

void DrawAllSprites(sf::RenderWindow &window, sf::Sprite &player_sprite,
                    std::array<sf::Sprite, 45> walls,
                    std::array<sf::Sprite, 12> platforms) {
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
    window.draw(player_sprite);

    window.display();
}
