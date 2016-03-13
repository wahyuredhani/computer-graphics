#include <GL/glut.h>
#include <math.h>

const GLdouble twoPi = 6.283185;
const GLint a = 100, b = 50;

struct screenPt{
	GLint x, y;
};

GLsizei winWidth = 600, winHeight = 500;

void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, (GLdouble) winWidth, 0.0, (GLdouble) winHeight);
}

void lineSegment(screenPt pt1, screenPt pt2){
    glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2i(pt1.x, pt1.y);
		glVertex2i(pt2.x, pt2.y);
	glEnd();
}

void drawCurve(void){
	GLfloat r, theta, dtheta = 1.0 / (GLfloat) a;
	GLint x0 = winWidth/2, y0 = winHeight/2;
	screenPt curvePt[2];
	glColor3f(0.0, 0.0, 0.0);
	curvePt[0].x = x0;
	curvePt[0].y = y0;
	curvePt[0].x += a + a;
	theta = dtheta;
	while(theta < twoPi){
		r = a * (1 + cos(theta));
		curvePt[1].x = x0 + r*cos(theta);
		curvePt[1].y = y0 + r*sin(theta);
		lineSegment(curvePt[0], curvePt[1]);
		curvePt[0] = curvePt[1];
		theta += dtheta;
	}
}

void displayFunc(void){
	glClear(GL_COLOR_BUFFER_BIT);
	drawCurve();
	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight){
	glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) winWidth, 0.0, (GLdouble) winHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Cardioid");
	init();
    glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFunc);
	glutMainLoop();
}
