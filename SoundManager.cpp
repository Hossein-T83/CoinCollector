#include "SoundManager.h"
//definition of constructor
soundManager::soundManager() {
	//loading buffers from file then assigning it to sounds
	collectingBuffer.loadFromFile("sound/coin.wav");
	collecting.setBuffer(collectingBuffer);

	cherryBuffer.loadFromFile("sound/cherry.wav");
	cherrySound.setBuffer(cherryBuffer);

	winBuffer.loadFromFile("sound/win.wav");
	winSound.setBuffer(winBuffer);

	hitBuffer.loadFromFile("sound/hit.wav");
	hit.setBuffer(hitBuffer);
}
//defninition of methods to play sounds
void soundManager::playCollect() {
	collecting.play();
}
void soundManager::playCherry() {
	cherrySound.play();
}
void soundManager::playHit() {
	hit.play();
}
void soundManager::playWin() {
	winSound.play();
}