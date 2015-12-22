#pragma once
#include <gl/glut.h>

class Fireplay
{
	double linex, liney;
	int result = 0;
	int c1 = 0, c2 = 0;
	int ptr = 0;

public:
	int p[101][2], z;


	void init(int x1, int y1, int x2, int y2, int zval)
	{
		p[0][0] = x1, p[0][1] = y1;
		p[100][0] = x2, p[100][1] = y2;
		linex = p[100][0] - p[0][0];
		liney = p[100][1] - p[0][1];
		c1 = 2 * liney;
		c2 = 2 * (liney - linex);
		result = 2 * liney - linex;
		for (int i = 0; i <= 100; i++)Bresen(i);
		z = zval;
		ptr = 0;
	}

	void Bresen(int n)
	{
		if (n > 0) {
			if (result >= 0) result += c2;
			else if (result < 0) result += c1;
		}
		if (result >= 0) p[n + 1][1] = p[n][1] + 1;
		else if (result < 0) p[n + 1][1] = p[n][1];
		p[n + 1][0] = p[n][0] + 1;
	}
	void draw()
	{
		glPointSize(0.5);
		for (int j = 0; j < ptr; j++){
			glColor3f(0.8, 0.0, 0.0);

			glBegin(GL_POINTS);
			glVertex3f(p[j][0], p[j][1], z);
			glEnd();
		}

	}
	void update(int val){ if (ptr < 101) ptr += val; }
	bool motionend(){
		if (ptr == 100) return true;
		else return false;
	}
	
};

class Bomb : private Fireplay{
	bool flying = true;
	int x, y, z, yval, bptr;
private:
	Fireplay boomline[8];

public:
	//int num = 5;

	void Init_boom(int cenx, int ceny, int valz)
	{
		for (int i = 0; i < 8; i++){ boomline[i].init(cenx, ceny, cenx + 100, ceny + 70, valz); }

		for (int j = 0; j <= 100; j++){
			boomline[1].p[j][0] = -1 * boomline[0].p[j][0] + cenx * 2;
			boomline[2].p[j][0] = -1 * boomline[0].p[j][0] + cenx * 2;
			boomline[2].p[j][1] = -1 * boomline[0].p[j][1] + ceny * 2;
			boomline[3].p[j][1] = -1 * boomline[0].p[j][1] + ceny * 2;
			//  ½ÊÀÚ°¡
			boomline[4].p[j][0] = cenx;
			boomline[4].p[j][1] = boomline[0].p[j][1];
			boomline[5].p[j][0] = boomline[0].p[j][0];
			boomline[5].p[j][1] = ceny;
			boomline[6].p[j][0] = cenx;
			boomline[6].p[j][1] = -1 * boomline[0].p[j][1] + ceny * 2;
			boomline[7].p[j][0] = -1 * boomline[0].p[j][0] + cenx * 2;
			boomline[7].p[j][1] = ceny;
		}
		x = cenx, y = ceny, z = valz;

		yval = y - 500;

		flying = true;
		bptr = 0;
	}
	void draw()
	{


		for (int i = 0; i < 8; i++){
			if (flying == true){
				glLineWidth(0.5);
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex3f(x, y - 500, z);
				glVertex3f(x, yval, z);
				glEnd();
			}
			else if (flying == false){
				boomline[i].draw();

			}
			//printf("%d : %d  \n", i , boomline[i].ptr);
			//printf("%d : %d %d \n", i, boomline[i].p[boomline[i].ptr - 1][0], boomline[i].p[boomline[i].ptr - 1][1]);

		}


	}
	void update(int val)
	{
		for (int i = 0; i < 8; i++) {
			if (flying == true) {
				yval += val;
				if (yval >= y) flying = false;
			}
			else if (flying == false){
				boomline[i].update(val);
				//if (bptr >= 100) Init_boom(x, y, z);
			}
			//boomline[i].printLoc(i);
		}
		if (flying == false){
			bptr += val;
			if (bptr >= 100) Init_boom(x, y, z);
		}
	}

};

