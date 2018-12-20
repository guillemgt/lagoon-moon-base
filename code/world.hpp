#ifndef world_hpp
#define world_hpp

#include "render.hpp"

const u16 BLOCK_IS_SOLID          = 0x0001;
const u16 BLOCK_IS_HARMFUL_RIGHT  = 0x0002;
const u16 BLOCK_IS_HARMFUL_UP     = 0x0004;
const u16 BLOCK_IS_HARMFUL_LEFT   = 0x0008;
const u16 BLOCK_IS_HARMFUL_DOWN   = 0x0010;
const u16 BLOCK_IS_HARMFUL_CENTER = 0x0020;
const u16 BLOCK_IS_GOAL           = 0x0040;
const u16 BLOCK_IS_TRANSPARENT    = 0x0080;
const u16 BLOCK_IS_RANDOM         = 0x0100;
const u16 BLOCK_HAS_TWO_LAYERS    = 0x0200;
const u16 BLOCK_STOPS_PLATFORMS   = 0x0400;

const u16 BLOCK_IS_HARMFUL = BLOCK_IS_HARMFUL_CENTER | BLOCK_IS_HARMFUL_RIGHT | BLOCK_IS_HARMFUL_UP | BLOCK_IS_HARMFUL_LEFT | BLOCK_IS_HARMFUL_DOWN;

const RgbaColor basic_color = {35, 35, 35, 255};

const int max_level_width  = 30;
const int max_level_height = 20;
const int max_levels = 25;

extern int  level_width;
extern int  level_height;
extern char **level_layout, **level_moving_layout;
const RgbaColor level_color = {200, 210, 200, 255};
extern u16  block_info[256];
extern Vec2 goal_position;

extern int levels_num;
extern int current_level;

void load_world();
void load_level_into_buffer(BufferAndCount *buffer, BufferAndCount *t_buffer);
void load_changing_level_into_buffer(BufferAndCount *buffer);
void load_goal_into_buffer(BufferAndCount *buffer, BufferAndCount *loading_buffer);
void load_level(int num);

#endif /* world_hpp */
