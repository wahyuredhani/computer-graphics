#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535898
#define SPIRAL

void init()
{
	glClearColor(1, 1, 1, 1);
	glShadeModel(GL_FLAT);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glLoadIdentity();
#ifdef SPIRAL
	GLfloat x, y, angle, ratio;

	GLint circle_points = 1000;
	GLint i;
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < circle_points-1; i++)
	{
		angle = 4*2*PI*i/circle_points;
		ratio = (GLfloat)circle_points/(circle_points-i);
		x = cos(angle);
		y = sin(angle);
		glVertex2f(x/ratio, y/ratio);
	}
	glEnd();
#else
	int count;
	glBegin(GL_LINE_STRIP);
	for(count = 0; count < 10; count ++)
	{
		glVertex2f((GLfloat)-1/(count + 1), (GLfloat)1/(count + 1));
		glVertex2f((GLfloat)0/(count + 1), (GLfloat)-1/(count + 1));
		glVertex2f((GLfloat)1/(count + 2), (GLfloat)1/(count + 2));
	}
	glEnd();
#endif
	glutSwapBuffers();
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spiral");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
