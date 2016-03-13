#include<iostream>
#include<GL/glut.h>

using namespace std;

void init()
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200,200,-200,200);
}

void setPixel(int x,int y)
{
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void ellipsePts(int x,int y,int xc,int yc)
{
    setPixel(x+xc,y+yc);
    setPixel(x+xc,-y+yc);
    setPixel(-x+xc,-y+yc);
    setPixel(-x+xc,y+yc);
}

void ellipse(int a,int b,int xc,int yc)
{
    float d=(float)b*b+a*a*(.25-b);
    int x=0,y=b;
    ellipsePts(x,y,xc,yc);

    while(a*a*y>b*b*x)
    {
        if(d<0)
        d+=b*b*(2*x+3);
        else
        {
            d+=b*b*(2*x+3)+a*a*(2-2*y);
            y--;
        }
        x++;
        ellipsePts(x,y,xc,yc);
    }
    d=(float)b*b*(x-0.5)*(x-0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
    while(y>=0)
    {
        if(d<0)
        {
            d+=b*b*(2*x+2)+a*a*(3-2*y);x++;
        }
        else
        {
            d+=a*a*(3-2*y);
        }
        y--;
        ellipsePts(x,y,xc,yc);
    }
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    ellipse(120,60,10,10);
    glFlush();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(300, 200);
    glutInitWindowSize(400,400);
    glutCreateWindow("Ellipse");
    init();
    glutDisplayFunc(&display);
    glutMainLoop();
    return 0;
}
