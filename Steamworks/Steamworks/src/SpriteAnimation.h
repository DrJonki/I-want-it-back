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

	/// Loads an animation strip from an image file. This implementation takes one line of sprites
	/// on the sheet and assigns them to one animation cycle.
	/// @param A reference to the source image.
	/// @param The left-most X coordinate of the first sprite image.
	/// @param The top Y coordinate of the first sprite image.
	/// @param The horizontal size of one frame. All the frames on the sheet must be this same size.
	/// @param The vertical size of one frame.
	/// @param Number of frames to load. Must be exact. Missing textures will be replaced with a white box.
	/// @param Is texture smoothing on.
	bool loadSheet(sf::Image &sheet,
				   const int startX,
				   const int startY,
				   const int frameSizeX,
				   const int frameSizeY,
				   const int frameCount,
				   const bool smooth = false);


	/// Step animation cycle forward by 1 / _stepInterval.
	/// For example, if the step interval was 10,
	/// this call would have to be made 10 times before the frame would update.
	/// @param Ignore step interval and force frame change.
	void stepForward(const bool force = false);


	/// Step animation cycle backward by 1 / _stepInterval.
	/// For example, if the step interval was 10,
	/// this call would have to be made 10 times before the frame would update.
	/// @param Ignore step interval and force frame change.
	void stepBack(const bool force = false);

	/// Get the current frame number.
	/// @return Number of the current frame.
	int getCurrentFrame() { return _currentFrame; };

	/// Set the current frame. Can be used to reset the animation.
	/// @param The number of the frame to be set as current.
	void setCurrentFrame(const unsigned int currentFrame);


	/// Returns true if the current frame is the last one in the cycle.
	/// @return Current frame is the last one.
	bool lastFrame();

	/// Returns true if the current frame is different from the last one.
	/// @return Current frame is different from the last.
	bool frameChanged();


	/// Set the step interval. For example,
	/// a value of 2 means the frame gets updated every second step call.
	/// @param The desired step interval.
	void setStepInterval(const unsigned int stepInterval) { _stepInterval = stepInterval; };


	/// Returns the set step interval.
	/// @return Current step interval.
	int getStepInterval() { return _stepInterval; };


	/// Assigns a sound to be played when _currentFrame matches the parametre.
	/// The sound needs to be alive outside this class.
	/// @param A reference to the sound to be assigned.
	/// @param Frame into which the sound shall be assigned.
	void assignSound(sf::Sound& sound, const unsigned int frame);
	

	/// Releases the sound hook for the specified frame.
	/// @param The number of the frame from which the sound is to be unassigned from.
	/// @param Should all sounds be unassigned. If true, the value of the first parameter doesn't matter.
	void unassignSound(const unsigned int frame, const bool all = false);


	/// Returns a reference to the current frame texture.
	/// @return Current texture in the cycle.
	sf::Texture& getCurrentTexture() { return frameTexture[_currentFrame - 1]; };

private:
	/// The current animation frame.
	unsigned int _currentFrame;

	/// Number of frames in animation.
	unsigned int _frameCount; 

	/// How many times to call the update function before updating frame.
	unsigned int _stepInterval;

	/// A helper variable to check the step interval.
	unsigned int _tempSteps;

	/// A helper variable to check if frame has changed.
	bool _frameChanged;


	/// A container for the textures.
	std::vector<sf::Texture> frameTexture; 

	//std::vector<> assignedSounds;
};