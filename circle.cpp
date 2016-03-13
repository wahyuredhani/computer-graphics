#include <GL/glut.h>
#include <math.h>

const int n = 1000;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;

void DrawCircle()
{
    glLineWidth(3);
    glColor3f( 0.0, 0.0, 0.0 );
    int i;
    glBegin(GL_LINE_LOOP);
    for(i=0; i<n; ++i)
        glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
    glEnd();
    glFlush();
}
void myDisplay()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawCircle();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle");
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
