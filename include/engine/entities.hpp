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

typedef struct PlayerSpeed {
    float speed;
    float accel;
} PlayerSpeed;

#endif  // ENTITIES_HPP
