// Course: COSC 3P98 
// Project: Assignment 2
// Professor Name: Dr. Brian Ross 
// TA Name: Tennyson Demchuk
// 
// Student Name: Matthew Milne --- Student Num: 5118872 --- Email: mm11ju@brocku.ca
// Date Created: October 20, 2021
// Date Submitted: November 5, 2021
// 
// Redivider Graphics is a "pseudo" company name I created for use in all of my projects

#include "Headers.h"

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < global.vertices.size(); i++)
	{
		glVertex2i(global.vertices[i].x, global.vertices[i].y);
	}
	glEnd();
	glFlush();
	glBegin(GL_LINES);
	if (!global.hullVertices.empty())
	{
		for (int i = 0; i < global.hullVertices.size() - 1; i++)
		{
			if (!global.hullVertices[i].hullEnd)
			{
				glVertex2i(global.hullVertices[i].x, global.hullVertices[i].y);
				glVertex2i(global.hullVertices[i + 1].x, global.hullVertices[i + 1].y);
			}
		}
	}
	glEnd();
	glFlush();
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	//Initialize window
	glutInit(&argc, argv);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("Redivider Graphics");
	global.mainWindow = GetActiveWindow();
	ShowWindow(global.mainWindow, SW_SHOWMAXIMIZED);
	//functions
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, glutGet(GLUT_SCREEN_WIDTH), 0.0, glutGet(GLUT_SCREEN_HEIGHT));
	glutMainLoop();
	return 0;
}