#include "ContactListener.h"


ContactListener::ContactListener(void)
{
	_timeout = 0;

	_timeoutClock.restart();
}

ContactListener::~ContactListener(void)
{
	_data.clear();
}

bool ContactListener::inContact(const int data)
{
	_timeout_t = _timeoutClock.getElapsedTime();
	if (_contacts >= 1 && _timeout_t.asMilliseconds() >= _timeout){
		_timeoutClock.restart();
		return true;
	}
	return false;
}

void ContactListener::addData(const int data, const int timeout)
{


}


void ContactListener::BeginContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	for (int i = 0; i < _data.size(); i++){
		if ((int)fixtureUserData == _data[i]) _contacts[i]++;
	}
	
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
	for (int i = 0; i < _data.size(); i++){
		if ((int)fixtureUserData == _data[i]) _contacts[i]++;
	}
}

void ContactListener::EndContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    for (int i = 0; i < _data.size(); i++){
		if ((int)fixtureUserData == _data[i]) _contacts[i]--;
	}

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    for (int i = 0; i < _data.size(); i++){
		if ((int)fixtureUserData == _data[i]) _contacts[i]--;
	}
}