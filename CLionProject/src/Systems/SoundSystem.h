//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_SOUNDSYSTEM_H
#define ROGUEEMBLEMGAME_SOUNDSYSTEM_H


#include "System.h"

//Class that will manage sound and music
class SoundSystem : public System {
public:
	SoundSystem() = default;

	//Inherited methods from System
	void handleMsg(Message &msg) override;

	void startup() override;

	void shutdown() override;


private:
	//Plays a sound effect
	//void playSound(SoundEffect& sound);

	//Starts/stops/pauses/resumes current music
	//void playMusic(Music& music);
	//void stopMusic();
};


#endif //ROGUEEMBLEMGAME_SOUNDSYSTEM_H
