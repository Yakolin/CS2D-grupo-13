#include "soundConfig.h"
#include <SDL_mixer.h>

SoundConfig::SoundConfig():
	effects(),
	musics(),
	start_game(false)
{

	loadMusic(Music::SALA_ESPERA,"assets/sfx/sala_fixed.wav");
	//loadMusic(Music::JUEGO,"");

}

void SoundConfig::set_start_game(const bool& new_state){ start_game = new_state;}

bool SoundConfig::get_state_game(){return start_game;}

bool SoundConfig::loadEffect(const std::string& id, const std::string& filepath) {
	Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());
	if (!chunk) {
		SDL_Log("No se pudo cargar efecto %s: %s", filepath.c_str(), Mix_GetError());
		return false;
	}
	effects[id] = chunk;
	return true;
}

void SoundConfig::playEffect(const std::string& id, int loops = 0) {
	if (effects.find(id) != effects.end()) {
		Mix_PlayChannel(-1, effects[id], loops);
	}
}


bool SoundConfig::loadMusic(const Music& id, const std::string& filepath) {
	std::cout << "Música cargando : " << static_cast<int>(id) << std::endl;
	Mix_Music* music = Mix_LoadMUS(filepath.c_str());
    if (!music) {
        SDL_Log("No se pudo cargar música %s: %s", filepath.c_str(), Mix_GetError());
        return false;
    }
    musics[id] = music;
    std::cout << "Música cargada correctamente con ID: " << static_cast<int>(id) << std::endl;
	return true;
}
/*
post: reprodice una musica por defecto en bucle -1 pero se puede pasar un numeros de reproduccion.
*/
void SoundConfig::playMusic(const Music& id, int loops = -1) {
	std::cout << "Reproduciendo música: " << static_cast<int>(id) << std::endl;

    auto it = musics.find(id);
    if (it == musics.end()) {
        std::cerr << "No se encontró la música con ID: " << static_cast<int>(id) << std::endl;
        return;
    }

    if (Mix_PlayMusic(it->second, loops) == -1) {
        std::cerr << "Error al reproducir la música: " << Mix_GetError() << std::endl;
    }
}
/*
post: detine la musica actual
*/
void SoundConfig::stopMusic() {
	std::cout <<"cerrando musica actual";
	Mix_HaltMusic();
}

void SoundConfig::setPosition(const int& channel,const Uint16& angle,const Uint8& distance) {
	Mix_SetPosition(channel, angle, distance);
}

SoundConfig::~SoundConfig() {
	for (auto& pair : effects) {
        Mix_FreeChunk(pair.second); 
    }
    effects.clear(); 
    for (auto& pair : musics) {
        Mix_FreeMusic(pair.second);  
    }
    musics.clear(); 
}