//Subject:South Park Character - Ike Moisha Broflovski

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

#define PASSIVE 0
#define ACTIVE 1

#define STOP 0
#define START 1

//keyboard processes
int special_keyboard_key = 0;	// Last key pressed 
unsigned char keyboard_key = ' ';	// Last key pressed 

//for zoom in and zoom out
double magnitude = 0.65;

//rotation processes
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

//animation for swing
int swing_mode = STOP;
double swing_alfa = 0; 
double swing_step = 2;
int swing_active = PASSIVE;

//animation for head
int head_mode = START;
double head_alfa = 0; 
double head_step = 0.5;
int head_active = PASSIVE;

//animation for head
double hand_alfa = 0; 
double hand_step = 0.5;
int hand_active = PASSIVE;

//initial size of graphics window.
const int WIDTH  = 600;
const int HEIGHT = 600;

//current size of window.
int width  = WIDTH;
int height = HEIGHT;

//bounds of viewing frustum.
double nearPlane =  5;
double farPlane  = 15;

//viewing angle.
double fovy = 40.0;

//sphere
void draw_sphere(void)
{
	glutSolidSphere(0.1,30,30);     //radius, lines of longitude, lines of latitude
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
		glColor3f(0.26,0.67,0.71);
		glScalef(2,0,2);
		draw_sphere();
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.26,0.67,0.71);
		glScalef(2,3,2);
		draw_sphere();
	glPopMatrix();
	
	glDisable(GL_CLIP_PLANE0);

	glPushMatrix();
		glColor3f(0.26,0.67,0.71);
		glScalef(2,1.5,2);
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
		
		glRotatef(swing_alfa,1,0,0); //swing_alfa
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
		glRotatef(-10,1,0,1);
		glTranslatef(0,0.1,-0.15);
		glScalef(0.75,1.5,0);
		draw_sphere();
	glPopMatrix();

	//shoes
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	glPushMatrix();
		glColor3f(0.26,0.67,0.71);
		glRotatef(-10,1,0,1);
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
		glRotatef(25,0,0,1);
		glTranslatef(-0.23,-0.22,-0.2);
		draw_left_leg();
	glPopMatrix();

	//right leg
	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_CLIP_PLANE1);
	glPushMatrix();
		glRotatef(-25,0,0,1);
		glTranslatef(0.23,-0.22,-0.2);
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

//chair
void draw_chair()
{
	//left line
	glPushMatrix();
		glColor3f(0.49,0.51,0.53);
		glTranslatef(-0.22,-0.5,0);
		glScalef(0.1,10,0.1);
		draw_cube();
	glPopMatrix();

	//right line
	glPushMatrix();
		glTranslatef(0.22,-0.5,0);
		glScalef(0.1,10,0.1);
		draw_cube();
	glPopMatrix();

	//wooden seat
	glPushMatrix();
		glColor3f(0.61,0.41,0.21);
		glTranslatef(0,-1.0,0);
		glScalef(5,0.5,2);
		draw_cube();
	glPopMatrix();

	//ike
	glPushMatrix();	
		glTranslatef(0,-0.6,0.080);
		draw_ike();
	glPopMatrix();
}

//up column
void draw_up_column(void)
{
	glPushMatrix();
		glScalef(10,0.5,0.5);
		draw_cube();
	glPopMatrix();
}

//left column
void draw_left_column(void)
{
	glPushMatrix();
		glRotatef(15,1,0,0);
		glTranslatef(-0.475,-0.65,0);
		glScalef(0.5,13,0.5);
		draw_cube();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-15,1,0,0);
		glTranslatef(-0.475,-0.65,0);
		glScalef(0.5,13,0.5);
		draw_cube();
	glPopMatrix();
}

//right column
void draw_right_column(void)
{
	glPushMatrix();
		glScalef(-1,1,1);
		draw_left_column();
	glPopMatrix();
}

//swing
void draw_swing(void)
{
	//chair
	glPushMatrix();
		glRotatef(swing_alfa,1, 0, 0);
		draw_chair();
	glPopMatrix();

	//up column
	glPushMatrix();
		draw_up_column();
	glPopMatrix();

	//left and right column
	glPushMatrix();
		draw_left_column();
		draw_right_column();
	glPopMatrix();

}


//all of them
void draw_all_of_them(void)
{
	glPushMatrix();
		glTranslatef(0,0.5,0);
		draw_swing();
	glPopMatrix();

	//floor
	glPushMatrix();
		glColor3f(0,1,0);
		glTranslatef(0,-0.75,0);
		glScalef(20,0.3,20);
		draw_cube();
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
			swing_alfa = 0.0f;
			swing_active = PASSIVE;
			swing_mode = STOP;
			magnitude = 0.65;
			break;
		case GLUT_KEY_UP:
			xRot-= 5.0f;
			break;
		case GLUT_KEY_DOWN:
			xRot += 5.0f;
			break;
		case GLUT_KEY_LEFT:
			yRot -= 5.0f;
			break;
		case GLUT_KEY_RIGHT:
			yRot += 5.0f;
			break;
		case GLUT_KEY_PAGE_UP:
			zRot -= 5.0f;
			break;
		case GLUT_KEY_PAGE_DOWN:
			zRot += 5.0f;
			break;
		case GLUT_KEY_END:
			exit(1);
			break;
		default:
			break;
	}

	if(key > 356.0f)
		xRot = 0.0f;

	if(key < -1.0f)
		xRot = 355.0f;

	if(key > 356.0f)
		yRot = 0.0f;

	if(key < -1.0f)
		yRot = 355.0f;

	if(key > 356.0f)
		zRot = 0.0f;

	if(key < -1.0f)
		zRot = 355.0f;

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
   	glClearColor(1.0, 1.0, 1.0, 1.0);//****
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

//menu
void menu(int option)
{
	switch(option)
	{
		case 1:
			swing_alfa = 0.0;
			swing_step = 5.0;
			swing_mode = START;
			head_alfa = 0.0;
			head_mode = STOP;
			break;
		case 2:
			swing_alfa = 0.0;
			swing_step = 2.0;
			swing_mode = START;
			head_alfa = 0.0;
			head_mode = STOP;
			break;
		case 3:
			swing_alfa = 0.0;
			swing_step = 1.0;
			swing_mode = START;
			head_alfa = 0.0;
			head_mode = STOP;
			break;
		case 4:
			swing_mode = START;
			head_alfa = 0.0;
			head_mode = STOP;
			break;
		case 5:
			swing_mode = STOP;
			head_mode = START;
			break;
		case 6:
			exit(1);
			break;
		default:
			break;
	}
}

//create menu
void create_menus(void)
{
	glutCreateMenu(menu);
	glutAddMenuEntry("Faster",1);
	glutAddMenuEntry("Normal",2);
	glutAddMenuEntry("Slower",3);
	glutAddMenuEntry("Start",4);
	glutAddMenuEntry("Stop",5);
	glutAddMenuEntry("Quit",6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//idle for swing
void idle_swing(void)
{
	const double SWING_ALL_ROUND = 90.0;
	
	if((swing_alfa < SWING_ALL_ROUND) && (swing_active == PASSIVE) && (swing_mode == START))
	{
		swing_alfa += swing_step;
	}
	else if((swing_alfa >= SWING_ALL_ROUND) && (swing_mode == START))
	{
		swing_active = ACTIVE;
	}
	if((swing_active == ACTIVE) && (swing_mode == START))
	{
		swing_alfa -= swing_step;

		if(swing_alfa == -SWING_ALL_ROUND)
		{
			swing_active = PASSIVE;
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
	idle_swing();
	idle_head();
	idle_hand();
	glutPostRedisplay();
}

//display a bit-mapped character string. 
void showstring (GLfloat x, GLfloat y, char *string) 
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}

//display the value of a property represented as an array with n components. 
void show (GLfloat y, char *name) 
{
	char buf[100];
	showstring(-1.4, y, name);
}

//display the values of all lighting parameters. 
void report()
{	
	char buf[100];
	showstring(-1.4,0.5,"Return first situation : HOME");
	show(0.45f,"Rotate at x axis: UP-DOWN");
	show(0.4f,"Rotate at y axis: LEFT-RIGHT");
	show(0.35f,"Rotate at z axis: PAGE_UP-PAGE_DOWN");
	show(0.3f,"ZoomIn: +");
	show(0.25f,"ZoomOut: -");
	show(0.2f,"Quit: END");
	show(0.15f,"Animation: RIGHT_CLICK");
	show(0.14f,"_____________________________________");
	switch (keyboard_key) 
	{
		case '+':
			strcpy(buf, "ZoomIn (+)");
			break;
		case '-':
			strcpy(buf, "ZoomOut (-)");
			break;
	}
	switch(special_keyboard_key)
	{
		case GLUT_KEY_HOME:
			strcpy(buf, "Returned First Situation...");
			break;
		case GLUT_KEY_UP:
			strcpy(buf, "Rotated at x axis (-)");
			break;
		case GLUT_KEY_DOWN:
			strcpy(buf, "Rotated at x axis (+)");
			break;
		case GLUT_KEY_LEFT:
			strcpy(buf, "Rotated at y axis (-)");
			break;
		case GLUT_KEY_RIGHT:
			strcpy(buf, "Rotated at y axis (+)");
			break;
		case GLUT_KEY_PAGE_UP:
			strcpy(buf, "Rotated at z axis (-)");
			break;
		case GLUT_KEY_PAGE_DOWN:
			strcpy(buf, "Rotated at z axis (+)");
			break;
		case GLUT_KEY_END:
			strcpy(buf, "Bye bye :)");
			break;
		default:
			break;
	}
	showstring(-1.4,0.05,buf);
}

//display
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 

	gluLookAt(0,0,0,10,8,-10,0,1,0); //camera setting
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
		draw_xyz_axis();
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

	glutInitWindowSize(width,height);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Ike Moisha Broflovski");
	
	light();

	glutReshapeFunc(change_size);
	glutDisplayFunc(display);
	glutSpecialFunc(special_keyboard);
	glutKeyboardFunc(keyboard);
	create_menus();
	glutIdleFunc(idle_all_of_them);
	
	glutMainLoop();    
	return 0;
}
