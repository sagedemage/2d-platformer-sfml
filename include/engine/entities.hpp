#ifndef ENTITIES_HPP
#define ENTITIES_HPP

typedef struct CollisionState {
    bool on_the_floor;
    bool on_the_platform;
} CollisionState;

typedef struct MotionState {
    bool jump;
    int jump_frames;
} MotionState;

typedef struct MotionSpeed {
    float speed;
    float accel;
} MotionSpeed;

typedef struct Player {
    CollisionState collision_state{};
    MotionState motion_state{};
    MotionSpeed motion_speed{};
    sf::Sprite sprite;
} Player;

#endif  // ENTITIES_HPP
