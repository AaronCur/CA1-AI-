#include "Game.h"

/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(sf::VideoMode(3000, 2000), "AI LabCA1", sf::Style::Default)
{
	m_Grid = new Grid();
	m_player = new Player();
	/*Enemy* m_pursue = new Pursue(*this);
	Enemy* m_arriveFast = new Arrive(60.0f, 100.0f, 100.0f);
	Enemy* m_arriveSlow = new Arrive(150.0f, 1720.0f, 1000.0f);
	Enemy* m_seek = new Seek();
	Enemy* m_wander = new Wander();*/

	//Factory* factory = new EnemyFactory;

	/*enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());
	enemies.push_back(factory->CreateEnemy());*/

	//enemies.push_back(m_pursue);
	//enemies.push_back(m_arriveFast);
	//enemies.push_back(m_arriveSlow);
	//enemies.push_back(m_seek);
	////enemies.push_back(m_flee);
	//enemies.push_back(m_wander);
	miniMapView.setViewport(sf::FloatRect(0.73f, 0.02f, 0.25f, 0.25f));
	miniMapView.setSize(3000, 2000);
	miniMapView.setCenter(1500, 1000);

	gameView.setViewport(sf::FloatRect(0, 0, 1, 1));
	gameView.setSize(3000, 2000);
	gameView.setCenter(1500, 1000);
	gameView.zoom(0.5f);


}

/// <summary>
/// 
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
/// 
/// </summary>
void Game::update(double dt)
{
	m_player->update(dt);
	gameView.setCenter(m_player->getPosition());
	m_Grid->update();

	/*for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(m_player->getPosition(), m_player->getVelocity());
		enemies[i]->collisionAvoidance(enemies);
	}*/
	//m_enemy->update(m_player->getPosition());
	//m_enemySeek->update(m_player->getPosition());

	//	m_enemyFlee->update(m_player->getPosition());
	//m_enemyPursue->update(m_player->getPosition(), m_player->getVelocity());

}

/// <summary>
/// 
/// </summary>
void Game::render()
{
	//m_window.setView(follow);
	
	m_window.clear(sf::Color::White);
	m_window.setView(gameView);
	m_Grid->render(m_window);
	m_player->render(m_window);

	m_window.setView(miniMapView);
	m_Grid->render(m_window);
	m_player->render(m_window);

	//m_player->render(m_window);

	/*for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(m_window);
	}*/
	//	m_enemyPursue->render(m_window);
	//m_enemy->render(m_window);
	//m_enemySeek->render(m_window);
	//m_enemyFlee->render(m_window);
	m_window.display();
}