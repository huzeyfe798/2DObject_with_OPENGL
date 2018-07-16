#include <GL/glut.h>
#include<iostream>
#include <ctime>


using namespace std;



struct points {

	GLfloat x, y;
	points() { x = 0.0; y = 0.0; }
	points(GLfloat ax, GLfloat ay) : x(ax),y(ay){}
};

struct Colors {

	GLfloat r,g,b;
	Colors() { r = 0.0; g = 0.0;  b = 0.0; }
	Colors(GLfloat ar, GLfloat ag, GLfloat ab) {
		r = ar;
		g = ag;
		b = ab;
	}


};

class rectangle {
public:
	points pts[4];
	Colors rec;
	

	rectangle() {
		pts[0] = points(40, 160);
		pts[1] = points(40, 280);
		pts[2] = points(280, 280);
		pts[3] = points(280, 160);

		
	}


};

class triangle {
public:
	points pts1[3];
	Colors tri;
	
	triangle() {
		pts1[0] = points(360, 80);
		pts1[1] = points(600, 80);
		pts1[2] = points(480, 320);

		tri.r = 0.0;
		tri.g = 0.632;
		tri.b = 0.90625;
		}
};

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 640.0, 0.0, 360.0);
}

void exitkey(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
	{
		exit(0);
	}
}
int bx = 0;
int by = 0;
int last_x = 0;
int last_y = 0;
int confirm = 0;

rectangle *rec1 = new rectangle;
triangle *tri1 = new triangle;
void changecolormouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON &&
		state == GLUT_DOWN) {
		if (x >= tri1->pts1[0].x && x <= tri1->pts1[2].x && (360-y) >= tri1->pts1[0].y && (360-y) <= tri1->pts1[2].y) {
			if (((tri1->pts1[2].y - tri1->pts1[0].y) / (tri1->pts1[2].x - tri1->pts1[0].x)) >= ((360 - y) - tri1->pts1[0].y)/((x - tri1->pts1[0].x) )) {
				srand(time(0));
				GLfloat ry = static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
				GLfloat gy = static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
				GLfloat by = static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
				tri1->tri.r = ry;
				tri1->tri.g = gy;
				tri1->tri.b = by;

				glutPostRedisplay();

			}
		}
		if (x <= tri1->pts1[1].x && x >= tri1->pts1[2].x && (360 - y) >= tri1->pts1[1].y && (360 - y) <= tri1->pts1[2].y) {
			if (((tri1->pts1[2].y - tri1->pts1[1].y) / (tri1->pts1[2].x - tri1->pts1[1].x)) <= ((360 - y) - tri1->pts1[1].y) / ((x - tri1->pts1[1].x))) {
				srand(time(0));
				GLfloat ry = static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
				GLfloat gy = static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
				GLfloat by = static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
				tri1->tri.r = ry;
				tri1->tri.g = gy;
				tri1->tri.b = by;

				glutPostRedisplay();

			}
		}
		if (x >= rec1->pts[0].x && x <= rec1->pts[2].x && (360 - y) >= rec1->pts[0].y && (360 - y) <= rec1->pts[2].y) {
			last_x = x;
			last_y = y;
			confirm = state == GLUT_DOWN;
			
		
		}
		
		
		
	}
}
void motion_func_rectangle(int x, int y) {
	if (x >= rec1->pts[0].x && x <= rec1->pts[2].x && (360 - y) >= rec1->pts[0].y && (360 - y) <= rec1->pts[2].y) {

		if (confirm) {
			bx = x - last_x;
			by = y - last_y;
		}
		rec1->pts[0].x += bx;
		rec1->pts[1].x += bx;
		rec1->pts[2].x += bx;
		rec1->pts[3].x += bx;
		rec1->pts[0].y -= by;
		rec1->pts[1].y -= by;
		rec1->pts[2].y -= by;
		rec1->pts[3].y -= by;
		glutPostRedisplay();
		last_x = x;
		last_y = y;
	}
}







void drawing(rectangle a, triangle b) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(a.rec.r, a.rec.g,a.rec.b);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_POLYGON);
	glVertex2i(a.pts[0].x,a.pts[0].y);
	glVertex2i(a.pts[1].x, a.pts[1].y);
	glVertex2i(a.pts[2].x, a.pts[2].y);
	glVertex2i(a.pts[3].x, a.pts[3].y);
	glEnd();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(b.tri.r, b.tri.g, b.tri.b);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_TRIANGLES);
	glVertex2i(b.pts1[0].x, b.pts1[0].y);  
	glVertex2i(b.pts1[1].x, b.pts1[1].y);  
	glVertex2i(b.pts1[2].x, b.pts1[2].y);  
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawing(*rec1,*tri1);

	glFlush();
}
int main(GLint argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 360);
	glutCreateWindow("HomeWork I");
	
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(exitkey);
	glutMotionFunc(motion_func_rectangle);
	
	glutMouseFunc(changecolormouse);
	
	

	glutMainLoop();

	return 0;
}
