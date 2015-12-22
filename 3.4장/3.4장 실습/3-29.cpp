#include <gl/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);
void spline(class point *p);

#define PI 3.141592

double angle = 0.0;
double plus = 10.0;
int i;
int r = 100;
double cenX = 400.0, cenY = 300.0;

class point{
public:
	double p[4][2];
	int ptr = 0;

	void setpoint(double x, double y){
		p[ptr][0] = x, p[ptr][1] = y;
		printf("%lf, %lf, %d \n", p[ptr][0], p[ptr][1], ptr);
		ptr++;
		//if (ptr == 3) { return false;}
		//else return true;
	}

};
class point point[10];
int num = 0;
int nummax = 10;


bool Reverse = false;

void main(int argc, char *argv[])
{
	srand((unsigned int)time(NULL));

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("½Ç½À");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);

	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, TimerFunction, 1);

	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i <= num; i++){
		spline(&point[i]);
	}

	glFlush();
}

GLvoid Reshape(int w, int h)
{

	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 800.0, -1.0, 1.0);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	double mx = (double)x, my = double(800.0 - y);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%lf, %lf \n", mx, my);
		point[num].setpoint(mx, my);

		if (point[num].ptr == 4) {
			if (num < nummax) {
				num++;
				point[num].setpoint(mx, my);
			}
		}

	}
}

GLvoid TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}

void spline(class point *pt)
{

	GLfloat ctrlpoint[4][3];
	printf("ptr ::: %d \n", pt->ptr);
	for (int i = 0; i < pt->ptr; i++) ctrlpoint[i][0] = pt->p[i][0], ctrlpoint[i][1] = pt->p[i][1], ctrlpoint[i][2] = 0.0;

	glPointSize(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i < pt->ptr; i++) glVertex3fv(&ctrlpoint[i][0]);
	glEnd();

	if (pt->ptr == 4){
		glColor3f(0.0, 0.0, 1.0);
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoint[0][0]);
		glEnable(GL_MAP1_VERTEX_3);
		glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 30; i++)	glEvalCoord1f((GLfloat)i / 30.0);
		glEnd();
		glDisable(GL_MAP1_VERTEX_3);
	}

	//glEnable(GL_MAP2_VERTEX_3);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (key == 'r')
	{
		for (int i = 0; i < 10; i++)
		{
			point[i].ptr = 0;
		}
	
	}
}