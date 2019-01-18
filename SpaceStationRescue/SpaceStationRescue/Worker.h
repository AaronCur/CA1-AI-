#pragma once
#include <iostream>
#include <vector>
#include "Grid.h"
#include <SFML\Config.hpp>
#include <string>
#include "Player.h"


class Worker
{
public:
	Worker();
	~Worker();

	void update(Player &m_player);
	void render(sf::RenderWindow &window);
	float getRandom(int x, int y);
	sf::Vector2f getPosition();
	void collision(Player &m_player);

	int count = 0;
	int spawn =0;
	bool alive;

protected:

private:
	sf::Vector2f velocity;
	sf::Vector2f m_position;
	
	float maxSpeed;
	float rotation;
	float maxRotation;
	
	sf::Texture workerTxt;
	sf::Sprite workerSprite;
	
	int rotateWorker(sf::Vector2f vel, int rotate);
	void spawnWorkers();

	Grid *m_Grid;
	int pGridX;
	int pGridY;
	
};