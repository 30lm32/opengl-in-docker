//Subject: 3D William Tell

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PASSIVE 0
#define ACTIVE 1

#define STOP 0
#define START 1

//keyboard processes
int special_keyboard_key = 0;	// Last key pressed 
unsigned char keyboard_key = ' ';	// Last key pressed 

//for zoom in and zoom out
double magnitude = 0.5;

//rotation processes
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;


//animation for head
int head_mode = START;
double head_alfa = 0; 
double head_step = 0.5;
int head_active = PASSIVE;

//animation for hand
double hand_alfa = 0; 
double hand_step = 0.5;
int hand_active = PASSIVE;

//
double cartmen_x = -1.25;
double cartmen_z = 0.0;
double robotic_hand_z_rotation = 0.0;
double robotic_hand_x_rotation = 0.0;

//oka hareketleri i�in ba�lang�� de�erleri
int result = -1;

double arrow_x = 0.0;
double arrow_y = 0.0;
double arrow_z = 0.0;

//initial size of graphics window.
const int WIDTH  = 950;
const int HEIGHT = 600;

//current size of window.
int width  = WIDTH;
int height = HEIGHT;

//bounds of viewing frustum.
double nearPlane =  5;
double farPlane  = 15;

//viewing angle.
double fovy = 40.0;
//declerations
void idle_arrow(void);
void showstring (GLfloat x, GLfloat y, char *string) ;
int button = 0;
//sphere
void draw_sphere(void)
{
	glutSolidSphere(0.1,20,20);     //radius, lines of longitude, lines of latitude
	glFlush();
}

//cube
void draw_cube(void)
{
	glutSolidCube(0.1);   
	glFlush();
}

//elipsoid
void draw_elipsoid(void)
{
	GLdouble eqn_y[4] = {0.0, 1.0, 0.0, 0};
	
	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	
	glClipPlane(GL_CLIP_PLANE0, eqn_y);
	glEnable(GL_CLIP_PLANE0);
	
	glPushMatrix();
		//glColor3f(0.26,0.67,0.71);
		glScalef(2,0,2);
		draw_sphere();
	glPopMatrix();

	glPushMatrix();
		//glColor3f(0.26,0.67,0.71);
		glScalef(2,3,2);
		draw_sphere();
	glPopMatrix();
	
	glDisable(GL_CLIP_PLANE0);

	glPushMatrix();
		//glColor3f(0.26,0.67,0.71);
		glScalef(2,1.5,2);
		draw_sphere();
	glPopMatrix();
}
//empty cylinder
void draw_empty_cylinder(double base_r,double top_r,double height)
{
	GLUquadricObj *new_quadric = gluNewQuadric(); 
	gluCylinder(new_quadric,base_r, top_r, height,20,20);
	glFlush();
}
//cylinder
void draw_cylinder(double base_r,double top_r,double height)
{
	glPushMatrix();
		draw_empty_cylinder(base_r,top_r,height);
	glPopMatrix();

	glPushMatrix();
		//glTranslatef()
		glScalef(base_r/0.1,base_r/0.1,0.01);
		draw_sphere();
	glPopMatrix();

	glPushMatrix();
		//glTranslatef()
		glTranslatef(0,0,height);
		glScalef(top_r/0.1,top_r/0.1,0.01);
		draw_sphere();
	glPopMatrix();

}
//hair
void draw_hair(void)
{
	glPushMatrix();
		glColor3f(0,0,0);
		glScalef(0.15,1.0,0.1);
		draw_sphere();
	glPopMatrix();

	//hair#1
	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,0,0,1);
		glScalef(0.15,1,0.1);
		draw_sphere();
	glPopMatrix();

	//hair#2
	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(45,0,0,1);
		glScalef(0.15,1,0.1);
		draw_sphere();
	glPopMatrix();

	//hair#3
	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(-45,0,0,1);
		glScalef(0.15,1,0.1);
		draw_sphere();
	glPopMatrix();
}

//eye
void draw_eye(void)
{
	glPushMatrix();
		glColor3f(0,0,0);
		glScalef(0.4,0.4,1);
		draw_sphere();
	glPopMatrix();
}

//nose
void draw_nose(void)
{
	glPushMatrix();
		glColor3f(0,0,0);
		glScalef(0.2,0.5,1);
		draw_sphere();
	glPopMatrix();
}

//up head
void draw_part1_head(void)
{
	GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};

	//hairs
	glPushMatrix();
		glTranslatef(0,0.35,0);
		glRotatef(85,1,0,0);
		glScalef(2.5,2.5,6);
		draw_hair();
	glPopMatrix();

	//left eye
	glPushMatrix();
		glTranslatef(-0.08,0.15,-0.28);
		draw_eye();
	glPopMatrix();
	
	//right eye
	glPushMatrix();
		glTranslatef(0.08,0.15,-0.28);
		draw_eye();
	glPopMatrix();
	
	//nose
	glPushMatrix();
		glTranslatef(0,0.06,-0.31);
		draw_nose();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0,0,0);
		glScalef(4,0,4);
		draw_sphere();
	glPopMatrix();

	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	
	//up of head
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glScalef(4,4,4);
		draw_sphere();
	glPopMatrix();
}

//down head 
void draw_part2_head(void)
{
	GLdouble eqn[4] = {0.0, -1.0, 0.0, 0.0};
	
	glPushMatrix();
		glColor3f(0,0,0);
		glScalef(4,0,4);
		draw_sphere();
	glPopMatrix();
	
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);

	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glScalef(4,4,4);
		draw_sphere();
	glPopMatrix();
}

//complete of head
void draw_head(void)
{
	//up head
	glPushMatrix();
		
		//glRotatef(swing_alfa,1,0,0); //swing_alfa
		glRotatef(head_alfa,0,1,0); //head_alfa
		glTranslatef(0,0.1,0);
		glRotatef(5,0,0,1);
		draw_part1_head();
	glPopMatrix();
	
	//down head
	glPushMatrix();
		glRotatef(-20,1,0,0);
		draw_part2_head();
	glPopMatrix();
}

//hand
void draw_hand(void)
{
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glScalef(0.8,1,0.5);
		draw_sphere();
	glPopMatrix();

	//fingers (left to right)
	//finger#1
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glRotatef(-10,1,0,0);
		glRotatef(10,0,0,1);
		glTranslatef(-0.045,0.1,0);
		glScalef(0.2,1.5,0.25);
		draw_sphere();
	glPopMatrix();

	//finger#2
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glRotatef(5,0,0,1);
		glTranslatef(-0.015,0.12,0);
		glScalef(0.2,1.5,0.25);
		draw_sphere();
	glPopMatrix();

	//finger#3
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glTranslatef(0.015,0.12,0);
		glScalef(0.2,1.5,0.25);
		draw_sphere();
	glPopMatrix();
	
	//finger#4
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glRotatef(-10,1,0,0);
		glTranslatef(0.045,0.1,0);
		glScalef(0.2,1.5,0.25);
		draw_sphere();
	glPopMatrix();

	//finger#5
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glTranslatef(0.01,-0.01,-0.05);
		glRotatef(-70,1,0,0);
		glScalef(0.2,1,0.25);		
		draw_sphere();
	glPopMatrix();
}

//left arm
void draw_left_arm(void)
{
	glPushMatrix();
		glColor3f(0.26,0.67,0.71);
		glTranslatef(0,-0.13,0);
		glScalef(0.3,0.75,0.5);
		glRotatef(180,0,0,1);
		draw_elipsoid();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(hand_alfa,1,0,0);
		glScalef(0.6,0.5,1);
		draw_hand();
	glPopMatrix();
}

//rigt arm
void draw_right_arm(void)
{
	glPushMatrix();
		glScalef(-1,1,1);
		draw_left_arm();
	glPopMatrix();
}

//left_leg
void draw_left_leg(void)
{
	GLdouble eqn[4] = {0.0, 0.0, 1.0, 0.0};
	
	//back of leg
	glPushMatrix();
		glColor3f(0.26,0.67,0.71);
		glTranslatef(0,0,0.05);
		glScalef(0.3,0.4,1);
		draw_elipsoid();
	glPopMatrix();

	//under of shoes
	glPushMatrix();
		glColor3f(1,1,1);
		glRotatef(20,0,0,1);
		glTranslatef(0,0.1,-0.15);
		glScalef(0.75,1.5,0);
		draw_sphere();
	glPopMatrix();

	//shoes
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	glPushMatrix();
		glColor3f(0.26,0.67,0.71);
		glRotatef(20,0,0,1);
		glTranslatef(0,0.1,-0.15);
		glScalef(0.75,1.5,1);
		draw_sphere();
	glPopMatrix();
}

//right_leg
void draw_right_leg(void)
{
	glPushMatrix();
		glScalef(-1,1,1);
		draw_left_leg();
	glPopMatrix();
}

//body
void draw_body(void)
{
	//body	
	glPushMatrix();
		glColor3f(0.26,0.67,0.71);
		glTranslatef(0,-0.2,0);	
		draw_elipsoid();
	glPopMatrix();

	//buttons (up to down)
	glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(15,1,0,0);
		glTranslatef(0,-0.1,-0.145);	
		glScalef(0.2,4,0.3);
		draw_cube();
	glPopMatrix();

	//button#1
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(-0.025,-0.05,-0.155);	
		glScalef(0.15,0.15,0.3);
		draw_sphere();
	glPopMatrix();

	//button#2
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(-0.025,-0.12,-0.175);	
		glScalef(0.15,0.15,0.3);
		draw_sphere();
	glPopMatrix();

	//button#3
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(-0.025,-0.19,-0.185);	
		glScalef(0.15,0.15,0.3);
		draw_sphere();
	glPopMatrix();

	//left leg
	glDisable(GL_CLIP_PLANE0);
	glPushMatrix();
		//glRotatef(-25,0,0,1);
		glTranslatef(-0.125,-0.4,0.0);
		glRotatef(-90,1,0,0);
		draw_left_leg();
	glPopMatrix();

	//right leg
	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glPushMatrix();
		//glRotatef(0,0,0,1);

		glTranslatef(0.125,-0.4,0.0);
		glRotatef(-90,1,0,0);
		//glTranslatef(0.23,-0.22,-0.2);
		draw_right_leg();
	glPopMatrix();
	
	//left arm
	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);

	glPushMatrix();
		glRotatef(-25,0,1,0);
		glTranslatef(-0.35,0.07,0.05);
		glRotatef(70,0,0,1);
		draw_left_arm();
	glPopMatrix();

	//right arm
	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glPushMatrix();
		glRotatef(25,0,1,0);
		glTranslatef(0.35,0.07,0.05);
		glRotatef(-70,0,0,1);
		draw_right_arm();
	glPopMatrix();
}

//ike
void draw_ike(void)
{
	//head
	glPushMatrix();
		glScalef(0.5,0.5,0.5);
		draw_head();
	glPopMatrix();
	
	//body
	glPushMatrix();
		glScalef(0.6,0.5,0.5);
		glTranslatef(0,-0.4,0);
		draw_body();
	glPopMatrix();
}
//wall
void draw_wall(void)
{
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glScalef(0.75,8,20);
		draw_cube();
	glPopMatrix();
}

//apple
void draw_apple(void)
{
	glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(0,0,0);
		glScalef(0.4,0.4,0.4);
		glRotatef(180,0,1,0);
		glRotatef(180,1,0,0);
		draw_elipsoid();
	glPopMatrix();

	//sap
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glTranslatef(0,0.05,0);
		glRotatef(-10,0,0,1);
		glScalef(0.1,1,0.1);
		draw_cube();
	glPopMatrix();

	//leaf#1
	glPushMatrix();
		glColor3f(0,1,0);
		glTranslatef(0.02,0.06,-0.025);
		glRotatef(150,0,1,0);
		glRotatef(110,1,0,0);
		glScalef(0.1,0.125,0.02);
		draw_elipsoid();
	glPopMatrix();

	//leaf#2
	glPushMatrix();
		glColor3f(0,1,0);
		glTranslatef(-0.02,0.06,-0.025);
		glRotatef(-150,0,1,0);
		glRotatef(110,1,0,0);
		glScalef(0.1,0.125,0.02);
		draw_elipsoid();
	glPopMatrix();
}
//lines
void draw_line(void)
{
	//midline
	glPushMatrix();
		glColor3f(1,1,1);
		glScalef(0.25,0.4,20);
		draw_cube();
	glPopMatrix();

	//midpoint
	glPushMatrix();
		glColor3f(1,1,1);
		glScalef(0.5,0.3,0.5);
		draw_sphere();
	glPopMatrix();

	//left line
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(-1.485,0,0);
		glScalef(0.25,0.4,20);
		draw_cube();
	glPopMatrix();

	//back line
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,0,1);
		glScalef(30,0.4,0.25);
		draw_cube();
	glPopMatrix();
	
	//front line
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,0,-1);
		glScalef(30,0.4,0.25);
		draw_cube();
	glPopMatrix();
}


//arrow
void draw_arrow(void)
{
	//head
	glPushMatrix();
		glColor3d(1,1,1);
		draw_cylinder(0.2,0,0.5);
	glPopMatrix();

	//sap
	glPushMatrix();
		glColor3f(0.84,0.75,0.61);
		glTranslatef(0,0,-4);
		draw_cylinder(0.075,0.075,4);
	glPopMatrix();

	//
	glPushMatrix();
		glColor3d(1,1,0);
		glTranslatef(0,0,-4.25);
		draw_empty_cylinder(0.2,0,0.5);
	glPopMatrix();
}

//robotic hand part1
void draw_robotic_hand_part1(void)
{
	//cylinder#1
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,0,-0.75);
		glRotatef(90,0,1,0);
		draw_cylinder(0.5,0.5,4);
	glPopMatrix();

	//cylinder#2
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,0,0.75);
		glRotatef(90,0,1,0);
		draw_cylinder(0.5,0.5,4);
	glPopMatrix();

	//cylinder#3
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,0.75,0);
		glRotatef(90,0,1,0);
		draw_cylinder(0.5,0.5,4);
	glPopMatrix();

	//cylinder#4
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,-0.75,0);
		glRotatef(90,0,1,0);
		draw_cylinder(0.5,0.5,4);
	glPopMatrix();

	//sphere#1
	glPushMatrix();
		glColor3f(1,1,1);
		glScalef(12,12,12);
		draw_sphere();
	glPopMatrix();

	//arrow1
	glPushMatrix();
		glTranslatef(6,0,-0.75);
		glScalef(1.5,1.5,1.5);
		glRotatef(90,0,1,0);
		draw_arrow();
	glPopMatrix();

	//arrow2
	glPushMatrix();
		glTranslatef(6,0,0.75);
		glScalef(1.5,1.5,1.5);
		glRotatef(90,0,1,0);
		draw_arrow();
	glPopMatrix();

	//arrow3
	glPushMatrix();
		glTranslatef(6,0.75,0);
		glScalef(1.5,1.5,1.5);
		glRotatef(90,0,1,0);
		draw_arrow();
	glPopMatrix();

	//arrow4
	glPushMatrix();
		glTranslatef(6,-0.75,0);
		glScalef(1.5,1.5,1.5);
		glRotatef(90,0,1,0);
		draw_arrow();
	glPopMatrix();
}

//robotic hand part2
void draw_robotic_hand_part2(void)
{
	//cylinder
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(-0.4,0,-0.3);
		glRotatef(-80,1,0,0);
		draw_cylinder(0.5,0.5,4);
	glPopMatrix();
	
	//sphere
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(-0.4,4,0.5);
		glScalef(12,12,12);
		draw_sphere();
	glPopMatrix();
}
//robotic hand
void draw_robotic_hand(void)
{
	//part#1
	glPushMatrix();
		glRotatef(head_alfa,1,0,0);
		glRotatef(robotic_hand_z_rotation,0,0,1);
		draw_robotic_hand_part1();
	glPopMatrix();

	//part#2
	glPushMatrix();
		draw_robotic_hand_part2();
	glPopMatrix();
}
//xyz axises
void draw_xyz_axis(void)
{
	//x axis -> red
	glPushMatrix();
		glColor3f(1,0,0);
		glScalef(100,0.02,0.02);
		draw_cube();
	glPopMatrix();

	//y axis -> green
	glPushMatrix();
		glColor3f(0,1,0);
		glScalef(0.025,100,0.025);
		draw_cube();
	glPopMatrix();

	//z axis -> Blue
	glPushMatrix();
		glColor3f(0,0,1);
		glScalef(0.01,0.01,100);
		draw_cube();
	glPopMatrix();
}

//resize window
void change_size(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, GLfloat(width) / GLfloat(height), nearPlane, farPlane);
}

//keyboard
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '+':
			if(magnitude >= 0)
				magnitude += 0.05;
			if(magnitude < 0)
				magnitude -=0.05;
			break;
		case '-':
			if(magnitude >= 0)
				magnitude -= 0.05;
			if(magnitude < 0)
				magnitude +=0.05;
			break;
		case 'w':
			xRot-= 5.0f;
			break;
		case 'z':
			xRot += 5.0f;
			break;
		case 'a':
			yRot -= 5.0f;
			break;
		case 's':
			yRot += 5.0f;
			break;
		case 'e':
			zRot -= 5.0f;
			break;
		case 'd':
			zRot += 5.0f;
			break;
		case 'r':
			button = 1;
			break;
		default:
			break;
	}
	keyboard_key = key;
}

//special keyboard
void special_keyboard(int key, int x, int y)
{	
	switch(key)
	{
		case GLUT_KEY_HOME:
			xRot = 0.0f;
			yRot = 0.0f;
			zRot = 0.0f;
			magnitude = 0.5;
			break;
		case GLUT_KEY_UP:
			if(button != 1) {
				if(robotic_hand_z_rotation < 90) { robotic_hand_z_rotation += 1; }
			}
			break;
		case GLUT_KEY_DOWN:
			if(button != 1) {
				if(robotic_hand_z_rotation > 0) { robotic_hand_z_rotation -= 1; }
			}
			break;
		case GLUT_KEY_LEFT:
			if(button != 1) {
				if(cartmen_x > -1.31) { cartmen_x -= 0.05f; }
			}
			break;
		case GLUT_KEY_RIGHT:
			if(button != 1) {
				if(cartmen_x < -0.1) { cartmen_x += 0.05f; }
			}
			break;
		case GLUT_KEY_PAGE_UP:
			if(button != 1) {
				if(cartmen_z < 0.6) { cartmen_z += 0.05f; }
			}
			break;
		case GLUT_KEY_PAGE_DOWN:
			if(button != 1) {
				if(cartmen_z > -0.6) { cartmen_z -= 0.05f; }
			}
			break;
		case GLUT_KEY_END:
			exit(1);
			break;
		default:
			break;
	}
	special_keyboard_key = key;
	glutPostRedisplay();	
}

//light
void light(void)
{
	GLfloat mat_ambdif[]   = { 1.0, 1.0, 1.0, 1.0 };		// white, doesn't matter
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };// white
   	GLfloat mat_shininess[] = { 50.0 };
   	GLfloat light_position[] = {  7.0, 7.0, -9.0, 0.0 };// directional light (last component = 0) ****
   	glClearColor(0.25, 0.25, 0.25, 0.0);//****
	glMatrixMode(GL_PROJECTION);//!!!!!!!!!!!!!

	// Enable GL_SMOOTH if you have curved surfaces or are using different colors for each vertex
	// (No effect on this example)
   	glShadeModel (GL_SMOOTH);

	// Specular and shininess are optional, some objects won't need them
	// I'm including it here for the sake of completeness
	// See Red Book, chapter 5 for further details
	
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif);	// set both amb and diff components
   	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		// set specular
   	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		// set shininess
   	glLightfv(GL_LIGHT0, GL_POSITION, light_position);		// set light "position", in this case direction
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);		// swing_active material changes by glColor3f(..)
   	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
}

//idle for arrow
void idle_arrow(void) {
	
	if(button == 1)
	{
		
		if(arrow_x < abs(cartmen_x) )
		{

			arrow_x += 0.05*abs(cos(robotic_hand_z_rotation));
			arrow_y += 0.05*abs(sin(robotic_hand_z_rotation));
			printf("Arrow_x= %f Arrow_y= %f Arrow_z= %f\n",arrow_x,arrow_y,cartmen_z);
		}

		else if(abs(cartmen_x) <= arrow_x && arrow_x < 2.5)
		{
			arrow_x += 0.05*abs(cos(robotic_hand_z_rotation));
			arrow_y -= 0.05*abs(sin(robotic_hand_z_rotation));
		}
		else if(arrow_x >= 2.5 )
		{
			cartmen_x = -1.25;
			arrow_x = 0;
			arrow_y = 0;
			button = 0;
			robotic_hand_z_rotation = 0;		
		}
		if(1.8 <= arrow_y && arrow_y <5.0  && 1.15 < arrow_x && arrow_x <= 1.35 && 0.20<=cartmen_z && cartmen_z <0.30)
		{
			result = 1;
		}	
		
	}
}
//idle for head
void idle_head(void)
{
	const double HEAD_ALL_ROUND = 30.0;
	
	if((head_alfa < HEAD_ALL_ROUND) && (head_active == PASSIVE) && (head_mode == START))
	{
		head_alfa += head_step;
	}
	else if((head_alfa >= HEAD_ALL_ROUND) && (head_mode == START))
	{
		head_active = ACTIVE;
	}
	if((head_active == ACTIVE) && (head_mode == START))
	{
		head_alfa -= head_step;

		if(head_alfa == -HEAD_ALL_ROUND)
		{
			head_active = PASSIVE;
		}
	}
}

//idle for hand
void idle_hand(void)
{
	const double HAND_ALL_ROUND = 10.0;
	
	if((hand_alfa < HAND_ALL_ROUND) && (hand_active == PASSIVE))
	{
		hand_alfa += hand_step;
	}
	else if((hand_alfa >= HAND_ALL_ROUND))
	{
		hand_active = ACTIVE;
	}
	if((hand_active == ACTIVE))
	{
		hand_alfa -= hand_step;

		if(hand_alfa == -HAND_ALL_ROUND)
		{
			hand_active = PASSIVE;
		}
	}
}

//idle
void idle_all_of_them(void)
{
	idle_arrow();
	idle_head();
	idle_hand();
	glutPostRedisplay();

}

//display a bit-mapped character string. 
void showstring (GLfloat x, GLfloat y, char *string) 
{
	int len, i;
	glRasterPos2f(x,y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}

//display the value of a property represented as an array with n components. 
void show (GLfloat y, char *name) 
{
	char buf[500];
	showstring(-0.8, y, name);
}

//display the values of all lighting parameters. 
void report()
{	
	char buf[500];
	showstring(-0.8,1.0,"Return first situation : HOME");
	show(0.95f,"Rotate hand: UP-DOWN");
	show(0.9f,"Move on x axis: LEFT-RIGHT");
	show(0.85f,"Move on z axis: PAGE_UP-PAGE_DOWN");
	show(0.8f,"Throw an arrow: r");
	show(0.75f,"Camera Setting: a, s, w, z, e, d");
	show(0.7f,"ZoomIn: +");
	show(0.65f,"ZoomOut: -");
	show(0.6f,"Quit: END");

	if(result == 1)
	{
		strcpy(buf, "You Win!!!");
		showstring(-0.8,0.5,buf);
	}
	else if(result == 0)
	{
		strcpy(buf, "Game Over");
		showstring(-0.8,0.5,buf);
	}

}


//CARTMEN----------------------------------------------------------------
void drawHead() // Kafayi cizen fonksiyon
{
	glPushMatrix();
	glColor3f(0.867,0.718,0.527);
	glScalef(1,0.7,1);
	glTranslatef(0,50,0);
    glutSolidSphere(100,20,20);
	glPopMatrix();
}
void drawHat() // Sapkayi cizen fonksiyon
{
	glPushMatrix();
	GLdouble body[4] = {0.0, 1.0, 0.0, -10.0};
	glColor3f(0.195,0.597,0.796);
	glClipPlane (GL_CLIP_PLANE0, body);	
	glEnable (GL_CLIP_PLANE0);
	glScalef(1,0.7,1);
	glTranslatef(0,55,0);
	glRotatef(-25,1.0,0.0,0.0);
    glutSolidSphere(102,30,30);
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0.644,0);		
	glScalef(1,0.7,1);
	glTranslatef(0,60,0);
	glRotatef(65,1.0,0.0,0.0);
	glutSolidTorus(5,103,10,50);	
	glPopMatrix();

	
	glPushMatrix();
	glColor3f(1,0.644,0);			
	glRotatef(-25,1.0,0.0,0.0);
	glTranslatef(0,90,0);
    glutSolidSphere(40,20,20);	
	glPopMatrix();
}
void drawEyes() //Gozleri cizen fonksiyon
{
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(-20,39,68);
	glRotatef(-35,0,0,1);	
	glScalef(0.8,0.95,0.95);
    glutSolidSphere(40,20,20);	
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(20,39,68);
	glRotatef(35,0,0,1);	
	glScalef(0.8,0.95,0.95);
    glutSolidSphere(40,20,20);	
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(16,39,103);	
	glScalef(0.8,0.95,0.95);
    glutSolidSphere(5,20,20);	
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(-16,39,103);	
	glScalef(0.8,0.95,0.95);
    glutSolidSphere(5,20,20);	
	glPopMatrix();
}


void drawMounthNNose() // Agiz ve burun cizimi
{
	glPushMatrix();
	glColor3f(0,0,0);	
	glTranslatef(0,38,10);
	glRotatef(-38,1.0,0.0,0.0);
	glScalef(1.2,1,1);
	glutSolidTorus(1,78,50,75);	
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);	
	glTranslatef(0,27,41);
	glRotatef(-38,1.0,0.0,0.0);
	glScalef(1.2,1,1);
	glutSolidTorus(2,50,50,75);	
	glPopMatrix();
}

void drawBody() // Govde cizimi
{
	glPushMatrix();
	glColor3f(1,0.1,0.1);
	glScalef(1.3,0.8,0.7);
	glTranslatef(0,-80,-50);
    glutSolidSphere(100,20,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0.1,0.1);
	glScalef(1.3,0.8,0.7);
	glTranslatef(0,-120,-50);
    glutSolidSphere(90,20,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0.1,0.1);
	glScalef(1.3,0.8,0.7);
	glTranslatef(0,-110,-50);
    glutSolidSphere(95,20,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0.1,0.1);
	glScalef(1.1,0.8,0.9);
	glTranslatef(0,-120,-22);
    glutSolidSphere(97,20,20);
	glPopMatrix();
}
void drawArms() // Kollarin cizimi
{
	glPushMatrix();
	glColor3f(1,0.1,0.1);
	glTranslatef(-140,-60,-35);
	glRotatef(40,0,0,1);
	glScalef(2.2,0.7,1);		
	glutSolidSphere(35,20,20);
	glPopMatrix();
}
void drawHands() // Ellerin cizimi
{
	glPushMatrix();
	glColor3f(1,0.644,0);
	glTranslatef(-205,-110,-35);
	glRotatef(-40,0,0,1);
	glScalef(0.6,1,0.2);		
	glutSolidSphere(25,20,20);	
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0.644,0);
	glTranslatef(-205,-110,-35);
	glTranslatef(-10,4,0);
	glRotatef(-70,0,0,1);
	glScalef(0.4,2,0.4);		
	glutSolidSphere(9,20,20);
	glPopMatrix();
}
void drawLegs() // Bacaklarin cizimi
{
	glPushMatrix();
	glColor3f(0.625,0.32,0.175);	
	GLdouble clip[4]={0.0,0.0,-1.0,80};
	glClipPlane(GL_CLIP_PLANE1,clip);
	glEnable(GL_CLIP_PLANE1);
	glTranslatef(40,-120,-30);
	glScalef(1,1,0.75);
	glRotatef(90,1,0,0);
	glutSolidCone(60,200,30,30);
	glDisable(GL_CLIP_PLANE1);	
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.625,0.32,0.175);		
	glClipPlane(GL_CLIP_PLANE1,clip);
	glEnable(GL_CLIP_PLANE1);
	glTranslatef(-40,-120,-30);
	glScalef(1,1,0.75);
	glRotatef(90,1,0,0);
	glutSolidCone(60,200,30,30);
	glDisable(GL_CLIP_PLANE1);	
	glPopMatrix();
}
void drawShoes()  // Ayakkabilar
{
	glPushMatrix();
	glColor3f(0,0.0,0.0);
	glTranslatef(40,-200,-2);	
	glScalef(0.65,0.2,1);		
	glutSolidSphere(65,20,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0.0,0.0);
	glTranslatef(-40,-200,-2);	
	glScalef(0.65,0.2,1);		
	glutSolidSphere(65,20,20);
	glPopMatrix();
}
void draw_cartmen(void)
{

	glPushMatrix();
		glRotatef(-head_alfa,0,1,0);
		drawHat();
		drawHead();
	glPopMatrix();

  glPushMatrix();
	drawEyes();
	drawMounthNNose();
	drawBody();  
	drawArms();  
	drawLegs();
	drawShoes();	
	drawHands();
  glPopMatrix();
}
//CARTMEN----------------------------------------------------------------

void draw_all_of_them(void)
{
	//ike
	glPushMatrix();	
		glTranslatef(1.25,-0.35,0);
		glRotatef(90,0,1,0);
		glScalef(0.75,0.75,0.75);
		draw_ike();
	glPopMatrix();

	//apple
	glPushMatrix();
		glTranslatef(1.25,-0.05,0);
		glScalef(0.75,1,0.75);
		glRotatef(head_alfa,0,1,0);
		draw_apple();
	glPopMatrix();


	//cartmen
	glPushMatrix();
		glTranslatef(cartmen_x,-0.3,cartmen_z);
		glRotatef(90,0,1,0);
		glScalef(0.002,0.002,0.002);
		draw_cartmen();
	glPopMatrix();
	
	//wall
	glPushMatrix();
		glTranslatef(1.47,-0.36,0);
		glRotatef(180,0,1,0);
		draw_wall();
	glPopMatrix();

	//line
	glPushMatrix();
		glTranslatef(0,-0.74,0);
		draw_line();
	glPopMatrix();
	
	//floor
	glPushMatrix();
		glColor3f(0,1,0);
		glTranslatef(0,-0.75,0);
		glScalef(30,0.3,20);
		draw_cube();
	glPopMatrix();

	//arrow
	glPushMatrix();
		if(button == 1)
		{
			glTranslatef(arrow_x+(cartmen_x + 0.275),arrow_y - 0.6,cartmen_z - 0.275);
			glScalef(0.075,0.075,0.075);
		}
		else
		{
			glScalef(0,0,0);
		}
		glRotatef(90,0,1,0);
		draw_arrow();
	glPopMatrix();

	//robotic hand
	glPushMatrix();
		glTranslatef(cartmen_x + -0.05,-0.6,cartmen_z - 0.275);
		glScalef(0.05,0.05,0.05);
		draw_robotic_hand();
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 

	gluLookAt(0,0,0,-10,8,-10,0,1,0); //camera setting
	glPushMatrix();
		glScalef(magnitude,magnitude,magnitude);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		draw_all_of_them();
	glPopMatrix();

	//xyz axises
	glPushMatrix();
		report();
	glPopMatrix();

		
	glutSwapBuffers(); 
	glFlush();
}

//main
int main(int argc, char **argv)
{
	//this is init function
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

	// // game mode is starting here 
	// #ifndef WIN32
	// 	glutGameModeString("1024x768:32@60");
	// #else
	// 	glutGameModeString("width=1024;height=768;bpp=32;");
	// #endif

	// // enter game mode
	// glutEnterGameMode();

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(10,10);
	glutCreateWindow("3D William Tell");

	light();

	glutReshapeFunc(change_size);
	glutDisplayFunc(display);
	glutSpecialFunc(special_keyboard);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle_all_of_them);
	
	glutMainLoop();    
	return 0;
}