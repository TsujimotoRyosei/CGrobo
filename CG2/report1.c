#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#define	imageWidth 256
#define	imageHeight 256

static int head = 0, shoulder = 0, elbow = 0, hand = 0, hip_joint = 0, samplingTime = 180, shoulder_direction = 0, hip_direction = 0, angle = 0;
unsigned char	mouseFlag = GL_FALSE, texImage[imageHeight][imageWidth][3];
int				xStart, yStart, select = 1;
double			xAngle = 0.0, yAngle = 0.0, z = 0.0;

void myInit(char* progname)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
}

void readPPMImage(char* filename)
{
	FILE* fp;
	int  ch, i;

	if (fopen_s(&fp, filename, "r") != 0) {
		fprintf(stderr, "Cannot open ppm file %s\n", filename);
		exit(1);
	}
	fread(texImage, 1, imageWidth * imageHeight * 3, fp);
	fclose(fp);
}

void setUpTexture1(void)
{
	readPPMImage("robot.ppm");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,
		0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
}

void setUpTexture2(void)
{
	readPPMImage("ground.ppm");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,
		0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
}

void setUpTexture3(void)
{
	readPPMImage("body.ppm");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,
		0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
}

void setUpTexture4(void)
{
	readPPMImage("leg.ppm");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,
		0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
}

void setUpTexture5(void)
{
	readPPMImage("arm.ppm");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,
		0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
	glTexGenf(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenf(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
}

void mySetlight()
{
	float light_position[] = { 3.0, 10.0, 1.0, 1.0 };
	float light_ambient[] = { 0.3, 0.4, 0.2, 1.0 };
	float light_diffuse[] = { 0.6, 0.5, 0.3, 1.0 };
	float light_specular[] = { 1.0, 0.0, 0.5, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHT0);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);


	glPushMatrix();

	glRotated(xAngle, 1.0, 0.0, 0.0);
	glRotated(yAngle, 0.0, 1.0, 0.0);

	setUpTexture5();
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	/* left shoulder */
	glTranslated(0.2, 1.0, z);
	glRotated((double)shoulder, 1.0, 0.0, 0.0);
	glTranslated(1.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.4, 2.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/* left elbow */
	glTranslated(-1.0, -2.0, 0.0);
	glRotated((double)elbow, 1.0, 0.0, 0.0);
	glTranslated(1.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.4, 2.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/* left hand */
	glTranslated(-1.0, -1.4, 0.0);
	glRotated((double)hand, 1.0, 0.0, 0.0);
	glTranslated(1.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.4, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	/* head */
	setUpTexture1();
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslated(0.0, 2.3, z);
	glRotated((double)head, 1.0, 0.0, 0.0);
	glScaled(1.0, 0.6, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	/* body */
	setUpTexture3();
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslated(0.0, 0.0, z);
	glScaled(2.0, 4.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	setUpTexture4();
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	/* left hip joint */
	glTranslated(-0.3, -2.7, z);
	glRotated((double)hip_joint, 1.0, 0.0, 0.0);
	glTranslated(1.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.6, 1.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/* left knee */
	glTranslated(0.0, -1.2, 0.0);
	glPushMatrix();
	glScaled(0.6, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/* left foot */
	glTranslated(0.0, -0.7, 0.2);
	glPushMatrix();
	glScaled(0.6, 0.4, 1.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	setUpTexture5();
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	/* right shoulder */
	glTranslated(-0.2, 1.0, z);
	glRotated(-(double)shoulder, 1.0, 0.0, 0.0);
	glTranslated(-1.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.4, 2.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/* right elbow */
	glTranslated(1.0, -2.0, 0.0);
	glRotated(-(double)elbow, 1.0, 0.0, 0.0);
	glTranslated(-1.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.4, 2.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/* right hand */
	glTranslated(1.0, -1.4, 0.0);
	glRotated(-(double)hand, 1.0, 0.0, 0.0);
	glTranslated(-1.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.4, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	/* right hip joint */
	setUpTexture4();
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslated(0.3, -2.7, z);
	glRotated(-(double)hip_joint, 1.0, 0.0, 0.0);
	glTranslated(-1.0, 0.0, 0.0);
	glPushMatrix();
	glScaled(0.6, 1.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/* right knee */
	glTranslated(0.0, -1.2, 0.0);
	glPushMatrix();
	glScaled(0.6, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/* right foot */
	glTranslated(0.0, -0.7, 0.2);
	glPushMatrix();
	glScaled(0.6, 0.4, 1.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	setUpTexture2();
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslated(0.0, -5.0, 0.0);
	glPushMatrix();
	glScaled(30.0, 0.4, 40.0);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glutSwapBuffers();
}

void getValueFromMenu(int value)
{
	switch (value) {
	case 1:
		select = 0;
		break;
	case 2:
		select = 1;
		break;
	default:
		break;
	}
}
void mySetMenu()
{
	glutCreateMenu(getValueFromMenu);
	glutAddMenuEntry("STOP", 1);
	glutAddMenuEntry("MOVE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void myReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)width / (double)height, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void myTimer(int value)
{
	if (value == 1)
	{
		glutTimerFunc(samplingTime, myTimer, select);
		if (shoulder_direction == 0)
		{
			shoulder = (shoulder + 5) % 360;
			elbow = (elbow + 1) % 360;
			hand = (hand + 1) % 360;
			head = (head + 1) % 360;
			if (shoulder == 10)
			{
				shoulder_direction = 1;
			}
		}
		else if (shoulder_direction == 1)
		{
			shoulder = (shoulder - 5) % 360;
			elbow = (elbow - 1) % 360;
			hand = (hand - 1) % 360;
			head = (head - 1) % 360;
			if (shoulder == -20)
			{
				shoulder_direction = 0;
			}
		}
		if (hip_direction == 0)
		{
			hip_joint = (hip_joint + 5) % 360;
			z += 0.1;
			if (hip_joint == 15)
			{
				hip_direction = 1;
			}
		}
		else if (hip_direction == 1)
		{
			hip_joint = (hip_joint - 5) % 360;
			if (hip_joint == -15)
			{
				hip_direction = 0;
			}
		}
		glutPostRedisplay();
	}
	if (value == 0)
	{
		glutTimerFunc(samplingTime, myTimer, select);
		if (shoulder_direction == 0)
		{
			shoulder = (shoulder + 0) % 360;
			elbow = (elbow + 0) % 360;
			hand = (hand + 0) % 360;
			head = (head + 0) % 360;
			if (shoulder == 30)
			{
				shoulder_direction = 1;
			}
		}
		else if (shoulder_direction == 1)
		{
			shoulder = (shoulder - 0) % 360;
			elbow = (elbow - 0) % 360;
			hand = (hand - 0) % 360;
			head = (head - 0) % 360;
			if (shoulder == 0)
			{
				shoulder_direction = 0;
			}
		}
		if (hip_direction == 0)
		{
			hip_joint = (hip_joint + 0) % 360;
			if (hip_joint == 15)
			{
				hip_direction = 1;
			}
		}
		else if (hip_direction == 1)
		{
			hip_joint = (hip_joint - 0) % 360;
			if (hip_joint == -15)
			{
				hip_direction = 0;
			}
		}
		glutPostRedisplay();
	}
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's':
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'S':
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'E':
		elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'h':
		hand = (hand + 5) % 360;
		glutPostRedisplay();
		break;
	case 'H':
		hand = (hand - 5) % 360;
		glutPostRedisplay();
		break;
	case 'j':
		hip_joint = (hip_joint + 5) % 360;
		glutPostRedisplay();
		break;
	case 'J':
		hip_joint = (hip_joint - 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		head = (head + 5) % 360;
		glutPostRedisplay();
		break;
	case 'A':
		head = (head - 5) % 360;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void myMouseMotion(int x, int y)
{
	int		xdis, ydis;
	double	a = 0.5;

	if (mouseFlag == GL_FALSE) return;
	xdis = x - xStart;
	ydis = y - yStart;
	xAngle += (double)ydis * a;
	yAngle += (double)xdis * a;

	xStart = x;
	yStart = y;
	glutPostRedisplay();
}

void myMouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xStart = x;
		yStart = y;
		mouseFlag = GL_TRUE;
	}
	else {
		mouseFlag = GL_FALSE;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	myInit(argv[0]);
	mySetMenu();
	mySetlight();
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouseFunc);
	glutMotionFunc(myMouseMotion);
	glutTimerFunc(samplingTime, myTimer, select);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
