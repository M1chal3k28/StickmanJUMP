#pragma once
#include <SFML/Audio.hpp>

enum SoundEffect {
	Jump,
	Shoot,
	PowerUp,
	Hit,
	Dead,
	LevelUp,
	ShieldBreak
};

class AudioHandler
{
public:
	AudioHandler();
	virtual ~AudioHandler() {};

	void playEffect(SoundEffect effectName);
	void playLoopMusic();
	void stopLoopedMusic();

private:
	// Buffers !
	sf::SoundBuffer jump;
	sf::SoundBuffer shoot;
	sf::SoundBuffer powerUp;
	sf::SoundBuffer hit;
	sf::SoundBuffer dead;
	sf::SoundBuffer levelUp;
	sf::SoundBuffer shieldBreak;

	// Elements to play;
	sf::Sound shieldBreakEffect;
	sf::Sound jumpEffect;
	sf::Sound shootEffect;
	sf::Sound powerUpEffect;
	sf::Sound hitEffect;
	sf::Sound deadEffect;
	sf::Sound levelUpEffect;

	// Music
	sf::Music music;
};