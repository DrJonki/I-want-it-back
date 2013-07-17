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

std::vector<void*>& ContactListener::getOtherData(void* data)
{
	for (unsigned int i = 0; i < _contactData.size(); i++){
		if (data == _contactData[i]._data){
			return _contactData[i]._otherData;
		}
	}

	return dummyVector;
}


void ContactListener::addData(void* data, const int timeout)
{
	_contactData.push_back(_contactDataStruct());

	_contactData.back()._data = data;
	_contactData.back()._timeout = timeout;
	_contactData.back()._contacts = 0;
}


void ContactListener::BeginContact(b2Contact* contact){
    //check if fixture A was the sensor
	for (unsigned int i = 0; i < _contactData.size(); i++){
		if (contact->GetFixtureA()->GetUserData() == _contactData[i]._data) _contactData[i]._contacts++;
		//else _contactData[i]._otherData.emplace_back(contact->GetFixtureA()->GetUserData());
	}
	
    //check if fixture B was the sensor
	for (unsigned int i = 0; i < _contactData.size(); i++){
		if (contact->GetFixtureB()->GetUserData() == _contactData[i]._data) _contactData[i]._contacts++;
		//else _contactData[i]._otherData.emplace_back(contact->GetFixtureB()->GetUserData());
	}
}

void ContactListener::EndContact(b2Contact* contact){
    //check if fixture A was the sensor
    for (unsigned int i = 0; i < _contactData.size(); i++){
		if (contact->GetFixtureA()->GetUserData() == _contactData[i]._data){
			_contactData[i]._contacts--;
			/*for (unsigned int j = 0; j < _contactData[i]._otherData.size(); j++){
				if (_contactData[i]._otherData[j] == contact->GetFixtureA()->GetUserData()){
					_contactData[i]._otherData.erase(_contactData[i]._otherData.begin() + j);
				}
			}*/
		}
	}

    //check if fixture B was the sensor
    for (unsigned int i = 0; i < _contactData.size(); i++){
		if (contact->GetFixtureB()->GetUserData() == _contactData[i]._data){
			_contactData[i]._contacts--;
			/*for (unsigned int j = 0; j < _contactData[i]._otherData.size(); j++){
				if (_contactData[i]._otherData[j] == contact->GetFixtureB()->GetUserData()){
					_contactData[i]._otherData.erase(_contactData[i]._otherData.begin() + j);
				}
			}*/
		}
	}
}