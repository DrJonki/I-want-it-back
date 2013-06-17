#include "Particle.h"


Particle::Particle(int interval, float posX, float posY, sf::Vector2f direction, float randOffset)
{
	particleTexture.loadFromFile("Resources/Graphics/particle.png");

	m_interval = interval;
	m_posX = posX;
	m_posY = posY;
	m_direction.x = direction.x;
	m_direction.y = direction.y;

	m_randMin = -randOffset;
	m_randMax = randOffset;

	m_count = 0;

	pushParticle();
}

Particle::~Particle(void){}

void Particle::update()
{
	m_count++;

	if (m_count >= m_interval){
		pushParticle();

		m_count = 0;
	}

	for (unsigned int i = 0; i < particle.size(); i++){
		particle[i].move(particleVector[i]);
		particle[i].rotate(1);
		particle[i].setFillColor(sf::Color(particle[i].getFillColor().r,
										   particle[i].getFillColor().g,
										   particle[i].getFillColor().b,
										   particle[i].getFillColor().a - 2));

		if (particle[i].getFillColor().a <= 3){
			particle.erase(particle.begin() + i);
			particleVector.erase(particleVector.begin() + i);
		}
	}
}

void Particle::draw(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < particle.size(); i++){
		window.draw(particle[i]);
	}
}

void Particle::pushParticle()
{
	particle.emplace_back(sf::CircleShape());

	particle.back().setRadius(20);
	particle.back().setTexture(&particleTexture);
	particle.back().setOrigin(particle.back().getRadius(), particle.back().getRadius());
	particle.back().setPosition(m_posY, m_posY);

	particleVector.emplace_back(sf::Vector2f(m_direction.x + m_rand.fGetRandom(m_randMin, m_randMax),
											 m_direction.x + m_rand.fGetRandom(m_randMin, m_randMax)));
}
