#include "entity.h"


#include <stdio.h>

entity_t calculate_offset(entity_t entity)
{
    if (entity.delta.x < 0) {entity.offset.x = (-1) * entity.collision_size;}
    else {entity.offset.x = entity.collision_size;}

    if (entity.delta.y < 0) {entity.offset.y = (-1) * entity.collision_size;}
    else {entity.offset.y = entity.collision_size;}

    return entity;
}


int can_move(position_2D idx, position_2D offset)
{
    int front  = map[REAL_POS_TO_GRID_POS(offset.x, offset.y)];
    int x_axis = map[REAL_POS_TO_GRID_POS(offset.x, idx.y)];
    int y_axis = map[REAL_POS_TO_GRID_POS(idx.x, offset.y)];

    return !((front != AIR) && (x_axis == AIR) && (y_axis == AIR));
}


int is_colliding_in_axis(entity_t entity, int axis)
{
    entity = calculate_offset(entity);

    position_2D idx;
    idx.x = entity.pos.x / (float) MAP_CELL_SIZE;
    idx.y = entity.pos.y / (float) MAP_CELL_SIZE;

    position_2D add_offset;
    add_offset.x = (entity.pos.x + entity.offset.x) / (float) MAP_CELL_SIZE;
    add_offset.y = (entity.pos.y + entity.offset.y) / (float) MAP_CELL_SIZE;

    position_2D sub_offset;
    sub_offset.x = (entity.pos.x - entity.offset.x) / (float) MAP_CELL_SIZE;
    sub_offset.y = (entity.pos.y - entity.offset.y) / (float) MAP_CELL_SIZE;

    if (axis == FRONT_X_AXIS_COLLISION)
    {
        printf("(%f, %f)\n", idx.x, idx.y);
        if (can_move(idx, add_offset))
        {
            return (map[REAL_POS_TO_GRID_POS(add_offset.x, idx.y)] != AIR);
        }
        else {return true;}
    }
    else if (axis == FRONT_Y_AXIS_COLLISION)
    {
        if (can_move(idx, add_offset))
        {
            return (map[REAL_POS_TO_GRID_POS(idx.x, add_offset.y)] != AIR);
        }
        else {return true;}
    }
    else if (axis == BACK_X_AXIS_COLLISION)
    {
        if (can_move(idx, sub_offset))
        {
            return (map[REAL_POS_TO_GRID_POS(sub_offset.x, idx.y)] != AIR);
        }
        else {return true;}
    }
    else if (axis == BACK_Y_AXIS_COLLISION)
    {
        if (can_move(idx, sub_offset))
        {
            return (map[REAL_POS_TO_GRID_POS(idx.x, sub_offset.y)] != AIR);
        }
        else {return true;}
    }

    return true;
}
