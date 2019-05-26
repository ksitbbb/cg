#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416
GLint animation=0;
typedef struct coordinates
{
	GLfloat x,y,z;
} Point3D;

void BinoCoeff(GLint n, GLfloat *bino)
{
	GLint k, j;
	for(k=0;k<=n;k++)
	{
		bino[k]=1;
		for(j=n;j>=k+1; j--)
		bino[k]*=j;                 //bino[k] = n(n-1).....(k+1) = n!/k!
		for(j=n-k;j>=2;j--)
		bino[k]/=j;                 //bino[k] = n!/k!(n-k)(n-k-1)....2 = n!/k!.....(n-k)!
	}
}
void ComputeBezierPt(GLfloat u, Point3D *BezierPt, GLint nCtrlPts, Point3D *CtrlPts, GLfloat *bino)
{
	GLint k, n=nCtrlPts-1;
	GLfloat BezierFcn;
	BezierPt ->x =BezierPt ->y = BezierPt->z=0.0;
	for(k=0; k< nCtrlPts; k++)
	{
		BezierFcn = bino[k] * pow(u, k) * pow( 1-u, n-k);
		BezierPt ->x += CtrlPts[k].x * BezierFcn;
		BezierPt ->y += CtrlPts[k].y * BezierFcn;
		BezierPt ->z += CtrlPts[k].z * BezierFcn;
	}
}

void PlotBezierPts(Point3D *CtrlPts, GLint nCtrlPts, GLint nBezierCurvePts)
{
	Point3D BezierCurvePt;
	GLfloat u;
	GLfloat *bino, k;
	bino= (float *)malloc(nCtrlPts*(sizeof(float)));
	BinoCoeff(nCtrlPts-1, bino);
	glBegin(GL_LINE_STRIP);
	for(k=0; k<=nBezierCurvePts; k++)
	{
		u=(GLfloat)(k)/(GLfloat)(nBezierCurvePts);
		ComputeBezierPt(u, &BezierCurvePt, nCtrlPts, CtrlPts, bino);
		glVertex2f(BezierCurvePt.x, BezierCurvePt.y);
	}
	glEnd();
	free(bino);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLint nCtrlPts=4;
	GLint nBezierCurvePts=30;
	static float theta=0;
	Point3D CtrlPts[4]={{100,410,0},{180,470,0},{260,350,0},{340,410,0}};
	CtrlPts[1].x +=60*sin(theta * PI/180.0);
	CtrlPts[1].y +=40*sin(theta * PI/180.0);
	CtrlPts[2].x -=40*sin((theta+40) * PI/180.0);
	CtrlPts[2].y -=60*sin((theta+50) * PI/180.0);
	CtrlPts[3].x -=30*sin((theta-30) * PI/180.0);
	CtrlPts[3].y +=20*sin((theta-40) * PI/180.0);
	if(animation==2)
	theta+=0.7;
	glPointSize(5);
	glLineWidth(5);
	glPushMatrix();
	glColor3f(1, 0.7, 0.4);//saffron
	for(int i=0;i<25;i++)
	{
		glTranslatef(0, -1.8, 0);
		PlotBezierPts(CtrlPts, nCtrlPts, nBezierCurvePts);
	}

	glColor3f(1, 1, 1); //Indian flag: white color code
	for(int i=0;i<25;i++)
	{
		glTranslatef(0, -1.8, 0);
		PlotBezierPts(CtrlPts, nCtrlPts, nBezierCurvePts);
	}

	glColor3f(0,0.8,0); //Indian flag: green color code
	for(int i=0;i<25;i++)
	{
		glTranslatef(0, -1.8, 0);
		PlotBezierPts(CtrlPts, nCtrlPts, nBezierCurvePts);
	}
	glPopMatrix();
	glColor3f(0.8, 0.8,0.8);
	glBegin(GL_LINES);
	glVertex2f(100,410);
	glVertex2f(100,20);
	glEnd();
	glutPostRedisplay();
	glutSwapBuffers();
}
void init()
{
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,520);
}
void menu(int option)
{
	if(option==1)
		animation=1;
	if(option==2)
		animation=2;
        glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bezier Curve");
	init();
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	glutAddMenuEntry("Flag without animation",1);
	glutAddMenuEntry("Flag with animation",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
