#pragma once
#include "SDL_ttf.h"
#include <iostream>
#include "SDL_mixer.h"
#include "mesh.h"

class ResourcePool
{
public:
	static ResourcePool* GetInstance();
	void Clear();

	TTF_Font* GetFont();
	Mesh GetAsteroidBigMesh();
	Mesh GetAsteroidMediumMesh();
	Mesh GetAsteroidSmallMesh();
	Mesh GetAlienMesh();

private:
	ResourcePool();
	~ResourcePool();
	static ResourcePool* instance;

	// Font
	const char* _fontPath = "Assets/Retroica.ttf";
	const int _fontSize = 24;
	TTF_Font* _font;

	// Mesh
	const char* _asteroidBigMeshPath = "Assets/asteroid_big.obj";
	const char* _asteroidMediumMeshPath = "Assets/asteroid_medium.obj";
	const char* _asteroidsmallMeshPath = "Assets/asteroid_small.obj";
	const char* _alienMeshPath = "Assets/alien.obj";

	Mesh _asteroidBigMesh;
	Mesh _asteroidMediumMesh;
	Mesh _asteroidSmallMesh;
	Mesh _alienMesh;
};

