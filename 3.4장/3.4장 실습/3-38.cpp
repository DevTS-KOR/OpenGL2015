#pragma warning (disable:4996)
#include <gl/glut.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void TimerFunc(int value);
void Ground();
void BackGround();
void Tri();
void Viewcar();
void Wire();

GLvoid SetupRC();
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
GLubyte *pBytes[4];
BITMAPINFO *info;
GLuint* textures;
float fZoom = 1000.f;

float tri_rotate = 0.f;
float viewcar_rotate = 0.f;
float viewcar_rotate2 = 0.f;
float diffuse_Light = 0.8f;
float ambient_Light = 0.5f;
float specre_f = 0.1f;
bool Light1 = true;

float wire = 0.f;
float wire_Plus = 5.f;
float duck_x = 0.f;
float duck_y = 0.f;
bool wire_jump = false;
int iCount = 0;

void main()
{
	//초기화 함수들
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3-38");
	SetupRC();
	glutDisplayFunc(drawScene);		//출력 함수 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerFunc, 1);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glMatrixMode(GL_MODELVIEW);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, fZoom, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

	GLfloat diffuseLight[] = { diffuse_Light, diffuse_Light, diffuse_Light, 1.0f };
	GLfloat ambientLight[] = { ambient_Light, ambient_Light, ambient_Light, 1.0f };
	GLfloat specref[] = { specre_f, specre_f, specre_f, 1.0f };

	GLfloat lightPos[] = { -800.f, -300.f, 500.f, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specref);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


	glPushMatrix();
	glTranslatef(0.f, -300.f, 500.f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(50);
	glTranslatef(0.f, 300.f, -500.f);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	if (Light1 == true)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);

	//텍스처 파라미터 설정 --- (4)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	Ground();
	BackGround();
	Tri();
	Viewcar();
	Wire();
	glPopMatrix();

	//glFlush();
	glutSwapBuffers();		//결과 출력
}

GLvoid Reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	//glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);	
	gluPerspective(60.0, 1.0, 1.0, 2000.0);
	//gluLookAt(0.0, 0.0, 500.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
	//glMatrixMode(GL_MODELVIEW);
}

void Ground()
{
	//glRotatef(40, 0, 1, 0);
	glColor3f(0.8f, 0.5f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-400.f, -300.f, 500.0f);
	glVertex3f(400.f, -300.f, 500.0f);
	glVertex3f(400.f, -300.f, 0.f);
	glVertex3f(-400.f, -300.f, 0.f);
	glEnd();

}
void BackGround()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 800, 800, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-800.f, -800.f, -100.f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(800.f, -800.f, -100.f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(800.f, 800.f, -100.f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-800.f, 800.f, -100.f);
	glEnd();
}


void Tri()
{

	glPushMatrix();
	glTranslatef(-200.f, -220.f, 100.0);
	glRotatef(-tri_rotate, 0, 1, 0);
	glPushMatrix();
	glRotatef(45, 1, 0, 0);
	glRotatef(50, 0, 1, 0);
	//glRotatef(45, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(50);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-200.f, -220.f, 100.0);
	glRotatef(tri_rotate, 0, 1, 0);
	glPushMatrix();
	glRotatef(45, 1, 0, 0);
	glRotatef(50, 0, 1, 0);
	//glRotatef(45, 0, 0, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 0.2f, 0.8f, 0.5f);
	glutSolidCube(100);
	glBlendFunc(GL_ONE, GL_ZERO);
	glPopMatrix();
	glPopMatrix();


	
}

void Viewcar()
{
	glPushMatrix();
	glTranslatef(200.f, 0.0f, 0.0f);
	glRotatef(viewcar_rotate, 0, 0, 1);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidTorus(10, 200, 100, 100);

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5, 10, 1);
	glutSolidCube(50);
	glScalef(2, 0.1, 1);
	glTranslatef(0.0f, 250.f, 0.0f);
	glRotatef(-viewcar_rotate, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(50);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5, 10, 1);
	glutSolidCube(50);
	glScalef(2, 0.1, 1);
	glTranslatef(0.0f, 250.f, 0.0f);
	glRotatef(-viewcar_rotate + 45, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(50);
	glTranslatef(0.0f, -250.f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5, 10, 1);
	glutSolidCube(50);
	glScalef(2, 0.1, 1);
	glTranslatef(0.0f, 250.f, 0.0f);
	glRotatef(-viewcar_rotate + 90, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(50);
	glTranslatef(0.0f, -250.f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(135, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5, 10, 1);
	glutSolidCube(50);
	glScalef(2, 0.1, 1);
	glTranslatef(0.0f, 250.f, 0.0f);
	glRotatef(-viewcar_rotate + 135, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(50);
	glTranslatef(0.0f, -250.f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5, 10, 1);
	glutSolidCube(50);
	glScalef(2, 0.1, 1);
	glTranslatef(0.0f, 250.f, 0.0f);
	glRotatef(-viewcar_rotate + 180, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(50);
	glTranslatef(0.0f, -250.f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(225, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5, 10, 1);
	glutSolidCube(50);
	glScalef(2, 0.1, 1);
	glTranslatef(0.0f, 250.f, 0.0f);
	glRotatef(-viewcar_rotate + 225, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(50);
	glTranslatef(0.0f, -250.f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5, 10, 1);
	glutSolidCube(50);
	glScalef(2, 0.1, 1);
	glTranslatef(0.0f, 250.f, 0.0f);
	glRotatef(-viewcar_rotate + 270, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(50);
	glTranslatef(0.0f, -250.f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(315, 0, 0, 1);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(0.5, 10, 1);
	glutSolidCube(50);
	glScalef(2, 0.1, 1);
	glTranslatef(0.0f, 250.f, 0.0f);
	glRotatef(-viewcar_rotate + 315, 0, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(50);
	glTranslatef(0.0f, -250.f, 0.0f);
	glPopMatrix();

	glPopMatrix();
}

void Wire()
{
	glPushMatrix();
	glTranslatef(-200.f, -100.0f, 300.f);
	glRotatef(wire, 0, 0, 1);
	glTranslatef(200.f, 100.0f, -300.f);

	glLineWidth(5);
	glColor3f(1.0f, 0.0f, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-200.0f, -100.f, 300.0f);
	glVertex3f(-300.f, -200.0f, 300.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-200.0f, -100.f, 300.0f);
	glVertex3f(-100.f, -200.0f, 300.0f);
	glEnd();

	glTranslatef(-200.f, -200.f, 300.f);
	glScalef(4, 0.5, 1);
	glColor3f(0.7f, 0.1f, 0.7f);
	glutSolidCube(50);
	glScalef(0.25, 2, 1);
	glTranslatef(200.f, 200.f, -300.f);
	glPopMatrix();
	/////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(100.f, -100.0f, 300.f);
	glRotatef(-wire, 0, 0, 1);
	glTranslatef(-100.f, 100.0f, -300.f);

	glLineWidth(5);
	glColor3f(1.0f, 0.0f, 0.0);
	glBegin(GL_LINES);
	glVertex3f(100.0f, -100.f, 300.0f);
	glVertex3f(0.f, -200.0f, 300.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(100.0f, -100.f, 300.0f);
	glVertex3f(200.f, -200.0f, 300.0f);
	glEnd();

	glTranslatef(100.f, -200.f, 300.f);
	glScalef(4, 0.5, 1);
	glColor3f(0.7f, 0.1f, 0.7f);
	glutSolidCube(50);
	glScalef(0.25, 2, 1);
	glTranslatef(100.f, 200.f, -300.f);
	glPopMatrix();
	//////////////////////////////////////////////////
	glPushMatrix();
	if (wire_jump == false)
	{
		glTranslatef(-200.f, -100.0f, 300.f);
		glRotatef(wire, 0, 0, 1);
		glTranslatef(200.f, 100.0f, -300.f);

		glTranslatef(-200.f, -175.f, 300.f);

		glColor3f(0.8f, 0.8f, 0.0f);
		glutSolidSphere(20, 20, 20);
		glTranslatef(0.0f, 15.f, 0.0f);
		glutSolidSphere(15, 10, 10);
		glTranslatef(0.0f, -15.f, 0.0f);
	}
	else
	{
		glTranslatef(100.f, -100.0f, 300.f);
		glRotatef(-wire, 0, 0, 1);
		glTranslatef(-100.f, 100.0f, -300.f);

		glTranslatef(100.f, -175.f, 300.f);
		glColor3f(0.8f, 0.8f, 0.0f);
		glutSolidSphere(20, 20, 20);
		glTranslatef(0.0f, 15.f, 0.0f);
		glutSolidSphere(15, 10, 10);
		glTranslatef(0.0f, -15.f, 0.0f);
	}
	glPopMatrix();
}



void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		if (Light1 == true)
			Light1 = false;
		else
			Light1 = true;
	}
	else if (key == 'z')
		fZoom += 10.f;
	else if (key == 'Z')
		fZoom -= 10.f;
}

void TimerFunc(int value)
{
	tri_rotate += 10.f;
	viewcar_rotate += 2.f;

	if (wire == 50.f)
	{
		wire_Plus *= -1;
		++iCount;
	}
	else if (wire == -50.f)
	{
		wire_Plus *= -1;

	}
	wire += wire_Plus;

	if (iCount % 2 == 0)
		wire_jump = false;
	else
		wire_jump = true;

	glutPostRedisplay();
	glutTimerFunc(50, TimerFunc, 1);
}

GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

GLvoid SetupRC()
{
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

	pBytes[0] = LoadDIBitmap("3-38 롤러코스터.bmp", &info);

}

