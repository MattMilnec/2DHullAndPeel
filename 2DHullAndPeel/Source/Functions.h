//this file contains all the functions used to create the data structures for the points and hulls
#pragma once

//function used to create random coordinates and saves them in a data structure
void randomCoords(int value)
{
	for (int j = 0; j < value; j++)
	{
		bool quit = false;
		while (!quit)
		{
			bool same = false;
			int x = rand() % (glutGet(GLUT_SCREEN_WIDTH) - 5) + 5;
			int y = rand() % (glutGet(GLUT_SCREEN_HEIGHT) - 15) + 5;

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

//function used to create the hull and stores it in a data structure
void hull(std::vector<Coordinates>& tempVertices)
{
	global.tempHullVertices.clear();
	global.coords = tempVertices[0];
	for (int i = 0; i < tempVertices.size(); i++)
	{
		if (tempVertices[i].x < global.coords.x)
			global.coords = tempVertices[i];
	}
	global.hullVertices.push_back(global.coords);
	global.tempHullVertices.push_back(global.coords);
	for (int i = 0; i < global.workVertices.size(); i++)
	{
		if (global.coords.x == global.workVertices[i].x && global.coords.y == global.workVertices[i].y)
			global.workVertices[i].visited = true;
	}
	bool quit = false;
	while (!quit)
	{
		for (int i = 0; i < tempVertices.size(); i++)
		{
			if (tempVertices[i].x == global.coords.x && tempVertices[i].y == global.coords.y)
			{
			} //do nothing 
			else
			{
				global.coords2 = tempVertices[i];
				int a = global.coords.y - global.coords2.y;
				int b = global.coords2.x - global.coords.x;
				int c = global.coords.x * global.coords2.y - global.coords.y * global.coords2.x;
				for (int j = 0; j < tempVertices.size(); j++)
				{
					if (tempVertices[j].x == global.coords2.x && tempVertices[j].y == global.coords2.y)
					{
					} //do nothing 
					else
					{
						int d = a * tempVertices[j].x + b * tempVertices[j].y + c;
						if (d < 0)
						{
							global.negativeD.push_back(d);
							break;
						}
						if (d == 0)
						{
							if (global.coords.x != global.coords2.x)
							{
								if (global.coords.x < global.coords2.x)
								{
									global.tempCoords = global.coords;
									global.tempCoords2 = global.coords2;
								}
								else if (global.coords.x > global.coords2.x)
								{
									global.tempCoords = global.coords2;
									global.tempCoords2 = global.coords;
								}
								if (tempVertices[j].x > global.tempCoords.x && tempVertices[j].x < global.tempCoords2.x)
									global.negativeD.push_back(d);
							}
							else if (global.coords.x == global.coords2.x)
							{
								if (global.coords.y < global.coords2.y)
								{
									global.tempCoords = global.coords;
									global.tempCoords2 = global.coords2;
								}
								if (global.coords.y > global.coords2.y)
								{
									global.tempCoords = global.coords2;
									global.tempCoords2 = global.coords;
								}
								if (tempVertices[j].y > global.tempCoords.y && tempVertices[j].y < global.tempCoords2.y)
									global.negativeD.push_back(d);
							}

						}
					}
				}
				if (global.negativeD.empty())
				{
					global.hullVertices.push_back(tempVertices[i]);
					global.tempHullVertices.push_back(tempVertices[i]);
					for (int j = 0; j < global.workVertices.size(); j++)
					{
						if (global.coords2.x == global.workVertices[j].x && global.coords2.y == global.workVertices[j].y)
							global.workVertices[j].visited = true;
					}
					for (int j = 0; j < global.tempHullVertices.size(); j++)
					{
						for (int k = 0; k < global.tempHullVertices.size(); k++)
						{
							if (global.tempHullVertices[k].x == global.tempHullVertices[j].x &&
								global.tempHullVertices[k].y == global.tempHullVertices[j].y && k != j)
							{
								for (int m = global.hullVertices.size() - 1; m >= 0; m--)
								{
									if (global.tempHullVertices[j].x == global.hullVertices[m].x &&
										global.tempHullVertices[j].y == global.hullVertices[m].y)
									{
										global.hullVertices[m].hullEnd = true;
										break;
									}
								}
								quit = true;
							}
						}
					}
				}
				else
				{
					global.negativeD.clear();
				}
			}
		}
		global.coords = global.hullVertices[global.hullVertices.size() - 1];
	}
}

//function removes vertices that are on the hull
void cutVertices()
{
	for (int i = 0; i < global.workVertices.size(); i++)
	{
		if (!global.workVertices[i].visited)
		{
			global.workNewVertices.push_back(global.workVertices[i]);
		}
	}
}

// calls hull on remaining vertices to create a peel
void peel()
{
	bool quit = false;
	while (!quit)
	{
		hull(global.workNewVertices);
		global.workNewVertices.clear();
		cutVertices();
		if (global.workNewVertices.size() < 3)
			quit = true;
	}
}

//resets all data structures 
void resetData()
{
	global.vertices.clear();
	global.workVertices.clear();
	global.workNewVertices.clear();
	global.hullVertices.clear();
	global.tempHullVertices.clear();
	global.negativeD.clear();
	global.coords.hullEnd = false;
	global.coords.visited = false;
}