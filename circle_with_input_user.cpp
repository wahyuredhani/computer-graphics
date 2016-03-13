/*
Name: Karthik Gopalakrishnan
Roll: 1101CS21

Computer Graphics Lab Assignment 2
*/

#define GLUT_STATIC
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
using namespace std;

float xC, yC, R;
void (*ptr)(void);

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); /* clear all pixels */
    
    glColor3f(1.0, 1.0, 1.0);    //white color for basic circle drawing algorithm
    glBegin(GL_POINTS);
    
    float x,y;
    for(x = 0; x <= R/1.414; x++)
    {
         y = sqrt(R*R - x*x);
         
         glVertex3f(x + xC, yC + round(y), 0);
         glVertex3f(yC + round(y), x + xC, 0);
         glVertex3f(yC + round(y), -x + xC, 0);
         glVertex3f(x + xC, yC - round(y), 0);
         glVertex3f(-x + xC, yC - round(y), 0);
         glVertex3f(yC - round(y), -x + xC, 0);
         glVertex3f(yC - round(y), x + xC, 0);
         glVertex3f(-x + xC, yC + round(y), 0);
    }
    
    glEnd();
    
    glFlush(); /* start processing buffered OpenGL routines */
}

void CirclePoints(float x, float y)
{
     glVertex3f(x + xC,y + yC,0);
     glVertex3f(y + xC,x + yC,0);
     glVertex3f(y + xC,-x + yC,0);
     glVertex3f(x + xC,-y + yC,0);
     glVertex3f(-x + xC,-y + yC,0);
     glVertex3f(-y + xC,-x + yC,0);
     glVertex3f(-y + xC,x + yC,0);
     glVertex3f(-x + xC,y + yC,0);
}

void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 0.0, 0.0);     //red color for mid-point circle drawing algorithm using second order differences
    glBegin(GL_POINTS);
    
    float x, y, d, delE, delSE;
    x = 0;
    y = R;
    d = 1 - R;
    delE = 3;
    delSE = -2*R + 5;
    CirclePoints(x,y);
    while(y > x)
    {
            if(d < 0)
            {
                 d = d + delE;
                 delE = delE + 2;
                 delSE = delSE + 2;
                 x = x + 1;
            }
            else
            {
                d = d + delSE;
                delE = delE + 2;
                delSE = delSE + 4;
                x = x + 1;
                y = y - 1;
            }
            CirclePoints(x,y);
    }
    
    glEnd();
    
    glFlush();
}

void display3(void)
{
     glClear(GL_COLOR_BUFFER_BIT);
     
     glColor3f(0.0, 0.0, 1.0);     //blue color for modified mid-point circle drawing algorithm (Extra Credit)
     glBegin(GL_POINTS);
     
     float x, y, d, delE, delSE;
     x = 0;
     y = R;
     d = 5 - 4*R;
     delE = 12;
     delSE = -8*R + 20;
     CirclePoints(x,y);
     while(y > x)
     {
            if(d < 0)
            {
                 d = d + delE;
                 delE = delE + 8;
                 delSE = delSE + 8;
                 x = x + 1;
            }
            else
            {
                d = d + delSE;
                delE = delE + 8;
                delSE = delSE + 16;
                x = x + 1;
                y = y - 1;
            }
            CirclePoints(x,y);
      }
      
      glEnd();
      
      glFlush();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0); /* select clearing color */
    glMatrixMode(GL_PROJECTION); /* initialize viewing values */
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
     if(key == 32)     //space
     {
            if(ptr == &display)
            {
                   ptr = &display2;
            }
            else if(ptr == &display2)
            {
                ptr = &display3;
            }
            else
            {
                ptr = &display;
            }
            
            ptr();
     }
}

/* Declare initial window size, position, and display mode. Call initialization routines. Register callback function
to display graphics. Enter main loop and process events. */
int main(int argc, char** argv) {
    
    ptr = &display;
    
    cout<<"Enter the centre of the circle (xC, yC):"<<endl;
    cin>>xC>>yC;
    cout<<"Enter the radius of the circle:"<<endl;
    cin>>R;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Circle Drawing");
    init();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(ptr);
    glutMainLoop();
    
    return 0;
}