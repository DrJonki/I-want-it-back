#pragma once

#include <Box2D\Box2D.h>
#include <SFML\System\Clock.hpp>

class ContactListener : public b2ContactListener
{
public:
	ContactListener(void);
	~ContactListener(void);

	void setID(const int id) { _id = id; };

	void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

	bool canJump();
	
private:

	sf::Clock jumpTimeout;

	int footContacts;

	int _id;
};

