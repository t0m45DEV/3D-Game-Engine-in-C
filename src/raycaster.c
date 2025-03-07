#include "raycaster.h"


void cast_rays(void)
{
    int count_of_hits;
    position_2D_t map_ray;
    int ray_in_map;
    position_2D_t ray_pos;
    position_2D_t ray_offset = {0, 0};
    float distance_from_player;
    float angle_cosine;

    entity_t player = get_player_info();

    float ray_angle = player.angle - (DEG_TO_RAD(FOV / 2));
    ray_angle = adjust_angle(ray_angle);

    for (int ray_idx = 0; ray_idx < AMMOUNT_OF_RAYS; ray_idx++)
    {
        /* Check horizontal lines */

        float distance_h = INFINITY;
        position_2D_t ray_H = {0, 0};
        structures_t surface_H = AIR;

        count_of_hits = 0;
        float aTan = -1 / tan(ray_angle);

        if (are_equals(ray_angle, RIGHT_DIR) || are_equals(ray_angle, LEFT_DIR)) /* If looking straight left or right */
        {
            ray_pos.x = player.pos.x;
            ray_pos.y = player.pos.y;

            count_of_hits = game_state.current_level_info.map_size.y;
        }
        else if (ray_angle > LEFT_DIR) /* If looking down */
        {
            ray_pos.y = (((int) player.pos.y / MAP_CELL_SIZE) * MAP_CELL_SIZE) - PRECISION;
            ray_pos.x = (player.pos.y - ray_pos.y) * aTan + player.pos.x;

            ray_offset.y = (-1) * MAP_CELL_SIZE;
            ray_offset.x = (-1) * ray_offset.y * aTan;
        }
        else if (ray_angle < LEFT_DIR) /* If looking up */
        {
            ray_pos.y = (((int) player.pos.y / MAP_CELL_SIZE) * MAP_CELL_SIZE) + MAP_CELL_SIZE;
            ray_pos.x = (player.pos.y - ray_pos.y) * aTan + player.pos.x;

            ray_offset.y = MAP_CELL_SIZE;
            ray_offset.x = (-1) * ray_offset.y * aTan;
        }

        while (count_of_hits < game_state.current_level_info.map_size.y)
        {
            map_ray.x = (int) (ray_pos.x / MAP_CELL_SIZE);
            map_ray.y = (int) (ray_pos.y / MAP_CELL_SIZE);
            ray_in_map = REAL_POS_TO_GRID_POS(map_ray.x, map_ray.y);

            if ((is_valid_map_index(ray_in_map)) && (map_w[ray_in_map] != AIR)) /* Hit a wall */
            {
                ray_H.x = ray_pos.x;
                ray_H.y = ray_pos.y;
                distance_h = distance_between(player.pos, ray_pos);
                surface_H = map_w[ray_in_map];

                count_of_hits = game_state.current_level_info.map_size.y; /* End the loop */
            }
            else /* Check the next */
            {
                ray_pos.x += ray_offset.x;
                ray_pos.y += ray_offset.y;
                count_of_hits += 1;
            }
        }
        /* Check vertical lines */

        float distance_v = INFINITY;
        position_2D_t ray_V = {0, 0};
        structures_t surface_V = AIR;

        count_of_hits = 0;
        float nTan = (-1) * tan(ray_angle);

        if (are_equals(ray_angle, UP_DIR) || are_equals(ray_angle, DOWN_DIR)) /* If looking straight up or down */
        {
            ray_pos.x = player.pos.x;
            ray_pos.y = player.pos.y;

            count_of_hits = game_state.current_level_info.map_size.x;
        }
        else if ((ray_angle > UP_DIR) && (ray_angle < DOWN_DIR)) /* If looking left */
        {
            ray_pos.x = (((int) player.pos.x / MAP_CELL_SIZE) * MAP_CELL_SIZE) - PRECISION;
            ray_pos.y = (player.pos.x - ray_pos.x) * nTan + player.pos.y;

            ray_offset.x = (-1) * MAP_CELL_SIZE;
            ray_offset.y = (-1) * ray_offset.x * nTan;
        }
        else if ((ray_angle < UP_DIR) || (ray_angle > DOWN_DIR)) /* If looking right */
        {
            ray_pos.x = (((int) player.pos.x / MAP_CELL_SIZE) * MAP_CELL_SIZE) + MAP_CELL_SIZE;
            ray_pos.y = (player.pos.x - ray_pos.x) * nTan + player.pos.y;

            ray_offset.x = MAP_CELL_SIZE;
            ray_offset.y = (-1) * ray_offset.x * nTan;
        }

        while (count_of_hits < game_state.current_level_info.map_size.x)
        {
            map_ray.x = (int) (ray_pos.x / MAP_CELL_SIZE);
            map_ray.y = (int) (ray_pos.y / MAP_CELL_SIZE);
            ray_in_map = REAL_POS_TO_GRID_POS(map_ray.x, map_ray.y);

            if ((is_valid_map_index(ray_in_map)) && (map_w[ray_in_map] != AIR)) /* Hit a wall */
            {
                ray_V.x = ray_pos.x;
                ray_V.y = ray_pos.y;
                distance_v = distance_between(player.pos, ray_pos);
                surface_V = map_w[ray_in_map];

                count_of_hits = game_state.current_level_info.map_size.x; /* End the loop */
            }
            else /* Check the next */
            {
                ray_pos.x += ray_offset.x;
                ray_pos.y += ray_offset.y;
                count_of_hits += 1;
            }
        }

        float actual_orientation;
        structures_t actual_surface;

        if (distance_h < distance_v)
        {
            ray_pos.x = ray_H.x;
            ray_pos.y = ray_H.y;
            distance_from_player = distance_h;
            
            actual_orientation = NORTH_SOUTH_WALL;
            actual_surface = surface_H;
        }
        else
        {
            ray_pos.x = ray_V.x;
            ray_pos.y = ray_V.y;
            distance_from_player = distance_v;

            actual_orientation = WEAST_EAST_WALL;
            actual_surface = surface_V;
        }

        if (!game_state.is_on_debug_view_mode)
        {
            angle_cosine = player.angle - ray_angle;
            angle_cosine = adjust_angle(angle_cosine);

            distance_from_player = distance_from_player * cos(angle_cosine); /* Fix fisheye */
            render_line((ray_t) {ray_idx, ray_pos, ray_angle, distance_from_player, actual_surface, actual_orientation});
        }
        else
        {
            glColor3f(RAY_COLOR.r, RAY_COLOR.g, RAY_COLOR.b);
            glLineWidth(2);
            glBegin(GL_LINES);
            glVertex2i(player.pos.x, player.pos.y);
            glVertex2i(ray_pos.x, ray_pos.y);
            glEnd();
        }

        ray_angle += (DEGREE / RATIO_ANGLE_RAYS);
        ray_angle = adjust_angle(ray_angle);
    }
}
