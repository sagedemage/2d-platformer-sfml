#include "physics.hpp"

float Gravity(sf::Vector2f position, float accel) {
    position.y += accel;

    return position.y;
}

void JumpPhysics(sf::Sprite *player, MotionState *motion_state,
                 PlayerSpeed player_speed) {
    /* Jump physics */
    if (motion_state->jump) {
        player->move(0.F, -player_speed.accel * 2);
        motion_state->jump_frames += 1;
    }

    if (motion_state->jump_frames == 8) {
        motion_state->jump = false;
        motion_state->jump_frames = 0;
    }
}
