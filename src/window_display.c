#include "window_display.h"

int resolution = LOW_RESOLUTION;

bool debug_2D_view = false;
bool show_3D_view = true;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    move_player();
    
    if (debug_2D_view) draw_map_2D();
    cast_rays(debug_2D_view);
    if (debug_2D_view) draw_player();
    
    glutSwapBuffers();
}


void resize(int x, int y)
{
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}


void window_create(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(X_CENTER_POS, Y_CENTER_POS);
    glutCreateWindow(WINDOW_TITLE);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glClearColor(0.5, 0.5, 0.5, 0);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(buttons_down);
    glutKeyboardUpFunc(buttons_up);
    glutMainLoop();
}
