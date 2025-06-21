#include "soundConfig.h"
#include <SDL_mixer.h>

SoundConfig::SoundConfig():
	effects(),
	musics(),
	start_game(false)
{

	//loadMusic(Music::SALA_ESPERA,"assets/sfx/sala_fixed.wav");
	//loadMusic(Music::JUEGO,"");
	loadFromYAML("assets/music.yaml");

}
SoundType soundTypeFromString(const std::string& str) {
    if (str == "SHOOT") return SoundType::SHOOT;
    if (str == "WALK") return SoundType::WALK;
    if (str == "RELOAD") return SoundType::RELOAD;
    if (str == "HIT") return SoundType::HIT;
    if (str == "CHANGE_WEAPON") return SoundType::CHANGE_WEAPON;
    if (str == "DROP") return SoundType::DROP;
    if (str == "DIE") return SoundType::DIE;
    if (str == "PICK_UP") return SoundType::PICK_UP;

    throw std::invalid_argument("Tipo de efecto desconocido: " + str);
}

Music musicFromString(const std::string& str) {
    if (str == "SALA_ESPERA") return Music::SALA_ESPERA;
    if (str == "JUEGO") return Music::JUEGO;
    throw std::invalid_argument("Tipo de música desconocido: " + str);
}

WeaponCode shootFromString(const std::string& str) {
    if (str == "GLOCK") return WeaponCode::GLOCK;
    if (str == "AK47") return WeaponCode::AK47;
    if (str == "AWP") return WeaponCode::AWP;
    if (str == "M3") return WeaponCode::M3;
    if (str == "KNIFE") return WeaponCode::KNIFE;
    if (str == "BOMB") return WeaponCode::BOMB;
    throw std::invalid_argument("WeaponCode desconocido: " + str);
}


void SoundConfig::loadFromYAML(const std::string& filepath) {
    YAML::Node config = YAML::LoadFile(filepath);

    if (config["shoot"]) {
        for (const auto& node : config["shoot"]) {
            std::string key = node.first.as<std::string>();
            std::string path = node.second.as<std::string>();
			WeaponCode id = shootFromString(key);
			load_shoot(id, path);
        }
    }
	if (config["effect"]) {
        for (const auto& node : config["effect"]) {
            std::string key = node.first.as<std::string>();
            std::string path = node.second.as<std::string>();
			SoundType id = soundTypeFromString(key);
			load_effect(id, path);
        }
    }
    if (config["music"]) {
        for (const auto& node : config["music"]) {
            std::string key = node.first.as<std::string>();
            std::string path = node.second.as<std::string>();
			Music id = musicFromString(key);
			load_music(id, path);
        }
    }
}


void SoundConfig::set_start_game(const bool& new_state){ start_game = new_state;}

bool SoundConfig::get_state_game(){return start_game;}

void SoundConfig::load_effect(const SoundType& id, const std::string& filepath) {
	
	Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());
	if (!chunk) {
		SDL_Log("No se pudo cargar efecto %s: %s", filepath.c_str(), Mix_GetError());
		return ;
	}
	effects[id] = chunk;
    std::cout << "effecto cargada correctamente con ID: " << static_cast<int>(id) << std::endl;

}

void SoundConfig::load_shoot(const WeaponCode& id, const std::string& filepath) {
	
	Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());
	if (!chunk) {
		SDL_Log("No se pudo cargar shoot %s: %s", filepath.c_str(), Mix_GetError());
		return ;
	}
	shoots[id] = chunk;
    std::cout << "shoot cargada correctamente con ID: " << static_cast<int>(id) << std::endl;
}

void SoundConfig::load_music(const Music& id, const std::string& filepath) {

	Mix_Music* music = Mix_LoadMUS(filepath.c_str());
    if (!music) {
        SDL_Log("No se pudo cargar música %s: %s", filepath.c_str(), Mix_GetError());
        return ;
    }
    musics[id] = music;
    std::cout << "Música cargada correctamente con ID: " << static_cast<int>(id) << std::endl;
}

void SoundConfig::play_effect(const SoundType& id, int loops ) {
	
	if (effects.find(id) != effects.end()) {
		Mix_PlayChannel(-1, effects[id], loops);
	}
}
void SoundConfig::play_effect_with_position(const SoundType& id, Uint16 angle, Uint8 distance) {
    auto it = effects.find(id);
    if (it == effects.end()) {
        SDL_Log("Efecto no encontrado para el ID %d", static_cast<int>(id));
        return;
    }

    int canal = Mix_PlayChannel(-1, it->second, 0);
    if (canal != -1) {
        set_position(canal, angle, distance);
    } else {
        SDL_Log(" No hay canales disponibles para reproducir el sonido.");
    }
}


void SoundConfig::play_shoot_with_position(const WeaponCode& id, Uint16 angle, Uint8 distance) {
    
	auto it = shoots.find(id);
    if (it == shoots.end()) {
        SDL_Log("shoot no encontrado para el ID %d", static_cast<int>(id));
        return;
    }

    int canal = Mix_PlayChannel(-1, it->second, 0);
    if (canal != -1) {
        set_position(canal, angle, distance);
    } else {
        SDL_Log(" No hay canales disponibles para reproducir el sonido.");
    }
}

void SoundConfig::play_shoot(const WeaponCode& id, int loops) {
	if (shoots.find(id) != shoots.end()) {
		Mix_PlayChannel(-1, shoots[id], loops);
	}
}

void SoundConfig::play_music(const Music& id, int loops) {
    auto it = musics.find(id);
    if (it == musics.end()) {
        std::cerr << "No se encontró la música con ID: " << static_cast<int>(id) << std::endl;
        return;
    }

    if (Mix_PlayMusic(it->second, loops) == -1) {
        std::cerr << "Error al reproducir la música: " << Mix_GetError() << std::endl;
    }
}

void SoundConfig::stop_music() {
	std::cout <<"cerrando musica actual";
	Mix_HaltMusic();
}

void SoundConfig::set_position(const int& channel,const Uint16& angle,const Uint8& distance) {
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
	for (auto& pair : shoots) {
        Mix_FreeChunk(pair.second);  
    }
    shoots.clear(); 
}