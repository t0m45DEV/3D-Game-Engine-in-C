#include "map.h"

structures_t map_w[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 1, 0, 1, 1,
    1, 0, 1, 0, 1, 0, 0, 1,
    1, 0, 1, 0, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,

    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1,
    1, 1, 3, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1,
    1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

structures_t map_f[] =
{
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,

    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
};

structures_t map_c[] =
{
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,

    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
};

position_2D_t maps_sizes[LEVEL_COUNT] =
{
    (position_2D_t) {8, 8},
    (position_2D_t) {16, 8}
};

position_2D_t player_spawns[LEVEL_COUNT] =
{
    (position_2D_t) {1, 6},
    (position_2D_t) {1, 1}
};

int get_map_offset_from_id(const int level_idx)
{
    int ret = 0;

    for (int i = 0; i < level_idx; i++)
    {
        ret += (maps_sizes[i].x * maps_sizes[i].y);
    }
    return ret;
}

int is_valid_map_index(int idx)
{
    return ((idx > get_current_map_offset()) && (idx < (get_current_map_offset() + MAP_SIZE)));
}

void draw_map_2D(void)
{
    position_2D_t grid_pos;

    for (int y = 0; y < get_current_map_size().y; y++)
    {
        for (int x = 0; x < get_current_map_size().x; x++)
        {
            if (map_w[REAL_POS_TO_GRID_POS(x, y)] == AIR)
            {
                glColor3f(0, 0, 0);
            }
            else
            {
                glColor3f(1, 1, 1);
            }

            grid_pos.x = x * MAP_CELL_SIZE;
            grid_pos.y = y * MAP_CELL_SIZE;
            glBegin(GL_QUADS);
            glVertex2i(grid_pos.x                 + 1, grid_pos.y                 + 1);
            glVertex2i(grid_pos.x                 + 1, grid_pos.y + MAP_CELL_SIZE - 1);
            glVertex2i(grid_pos.x + MAP_CELL_SIZE - 1, grid_pos.y + MAP_CELL_SIZE - 1);
            glVertex2i(grid_pos.x + MAP_CELL_SIZE - 1, grid_pos.y                 + 1);
            glEnd();
        }
    }
}
