#include "Worker.h"
/// <summary>
/// Worker Constructor method
/// Sets image, rotation, velocity, scale.
/// </summary>
/// <param name="m_grid"></param>
Worker::Worker(Grid &m_grid):
	velocity(0,0),
	maxSpeed(3.0f),
	maxRotation(360),
	rotation(90),
	m_Grid(&m_grid),
	alive(true)
{
	//m_Grid = new Grid();
	spawnWorkers();

	if (!workerTxt.loadFromFile("./resources/worker.png"))
	{
		std::cout << "Cannot load worker image" << std::endl;
	}

	workerSprite.setTexture(workerTxt);
	workerSprite.setPosition(m_position);
	workerSprite.setRotation(rotation);
	workerSprite.setScale(0.3, 0.3);
	workerSprite.setOrigin(workerSprite.getTextureRect().width / 2, workerSprite.getTextureRect().height / 2);
	velocity.x = getRandom(10, -5);
	velocity.y = getRandom(10, -5);
	pGridX = m_position.x / m_Grid->m_tileSize;
	pGridY = m_position.y / m_Grid->m_tileSize;
}

Worker::~Worker()
{

}

/// <summary>
/// Checks collision for workers
/// Checks for collisions between walls, and player
/// if collides with player, alive is rendered false and players score is incremented.
/// </summary>
/// <param name="m_player"></param>
void Worker::collision(Player &m_player)
{
	if (m_Grid->m_tileGrid[pGridX][pGridY - 1]->getCurrentState() == OBSTACLE)
	{
		velocity.y *= -1;
		m_position.y += 5;

	}
	if (m_Grid->m_tileGrid[pGridX][pGridY + 1]->getCurrentState() == OBSTACLE)
	{
		velocity.y *= -1;
		m_position.y -= 5;
	}
	if (m_Grid->m_tileGrid[pGridX + 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		velocity.x *= -1;
		m_position.x -= 5;
	}
	if (m_Grid->m_tileGrid[pGridX - 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		velocity.x *= -1;
		m_position.x += 5;
	}

	
		if (workerSprite.getPosition().x - m_Grid->m_tileSize / 2 < m_player.getPosition().x + m_Grid->m_tileSize / 2 &&
			workerSprite.getPosition().x + m_Grid->m_tileSize / 2 > m_player.getPosition().x - m_Grid->m_tileSize / 2 &&
			workerSprite.getPosition().y - m_Grid->m_tileSize / 2 < m_player.getPosition().y + m_Grid->m_tileSize / 2 &&
			workerSprite.getPosition().y + m_Grid->m_tileSize / 2 > m_player.getPosition().y - m_Grid->m_tileSize / 2)
		{
			if (alive)
			{
				alive = false;
				m_player.score += 10;
			}
		}

}

/// <summary>
/// returns workers current position
/// </summary>
/// <returns></returns>
sf::Vector2f Worker::getPosition()
{
	return workerSprite.getPosition();
}

/// <summary>
/// Updates workers position, rotation and wander direction
/// </summary>
/// <param name="m_player"></param>
void Worker::update(Player &m_player)
{
	if (alive)
	{
		pGridX = floor(workerSprite.getPosition().x / m_Grid->m_tileSize);
		pGridY = floor(workerSprite.getPosition().y / m_Grid->m_tileSize);
		collision(m_player);
		m_position.x += velocity.x * 30 / 100;
		m_position.y += velocity.y * 30 / 100;
		workerSprite.setPosition(m_position.x, m_position.y);
		rotateWorker(velocity, rotation);

		workerSprite.setRotation(rotation);
		if (count >= 200)
		{
			velocity.x = getRandom(10, -5);
			velocity.y = getRandom(10, -5);
			count = 0;
		}

		count++;
	}
	
}

/// <summary>
/// gives workers initial velocity and direction
/// </summary>
void Worker::spawnWorkers()
{
	spawn = rand() % 5;
	m_position.x = m_Grid->m_spawnPoints[spawn]->m_position.x;
	m_position.y = m_Grid->m_spawnPoints[spawn]->m_position.y;
}

/// <summary>
/// randomises value for workers x and y velocity 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
float Worker::getRandom(int x, int y)
{
	
	//srand(time(NULL));
	count = rand() % 50;
	float randVal = rand() % x + y;
	return randVal;
}

/// <summary>
/// rotates worker so that it faces the correct direction based on its velocity
/// </summary>
/// <param name="vel"></param>
/// <param name="angle"></param>
/// <returns></returns>
int Worker::rotateWorker(sf::Vector2f vel, int angle)
{
	if (vel.x > 0 && angle < 80)
	{
		rotation += 10;
	}
	else if (vel.x > 0 && angle > 100)
	{
		rotation -= 10;
	}

	if (vel.x > 0 && vel.y > 0 && angle<130)
	{
		rotation += 10;
	}
	else if (vel.x > 0 && vel.y>0 && angle > 140)
	{
		rotation -= 10;
	}

	if (vel.y > 0 && angle < 170)
	{
		rotation += 10;
	}
	else if (vel.y > 0 && angle > 190)
	{
		rotation -= 10;
	}

	if (vel.x < 0 && vel.y > 0 && angle <215)
	{
		rotation += 10;
	}
	else if (vel.x < 0 && vel.y>0 && angle > 235)
	{
		rotation -= 10;
	}

	if (vel.x < 0 && angle <260)
	{
		rotation += 10;
	}
	else if (vel.x < 0 && angle > 280)
	{
		rotation -= 10;
	}

	if (vel.x < 0 && vel.y < 0 && angle <305)
	{
		rotation += 10;
	}
	else if (vel.x < 0 && vel.y < 0 && angle > 325)
	{
		rotation -= 10;
	}

	if (vel.y < 0 && angle < 350)
	{
		rotation += 10;
	}
	else if (vel.y < 0 && angle > 10)
	{
		rotation -= 10;
	}

	if (vel.x > 0 && vel.y < 0  && angle < 35)
	{
			rotation = 45;
	}
	return rotation;
	
}

/// <summary>
/// renders the worker while it is alive
/// </summary>
/// <param name="window"></param>
void Worker::render(sf::RenderWindow &window)
{
	if(alive)
	window.draw(workerSprite);

}

