#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Globals.h"
#include "DebugObject.h"

class DebugConsole
{
public:
	DebugConsole(void);
	~DebugConsole(void);

	template<typename T>
	void assignPtr(T* object, std::string title)
	{
		dObject.emplace_back(DebugObject());

		dObject.back().assignPtr(object, title);

		dObject.back().setFont(defaultFont);
		dObject.back().setCharacterSize(textProps.charSize);
		dObject.back().setPosition((float)textProps.x, (float)textProps.y);

		textProps.y += (textProps.charSize + 2);
	}
	
	void draw();
	void clear();

private:
	sf::RenderWindow debugWindow;
	sf::Font defaultFont;

	std::vector<DebugObject> dObject;

	struct
	{
		int x;
		int y;

		int charSize;
	} textProps;

	sf::Event e;
};

