#include "ContactListener.h"


ContactListener::ContactListener(void)
{
	footContacts = 0;

	jumpTimeout.restart();
}


ContactListener::~ContactListener(void)
{
}

bool ContactListener::canJump()
{
	sf::Time tJumpTimeout = jumpTimeout.getElapsedTime();
	if (footContacts >= 1 && tJumpTimeout.asMilliseconds() > 100){
		jumpTimeout.restart();
		return true;
	}
	return false;
}

void ContactListener::BeginContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == _id) footContacts++;

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();

    if ((int)fixtureUserData == _id) footContacts++;
}

void ContactListener::EndContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == _id) footContacts--;

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();

    if ((int)fixtureUserData == _id) footContacts--;
}