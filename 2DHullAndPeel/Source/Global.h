//this file is for global variables and structures
#pragma once

struct Coordinates
{
	int x;
	int y;
	bool visited;
	bool hullEnd;
};

struct Global
{
	HWND mainWindow;
	std::vector<Coordinates> vertices, workVertices, workNewVertices, hullVertices, tempHullVertices;
	std::vector<int> negativeD, mPress;
	Coordinates coords, coords2, tempCoords, tempCoords2;
	bool r, m;
} global;