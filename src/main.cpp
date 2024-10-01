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
                            std::array<sf::Sprite, 45> block_sprites,
                            std::array<sf::Sprite, 12> platform_sprites,
                            CollisionState *collision_state,
                            MotionSpeed motion_speed);

void DrawAllSprites(sf::RenderWindow &window, sf::Sprite &player,
                    std::array<sf::Sprite, 45> block_sprites,
                    std::array<sf::Sprite, 12> platform_sprites);

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

    sf::Texture block_texture;
    if (!block_texture.loadFromFile("./assets/tiles/tile1.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }

    sf::Sprite block_sprite;
    block_sprite.setTexture(block_texture);
    block_sprite.scale(sf::Vector2f(25 / block_sprite.getLocalBounds().width,
                                    25 / block_sprite.getLocalBounds().height));

    sf::Texture platform_texture;
    if (!platform_texture.loadFromFile("./assets/tiles/tile2.png")) {
        std::cout << "Unable to load image file" << std::endl;
    }

    sf::Sprite platform_sprite;
    platform_sprite.setTexture(platform_texture);
    platform_sprite.scale(
        sf::Vector2f(25 / platform_sprite.getLocalBounds().width,
                     25 / platform_sprite.getLocalBounds().height));

    // Scene Layout
    std::array<sf::Sprite, 45> block_sprites = {
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite,
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite,
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite,
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite,
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite,
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite,
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite,
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite,
        block_sprite, block_sprite, block_sprite, block_sprite, block_sprite};

    std::array<sf::Sprite, 12> platform_sprites = {
        platform_sprite, platform_sprite, platform_sprite, platform_sprite,
        platform_sprite, platform_sprite, platform_sprite, platform_sprite,
        platform_sprite, platform_sprite, platform_sprite, platform_sprite};

    block_sprites[0].setPosition(LEVEL_WIDTH - 25, LEVEL_HEIGHT - 25);
    block_sprites[1].setPosition(LEVEL_WIDTH - 50, LEVEL_HEIGHT - 25);
    block_sprites[2].setPosition(LEVEL_WIDTH - 75, LEVEL_HEIGHT - 25);
    block_sprites[3].setPosition(LEVEL_WIDTH - 100, LEVEL_HEIGHT - 25);
    block_sprites[4].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 25);
    block_sprites[5].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 25);
    block_sprites[6].setPosition(LEVEL_WIDTH - 175, LEVEL_HEIGHT - 25);
    block_sprites[7].setPosition(LEVEL_WIDTH - 200, LEVEL_HEIGHT - 25);
    block_sprites[8].setPosition(LEVEL_WIDTH - 225, LEVEL_HEIGHT - 25);
    block_sprites[9].setPosition(LEVEL_WIDTH - 250, LEVEL_HEIGHT - 25);
    block_sprites[10].setPosition(LEVEL_WIDTH - 275, LEVEL_HEIGHT - 25);
    block_sprites[11].setPosition(LEVEL_WIDTH - 300, LEVEL_HEIGHT - 25);
    block_sprites[12].setPosition(LEVEL_WIDTH - 325, LEVEL_HEIGHT - 25);
    block_sprites[13].setPosition(LEVEL_WIDTH - 350, LEVEL_HEIGHT - 25);
    block_sprites[14].setPosition(LEVEL_WIDTH - 375, LEVEL_HEIGHT - 25);
    block_sprites[15].setPosition(LEVEL_WIDTH - 400, LEVEL_HEIGHT - 25);
    block_sprites[16].setPosition(LEVEL_WIDTH - 425, LEVEL_HEIGHT - 25);
    block_sprites[17].setPosition(LEVEL_WIDTH - 450, LEVEL_HEIGHT - 25);
    block_sprites[18].setPosition(LEVEL_WIDTH - 475, LEVEL_HEIGHT - 25);
    block_sprites[19].setPosition(LEVEL_WIDTH - 500, LEVEL_HEIGHT - 25);
    block_sprites[20].setPosition(LEVEL_WIDTH - 525, LEVEL_HEIGHT - 25);
    block_sprites[21].setPosition(LEVEL_WIDTH - 550, LEVEL_HEIGHT - 25);
    block_sprites[22].setPosition(LEVEL_WIDTH - 575, LEVEL_HEIGHT - 25);
    block_sprites[23].setPosition(LEVEL_WIDTH - 600, LEVEL_HEIGHT - 25);
    block_sprites[24].setPosition(LEVEL_WIDTH - 625, LEVEL_HEIGHT - 25);
    block_sprites[25].setPosition(LEVEL_WIDTH - 650, LEVEL_HEIGHT - 25);
    block_sprites[26].setPosition(LEVEL_WIDTH - 675, LEVEL_HEIGHT - 25);
    block_sprites[27].setPosition(LEVEL_WIDTH - 700, LEVEL_HEIGHT - 25);
    block_sprites[28].setPosition(LEVEL_WIDTH - 725, LEVEL_HEIGHT - 25);
    block_sprites[29].setPosition(LEVEL_WIDTH - 750, LEVEL_HEIGHT - 25);
    block_sprites[30].setPosition(LEVEL_WIDTH - 550, LEVEL_HEIGHT - 100);
    block_sprites[31].setPosition(LEVEL_WIDTH - 525, LEVEL_HEIGHT - 100);
    block_sprites[32].setPosition(LEVEL_WIDTH - 500, LEVEL_HEIGHT - 100);
    block_sprites[33].setPosition(LEVEL_WIDTH - 475, LEVEL_HEIGHT - 100);
    block_sprites[34].setPosition(LEVEL_WIDTH - 450, LEVEL_HEIGHT - 100);
    block_sprites[35].setPosition(LEVEL_WIDTH - 425, LEVEL_HEIGHT - 125);
    block_sprites[36].setPosition(LEVEL_WIDTH - 400, LEVEL_HEIGHT - 125);
    block_sprites[37].setPosition(LEVEL_WIDTH - 375, LEVEL_HEIGHT - 125);
    block_sprites[38].setPosition(LEVEL_WIDTH - 350, LEVEL_HEIGHT - 125);
    block_sprites[39].setPosition(LEVEL_WIDTH - 325, LEVEL_HEIGHT - 150);
    block_sprites[40].setPosition(LEVEL_WIDTH - 300, LEVEL_HEIGHT - 175);
    block_sprites[41].setPosition(LEVEL_WIDTH - 275, LEVEL_HEIGHT - 200);
    block_sprites[42].setPosition(LEVEL_WIDTH - 250, LEVEL_HEIGHT - 200);
    block_sprites[43].setPosition(LEVEL_WIDTH - 225, LEVEL_HEIGHT - 200);
    block_sprites[44].setPosition(LEVEL_WIDTH - 200, LEVEL_HEIGHT - 200);

    platform_sprites[0].setPosition(LEVEL_WIDTH - 600, LEVEL_HEIGHT - 50);
    platform_sprites[1].setPosition(LEVEL_WIDTH - 575, LEVEL_HEIGHT - 75);
    platform_sprites[2].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 175);
    platform_sprites[3].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 175);
    platform_sprites[4].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 150);
    platform_sprites[5].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 150);
    platform_sprites[6].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 125);
    platform_sprites[7].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 125);
    platform_sprites[8].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 100);
    platform_sprites[9].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 100);
    platform_sprites[10].setPosition(LEVEL_WIDTH - 150, LEVEL_HEIGHT - 75);
    platform_sprites[11].setPosition(LEVEL_WIDTH - 125, LEVEL_HEIGHT - 75);

    MotionState motion_state;
    motion_state.jump = false;
    motion_state.jump_frames = 0;

    MotionSpeed motion_speed;
    motion_speed.speed = player_speed;
    motion_speed.accel = player_accel;

    CollisionState collision_state;
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
        DrawAllSprites(window, player.sprite, block_sprites, platform_sprites);

        // Gravity
        Gravity(&player.sprite, player.motion_speed.accel);

        // Jump physics
        JumpPhysics(&player.sprite, &player.motion_state, player.motion_speed);

        // Sprite Collisions
        PlayerSpriteCollisions(&player.sprite, block_sprites, platform_sprites,
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
                            std::array<sf::Sprite, 45> block_sprites,
                            std::array<sf::Sprite, 12> platform_sprites,
                            CollisionState *collision_state,
                            MotionSpeed motion_speed) {
    PlayerBlockCollision(player_sprite, block_sprites[0], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[1], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[2], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[3], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[4], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[5], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[6], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[7], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[8], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[9], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[10], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[11], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[12], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[13], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[14], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[15], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[16], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[17], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[18], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[19], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[20], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[21], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[22], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[23], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[24], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[25], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[26], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[27], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[28], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[29], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[30], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[31], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[32], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[33], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[34], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[35], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[36], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[37], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[38], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[39], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[40], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[41], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[42], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[43], collision_state,
                         motion_speed);
    PlayerBlockCollision(player_sprite, block_sprites[44], collision_state,
                         motion_speed);

    PlayerPlatformCollision(player_sprite, platform_sprites[0], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[1], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[2], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[3], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[4], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[5], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[6], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[7], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[8], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[9], collision_state,
                            motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[10],
                            collision_state, motion_speed.accel);
    PlayerPlatformCollision(player_sprite, platform_sprites[11],
                            collision_state, motion_speed.accel);
}

void DrawAllSprites(sf::RenderWindow &window, sf::Sprite &player_sprite,
                    std::array<sf::Sprite, 45> block_sprites,
                    std::array<sf::Sprite, 12> platform_sprites) {
    window.clear(sf::Color(84, 193, 255, 255));

    window.draw(block_sprites[0]);
    window.draw(block_sprites[1]);
    window.draw(block_sprites[2]);
    window.draw(block_sprites[3]);
    window.draw(block_sprites[4]);
    window.draw(block_sprites[5]);
    window.draw(block_sprites[6]);
    window.draw(block_sprites[7]);
    window.draw(block_sprites[8]);
    window.draw(block_sprites[9]);
    window.draw(block_sprites[10]);
    window.draw(block_sprites[11]);
    window.draw(block_sprites[12]);
    window.draw(block_sprites[13]);
    window.draw(block_sprites[14]);
    window.draw(block_sprites[15]);
    window.draw(block_sprites[16]);
    window.draw(block_sprites[17]);
    window.draw(block_sprites[18]);
    window.draw(block_sprites[19]);
    window.draw(block_sprites[20]);
    window.draw(block_sprites[21]);
    window.draw(block_sprites[22]);
    window.draw(block_sprites[23]);
    window.draw(block_sprites[24]);
    window.draw(block_sprites[25]);
    window.draw(block_sprites[26]);
    window.draw(block_sprites[27]);
    window.draw(block_sprites[28]);
    window.draw(block_sprites[29]);
    window.draw(block_sprites[30]);
    window.draw(block_sprites[31]);
    window.draw(block_sprites[32]);
    window.draw(block_sprites[33]);
    window.draw(block_sprites[34]);
    window.draw(block_sprites[35]);
    window.draw(block_sprites[36]);
    window.draw(block_sprites[37]);
    window.draw(block_sprites[38]);
    window.draw(block_sprites[39]);
    window.draw(block_sprites[40]);
    window.draw(block_sprites[41]);
    window.draw(block_sprites[42]);
    window.draw(block_sprites[43]);
    window.draw(block_sprites[44]);
    window.draw(platform_sprites[0]);
    window.draw(platform_sprites[1]);
    window.draw(platform_sprites[2]);
    window.draw(platform_sprites[3]);
    window.draw(platform_sprites[4]);
    window.draw(platform_sprites[5]);
    window.draw(platform_sprites[6]);
    window.draw(platform_sprites[7]);
    window.draw(platform_sprites[8]);
    window.draw(platform_sprites[9]);
    window.draw(platform_sprites[10]);
    window.draw(platform_sprites[11]);
    window.draw(player_sprite);

    window.display();
}
