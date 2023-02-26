// #include <GL/GL.h>  // provided by underlying OS
// #include <gl/GLU.h> // provided by underlying OS
// #include <GL/glut.h>
#include <GL/freeglut.h>

void display();
void init();
void timer_func(int te)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    // Initialize glut library
    glutInit(&argc, argv);

    // glutInitContextVersion(3, 3);
    // glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    // glutInitContextProfile(GLUT_CORE_PROFILE);

    // glutInitDisplayMode(GLUT_RGB);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);

    glutCreateWindow("GLUT Intro");

    glutDisplayFunc(display);
    // glutTimerFunc(1000, timer_func, 1);
    glutMainLoop();
}

void display()
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // glutPostRedisplay();
    // display frame buffer on the screen
    glFlush();
    glutSwapBuffers();

    //
}

void init()
{
}
