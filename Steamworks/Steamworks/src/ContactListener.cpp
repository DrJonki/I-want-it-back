#include "ContactListener.h"


ContactListener::ContactListener(void)
{
	_timeoutClock.restart();
}

ContactListener::~ContactListener(void)
{
	_contactData.clear();
}

void ContactListener::addData(void* data, const int timeout)
{
	_contactData.push_back(_contactDataStruct());

	_contactData.back()._data = data;
	_contactData.back()._timeout = timeout;
	_contactData.back()._contacts = 0;
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


void ContactListener::resetContacts()
{
	for (unsigned int i = 0; i < _contactData.size(); i++){
		_contactData[i]._contacts = 0;
	}
}


void ContactListener::BeginContact(b2Contact* contact){
    //check if fixture A was the sensor
	for (unsigned int i = 0; i < _contactData.size(); i++){
		if (contact->GetFixtureA()->GetUserData() == _contactData[i]._data){
			_contactData[i]._contacts++;
		}
	}
	
    //check if fixture B was the sensor
	for (unsigned int i = 0; i < _contactData.size(); i++){
		if (contact->GetFixtureB()->GetUserData() == _contactData[i]._data){
			_contactData[i]._contacts++;
		}
	}
}

void ContactListener::EndContact(b2Contact* contact){
    //check if fixture A was the sensor
    for (unsigned int i = 0; i < _contactData.size(); i++){
		if (contact->GetFixtureA()->GetUserData() == _contactData[i]._data){
			if (_contactData[i]._contacts > 0){
				_contactData[i]._contacts--;
			}
		}
	}

    //check if fixture B was the sensor
    for (unsigned int i = 0; i < _contactData.size(); i++){
		if (contact->GetFixtureB()->GetUserData() == _contactData[i]._data){
			if (_contactData[i]._contacts > 0){
				_contactData[i]._contacts--;
			}
		}
	}
}