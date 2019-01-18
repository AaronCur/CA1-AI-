#include "Game.h"

/// <summary>
/// Games Constructor method
/// Creates all things that will be displayed in the game Window.
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(1280, 960), "AI LabCA1", sf::Style::Default)
{
	srand(time(NULL));

	m_Grid = new Grid();

	for (int i = 0; i < 20; i++)
	{
		workers.push_back(new Worker(*m_Grid));
		
	}
	for (int i = 0; i < 3; i++)
	{	
		spawnSpot = rand() % 5;

		
			while ((std::find(usedSpawns.begin(), usedSpawns.end(), spawnSpot) != usedSpawns.end()))
			{
				spawnSpot = rand() % 5;
			}
			nests.push_back(new Nests(spawnSpot, *m_Grid));
			
			usedSpawns.push_back(spawnSpot);
			m_sweeper.push_back(new Sweeper(workers));
	}
	for (int i = 0; i < 4; i++)
	{
		int PowerupType = rand() % 4;


		while ((std::find(usedTypes.begin(), usedTypes.end(), PowerupType) != usedTypes.end()))
		{
			PowerupType = rand() % 4;
		}
		m_powerups.push_back(new Powerups(PowerupType));

		usedTypes.push_back(PowerupType);
	}
	
	

	m_player = new Player(*m_Grid);
	
	miniMapView.setViewport(sf::FloatRect(0.64f, 0.02f, 0.3f, 0.3f));
	miniMapView.setSize(3750, 3750);
	miniMapView.setCenter(1875, 1875);

	gameView.setViewport(sf::FloatRect(0, 0, 1, 1));
	gameView.setSize(1280, 960);
	gameView.setCenter(640, 480);




	if (!m_playerMMT.loadFromFile("./resources/PlayerMiniMap.png")) {
		//do something
	}

	if (!m_predatorMMT.loadFromFile("./resources/PredatorMiniMap.png")) {
		//do something
	}


	if (!m_MMT.loadFromFile("./resources/MiniMap.png")) {
		//do something
	}

	if (!m_font.loadFromFile("./resources/Adventure.otf")) {
		//do something
	}

	m_text.setFont(m_font);
	m_text.setString("YOU LOSE");
	m_text.setCharacterSize(200);
	m_text.setFillColor(sf::Color::Red);


	m_Grid->updateCost(m_player->pGridX, m_player->pGridY, 4000);

	for (int i = 0; i < nests.size(); i++) {
		predators.push_back(new Predator(nests[i]->getPosition().x, nests[i]->getPosition().y, *m_Grid));
	}
	
	m_playerMM.setTexture(m_playerMMT);
	m_playerMM.setOrigin(m_playerMM.getTextureRect().width / 2, m_playerMM.getTextureRect().height / 2);

	m_predatorMM.setTexture(m_predatorMMT);
	m_predatorMM.setOrigin(m_predatorMM.getTextureRect().width / 2, m_predatorMM.getTextureRect().height / 2);

	m_predatorMM2.setTexture(m_predatorMMT);
	m_predatorMM2.setOrigin(m_predatorMM2.getTextureRect().width / 2, m_predatorMM.getTextureRect().height / 2);

	m_predatorMM3.setTexture(m_predatorMMT);
	m_predatorMM3.setOrigin(m_predatorMM3.getTextureRect().width / 2, m_predatorMM.getTextureRect().height / 2);
	
	m_MM.setTexture(m_MMT);

	m_gameOverBG.setSize(sf::Vector2f(3751, 3751));
	m_gameOverBG.setFillColor(sf::Color(255, 255, 255, 200));



}

/// <summary>
/// While the window is open Run the game render, and update methods
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	timeSinceLastUpdate = clock.restart();

	while (m_window.isOpen())
	{
		ProcessEvents();
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
		}

		render();
	}
}
/// <summary>
/// Processes whether the window is open or closed
/// </summary>
void Game::ProcessEvents()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(e);
	}
}
void Game::processGameEvents(sf::Event& event)
{
}




/// <summary>
/// Calls all update methods for all elements in the game
/// </summary>
void Game::update(double dt)
{

	m_player->update(dt, m_powerups);
	gameView.setCenter(m_player->getPosition());
	
	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->update(*m_player);
	}

	if (m_player->m_healthSystem->m_healthValue > 0 || !m_player->score==200)
	{
		m_playerMM.setPosition(m_player->getPosition());
		m_playerMM.setRotation(m_player->getRotation());
		m_predatorMM.setPosition(predators[0]->getPosition());
		m_predatorMM.setRotation(predators[0]->getRotation());

		m_predatorMM2.setPosition(predators[1]->getPosition());
		m_predatorMM2.setRotation(predators[1]->getRotation());


		for (int i = 0; i < m_sweeper.size(); i++)
		{
			m_sweeper[i]->update(m_player->getPosition(), dt, *m_player);
		}
		for (int i = 0; i < m_powerups.size(); i++)
		{
			m_powerups[i]->update();
		}


		m_predatorMM3.setPosition(predators[2]->getPosition());
		m_predatorMM3.setRotation(predators[2]->getRotation());
		
		gameView.setCenter(m_player->getPosition());
		
		for (int i = 0; i < nests.size(); i++)
		{
			nests[i]->update(*m_player, dt);
		}
		for (int i = 0; i < predators.size(); i++)
		{
			predators[i]->update(*m_player, nests, dt);
		}
		if (m_player->pGridX != previousX || m_player->pGridY != previousY)
		{
			m_Grid->updateCost(m_player->pGridX, m_player->pGridY, 500);
			previousX = m_player->pGridX;
			previousY = m_player->pGridY;
		}

	}
	
}

/// <summary>
/// Renders and draws all instances of the game the game view
/// </summary>
void Game::render()
{
	//m_window.setView(follow);
	
	m_window.clear(sf::Color(45, 45, 45));
	m_window.setView(gameView);
	m_Grid->render(m_window, gameView, false);
	int i;
	for (i = 0; i < nests.size(); i++)
	{
		nests[i]->render(m_window);

	}
	m_player->render(m_window);
	for (i = 0; i < workers.size(); i++)
	{
		
		workers[i]->render(m_window);
	}


	for (int i = 0; i < predators.size(); i++)
	{
		predators[i]->render(m_window);
	}
	if (m_player->m_healthSystem->m_healthValue <= 0)
	{
		m_window.draw(m_gameOverBG);
		m_text.setString("YOU LOSE");
		m_text.setPosition(m_player->getPosition().x - 400, m_player->getPosition().y - 100);
		m_window.draw(m_text);
	}
	if (m_player->score == 200)
	{
		m_window.draw(m_gameOverBG);
		m_text.setFont(m_font);
		m_text2.setFont(m_font);
		m_text.setString("ALL WORKERS ARE SAFE");
		m_text2.setString("YOU WIN!");
		m_text2.setCharacterSize(100);
		m_text.setCharacterSize(100);
		m_text.setFillColor(sf::Color::Green);
		m_text2.setFillColor(sf::Color::Green);
		m_text.setPosition(m_player->getPosition().x - 600, m_player->getPosition().y - 100);
		m_text2.setPosition(m_player->getPosition().x - 200, m_player->getPosition().y);
		m_window.draw(m_text);
		m_window.draw(m_text2);
	}

	for (i = 0; i < m_sweeper.size(); i++)
	{
		m_sweeper[i]->render(m_window);
	}
	for (i = 0; i < m_powerups.size(); i++)
	{
		m_powerups[i]->render(m_window);
	}

	m_window.setView(miniMapView);

	m_window.draw(m_MM);
	for (int i = 0; i < m_Grid->m_spawnPoints.size(); i++) {
		m_Grid->m_spawnPoints[i]->render(m_window);
	}

	for (int i = 0; i < nests.size(); i++)
	{
		nests[i]->render(m_window);
	}

	
	m_window.draw(m_playerMM);
	if (predators[0]->m_healthSystem->m_healthValue > 0)
	{
		m_window.draw(m_predatorMM);
	}

	if (predators[1]->m_healthSystem->m_healthValue > 0)
	{
		m_window.draw(m_predatorMM2);
	}
	
	if (predators[2]->m_healthSystem->m_healthValue > 0)
	{
		m_window.draw(m_predatorMM3);
	}
	
	if (m_player->m_healthSystem->m_healthValue <= 0 || m_player->score==200)
	{
		m_window.draw(m_gameOverBG);
	
	}
	
	m_window.display();
}