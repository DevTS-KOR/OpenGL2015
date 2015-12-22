#include <gl/glut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	int Weigth, Height;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	
	for (int Weigth = -400; Weigth < 600; Weigth += 200)
	{
		for (int Height = 300; Height > -500; Height -= 200)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glRectf(Weigth, Height, Weigth + 100, Height - 100);
			glRectf(Weigth - 100, Height + 100, Weigth, Height);

			glColor3f(0.0f, 1.0f, 0.0f);
			glRectf(Weigth + 100, Height, Weigth + 200, Height - 100);
			glRectf(Weigth, Height + 100, Weigth + 100, Height);
		}
	}

	
	

	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}