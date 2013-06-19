#include "ContactListener.h"


ContactListener::ContactListener(void)
{
	_topContacts = 0;
	_leftContacts = 0;
	_bottomContacts = 0;
	_rightContacts = 0;

	_timeout.restart();
}


ContactListener::~ContactListener(void)
{}

bool ContactListener::touchingTop()
{
	_timeout_t = _timeout.getElapsedTime();
	if (_topContacts >= 1 && _timeout_t.asMilliseconds() > 100){
		_timeout.restart();
		return true;
	}
	return false;
}
bool ContactListener::touchingLeft()
{
	_timeout_t = _timeout.getElapsedTime();
	if (_leftContacts >= 1 && _timeout_t.asMilliseconds() > 100){
		_timeout.restart();
		return true;
	}
	return false;
}
bool ContactListener::touchingBottom()
{
	_timeout_t = _timeout.getElapsedTime();
	if (_bottomContacts >= 1 && _timeout_t.asMilliseconds() > 100){
		_timeout.restart();
		return true;
	}
	return false;
}
bool ContactListener::touchingRight()
{
	_timeout_t = _timeout.getElapsedTime();
	if (_rightContacts >= 1 && _timeout_t.asMilliseconds() > 100){
		_timeout.restart();
		return true;
	}
	return false;
}



void ContactListener::BeginContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == SEN_TOP) _topContacts++;
	if ((int)fixtureUserData == SEN_LEFT) _leftContacts++;
	if ((int)fixtureUserData == SEN_BOTTOM) _bottomContacts++;
    if ((int)fixtureUserData == SEN_RIGHT) _rightContacts++;

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == SEN_TOP) _topContacts++;
	if ((int)fixtureUserData == SEN_LEFT) _leftContacts++;
	if ((int)fixtureUserData == SEN_BOTTOM) _bottomContacts++;
    if ((int)fixtureUserData == SEN_RIGHT) _rightContacts++;
}

void ContactListener::EndContact(b2Contact* contact){
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ((int)fixtureUserData == SEN_TOP) _topContacts--;
	if ((int)fixtureUserData == SEN_LEFT) _leftContacts--;
	if ((int)fixtureUserData == SEN_BOTTOM) _bottomContacts--;
    if ((int)fixtureUserData == SEN_RIGHT) _rightContacts--;

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ((int)fixtureUserData == SEN_TOP) _topContacts--;
	if ((int)fixtureUserData == SEN_LEFT) _leftContacts--;
	if ((int)fixtureUserData == SEN_BOTTOM) _bottomContacts--;
    if ((int)fixtureUserData == SEN_RIGHT) _rightContacts--;
}