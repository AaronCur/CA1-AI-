#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Tile.h"



class Grid
{
public:
	Grid();
	void run();
	void update();
	void render(sf::RenderWindow &window);

private:
	
	void processEvents();
	void processGameEvents(sf::Event& event);
	
	void reset();
	void initGrid(int posX, int posY);
	void getPath(Tile m_startTile);

protected:

	static const int m_gridSize = 32;
	static const int m_tileSize = 60;
	float m_tileScale = 1;

	Tile *m_tileGrid[m_gridSize][m_gridSize];

	int x = 0;
	int y = 0;

	int m_tilePosX = 0;
	int m_tilePosY = 0;

	sf::Vector2i m_mousePos;

	Tile * m_startTile;
	Tile * m_goalTile;
	sf::Font m_font;

	bool m_leftPress = false;
	bool m_rightPress = false;
	sf::View gameView;
	sf::View miniMapView;
};