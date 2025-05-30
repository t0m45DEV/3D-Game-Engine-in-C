#include "entity.h"

#include <stdio.h>
#include "map.h"

void print_entity(const entity_t entity)
{
    printf("=== Entity ===\n");
    printf("Position: (%f, %f)\n", entity.pos.x, entity.pos.y);
    printf("Delta: (%f, %f)\n", entity.delta.x, entity.delta.y);
    printf("Angle: %f\n", entity.angle);
    printf("Movement velocity: %f\n", entity.movement_velocity);
    printf("Rotation velocity: %f\n", entity.rotation_velocity);
    printf("Collision size: %i\n", entity.collision_size);
    printf("Offset: (%f, %f)\n", entity.offset.x, entity.offset.y);
}


void update_offset(entity_t* entity)
{
    if (entity->delta.x < 0)
    {
        entity->offset.x = (-1) * entity->collision_size;
    }
    else
    {
        entity->offset.x = entity->collision_size;
    }

    if (entity->delta.y < 0)
    {
        entity->offset.y = (-1) * entity->collision_size;
    }
    else
    {
        entity->offset.y = entity->collision_size;
    }
}


int can_move(const position_2D_t idx, const position_2D_t offset)
{
    int front  = get_map_wall_at((position_2D_t) {offset.x, offset.y});
    int x_axis = get_map_wall_at((position_2D_t) {offset.x, idx.y});
    int y_axis = get_map_wall_at((position_2D_t) {idx.x, offset.y});

    /* Thing at idx don't have a wall directly on front
        and can slide in some axis X or Y */
    return !((front != AIR) && (x_axis == AIR) && (y_axis == AIR));
}


int is_colliding_in_axis(entity_t entity, const collision_directions_t axis)
{
    update_offset(&entity);

    position_2D_t idx;
    idx.x = entity.pos.x / (float) MAP_CELL_SIZE;
    idx.y = entity.pos.y / (float) MAP_CELL_SIZE;

    position_2D_t add_offset;
    add_offset.x = (entity.pos.x + entity.offset.x) / (float) MAP_CELL_SIZE;
    add_offset.y = (entity.pos.y + entity.offset.y) / (float) MAP_CELL_SIZE;

    position_2D_t sub_offset;
    sub_offset.x = (entity.pos.x - entity.offset.x) / (float) MAP_CELL_SIZE;
    sub_offset.y = (entity.pos.y - entity.offset.y) / (float) MAP_CELL_SIZE;

    if (can_move(idx, add_offset)) /* If can move forward */
    {
        if (axis == FRONT_X_AXIS_COLLISION) /* If can slide forward along X axis */
        {
            return (get_map_wall_at((position_2D_t) {add_offset.x, idx.y}) != AIR);
        }
        else if (axis == FRONT_Y_AXIS_COLLISION) /* If can slide forward along Y axis */
        {
            return (get_map_wall_at((position_2D_t) {idx.x, add_offset.y}) != AIR);
        }
    }
    if (can_move(idx, sub_offset)) /* If can move backward */
    {
        if (axis == BACK_X_AXIS_COLLISION) /* If can slide backward along X axis */
        {
            return (get_map_wall_at((position_2D_t) {sub_offset.x, idx.y}) != AIR);
        }
        else if (axis == BACK_Y_AXIS_COLLISION) /* If can slide backward along Y axis */
        {
            return (get_map_wall_at((position_2D_t) {idx.x, sub_offset.y}) != AIR);
        }
    }
    return true; /* Entity can't move at any direction */
}
