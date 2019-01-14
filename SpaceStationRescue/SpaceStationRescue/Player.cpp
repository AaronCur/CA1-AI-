#include "Player.h"
#include <iostream>
Player::Player() :
	m_position(900, 500),
	m_velocity(0,0),
	shape(100.0),
	m_rotation(0),
	m_maxSpeed(20.0),
	m_speed(0),
	m_heading(0,0)

{
	if (!m_texture.loadFromFile("./resources/Player.png")) {
		//do something
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.1, 0.1);
	m_sprite.setRotation(90);
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	DEG_TO_RAD = 3.14 / 180;

	m_grid = new Grid();

	pGridX = m_position.x / m_grid->m_tileSize;
	pGridY= m_position.y / m_grid->m_tileSize;
	m_bullet = new Bullet();
	
}
Player::~Player()
{

}

sf::Vector2f Player::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

void Player::speedUp()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += 2;
	}
}
void Player::speedDown()
{
	if (m_speed > 0)
	{
		m_speed -= 2;
	}
}
void Player::increaseRotation()
{

	m_rotation += 4.0f;
}
void Player::decreaseRotation()
{
	
	if (m_rotation != 0.00f)
	{
		m_rotation -= 4.0f;
	}
	else
	{
		m_rotation = 359.0f;
	}
	
	
}

void Player::update(double dt)
{

	pGridX = floor(m_sprite.getPosition().x / m_grid->m_tileSize);
	pGridY = floor(m_sprite.getPosition().y / m_grid->m_tileSize);

	collision();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		speedUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		speedDown();
	}
	

	m_heading.x = cos(m_rotation * (3.14 / 180));
	m_heading.y = sin(m_rotation * (3.14 / 180));

	m_velocity = m_heading * m_speed;
	
	m_sprite.setPosition(m_sprite.getPosition().x + m_velocity.x * (dt / 100), m_sprite.getPosition().y + m_velocity.y * (dt / 100));
	m_sprite.setRotation(m_rotation);

	respawn(m_sprite.getPosition().x, m_sprite.getPosition().y);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_bullet->getState() == false)
	{
		m_bullet->shoot(m_heading, m_sprite.getPosition(), m_rotation);
	}

	if (m_bullet->getState() == true){

		m_bullet->update(dt);
	}


}

void Player::respawn(float x, float y)
{
	if (y >= 1000 + 100)
	{
		//m_sprite.setPosition(m_sprite.getPosition().x, -200);
	}

	else if (y < -200)
	{
		//m_sprite.setPosition(m_sprite.getPosition().x,1100);
	}
	else if (x < -200)
	{
		//m_sprite.setPosition(2100, m_sprite.getPosition().y);
	}
	else if (x >= 2100)
	{
		//m_sprite.setPosition(200, m_sprite.getPosition().y);
	}
}

 void Player::collision()
{

	if (m_grid->m_tileGrid[pGridX][pGridY - 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX][pGridY - 1]->m_position.y + m_grid->m_tileSize))
		{
			m_sprite.setPosition(m_sprite.getPosition().x, m_grid->m_tileGrid[pGridX][pGridY - 1]->m_position.y + m_grid->m_tileSize + (m_grid->m_tileSize / 2));
		}
		
	}
	if (m_grid->m_tileGrid[pGridX][pGridY + 1]->getCurrentState() == OBSTACLE)
	{
		if (m_sprite.getPosition().y + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX][pGridY + 1]->m_position.y))
		{
			m_sprite.setPosition(m_sprite.getPosition().x, m_grid->m_tileGrid[pGridX][pGridY + 1]->m_position.y - (m_grid->m_tileSize / 2));
		}
	
	}
	  if (m_grid->m_tileGrid[pGridX + 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		 if (m_sprite.getPosition().x + (m_grid->m_tileSize / 2) >= (m_grid->m_tileGrid[pGridX + 1][pGridY]->m_position.x))
		 {
			 m_sprite.setPosition(m_grid->m_tileGrid[pGridX + 1][pGridY]->m_position.x - (m_grid->m_tileSize / 2), m_sprite.getPosition().y);
		 }
		
	}
	
	  if (m_grid->m_tileGrid[pGridX - 1][pGridY]->getCurrentState() == OBSTACLE)
	{
		 if (m_sprite.getPosition().x - (m_grid->m_tileSize / 2) <= (m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize))
		 {
			 m_sprite.setPosition(m_grid->m_tileGrid[pGridX - 1][pGridY]->m_position.x + m_grid->m_tileSize + (m_grid->m_tileSize / 2), m_sprite.getPosition().y);
		 }
	
	}

}

void Player::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);

	if (m_bullet->getState() == true) {

		m_bullet->render(window);
	}

	
}