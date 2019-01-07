#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
//#include "Player.h"
//#include "Enemy.h"
//#include "Pursue.h"
//#include "Arrive.h"
//#include "Flee.h"
//#include "Seek.h"
//#include "Wander.h"
#include "Grid.h"


class Game
{
public:
	Game();
	void run();

private:
	void update(double dt);
	void render();
	void ProcessEvents();
	void processGameEvents(sf::Event& event);

protected:
	sf::RenderWindow m_window;
	/*Player* m_player;*/

	sf::Vector2i m_mousePos;

	Tile * m_startTile;
	Tile * m_goalTile;

	int m_tilePosX = 0;
	int m_tilePosY = 0;
	static const int m_gridSize = 30;
	static const int m_tileSize = 60;
	float m_tileScale = 1;

	//Tile *m_tileGrid[m_gridSize][m_gridSize];

	//Enemy* m_pursue;

	//std::vector<Enemy*> enemies;
	Grid *m_Grid;
	bool m_leftPress = false;
	bool m_rightPress = false;

};
#endif // !GAME