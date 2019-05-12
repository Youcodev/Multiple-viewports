//This code creates 6 viewports, each of which has its own drawing and camera

#include <GL\freeglut.h>

int width = 800, height = 450; //Entire window dimensions (containing the viewports set)

void reshapeWindow(int w, int h) { //Callback function passed to glutReshapeFunc()
	width = w; height = h; //New window's dimensions
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//Use the Projection Matrix
	//This matrix determines how the 3D scene is transformed into a 2D (screen space) one
	glMatrixMode(GL_PROJECTION);
	//Reset Matrix
	glLoadIdentity();
	//Set the correct perspective
	//A perspective projection makes objects look smaller as they move away (like they do in the real world)
	gluPerspective(30, 450/150, 0.1, 100);
	//We can use glFrustum instead of gluPerspective
	//glutPerspective(fovy, aspect, zNear, zFar) ---> glFrustum(left, right, bottom, top, near, far)
	//glFrustum arguments can be calculated from those of glutPerspective as suggested in the following link
	//http://nehe.gamedev.net/article/replacement_for_gluperspective/21002/
	//near = zNear, far = zFar, top = -bottom = zNear * tan(fovy/2) and right = -left = top * aspect
	//glFrustum(-0.0804, 0.0804, -0.0268, 0.0268, 0.1, 100.0);
	//Get Back to the Modelview
	//This matrix position the scene objects in the world space
	//Switch back to this matrix for any drawing commands that follow
	glMatrixMode(GL_MODELVIEW);
}

void drawSquare() { //Drawing in immediate mode
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, -0.5f, 0.f); //Lower left vertex
	glVertex3f(0.5f, -0.5f, 0.f); //Lower right vertex
	glVertex3f(0.5f, 0.5f, 0.f); //Upper right vertex
	glVertex3f(-0.5f, 0.5f, 0.f); //Upper left vertex
	glEnd();
}

void display() { //Rendering function
	static float ang = 0.f; //Angle of rotation
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.f, 1.f, 0.f); //Set current color to yellow
	//Set the viewport to the bottom-left window
	//The viewport is the portion of the window used for the drawing
	glViewport(0, 0, width / 2, height/3);
	//Reset transformations
	glLoadIdentity();
	//Set the camera
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glRotatef(ang, 0.f, 0.f, 1.f);
	drawSquare();
	//glutWireTeapot(.7);
	//Set the viewport to the middle-left window
	glViewport(0, height / 3, width / 2, height / 3);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glRotatef(ang, 1.f, 0.f, 0.f);
	drawSquare();
	//glutWireTeapot(.7);
	//Set the viewport to the top-left window
	glViewport(0, 2 * height / 3, width / 2, height / 3);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glRotatef(ang, 0.f, 1.f, 0.f);
	drawSquare();
	//glutWireTeapot(.7);
	glColor3f(0.f, 0.f, 1.f); //Set current color to blue
	//Set the viewport to the bottom-right window
	glViewport(width / 2, 0, width / 2, height / 3);
	glLoadIdentity();
	gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);
	glRotatef(ang, 0.f, 0.f, 1.f);
	drawSquare();
	//glutWireTeapot(.7);
	//Set the viewport to the middle-right window
	glViewport(width / 2, height / 3, width / 2, height / 3);
	glLoadIdentity();
	gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);
	glRotatef(ang, 1.f, 0.f, 0.f);
	drawSquare();
	//glutWireTeapot(.7);
	//Set the viewport to the top-right window
	glViewport(width / 2, 2 * height / 3, width / 2, height / 3);
	glLoadIdentity();
	gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);
	glRotatef(ang, 0.f, 1.f, 0.f);
	drawSquare();
	//glutWireTeapot(.7);

	if (ang == 360)
		ang = 0.f;
	else
		ang += 2.f;
	
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow("Multiple viewports");
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeWindow);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}