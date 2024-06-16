#include "raycaster.h"

void cast_rays(bool debug_view)
{
    int dof;
    int ray_map_x;
    int ray_map_y;
    int ray_in_map;
    float ray_x;
    float ray_y;
    float x_offset;
    float y_offset;
    float distance_from_player;
    float angle_cosine;

    float ray_angle = player.angle - DEGREE * ANGLE_OF_VISION;

    if (ray_angle < 0)
    {
        ray_angle += 2 * PI;
    }
    else if (ray_angle > (2 * PI))
    {
        ray_angle -= 2 * PI;
    }

    for (int ray = 0; ray < AMMOUNT_OF_RAYS; ray++)
    {
        // Check horizontal lines

        float distance_h = INT32_MAX;
        float ray_x_h, ray_y_h;

        dof = 0;
        float aTan = -1 / tan(ray_angle);

        if ((ray_angle == 0) || (ray_angle == PI)) // If looking straight left or right
        {
            ray_x = player.x_pos;
            ray_y = player.y_pos;

            dof = MAP_Y_SIZE;
        }
        else if (ray_angle > PI) // If looking down
        {
            ray_y = (((int) player.y_pos / MAP_CELL_SIZE) * MAP_CELL_SIZE) - PRECISION;
            ray_x = (player.y_pos - ray_y) * aTan + player.x_pos;

            y_offset = (-1) * MAP_CELL_SIZE;
            x_offset = (-1) * y_offset * aTan;
        }
        else if (ray_angle < PI) // If looking up
        {
            ray_y = (((int) player.y_pos / MAP_CELL_SIZE) * MAP_CELL_SIZE) + MAP_CELL_SIZE;
            ray_x = (player.y_pos - ray_y) * aTan + player.x_pos;

            y_offset = MAP_CELL_SIZE;
            x_offset = (-1) * y_offset * aTan;
        }

        while (dof < MAP_Y_SIZE)
        {
            ray_map_x = (int) (ray_x / MAP_CELL_SIZE);
            ray_map_y = (int) (ray_y / MAP_CELL_SIZE);
            ray_in_map = ray_map_y * MAP_X_SIZE + ray_map_x;

            if ((ray_in_map > 0) && (ray_in_map < (MAP_X_SIZE * MAP_Y_SIZE)) && (map[ray_in_map] == 1)) // Hit a wall
            {
                ray_x_h = ray_x;
                ray_y_h = ray_y;
                distance_h = distance_between(player.x_pos, player.y_pos, ray_x, ray_y);

                dof = MAP_Y_SIZE;
            }
            else // Check the next 
            {
                ray_x += x_offset;
                ray_y += y_offset;
                dof += 1;
            }
        }

        // Check vertical lines

        float distance_v = INT32_MAX;
        float ray_x_v, ray_y_v;

        dof = 0;
        float nTan = (-1) * tan(ray_angle);

        if ((ray_angle == UP_DIR) || (ray_angle == DOWN_DIR)) // If looking straight up or down
        {
            ray_x = player.x_pos;
            ray_y = player.y_pos;

            dof = MAP_X_SIZE;
        }
        else if ((ray_angle > UP_DIR) && (ray_angle < DOWN_DIR)) // If looking left
        {
            ray_x = (((int) player.x_pos / MAP_CELL_SIZE) * MAP_CELL_SIZE) - PRECISION;
            ray_y = (player.x_pos - ray_x) * nTan + player.y_pos;

            x_offset = (-1) * MAP_CELL_SIZE;
            y_offset = (-1) * x_offset * nTan;
        }
        else if ((ray_angle < UP_DIR) || (ray_angle > DOWN_DIR)) // If looking right
        {
            ray_x = (((int) player.x_pos / MAP_CELL_SIZE) * MAP_CELL_SIZE) + MAP_CELL_SIZE;
            ray_y = (player.x_pos - ray_x) * nTan + player.y_pos;

            x_offset = MAP_CELL_SIZE;
            y_offset = (-1) * x_offset * nTan;
        }

        while (dof < MAP_X_SIZE)
        {
            ray_map_x = (int) (ray_x / MAP_CELL_SIZE);
            ray_map_y = (int) (ray_y / MAP_CELL_SIZE);
            ray_in_map = ray_map_y * MAP_X_SIZE + ray_map_x;

            if ((ray_in_map > 0) && (ray_in_map < (MAP_X_SIZE * MAP_Y_SIZE)) && (map[ray_in_map] == 1)) // Hit a wall
            {
                ray_x_v = ray_x;
                ray_y_v = ray_y;
                distance_v = distance_between(player.x_pos, player.y_pos, ray_x, ray_y);

                dof = MAP_Y_SIZE;
            }
            else // Check the next 
            {
                ray_x += x_offset;
                ray_y += y_offset;
                dof += 1;
            }
        }

        if (distance_h < distance_v)
        {
            ray_x = ray_x_h;
            ray_y = ray_y_h;
            distance_from_player = distance_h;
            glColor3f(0.9, 0, 0);
        }
        else
        {
            ray_x = ray_x_v;
            ray_y = ray_y_v;
            distance_from_player = distance_v;
            glColor3f(0.7, 0, 0);
        }

        angle_cosine = player.angle - ray_angle;

        if (angle_cosine < 0)
        {
            angle_cosine += 2 * PI;
        }
        else if (angle_cosine > (2 * PI))
        {
            angle_cosine -= 2 * PI;
        }

        distance_from_player = distance_from_player * cos(angle_cosine);
        render_line(distance_from_player, ray);

        if (debug_view)
        {
            glLineWidth(2);
            glBegin(GL_LINES);
            glVertex2i(player.x_pos, player.y_pos);
            glVertex2i(ray_x, ray_y);
            glEnd();
        }

        ray_angle += DEGREE;

        if (ray_angle < 0)
        {
            ray_angle += 2 * PI;
        }
        else if (ray_angle > (2 * PI))
        {
            ray_angle -= 2 * PI;
        }
    }
}
