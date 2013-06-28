#include "ContactListener.h"


ContactListener::ContactListener(void)
{
	_timeoutClock.restart();
}

ContactListener::~ContactListener(void)
{
	_contactData.clear();
}

bool ContactListener::inContact(void* data)
{
	for (int i = 0; i < _contactData.size(); i++){
		if (_contactData[i]._data == data){
			if (_contactData[i]._contacts > 0 && _timeoutClock.getElapsedTime().asMilliseconds() >= _contactData[i]._timeout){
				_timeoutClock.restart();
				return true;
			}
		}
	}

	return false;
}

void ContactListener::addData(void* data, const int timeout)
{
	_contactData.push_back(_contactDataStruct());

	_contactData.back()._data = data;
	_contactData.back()._timeout = timeout;
	_contactData.back()._contacts = 0;
}


void ContactListener::BeginContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	for (int i = 0; i < _contactData.size(); i++){
		if (fixtureUserData == _contactData[i]._data) _contactData[i]._contacts++;
	}
	
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
	for (int i = 0; i < _contactData.size(); i++){
		if (fixtureUserData == _contactData[i]._data) _contactData[i]._contacts++;
	}
}

void ContactListener::EndContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    for (int i = 0; i < _contactData.size(); i++){
		if (fixtureUserData == _contactData[i]._data) _contactData[i]._contacts--;
	}

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    for (int i = 0; i < _contactData.size(); i++){
		if (fixtureUserData == _contactData[i]._data) _contactData[i]._contacts--;
	}
}