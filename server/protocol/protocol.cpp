#include "protocol.h"

using ServerSpace::BuyWeapon;
using ServerSpace::Equip;
using ServerSpace::MousePosition;
using ServerSpace::Move;
using ServerSpace::Shoot;
using ServerSpace::ShootBurst;
/*
using ServerSpace::BuyAmmo;
*/
#include <iostream>

ServerProtocol::ServerProtocol(Socket& socket): socket(socket) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::read_byte_data(uint8_t& data) {
    uint8_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint8_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = data_readed;
}

void ServerProtocol::read_two_byte_data(uint16_t& data) {
    uint16_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint16_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El cliente cerró la conexión");
    }
    data = ntohs(data_readed);
}

const std::string ServerProtocol::read_string() {
    length_string_t raw_length;
    this->socket.recvall(reinterpret_cast<char*>(&raw_length), sizeof(raw_length));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("Error al intentar leer longitud del cliente");
    }

    length_string_t length = ntohs(raw_length);
    std::vector<char> buffer(length);

    this->socket.recvall(buffer.data(), length);
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("Error al intentar leer datos del client");
    }

    return std::string(buffer.begin(), buffer.end());
}


LobbyCommandType ServerProtocol::read_lobby_command() {
    lobby_command_t command;
    this->read_byte_data(command);
    return static_cast<LobbyCommandType>(command);
}

CreateGame ServerProtocol::read_create_game() {
    std::string game_name = this->read_string();

    map_name_t map_name;
    this->read_byte_data(map_name);

    skin_t ct_skin;
    this->read_byte_data(ct_skin);

    skin_t tt_skin;
    this->read_byte_data(tt_skin);

    return CreateGame(
            game_name, static_cast<MapName>(map_name),
            Skins(static_cast<CounterTerroristSkin>(ct_skin), static_cast<TerroristSkin>(tt_skin)));
}

JoinGame ServerProtocol::read_join_game() {
    std::string game_name = this->read_string();

    skin_t ct_skin;
    this->read_byte_data(ct_skin);

    skin_t tt_skin;
    this->read_byte_data(tt_skin);

    return JoinGame(game_name, Skins(static_cast<CounterTerroristSkin>(ct_skin),
                                     static_cast<TerroristSkin>(tt_skin)));
}

PlayerCommandType ServerProtocol::read_player_command() {
    player_command_t command;
    this->read_byte_data(command);
    return static_cast<PlayerCommandType>(command);
}

std::unique_ptr<Move> ServerProtocol::read_move(const player_id_t& player_id) {
    move_t move_type;
    this->read_byte_data(move_type);
    return std::make_unique<Move>(player_id, static_cast<MoveType>(move_type));
}


std::unique_ptr<BuyWeapon> ServerProtocol::read_buy_weapon(const player_id_t& player_id) {
    weapon_code_t weapon_code;
    this->read_byte_data(weapon_code);
    std::unique_ptr<BuyWeapon> buy_weapon =
            std::make_unique<BuyWeapon>(player_id, static_cast<WeaponCode>(weapon_code));
    return buy_weapon;
}

std::unique_ptr<Shoot> ServerProtocol::read_shoot(const player_id_t& player_id) {
    coordinate_t x;
    coordinate_t y;
    this->read_two_byte_data(x);
    this->read_two_byte_data(y);
    return std::make_unique<Shoot>(player_id, x, y);
}

std::unique_ptr<ServerSpace::ShootBurst> ServerProtocol::read_shoot_burst(
        const player_id_t& player_id) {
    coordinate_t x;
    coordinate_t y;
    this->read_two_byte_data(x);
    this->read_two_byte_data(y);
    return std::make_unique<ShootBurst>(player_id, x, y);
}


/*
std::unique_ptr<BuyAmmo> ServerProtocol::read_buy_ammo(player_id_t player_id) {
    weapon_type_t weapon_type;
    ammo_t ammo_count;
    this->read_byte_data(weapon_type);
    this->read_two_byte_data(ammo_count);
    return std::make_unique<BuyAmmo>(player_id, static_cast<WeaponType>(weapon_type),
ammo_count);
}
}

*/

std::unique_ptr<Equip> ServerProtocol::read_equip(const player_id_t& player_id) {
    equip_type_t equip_type;
    this->read_byte_data(equip_type);
    return std::make_unique<Equip>(player_id, static_cast<EquipType>(equip_type));
}

std::unique_ptr<MousePosition> ServerProtocol::read_mouse_position(const player_id_t& player_id) {
    coordinate_t mouse_x, mouse_y;
    this->read_two_byte_data(mouse_x);
    this->read_two_byte_data(mouse_y);
    return std::make_unique<MousePosition>(player_id, mouse_x, mouse_y);
}

void ServerProtocol::send_byte_data(const uint8_t& data) {
    this->socket.sendall(&data, sizeof(uint8_t));
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al cliente");
    }
}

void ServerProtocol::send_two_byte_data(uint16_t& data) {
    uint16_t data_to_send = htons(data);
    this->socket.sendall(&data_to_send, sizeof(uint16_t));
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al cliente");
    }
}


void ServerProtocol::send_map_info(const MapInfo& map_info) {
    map_name_t map_name = static_cast<map_name_t>(map_info.map_name);
    this->send_byte_data(map_name);

    RectangleInfo bomb_A = map_info.bomb_A;
    this->send_position(bomb_A.pos_min);
    this->send_position(bomb_A.pos_max);

    RectangleInfo bomb_B = map_info.bomb_B;
    this->send_position(bomb_B.pos_min);
    this->send_position(bomb_B.pos_max);

    RectangleInfo spawn_TT = map_info.spawn_TT;
    this->send_position(spawn_TT.pos_min);
    this->send_position(spawn_TT.pos_max);

    RectangleInfo spawn_CT = map_info.spawn_CT;
    this->send_position(spawn_CT.pos_min);
    this->send_position(spawn_CT.pos_max);

    length_walls_t walls_length = map_info.walls.size();
    this->send_two_byte_data(walls_length);
    for (const Position& wall: map_info.walls) {
        this->send_position(wall);
    }
    length_boxes_t boxes_length = map_info.boxes.size();
    this->send_two_byte_data(boxes_length);
    for (const Position& box: map_info.boxes) {
        this->send_position(box);
    }
}

void ServerProtocol::send_position(const Position& position) {
    coordinate_t x = position.x;
    this->send_two_byte_data(x);

    coordinate_t y = position.y;
    this->send_two_byte_data(y);
}

void ServerProtocol::send_list_games(ListGame& games) {
    std::vector<std::string> list_games = games.list_games;
    length_games_list_t list_size = list_games.size();
    this->send_two_byte_data(list_size);

    for (const std::string& game_name: list_games) {
        length_string_t name_length = game_name.size();
        this->send_two_byte_data(name_length);

        this->socket.sendall(game_name.data(), name_length);
        if (this->socket.is_stream_send_closed()) {
            throw ConnectionClosedException("Error al intentar enviar datos al cliente");
        }
    }
}

void ServerProtocol::send_game_info(GameInfo& game_info) {
    this->send_map_info(game_info.map_info);
    length_weapons_info_t weapons_length = game_info.weapons_purchasables.size();
    this->send_byte_data(weapons_length);
    for (const WeaponInfo& weapon_info: game_info.weapons_purchasables) {
        weapon_code_t weapon_code = static_cast<weapon_code_t>(weapon_info.code);
        this->send_byte_data(weapon_code);

        uint16_t price = weapon_info.price;
        this->send_two_byte_data(price);
    }
}

Acknowledge ServerProtocol::read_acknowledge() {
    acknowledge_t acknowledge;
    this->read_byte_data(acknowledge);
    return static_cast<Acknowledge>(acknowledge);
}

void ServerProtocol::send_client_id(player_id_t& client_id) { this->send_two_byte_data(client_id); }

void ServerProtocol::send_weapons(const PlayerImage& player_image) {
    length_weapons_images_t length_weapons = player_image.weapons.size();
    std::vector<WeaponImage> weapons_images = player_image.weapons;
    this->send_byte_data(length_weapons);

    for (const WeaponImage& weapon_image: weapons_images) {
        weapon_code_t weapon_code = static_cast<weapon_code_t>(weapon_image.weapon_code);
        this->send_byte_data(weapon_code);

        uint8_t current_bullets = weapon_image.current_bullets;
        this->send_byte_data(current_bullets);

        uint8_t magazine = weapon_image.magazine;
        this->send_byte_data(magazine);
    }
}
void ServerProtocol::send_sound(sound_type_t type, distance_sound_t distance) {
    this->send_byte_data(type);
    this->send_two_byte_data(distance);
}
void ServerProtocol::send_shoot_sounds(const PlayerImage& player_image) {
    length_heared_sounds_t length_shoot_sounds = player_image.heared_sounds.shoot_sounds.size();
    std::vector<SoundShootImage> shoot_sounds_images = player_image.heared_sounds.shoot_sounds;
    this->send_byte_data(length_shoot_sounds);
    for (const SoundShootImage& shoot: shoot_sounds_images) {
        distance_sound_t distance = shoot.distance;
        this->send_two_byte_data(distance);
        weapon_code_t code = static_cast<weapon_code_t>(shoot.code);
        this->send_byte_data(code);
    }
}
void ServerProtocol::send_common_sounds(const PlayerImage& player_image) {
    length_heared_sounds_t length_sounds = player_image.heared_sounds.common_sounds.size();
    std::vector<SoundCommonImage> sounds_images = player_image.heared_sounds.common_sounds;
    this->send_byte_data(length_sounds);
    for (const SoundCommonImage& common: sounds_images) {
        sound_type_t type = static_cast<sound_type_t>(common.type);
        distance_sound_t distance = common.distance;
        this->send_sound(type, distance);
    }
}
void ServerProtocol::send_sound_image(const PlayerImage& player_image) {
    this->send_common_sounds(player_image);
    this->send_shoot_sounds(player_image);
}
void ServerProtocol::send_players_images(std::vector<PlayerImage>& players_images) {
    length_players_images_t length_players = players_images.size();
    this->send_two_byte_data(length_players);

    for (const PlayerImage& player_image: players_images) {
        player_id_t player_id = player_image.player_id;
        this->send_two_byte_data(player_id);

        this->send_position(player_image.position);

        health_t health = player_image.health;
        this->send_byte_data(health);

        deaths_t deaths = player_image.deaths;
        this->send_byte_data(deaths);
        deaths_t kills = player_image.kills;
        this->send_byte_data(kills);
        points_t points = player_image.points;
        this->send_two_byte_data(points);

        money_t money = player_image.money;
        this->send_two_byte_data(money);
        money_t collected_money = player_image.collected_money;
        this->send_two_byte_data(collected_money);
        weapon_code_t equipped_weapon_code =
                static_cast<weapon_code_t>(player_image.equipped_weapon);
        this->send_byte_data(equipped_weapon_code);

        this->send_weapons(player_image);

        this->send_sound_image(player_image);

        team_t team = static_cast<team_t>(player_image.team);
        this->send_byte_data(team);

        this->send_position(player_image.mouse_position);

        skin_t ct_skin = static_cast<skin_t>(player_image.skin.ct_skin);
        this->send_byte_data(ct_skin);


        skin_t tt_skin = static_cast<skin_t>(player_image.skin.tt_skin);
        this->send_byte_data(tt_skin);
    }
}

void ServerProtocol::send_bullets_in_air(std::vector<BulletImage>& bullets_in_air_image) {
    length_bullets_in_air_t length_bullets = bullets_in_air_image.size();
    this->send_two_byte_data(length_bullets);
    for (const BulletImage& bullet_in_air_image: bullets_in_air_image) {
        this->send_position(bullet_in_air_image.initial);
        this->send_position(bullet_in_air_image.end);
        uint8_t width = bullet_in_air_image.width;
        weapon_code_t weapon_code = static_cast<weapon_code_t>(bullet_in_air_image.code);
        this->send_byte_data(width);
        this->send_byte_data(weapon_code);
    }
}

void ServerProtocol::send_bomb_image(BombImage& bomb_image) {
    weapon_code_t bomb_code = static_cast<weapon_code_t>(bomb_image.weapon_code);
    this->send_byte_data(bomb_code);

    this->send_position(bomb_image.position);

    bomb_state_t bomb_state = static_cast<bomb_state_t>(bomb_image.state);
    this->send_byte_data(bomb_state);
}

void ServerProtocol::send_weapons_dropped(std::vector<WeaponDropped>& weapons_dropped) {
    length_weapons_dropped_t weapons_length = weapons_dropped.size();
    this->send_byte_data(weapons_length);
    for (const WeaponDropped& weapon_dropped: weapons_dropped) {
        weapon_code_t weapon_code = static_cast<weapon_code_t>(weapon_dropped.weapon_code);
        this->send_byte_data(weapon_code);

        this->send_position(weapon_dropped.position);
    }
}

void ServerProtocol::send_game_state_image(GameStateImage& game_state_image) {
    game_state_t state = static_cast<game_state_t>(game_state_image.state);
    this->send_byte_data(state);

    round_time_t time = game_state_image.time;
    this->send_two_byte_data(time);

    round_t round = game_state_image.round;
    this->send_byte_data(round);
}

void ServerProtocol::send_game_image(GameImage& game_image) {
    player_id_t client_id = game_image.client_id;
    this->send_client_id(client_id);

    std::vector<PlayerImage> players_images = game_image.players_images;
    this->send_players_images(players_images);


    std::vector<BulletImage> bullets_in_air = game_image.bullets_in_air;
    this->send_bullets_in_air(bullets_in_air);

    BombImage bomb_image = game_image.bomb;
    this->send_bomb_image(bomb_image);

    std::vector<WeaponDropped> weapons_dropped = game_image.dropped_things;
    this->send_weapons_dropped(weapons_dropped);

    GameStateImage game_state_image = game_image.game_state;
    this->send_game_state_image(game_state_image);
}