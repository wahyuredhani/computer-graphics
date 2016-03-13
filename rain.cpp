#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <time.h>
#include <Stdlib.h>

#define DisplayWidth 800
#define DisplayHeight 600
#define DropsCount 100

int DisplayWidthNew;
int DisplayHeightNew;
void display();

struct drop{
	int x;
	int y;
};

typedef struct drop DROP;
DROP drops[DropsCount];

void display()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void rain(int numDrops)
{
	display();
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < DropsCount; ++i)
	{
		if (drops[i].x < 0)
			drops[i].x = DisplayWidthNew;
		if (drops[i].y < 0)
			drops[i].y = DisplayHeightNew;
		glVertex2f(drops[i].x, drops[i].y);
		glVertex2f(drops[i].x + 7, drops[i].y + 7);
		drops[i].x -= 15;
		drops[i].y -= 15;
	}
	glEnd();
	glFlush();
	glutTimerFunc(10, rain, 0);
}

void Reshape(int Width, int Height)
{
	if (Height == 0)
	{
		Height = 1;
	}
	DisplayWidthNew = Width;
	DisplayHeightNew = Height;
	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)Width, 0.0, (GLdouble)Height);
	display();
	glFlush();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	for (int i = 0; i < DropsCount; ++i)
	{
		drops[i].x = rand() % DisplayWidth;
		drops[i].y = rand() % DisplayHeight;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(DisplayWidth, DisplayHeight);
	glutCreateWindow("Rain");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutTimerFunc(200, rain, 0);
	glutMainLoop();
	return 0;
}
