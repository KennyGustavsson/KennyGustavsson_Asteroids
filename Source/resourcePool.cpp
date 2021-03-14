#include "resourcePool.h"

ResourcePool* ResourcePool::instance = 0;

ResourcePool* ResourcePool::GetInstance()
{
	if (instance == 0)
		instance = new ResourcePool();

	return instance;
}

void ResourcePool::Clear()
{
	TTF_CloseFont(_font);

	instance = 0;
	delete this;
}

TTF_Font* ResourcePool::GetFont()
{
	return _font;
}

Mesh ResourcePool::GetAsteroidBigMesh()
{
	return _asteroidBigMesh;
}

Mesh ResourcePool::GetAsteroidMediumMesh()
{
	return _asteroidMediumMesh;
}

Mesh ResourcePool::GetAsteroidSmallMesh()
{
	return _asteroidSmallMesh;
}

Mesh ResourcePool::GetAlienMesh()
{
	return _alienMesh;
}

ResourcePool::ResourcePool()
{
	// Font
	_font = TTF_OpenFont(_fontPath, _fontSize);
	if (_font == nullptr)
	{
		std::cout << "Could not load font" << std::endl;
		std::cout << TTF_GetError() << std::endl;
	}

	// Meshes
	if (!_asteroidBigMesh.LoadFromObjFile(_asteroidBigMeshPath)) 
	{
		std::cout << "Could not load asteroid big mesh: " << _asteroidBigMeshPath << std::endl;
	}

	if (!_asteroidMediumMesh.LoadFromObjFile(_asteroidMediumMeshPath))
	{
		std::cout << "Could not load asteroid medium mesh: " << _asteroidMediumMeshPath << std::endl;
	}

	if (!_asteroidSmallMesh.LoadFromObjFile(_asteroidsmallMeshPath))
	{
		std::cout << "Could not load asteroid small mesh: " << _asteroidsmallMeshPath << std::endl;
	}

	if (!_alienMesh.LoadFromObjFile(_alienMeshPath))
	{
		std::cout << "Could not load alien mesh: " << _alienMeshPath << std::endl;
	}
}

ResourcePool::~ResourcePool()
{
	delete _font;
}
