#ifndef SOUND_CONFIG_H
#define SOUND_CONFIG_H
#include <iostream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <yaml-cpp/yaml.h>

#include "../common/sound_image.h"

#include "tipos.h"

class SoundConfig {
private:
    std::map<SoundType, Mix_Chunk*> effects;
    std::map<WeaponCode, Mix_Chunk*> shoots;
    std::map<Music, Mix_Music*> musics;
    std::map<EffectType, Mix_Chunk*> sounds;
    bool bomb_explode;
    bool finish_round;
    bool start_game;


    void loadFromYAML(const std::string& filepath);

    /*
    pre: el canal debe estar activo
    post: aplica una posición espacial al canal de sonido especificado
    */
    void set_position(const int& channel, const Uint16& angle, const Uint8& distance);

public:
    SoundConfig(const int& volumen);

    void set_bomb(const bool& state);

    void set_round(const bool& state);

    bool get_bomb_sound();

    bool get_round_sound();

    void load_sound(const EffectType& id, const std::string& filepath);

    void play_effect_with_position(const SoundType& id, Uint16 angle, Uint8 distance);

    void play_shoot_with_position(const WeaponCode& id, Uint16 angle, Uint8 distance);
    /*
    pre: recibe un booleano válido
    post: actualiza el estado interno del juego
    */
    void set_start_game(const bool& new_state);

    /*
    post: devuelve el estado actual del juego
    */
    bool get_state_game();

    /*
    pre: filepath debe ser una ruta válida a un archivo .wav ..
    post: carga el efecto de sonido en el mapa effects bajo el id proporcionado
    */
    void load_effect(const SoundType& id, const std::string& filepath);

    /*
    pre: filepath debe ser una ruta válida a un archivo de música compatible
    post: carga la música en el mapa musics bajo el id proporcionado
    */
    void load_music(const Music& id, const std::string& filepath);

    void load_shoot(const WeaponCode& id, const std::string& filepath);

    /*
    pre: el id debe existir en el mapa effects
    post: reproduce el efecto de sonido correspondiente con la cantidad de repeticiones indicada por
    loops
    */
    void play_effect(const SoundType& id, int loops);

    void play_sound(const EffectType& id, int loops);

    /*
    pre: el id debe existir en el mapa musics
    post: reproduce la música correspondiente con la cantidad de repeticiones indicada por loops
    */
    void play_music(const Music& id, int loops);

    void play_shoot(const WeaponCode& id, int loops = 0);

    /*
    post: detiene la reproducción de la música actual
    */
    void stop_music();

    ~SoundConfig();
};

#endif  // SOUND_CONFIG_H
