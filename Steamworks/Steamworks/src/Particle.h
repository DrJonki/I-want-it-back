#pragma once

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>

#include "Randomizer.h"

class Particle
{
public:
	Particle(int interval, float posX, float posY, sf::Vector2f direction, float randOffset);
	~Particle(void);

	void update();
	void draw(sf::RenderWindow&);

private:
	void pushParticle();

	std::vector<sf::CircleShape> particle;
	std::vector<sf::Vector2f> particleVector;

	sf::Texture particleTexture;

	int m_interval;
	float m_posX, m_posY;
	sf::Vector2f m_direction;

	float m_randMin;
	float m_randMax;

	int m_count;

	Randomizer m_rand;
};

