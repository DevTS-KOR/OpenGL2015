#include <gl/glut.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int Width, int Height);

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 600);
	glutCreateWindow("3-3");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	float iRed = 1.0f;
	float iGreen = 0.7f;
	float iBlue = 0.9f;
	int iTime = 0;
	int iCount = 0;
	int iRandom = 0;
	srand((unsigned)time(NULL));

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3i(0, 0, 0);

	for (int i = -150; i <= 150; i += 300)		//세로선
	{
		glBegin(GL_LINES);
		glVertex2i(i, 300);
		glVertex2i(i, -300);
		glEnd();
	}

	for (int i = -100; i <= 100; i += 200)		//가로선
	{
		glBegin(GL_LINES);
		glVertex2i(-450, i);
		glVertex2i(450, i);
		glEnd();
	}
	

	iTime = GetTickCount();

	/*while (true)
	{
		if (GetTickCount() >= iTime + 500)
		{
			iGreen -= 0.1f;
			iBlue -= 0.1f;

			if (iGreen <= 0.0f)
				iGreen = 0.0f;
			if (iBlue <= 0.0f)
				iBlue = 0.0f;

			iTime = GetTickCount();
			++iCount;
		}*/

		
	
		for (int j = 300; j > -300; j -= 200)
		{
			for (int i = -450; i < 450; i += 300)
			{
				iRandom = rand() % 4;

				iGreen -= 0.07f;
				iBlue -= 0.09f;

				if (iGreen <= 0.0f)
					iGreen = 0.0f;
				if (iBlue <= 0.0f)
					iBlue = 0.0f;

				glColor3f(iRed, iGreen, iBlue);

				switch (iRandom)
				{
				case 0:
					glBegin(GL_LINES);
					glVertex2i(i + 50, j - 50);
					glVertex2i(i + 250, j - 150);
					glEnd();
					break;

				case 1:
					glBegin(GL_TRIANGLES);
					glVertex2i(i + 150, j - 50);
					glVertex2i(i + 225, j - 150);
					glVertex2i(i + 75, j - 150);
					glEnd();
					break;

				case 2:
					glBegin(GL_POLYGON);
					glVertex2i(i + 100, j - 50);
					glVertex2i(i + 200, j - 50);
					glVertex2i(i + 200, j - 150);
					glVertex2i(i + 100, j - 150);
					glEnd();
					break;

				case 3:
					glBegin(GL_POLYGON);
					glVertex2i(i + 150, j - 50);
					glVertex2i(i + 200, j - 100);
					glVertex2i(i + 175, j - 150);
					glVertex2i(i + 125, j - 150);
					glVertex2i(i + 100, j - 100);
					glEnd();
					break;

				}
				
			}
		}

		glFlush();

		/*if (iCount >= 10)
			break;
	}*/
}

GLvoid Reshape(int Width, int Height)
{
	glViewport(0, 0, Width, Height);
	glOrtho(-450.0, 450.0, -300.0, 300.0, -1.0, 1.0);
}