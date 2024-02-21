#include "ModelImport.h"
#include <fstream>
#include <sstream>
#include <glm/vec2.hpp>

std::unordered_map<std::string, unsigned int> ModelImport::cacheIndices{};
std::vector<MeshData*> ModelImport::cache{};

MeshData* ModelImport::loadFromFile(std::string const& path)
{
	const std::string ASSET_PATH = "./Resources/Models/";

	// Test cache first
	if (cacheIndices.count(path))
		return cache[cacheIndices[path]];

	MeshData* mesh = new MeshData();

	std::vector< unsigned int > vertexIndices, normalIndices, colorIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector<glm::vec3> temp_colors;
	std::vector< glm::vec3 > temp_normals;

	std::ifstream infile(ASSET_PATH+path);

	if (!infile.is_open())
	{
		throw std::runtime_error("Failed to load asset '" + path + "'. Asset doesn't exist or is inaccessible");
	}

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		std::string token;
		iss >> token;

		if (token == "v") // Vertices
		{
			glm::vec3 vertex{};
			iss >> vertex.x;
			iss >> vertex.y;
			iss >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (token == "vc") // Vertices
		{
			glm::vec3 vertex{};
			iss >> vertex.x;
			iss >> vertex.y;
			iss >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (token == "vn") // Normals
		{
			glm::vec3 normal{};
			iss >> normal.x;
			iss >> normal.y;
			iss >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (token == "f") // Faces
		{
			std::string group;
			while(std::getline(iss, group, ' '))
			{
				size_t index = group.find("//");
				if (index == std::string::npos)
					continue;

				std::string leftNum = group.substr(0,index);
				std::string rightNum = group.substr(index+2);
				vertexIndices.push_back(std::stoul(leftNum));
				normalIndices.push_back(std::stoul(rightNum));

			}
		}
	}
	
	for (unsigned int vertexIndex : vertexIndices)
	{
		glm::vec3 vertex = temp_vertices[vertexIndex-1];
		mesh->vertices.push_back(vertex);
	}

	for (unsigned int normalIndex : normalIndices)
	{
		glm::vec3 normal = temp_normals[normalIndex-1];
		mesh->normals.push_back(normal);
	}

	cacheIndices[path] = cache.size();
	cache.push_back(mesh);

	return mesh;
}
