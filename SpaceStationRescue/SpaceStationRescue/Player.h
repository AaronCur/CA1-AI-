#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <math.h>
#include "Grid.h"
#include "HealthSystem.h"
#include "Bullet.h"
#include "Powerups.h"

class Player
{
public:
	Player(Grid &m_Grid);
	~Player();

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void speedUp();
	void speedDown();
	void increaseRotation();
	void decreaseRotation();
	void respawn(float x, float y);
	void update(double dt, std::vector<Powerups*>&m_powerUps);
	void render(sf::RenderWindow &window);
	void collision(std::vector<Powerups*>&m_powerUps, double dt);

	float getRotation();

	bool firepower, shield = false;
	int bulletindex = 0;
	bool fired=false;
	HealthSystem *m_healthSystem;
	std::vector<Bullet *> m_bullet;
	int pGridX;
	int pGridY;

	int score;

private:
	sf::CircleShape shape;
	sf::RectangleShape m_rect;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	float m_orientation;

	float  DEG_TO_RAD;
	float m_maxSpeed;
	float m_rotation;
	sf::Vector2f m_heading;
	float m_speed;
	double cumulativeTime;
	sf::CircleShape shieldcrc;
	Grid *m_grid;

	int pGridX;
	int pGridY;


};