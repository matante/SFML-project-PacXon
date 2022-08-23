#pragma once
#include "Consts.h"
#include "Textures.h"
#include "Audio.h"
#include "Animation.h"
#include "EnumClasses.h"

class Object {
public:
// c-tors and d-tors
	Object(sf::Vector2f, Image, sf::Vector2u, float);
	virtual ~Object() = default;

	Object(const Object&) = default;
	Object& operator=(const Object&) = default;
	Object(Object&&) = default;
	Object& operator=(Object&&) = default;

public: //functions

	static bool contains(const Object& , const Object& );
	static bool collides(const Object& , const Object& );
	
	virtual void draw(sf::RenderWindow& );
	bool containsClick(const sf::Vector2f&)const;

	void update(int, float);
	void setScale(float, int, int);

	void setPos(sf::Vector2f pos) {m_sprite.setPosition(pos);};
	sf::Vector2f getPos() const {return m_sprite.getPosition();	};
	sf::Vector2f getOrg() const { return m_sprite.getOrigin(); };

	void setOrigin();

	sf::FloatRect getGlobalRectBound()const;
	bool isIntersects(const sf::FloatRect&) const;

	bool shouldBeDrawn() const {return m_drawMe;};
	void setDrawStatus(bool status) { m_drawMe = status; };


protected:
	Animation m_animation;
	sf::Sprite m_sprite;
	bool m_drawMe;
	unsigned m_row;

};
