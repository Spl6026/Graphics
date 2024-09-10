#include <GL/glut.h>
#include <math.h>
GLsizei wh = 500, ww = 500; /* initial window size */
GLfloat size = 3.0;
GLfloat posX = 0, posY = 0;
GLfloat angle = 0.0f;
int n = 300;
bool rotate = 0;
GLfloat L_hand = 0.0f;
bool LH_check = 0;
GLfloat R_hand = 0.0f;
bool RH_check = 0;
GLfloat L_foot = 20.0f;
bool LF_check = 0;
GLfloat R_foot = 20.0f;
bool RF_check = 0;
float L_eye_x = 0.5;
float L_eye_y = 0.8;
float R_eye_x = -0.5;
float R_eye_y = 0.8;
float eye_move_x = 0.0001;
float eye_move_y = 0.0001;


void number() {
	int x = 10;
	int y = -15;
	glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x + 2, y);
		glVertex2f(x + 2, y - 2);
		glVertex2f(x, y - 2);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(x + 2, y - 2);
		glVertex2f(x + 2, y - 4);
		glVertex2f(x + 2, y - 4);
		glVertex2f(x, y - 4);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(x + 3, y);
		glVertex2f(x + 5, y);
		glVertex2f(x + 5, y - 2);
		glVertex2f(x + 3, y - 2);
		glVertex2f(x + 3, y - 4);
		glVertex2f(x + 5, y - 4);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex2f(x + 6, y);
		glVertex2f(x + 8, y);
		glVertex2f(x + 8, y - 4);
		glVertex2f(x + 6, y - 4);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(x + 6, y - 2);
		glVertex2f(x + 8, y - 2);
	glEnd();
}

void hand(GLUquadricObj* quadricPtr) {
	glTranslatef(-3, 3.5, 0);
	glRotatef(L_hand, 1, 0, 0); //

	glRotatef(45, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glColor3f(0, 0, 0);
	gluCylinder(quadricPtr, 1, 1, 3, 15, 5);
	glTranslatef(0, 0, 3);
	gluSphere(quadricPtr, 1, 30, 10);
	glTranslatef(0, 0, -3);
	glRotatef(90, 0, 1, 0);
	glRotatef(-45, 0, 0, 1);

	glRotatef(-L_hand, 1, 0, 0); //
	glTranslatef(3, -3.5, 0); //左手


	glTranslatef(3, 3.5, 0);
	glRotatef(R_hand, 1, 0, 0); //

	glRotatef(-45, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glColor3f(0, 0, 0);
	gluCylinder(quadricPtr, 1, 1, 3, 15, 5);
	glTranslatef(0, 0, 3);
	gluSphere(quadricPtr, 1, 30, 10);
	glTranslatef(0, 0, -3);
	glRotatef(-90, 0, 1, 0);
	glRotatef(45, 0, 0, 1);

	glRotatef(-R_hand, 1, 0, 0); //
	glTranslatef(-3, -3.5, 0); //右手
}

void foot(GLUquadricObj* quadricPtr) {
	glRotatef(L_foot, 1, 0, 0);//
	glDisable(GL_CULL_FACE);
	glTranslatef(-1, -3.5, 0);
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
		glVertex3f(-2, 3, 0);
		glVertex3f(0, 1.8, 0);
		glVertex3f(0.2, 0, 0);
		glVertex3f(-2.2, 0, 0);
	glEnd();
	glTranslatef(1, 3.5, 0); //左腳
	glRotatef(-L_foot, 1, 0, 0);//

	glRotatef(R_foot, 1, 0, 0);//
	glTranslatef(1, -3.5, 0);
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
		glVertex3f(0, 1.8, 0);
		glVertex3f(2, 3, 0);
		glVertex3f(2.2, 0, 0);
		glVertex3f(-0.2, 0, 0);
	glEnd();
	glTranslatef(-1, 3.5, 0); //右腳
	glEnable(GL_CULL_FACE);
	glRotatef(-R_foot, 1, 0, 0);//
}

void eye() {
	glTranslatef(-2.3, -0.5, -5);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; ++i)
		glVertex3f(1.5 * sin(2 * 3.14 / n * i), 1.1 * cos(2 * 3.14 / n * i), 0);

	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-1.5, 1.1, 0);
		glVertex3f(1.5, 1.1, 0);
		glVertex3f(1.5, 0, 0);
		glVertex3f(-1.5, 0, 0);
	glEnd();//左眼白

	glTranslatef(L_eye_x, L_eye_y, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
		for (int i = 0; i < 300; ++i)
			glVertex3f(0.4 * sin(2 * 3.14 / n * i), 0.4 * cos(2 * 3.14 / n * i), 0);

	glEnd();
	glTranslatef(-L_eye_x, -L_eye_y, 0);//左眼球

	glTranslatef(4.6, 0, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 300; ++i)
		glVertex3f(1.5 * sin(2 * 3.14 / n * i), 1.1 * cos(2 * 3.14 / n * i), 0);

	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(-1.5, 1.1, 0);
		glVertex3f(1.5, 1.1, 0);
		glVertex3f(1.5, 0, 0);
		glVertex3f(-1.5, 0, 0);
	glEnd();//右眼白

	glTranslatef(R_eye_x, R_eye_y, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
		for (int i = 0; i < 300; ++i)
			glVertex3f(0.4 * sin(2 * 3.14 / n * i), 0.4 * cos(2 * 3.14 / n * i), 0);

	glEnd();
	glTranslatef(-R_eye_y, -R_eye_y, 0);//右眼球
}

void head(GLUquadricObj* quadricPtr) {
	glTranslatef(0, 8, 0);
	glColor3f(0, 0, 0);
	gluSphere(quadricPtr, 5, 30, 10); //頭


	glRotatef(90, 1, 0, 0);
	glTranslatef(-3, 0, -8);

	glTranslatef(-1, 0, 1);
	glRotatef(15, 0, 1, 0);
	gluCylinder(quadricPtr, 0, 2, 6, 5, 5);
	glRotatef(-15, 0, 1, 0);
	glTranslatef(1, 0, -1);

	glTranslatef(2, 0, 0);
	glTranslatef(-0.7, 0, 0);
	glRotatef(10, 0, 1, 0);
	gluCylinder(quadricPtr, 0, 2, 6, 5, 5);
	glRotatef(-10, 0, 1, 0);
	glTranslatef(0.7, 0, 0);

	glTranslatef(2, 0, 0);
	glTranslatef(0.7, 0, 0);
	glRotatef(-10, 0, 1, 0);
	gluCylinder(quadricPtr, 0, 2, 6, 5, 5);
	glRotatef(10, 0, 1, 0);
	glTranslatef(-0.7, 0, 0);

	glTranslatef(2, 0, 0);
	glTranslatef(1, 0, 1);
	glRotatef(-15, 0, 1, 0);
	gluCylinder(quadricPtr, 0, 2, 6, 5, 5);
	glRotatef(15, 0, 1, 0);
	glTranslatef(-1, 0, -1);
	glTranslatef(-3, 0, 8);
	glRotatef(-90, 1, 0, 0);//頭上的角

	glTranslatef(0, 0, -5);
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0, -1.5, 0.0);
		glVertex3f(1.5, -2.5, 0.0);
		glVertex3f(0.0, -2.5, -1.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0, -2.5, -1.0);
		glVertex3f(-1.5, -2.5, 0.0);
		glVertex3f(0.0, -1.5, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0, -2.6, -1.0);
		glVertex3f(1.5, -2.6, 0.0);
		glVertex3f(0.0, -3.4, 1.5);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(0.0, -3.4, 1.5);
		glVertex3f(-1.5, -2.6, 0.0);
		glVertex3f(0.0, -2.6, -1.0);
	glEnd();
	glTranslatef(0, 0, 5);//嘴

	eye();
}

void body(GLUquadricObj* quadricPtr) {
	glColor3f(0, 0, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadricPtr, 3, 4, 6, 15, 5);
	glTranslatef(0, 0, 6);
	gluSphere(quadricPtr, 4, 30, 10); //身體
	glTranslatef(0, 0, 2);
	glRotatef(-90, 1, 0, 0);

	hand(quadricPtr);

	foot(quadricPtr);

	glTranslatef(0, 0, -4);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
		for (int i = 0; i < n; ++i)
			glVertex3f(2.5 * sin(2 * 3.14 / n * i), 2 * cos(2 * 3.14 / n * i), 0);

	glEnd();
	glTranslatef(0, 0, 4); //身體的白
}

void mydisplay() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	number();
	glRotatef(angle, 0, 1, 0);
	GLUquadricObj* quadricPtr;
	quadricPtr = gluNewQuadric();
	gluQuadricNormals(quadricPtr, GLU_LINE);
	gluQuadricTexture(quadricPtr, GLU_NONE);
	gluQuadricDrawStyle(quadricPtr, GLU_FALSE);

	body(quadricPtr);

	head(quadricPtr);

	gluDeleteQuadric(quadricPtr);

	glPopMatrix();

	glFlush();
}

void myidle() {
	if (L_hand > 60.0f)
		LH_check = 1;

	else if(L_hand < -60.0f)
		LH_check = 0;
	
	LH_check ? L_hand -= 0.05 : L_hand += 0.05;

	if (R_hand > 60.0f)
		RH_check = 0;

	else if (R_hand < -60.0f)
		RH_check = 1;

	RH_check ? R_hand += 0.05 : R_hand -= 0.05;

	if (L_foot > 50.0f)
		LF_check = 1;

	else if (L_foot < -10.0f)
		LF_check = 0;

	LF_check ? L_foot -= 0.025 : L_foot += 0.025;

	if (R_foot > 50.0f)
		RF_check = 0;

	else if (R_foot < -10.0f)
		RF_check = 1;

	RF_check ? R_foot += 0.025 : R_foot -= 0.025;


	if (L_eye_x >= 1.3 || L_eye_x <= -0.3)
		eye_move_x = -eye_move_x;

	if (L_eye_y >= 0.8 || L_eye_y <= -0.8)
		eye_move_y = -eye_move_y;

	L_eye_x += eye_move_x;
	R_eye_x += eye_move_x;

	L_eye_y += eye_move_y;
	R_eye_y += eye_move_y;

	if(rotate)
		angle += 0.005;

	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-20.0, 20.0, -20.0 * (GLfloat)h / (GLfloat)w,
			20.0 * (GLfloat)h / (GLfloat)w, -20.0, 20.0);
	else
		glOrtho(-20.0 * (GLfloat)w / (GLfloat)h,
			20.0 * (GLfloat)w / (GLfloat)h, -20.0, 20.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);
}

/*void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glTranslatef(0, 1, 0);
		glFlush();
		break;
	case 'a':
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glTranslatef(-1, 0, 0);
		glFlush();
		break;
	case 's':
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glTranslatef(0, -1, 0);
		glFlush();
		break;
	case 'd':
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glTranslatef(1, 0, 0);
		glFlush();
		break;
	}

}
*/

void mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		rotate = !rotate;
	} // 點擊開始旋轉
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void myinit(void) {
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)ww, 0.0, (GLdouble)wh, -1.0, 1.0);
	glutReshapeFunc(myReshape);
}

void main(int argc, char** argv) {
	glutInitWindowSize(500, 500);
	glutCreateWindow("1102928 coooooool企鵝");
	glutDisplayFunc(mydisplay);
	glutMouseFunc(mouse);
	//glutKeyboardFunc(mykeyboard);
	glutIdleFunc(myidle);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	init();
	myinit();
	glutReshapeFunc(myReshape);

	glutMainLoop();
}

