#include "Object.h"


// --------------------------------------------------------------

Object::Object(sf::Vector2f location, Image img, sf::Vector2u imageCount,
	float switchTime)
	:	m_drawMe(true),m_row(0)
	
{
	
	m_animation = Animation(Textures::instance().getIconTexture(img), imageCount, switchTime);
	
	m_sprite.setTexture(Textures::instance().getIconTexture(img));
	m_sprite.setPosition(location);
	

}
// ------------------------------------

void Object::draw(sf::RenderWindow& window) 
{
	window.draw(m_sprite);
}
// --------------------------------------------------------------

bool Object::containsClick(const sf::Vector2f& mousePos)const
{
	return m_sprite.getGlobalBounds().contains(mousePos);
}
// ------------------------------------

void Object::update(int row, float deltaTime)
{
	m_animation.update(row, deltaTime);
	m_sprite.setTextureRect(m_animation.getUVRect());
}
// ------------------------------------

void Object::setScale(float size, int cols, int rows)
{
	
	auto x = m_sprite.getGlobalBounds().width / size;
	auto y = m_sprite.getGlobalBounds().height / size;
	
	m_sprite.setTextureRect(m_animation.getUVRect());

	m_sprite.setScale(sf::Vector2f(cols/x, rows/y));

}
// ------------------------------------


void Object::setOrigin()
{
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2,
		m_sprite.getLocalBounds().height / 2);
}
// ------------------------------------

sf::FloatRect Object::getGlobalRectBound() const
{
	return m_sprite.getGlobalBounds();
}
// --------------------------------------------------------------

// ------------------------------------

bool Object::contains(const Object& obj1, const Object& obj2)
{
	return obj2.getGlobalRectBound().contains(
		sf::Vector2f(obj1.getPos().x, obj1.getPos().y));
}
// ------------------------------------


bool Object::collides(const Object& obj1, const Object& obj2)
{
	return obj1.isIntersects(obj2.getGlobalRectBound());
}
// ------------------------------------

bool Object::isIntersects(const sf::FloatRect& otherRect) const
{
	return m_sprite.getGlobalBounds().intersects(otherRect);
}
