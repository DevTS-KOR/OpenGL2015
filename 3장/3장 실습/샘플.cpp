#include <gl/glut.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("샘플");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);		//윈도우의 크기가 변할때 취할 동작지정
	glutMainLoop();
}

//윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);		//그리기 색 지정
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);		//사각형 그리기
	glFlush();								//화면에 출력
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}