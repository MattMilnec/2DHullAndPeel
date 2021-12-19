//this file contains all the user input keyboard and mouse functions
#pragma once

void mouse(int button, int state, int a, int b)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		bool quit = false;
		while (!quit)
		{
			bool same = false;
			int x = a;
			int y = glutGet(GLUT_SCREEN_HEIGHT) - b;
			std::cout << b << "\n";

			for (int i = 0; i < global.vertices.size(); i++)
			{
				if (global.vertices[i].x == x && global.vertices[i].y == y)
					same = true;
			}
			if (!same)
			{
				global.coords.x = x;
				global.coords.y = y;
				global.vertices.push_back(global.coords);
				global.workVertices.push_back(global.coords);
				global.workNewVertices.push_back(global.coords);
				quit = true;
			}
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'Q':
	case 'q':
		exit(0);
		break;
	case 'r':
		SetForegroundWindow(GetConsoleWindow());
		ShowWindow(GetConsoleWindow(), SW_NORMAL);
		resetData();
		int value;
		std::cout << "\nEnter the amount of vertices to render: ";
		std::cin >> value;
		ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
		randomCoords(value);
		global.r = true;
		glutPostRedisplay();
		break;
	case 'm':
		global.mPress.push_back(1);
		if (global.mPress.size() <= 1)
		{
			resetData();
			glutMouseFunc(mouse);
			global.m = true;
			glutPostRedisplay();
		}
		if (global.mPress.size() >= 2)
			glutMouseFunc(NULL);
		break;
	case 'c':
		if (global.r || global.m)
			peel();
		global.r = false;
		global.m = false;
		global.mPress.clear();
		glutMouseFunc(NULL);
		glutPostRedisplay();
		break;
	}
}