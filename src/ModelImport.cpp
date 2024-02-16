#include "ModelImport.h"
#include <fstream>
#include <sstream>
#include <glm/vec2.hpp>

void ModelImport::loadFromFile(Mesh& mesh, std::string const& path)
{
	const std::string ASSET_PATH = "./Resources/Models/";

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
			while (std::getline(iss, group, ' '))
			{
				std::istringstream groupStream(group);
				std::string indexValue;
				while (std::getline(groupStream, indexValue, '/'))
				{
					if (indexValue.empty())
						continue;

					unsigned int index;
					std::stringstream(indexValue) >> index;

					if (vertexIndices.size() == normalIndices.size())
					{
						vertexIndices.push_back(index);
					}
					else
					{
						normalIndices.push_back(index);
					}
					
				}
			}
		}
	}
	
	for (unsigned int vertexIndex : vertexIndices)
	{
		glm::vec3 vertex = temp_vertices[vertexIndex-1];
		mesh.vertices.push_back(vertex);
	}

	for (unsigned int normalIndex : normalIndices)
	{
		glm::vec3 normal = temp_normals[normalIndex-1];
		mesh.normals.push_back(normal);
	}
}
