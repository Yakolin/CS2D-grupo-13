#ifndef SOUND_CONFIG_H
#define SOUND_CONFIG_H
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <SDL2/SDL.h>     
#include "tipos.h"
class SoundConfig{

private:
	std::map<std::string, Mix_Chunk*> effects;
	std::map<Music, Mix_Music*> musics;
    bool start_game;


public:
    SoundConfig();
    void set_start_game(const bool& new_state);

    bool get_state_game();

    bool loadEffect(const std::string& id, const std::string& filepath);
    void playEffect(const std::string& id, int loops);
    bool loadMusic(const Music& id, const std::string& filepath);
    void playMusic(const Music& id, int loops);
    void stopMusic();
    void setPosition(const int& channel,const  Uint16& angle,const Uint8& distance);
    ~SoundConfig();
};


#endif  // SOUND_CONFIG_H