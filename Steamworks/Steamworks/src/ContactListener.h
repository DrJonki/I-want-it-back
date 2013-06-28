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

	void addData(void* data, const int timeout = 0);

	bool inContact(void* data);
	
private:
	sf::Clock _timeoutClock;

	struct _contactDataStruct
	{
		int _contacts;
		void* _data;
		int _timeout;
	};

	std::vector<_contactDataStruct> _contactData;
};

