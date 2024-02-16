#include "Game.h"
#include <iostream>
#include <glm/ext/quaternion_common.hpp>
#include <cmath>


Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game", sf::Style::Default, sf::ContextSettings(24) },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture

	renderEngine.setPerspective(90, 800.0f/600.0f, 0.1f, 100.0f);
	renderEngine.setView(glm::lookAt(
		glm::vec3(0,10,0),
		glm::vec3(0,0,0),
		glm::vec3(1,0,0)
	));
	monkey.setRotation({-60,0,0});
	monkey.setPosition({0,1,0});
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	float speed = 5.0f * t_deltaTime.asSeconds();
	glm::vec3 pos = monkey.getPosition();
	glm::vec3 input{0,0,0};

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) input.z -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) input.z += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) input.x += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) input.x -= 1;

	if (input.x == 0.0f && input.z == 0.0f)
		return;

	input = normalize(input);
	float rotation = std::atan2(input.z, input.x);
	rotation *= (180.0f / 3.14159f);

	glm::vec3 originalRot = monkey.getRotation();
	originalRot.y = originalRot.y + (t_deltaTime.asSeconds()*10) * (rotation - originalRot.y);
	originalRot.y -= 90;
	monkey.setRotation(originalRot);
	pos += input * speed;

	monkey.setPosition(pos);
}

void Game::render()
{
	renderEngine.draw();
	m_window.pushGLStates();
	m_window.draw(m_logoSprite);
	m_window.popGLStates();
	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("./Resources/IMAGES/SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
	m_logoSprite.setScale(0.5f,0.5f);
}
