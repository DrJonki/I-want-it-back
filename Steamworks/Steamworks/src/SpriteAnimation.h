#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Audio/Sound.hpp>
#include <string>
#include <vector>
#include <memory>

class SpriteAnimation
{
public:
	SpriteAnimation(void);
	~SpriteAnimation(void);

	//Loads an animation strip from an image file. This implementation takes one line of sprites
	//on the sheet and assigns them to one animation cycle.
	void loadSheet(sf::Image &sheet,		//A reference to the source image
				   const int startX,		//The left-most X coordinate of the first sprite image
				   const int startY,		//The top Y coordinate of the 
				   const int frameSizeX,	//The horizontal size of one frame. All the frames on the sheet must be this same size
				   const int frameSizeY,	//The vertical size of one frame.
				   const int frameCount);	//Number of frames to load.

	void stepForward(); //Step forward the number of frames specified by _stepInterval
	void stepBack();	//Step the animation cycle backward respectively
	void setFrame(const unsigned int frame) { _currentFrame = frame; }; //Set the current frame. Can be used to reset the animation.

	bool lastFrame(); //Returns true if the current frame is the last one.

	void setStepInterval(const int interval) { _stepInterval = interval; }; //Set the step interval. For example, a value of 2 means the frame gets updated every second step call.
	int getStepInterval() { return _stepInterval; }; //Returns the set step interval.

	void assignSound(sf::Sound *sound, const unsigned int frame); //Assigns a sound to be played when _currentFrame matches the parametre.
																  //The sound needs to be alive outside this class.
	void unassignSound(const unsigned int frame, const bool all = false); //Releases the sound hook for the specified frame, or all of them if all = true

	sf::Texture getCurrentTexture() { return *frameTexture[_currentFrame - 1]; }; //Returns a pointer to the current frame texture.

private:
	unsigned int _currentFrame; //The current animation frame
	unsigned int _frameCount; //Number of frames in animation
	unsigned int _stepInterval; //How many times to call the update function before updating frame
	unsigned int _tempSteps; //A helper variable to check the step interval

	//std::vector<sf::Texture> frameTexture;
	std::vector<std::shared_ptr<sf::Texture>> frameTexture; //Container for the frame textures
	//std::vector<> assignedSounds;

protected:

	//Enumeration for the different animation states
	enum
	{
		IDLE, //IDLE2, IDLE3, etc.
		
		WALKING_LEFT,
		WALKING_RIGHT,
		RUNNING_LEFT,
		RUNNING_RIGHT,


		CROUCHING_LEFT,
		JUMPING_LEFT,
		SHOOTING_LEFT,

	};
};