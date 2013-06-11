#include "ContactListener.h"


ContactListener::ContactListener(void)
{
	footContacts = 0;
}


ContactListener::~ContactListener(void)
{
}

bool ContactListener::canJump()
{
	sf::Time tJumpTimeout = jumpTimeout.getElapsedTime();
	if (footContacts > 0 && tJumpTimeout.asMilliseconds() < 100){
		jumpTimeout.restart();
		return true;
	}
	return false;
}

void ContactListener::BeginContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( (int)fixtureUserData == 3) footContacts++;

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();

    if ((int)fixtureUserData == 3) footContacts++;
}

void ContactListener::EndContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == 3) footContacts--;

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();

    if ((int)fixtureUserData == 3) footContacts--;
}