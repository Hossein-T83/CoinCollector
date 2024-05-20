#pragma once
#include <SFML/Audio.hpp>
using namespace sf;
//creating class to manage sounds
class soundManager
{
public:
	//constructor
	soundManager();
	//functions for diffrent sounds
	void playCollect();
	void playCherry();
	void playWin();
	void playHit();

private:
	//all private varibles to create diffrent sounds
	SoundBuffer collectingBuffer;
	Sound collecting;

	SoundBuffer cherryBuffer;
	Sound cherrySound;

	SoundBuffer winBuffer;
	Sound winSound;

	SoundBuffer hitBuffer;
	Sound hit;

};

