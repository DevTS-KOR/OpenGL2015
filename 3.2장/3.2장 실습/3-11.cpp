#include <gl/glut.h>
#include <math.h>

#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);

float fCenter_Vertex_X = 0.0f;
float fCenter_Vertex_Y = 0.5f;
float fCenter_RectVertex_Y = 0.2f;
float fRotate = 0.0f;
float fScale = 2.0f;
float fScale_Change = 0.1f;
float fCircle_X[100];
float fCircel_Y[100];
float fAngle = 0.0f;
float fDistance = 0.5f;

bool bTriangle = false;
bool bRect = false;

void main()
{
	for (int i = 0; i < 100; i++)
	{
		fCircle_X[i] += sin(fAngle * PI) * fDistance;
		fCircel_Y[i] -= cos(fAngle * PI) * fDistance;
		fAngle += 0.05f;
	}

	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-11");
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/*glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(fCircle_X[i], fCircel_Y[i]);
	}
	glEnd();*/

	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(fCircle_X[i], fCircel_Y[i]);
	}
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();

	glPushMatrix();
	//glRotatef(fRotate, 0.0f, 0.0f, 1.0f);
	//glScalef(fScale, 1.0f, 1.0f);

	if (bTriangle == true)
	{
		glRotatef(fRotate, 0.0f, 0.0f, 1.0f);
		glScalef(fScale, 1.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(fCenter_Vertex_X, fCenter_Vertex_Y + 0.2f);
		glVertex2f(fCenter_Vertex_X - 0.1f, fCenter_Vertex_Y - 0.2f);
		glVertex2f(fCenter_Vertex_X + 0.1f, fCenter_Vertex_Y - 0.2f);
		glEnd();
	}

	if (bRect == true)
	{
		glScalef(fScale, fScale, 1.0f);
		glRotatef(fRotate, 0.0f, 0.0f, 1.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex2f(fCenter_Vertex_X - 0.1f, fCenter_RectVertex_Y + 0.1f);
		glVertex2f(fCenter_Vertex_X + 0.1f, fCenter_RectVertex_Y + 0.1f);
		glVertex2f(fCenter_Vertex_X + 0.1f, fCenter_RectVertex_Y - 0.1f);
		glVertex2f(fCenter_Vertex_X - 0.1f, fCenter_RectVertex_Y - 0.1f);
		glEnd();
	}


	glPopMatrix();


	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'p')
	{
		fRotate += 5.0f;
		fScale += fScale_Change;

		if (fScale >= 4.0f)
			fScale_Change = (-1) * fScale_Change;

		if (fScale <= 2.0f)
			fScale_Change = (-1) * fScale_Change;
	}

	if (key == 't' || key == 'T')
	{
		bTriangle = true;
		bRect = false;
	}

	if (key == 'r' || key == 'R')
	{
		bRect = true;
		bTriangle = false;
	}

	glutPostRedisplay();
}