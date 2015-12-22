#include <gl/glut.h> // includes gl.h glu.h
#include <stdio.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int, int, int, int);
GLvoid Timerfunction(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid MenuFunc(int button);

void MenuFunc(int button);

GLfloat start = 20.0;
GLfloat end = 50.0;
GLfloat density = 0.2;
GLfloat temp;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(600, 600); // �������� ũ�� ���� 
	glutCreateWindow("�ǽ�19"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene);// ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutTimerFunc(30, Timerfunction, 1);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();

}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	GLfloat fog_color[4] = { 0.7, 0.7, 0.7, 1.0 };

	glEnable(GL_FOG);
	//glFogf(GL_FOG_MODE, GL_LINEAR);

	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_START, start);
	glFogf(GL_FOG_END, end);

	glFogf(GL_FOG_DENSITY, density);

	glPushMatrix(); {
		glRotated(30, 1, 0, 0);
		glRotated(-45, 0, 1, 0);
		glTranslatef(-100, 0, 0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidCube(50);
	}
	glPopMatrix();

	glPushMatrix(); {
		glRotated(30, 1, 0, 0);
		glRotated(-45, 0, 1, 0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glutSolidCube(100);
	}
	glPopMatrix();

	glPushMatrix(); {
		glRotated(30, 1, 0, 0);
		glRotated(-45, 0, 1, 0);
		glTranslatef(100, 0, 0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glutSolidCube(50);
	}
	glPopMatrix();

	glutSwapBuffers(); // ��� ���
}
GLvoid Reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	gluPerspective(60.0, w / h, 1.0, 1000.0);

	gluLookAt(0.0, 0.0, 400.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	int SubMenu1, SubMenu2;
	int MainMenu;

	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("LINEAR", 1);
	glutAddMenuEntry("EXP", 2);
	glutAddMenuEntry("EXP2", 3);

	SubMenu2 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("����-��", 4);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("���", SubMenu1);
	glutAddSubMenu("��ġ�ٲٱ�", SubMenu2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutPostRedisplay();
}

GLvoid Timerfunction(int value)
{

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(30, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		density -= 0.01;
		break;
	case '-':
		density += 0.01;
		break;
	}

	glutPostRedisplay();
}


GLvoid MenuFunc(int button)
{
	switch (button) {
	case 1:
		glFogf(GL_FOG_MODE, GL_LINEAR);
		break;
	case 2:
		glFogf(GL_FOG_MODE, GL_EXP);
		break;
	case 3:
		glFogf(GL_FOG_MODE, GL_EXP2);
		break;
	case 4:
		temp = start;
		start = end;
		end = temp;
		break;
	}

	glutPostRedisplay();
}