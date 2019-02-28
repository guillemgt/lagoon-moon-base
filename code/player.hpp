#ifndef player_hpp
#define player_hpp

#include <time.h>
#include "render.hpp"

struct Player {
    Vec2 r, v;
    u32 flags;
    int at_platform;
    float jump_height, time_to_unstick, gravity_extra;
    
    bool space_was_up = false;
};
struct PlayerSnapshot {
    Vec2 r, v;
    float time;
    u32 flags;
};

struct GameStats {
    clock_t starting_time;
    float best_time;
    unsigned int best_lives;
};


const u32 PM_PUSHES_OBJECT_RIGHT  = 0x00000001;
const u32 PM_PUSHES_OBJECT_LEFT   = 0x00000002;
const u32 PM_PUSHES_OBJECT_BOTTOM = 0x00000004;
const u32 PM_PUSHES_OBJECT_TOP    = 0x00000008;
const u32 PM_PUSHED_OBJECT_RIGHT  = 0x00000010;
const u32 PM_PUSHED_OBJECT_LEFT   = 0x00000020;
const u32 PM_PUSHED_OBJECT_BOTTOM = 0x00000040;
const u32 PM_PUSHED_OBJECT_TOP    = 0x00000080;
const u32 PM_PUSHES_TILE_RIGHT  = 0x00000100;
const u32 PM_PUSHES_TILE_LEFT   = 0x00000200;
const u32 PM_PUSHES_TILE_BOTTOM = 0x00000400;
const u32 PM_PUSHES_TILE_TOP    = 0x00000800;
const u32 PM_PUSHED_TILE_RIGHT  = 0x00001000;
const u32 PM_PUSHED_TILE_LEFT   = 0x00002000;
const u32 PM_PUSHED_TILE_BOTTOM = 0x00004000;
const u32 PM_PUSHED_TILE_TOP    = 0x00008000;
const u32 PM_PUSHES_RIGHT  = PM_PUSHES_OBJECT_RIGHT  | PM_PUSHES_TILE_RIGHT;
const u32 PM_PUSHES_LEFT   = PM_PUSHES_OBJECT_LEFT   | PM_PUSHES_TILE_LEFT;
const u32 PM_PUSHES_BOTTOM = PM_PUSHES_OBJECT_BOTTOM | PM_PUSHES_TILE_BOTTOM;
const u32 PM_PUSHES_TOP    = PM_PUSHES_OBJECT_TOP    | PM_PUSHES_TILE_TOP;
const u32 PM_PUSHED_RIGHT  = PM_PUSHED_OBJECT_RIGHT  | PM_PUSHED_TILE_RIGHT;
const u32 PM_PUSHED_LEFT   = PM_PUSHED_OBJECT_LEFT   | PM_PUSHED_TILE_LEFT;
const u32 PM_PUSHED_BOTTOM = PM_PUSHED_OBJECT_BOTTOM | PM_PUSHED_TILE_BOTTOM;
const u32 PM_PUSHED_TOP    = PM_PUSHED_OBJECT_TOP    | PM_PUSHED_TILE_TOP;
const u32 PM_ON_GROUND = PM_PUSHES_BOTTOM;

const u32 PM_STICKING_TO_WALL_RIGHT = 0x00010000;
const u32 PM_STICKING_TO_WALL_LEFT  = 0x00020000;
const u32 PM_WALL_JUMPING_RIGHT     = 0x00040000;
const u32 PM_WALL_JUMPING_LEFT      = 0x00080000;
const u32 PM_STICKING_TO_WALL = PM_STICKING_TO_WALL_RIGHT | PM_STICKING_TO_WALL_LEFT;
const u32 PM_WALL_JUMPING = PM_WALL_JUMPING_RIGHT | PM_WALL_JUMPING_LEFT;
const u32 PM_DISABLED = 0x80000000;

struct SoundMessage {
    float time;
    u8 sound;
};
struct ParticleMessage {
    Vec2 r;
    float time;
    bool is_death;
};


const u8 frame_key_up    = 0x01;
const u8 frame_key_right = 0x02;
const u8 frame_key_down  = 0x04;
const u8 frame_key_left  = 0x08;
const u8 frame_key_space = 0x10;
const u8 frame_key_jump  = 0x11;
const float load_next_level_in_max = 1.5f;

const Vec2 enemies_speed = Vec2(-2.f, 0.f);

struct Platform {
    Vec2 r, size, v;
};

struct Particle {
    Vec2 r, v;
    RgbaColor color;
    float glitched_life;
};

const int MAX_ENEMIES = 16;
const int MAX_PLATFORMS = 8;
const int MAX_GATES = 8;

#define MAX_PARTICLES 9000
#define MAX_UPS 120 // Updates Per Second

const u8 GF_HORIZONTAL = 0x01;
const u8 GF_VISITED    = 0x02;
const u8 GF_IMMORTAL   = 0x04;
struct Gate {
    Vec2 r;
    float state;
    u8 flags;
};

struct Level {
    int width, height;
    char layout[max_level_width][max_level_height];
    StaticArray<Vec2, MAX_ENEMIES> enemies;
    StaticArray<Platform, MAX_PLATFORMS> platforms;
    float time_to_load_next_level, time_to_load_next_level_max, time;
    Vec2 start_r, goal_r;
    bool state, completed;
    int num;
};
struct LaggedLevel {
    Vec2 key_r;
    StaticArray<Vec2, MAX_PLATFORMS> platform_sizes;
    StaticArray<Gate, MAX_GATES>     gates;
};



struct PlatformInfo {
    Vec2 r, v;
};

struct LevelInfo {
    StaticArray<Vec2, MAX_ENEMIES>           enemies;
    StaticArray<PlatformInfo, MAX_PLATFORMS> platforms;
    Vec2i size;
    Vec2 start, start_first_time;
    char layout[max_level_width][max_level_height];
};
extern LevelInfo all_levels[];

void change_level_state(Level *level);
void reset_player(LevelInfo *level_info, Player *player, Level *level);

void load_player_into_buffer(GameState *game_state, BufferAndCount *buffer);
void load_particles_into_buffer(GameState *game_state, BufferAndCount *buffer);

void process_movement(GameState *game_state, u8 keys);
void init_messages(GameState *game_state);
void process_messages(GameState *game_state);

struct PlayerRenderingInfo {
    int current_frame_x = 0;
    int current_frame_y = 0;
    int time_in_current_frame = 0;
};

#endif /* player_hpp */
