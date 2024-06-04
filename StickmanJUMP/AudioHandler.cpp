#include "AudioHandler.h"

AudioHandler::AudioHandler()
{
	// Load from file
	this->shoot.loadFromFile("Sounds/shootEf.wav");
	this->jump.loadFromFile("Sounds/jump.wav");
	this->hit.loadFromFile("Sounds/hit.wav");
	this->powerUp.loadFromFile("Sounds/bonus.wav");
	this->dead.loadFromFile("Sounds/dead.wav");
	this->levelUp.loadFromFile("Sounds/levelUp.wav");
	this->shieldBreak.loadFromFile("Sounds/shieldBreak.wav");

	this->music.openFromFile("Sounds/music.mp3");
	this->music.setLoop(true);

	// Set audioEffect 
	this->shieldBreakEffect.setBuffer(this->shieldBreak);
	this->hitEffect.setBuffer(this->hit);
	this->powerUpEffect.setBuffer(this->powerUp);
	this->jumpEffect.setBuffer(this->jump);
	this->deadEffect.setBuffer(this->dead);
	this->shootEffect.setBuffer(this->shoot);
	this->levelUpEffect.setBuffer(this->levelUp);

	// Set volume
	this->shieldBreakEffect.setVolume(30);
	this->hitEffect.setVolume(30);
	this->powerUpEffect.setVolume(30);
	this->jumpEffect.setVolume(30);
	this->deadEffect.setVolume(30);
	this->shootEffect.setVolume(30);
	this->levelUpEffect.setVolume(30);
}

void AudioHandler::playEffect(SoundEffect effectName)
{
	if (effectName == Jump) jumpEffect.play();
	if (effectName == Hit) hitEffect.play();
	if (effectName == PowerUp) powerUpEffect.play();
	if (effectName == Dead) deadEffect.play();
	if (effectName == LevelUp) levelUpEffect.play();
	if (effectName == Shoot) shootEffect.play();
	if (effectName == ShieldBreak) shieldBreakEffect.play();
}

void AudioHandler::playLoopMusic()
{
	this->music.play();
}

void AudioHandler::stopLoopedMusic()
{
	this->music.stop();
}
