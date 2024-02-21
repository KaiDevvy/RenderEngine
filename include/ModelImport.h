#pragma once
#include <string>
#include "Mesh.h"
#include "MeshData.hpp"
#include <unordered_map>
#include <vector>

class ModelImport
{
public:
	static MeshData* loadFromFile(std::string const& path);

private:

	static std::unordered_map<std::string, unsigned int> cacheIndices;
	static std::vector<MeshData*> cache;
	
};

