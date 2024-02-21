#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Mesh.h"


class Sprite3D
{
public:
	Sprite3D(std::string const& texName);

private:
	sf::Texture m_tex;
	Mesh m_mesh{"spritepanel.obj"};
};

