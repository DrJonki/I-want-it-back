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
				   const int frameCount);	//Number of frames to load. Must be exact. Missing textures will be replaced with a white box.

	void stepForward(); //Step animation cycle forward by 1 / _stepInterval. For example, if the step interval was 10, this call would have to be made 10 times before the frame would update.
	void stepBack();	//Step the animation cycle backward respectively.
	void setCurrentFrame(const unsigned int currentFrame) { _currentFrame = currentFrame; _tempSteps = 1; }; //Set the current frame. Can be used to reset the animation.

	bool lastFrame(); //Returns true if the current frame is the last one.

	void setStepInterval( const unsigned int stepInterval) { _stepInterval = stepInterval; }; //Set the step interval. For example, a value of 2 means the frame gets updated every second step call.
	int getStepInterval() { return _stepInterval; }; //Returns the set step interval.

	void assignSound(sf::Sound *sound, const unsigned int frame); //Assigns a sound to be played when _currentFrame matches the parametre.
																  //The sound needs to be alive outside this class.
	void unassignSound(const unsigned int frame, const bool all = false); //Releases the sound hook for the specified frame, or all of them if all = true

	sf::Texture& getCurrentTexture() { return frameTexture[_currentFrame - 1]; }; //Returns a reference to the current frame texture.

private:
	unsigned int _currentFrame; //The current animation frame
	unsigned int _frameCount; //Number of frames in animation
	unsigned int _stepInterval; //How many times to call the update function before updating frame
	unsigned int _tempSteps; //A helper variable to check the step interval

	std::vector<sf::Texture> frameTexture; //Container for the textures
	//std::vector<> assignedSounds;

protected:

};