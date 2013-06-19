#pragma once

#include <Box2D\Box2D.h>
#include <SFML\System\Clock.hpp>

class ContactListener : public b2ContactListener
{
public:
	ContactListener(void);
	~ContactListener(void);

	void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

	bool touchingTop();
	bool touchingLeft();
	bool touchingBottom();
	bool touchingRight();
	
private:

	sf::Clock _timeout;
	sf::Time _timeout_t;

	int _topContacts, _leftContacts, _bottomContacts, _rightContacts;

	//Enumeration for the different sensors
	static const enum
	{
		SEN_TOP = 0x11,
		SEN_LEFT = 0x12,
		SEN_BOTTOM = 0x13,
		SEN_RIGHT = 0x14
	};
};

