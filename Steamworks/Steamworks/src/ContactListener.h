#pragma once

#include <Box2D\Box2D.h>
#include <SFML\System\Clock.hpp>

#include <vector>

class ContactListener : public b2ContactListener
{
public:
	ContactListener(void);
	~ContactListener(void);

	void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

	void addData(const int data, const int timeout = 0);

	bool inContact(const int data);
	
private:

	sf::Clock _timeoutClock;
	sf::Time _timeout_t;

	struct _contactDataStruct
	{
		int _contacts;
		int _data;
		int _timeout;
	};

	std::vector<_contactDataStruct> _contactData;
};

