#include "protocol.h"

#include <iostream>
ClientProtocol::ClientProtocol(Socket& socket): socket(socket) {}

ClientProtocol::~ClientProtocol() {}

void ClientProtocol::read_map_info(MapInfo& map_info) {
    map_name_t map_name;
    this->read_byte_data(map_name);

    RectangleInfo bomb_A, bomb_B, spawn_TT, spawn_CT;
    this->read_position(bomb_A.pos_min);
    this->read_position(bomb_A.pos_max);

    this->read_position(bomb_B.pos_min);
    this->read_position(bomb_B.pos_max);

    this->read_position(spawn_TT.pos_min);
    this->read_position(spawn_TT.pos_max);

    this->read_position(spawn_CT.pos_min);
    this->read_position(spawn_CT.pos_max);

    length_walls_t walls_length;
    this->read_two_byte_data(walls_length);
    std::vector<Position> walls;
    for (length_walls_t i = 0; i < walls_length; ++i) {
        Position wall;
        this->read_position(wall);
        walls.emplace_back(std::move(wall));
    }
    length_boxes_t boxes_length;
    this->read_two_byte_data(boxes_length);

    std::vector<Position> boxes;
    for (length_boxes_t i = 0; i < boxes_length; ++i) {
        Position box;
        this->read_position(box);
        boxes.emplace_back(std::move(box));
    }
    map_info.map_name = static_cast<MapName>(map_name);
    map_info.bomb_A = bomb_A;
    map_info.bomb_B = bomb_B;
    map_info.spawn_TT = spawn_TT;
    map_info.spawn_CT = spawn_CT;
    map_info.walls = std::move(walls);
    map_info.boxes = std::move(boxes);
}

GameInfo ClientProtocol::read_game_info() {
    MapInfo map_info;
    this->read_map_info(map_info);
    length_weapons_info_t weapons_length;
    this->read_byte_data(weapons_length);
    std::vector<WeaponInfo> weapons_purchasables;
    for (length_weapons_info_t i = 0; i < weapons_length; ++i) {
        weapon_code_t weapon_code;
        this->read_byte_data(weapon_code);

        uint16_t price;
        this->read_two_byte_data(price);

        weapons_purchasables.emplace_back(WeaponInfo(static_cast<WeaponCode>(weapon_code), price));
    }
    return GameInfo(std::move(map_info), std::move(weapons_purchasables));
}

std::vector<std::string> ClientProtocol::read_list_games() {
    length_games_list_t list_size;
    this->read_two_byte_data(list_size);

    std::vector<std::string> games_list;
    games_list.reserve(list_size);

    for (length_games_list_t i = 0; i < list_size; i++) {
        length_string_t name_length;
        this->read_two_byte_data(name_length);

        std::vector<char> buffer(name_length);
        this->socket.recvall(buffer.data(), name_length);

        if (this->socket.is_stream_recv_closed()) {
            throw ConnectionClosedException("Error al intentar recibir datos del servidor");
        }
        std::string game_name(buffer.data(), name_length);
        games_list.push_back(std::move(game_name));
    }
    return games_list;
}

void ClientProtocol::send_byte_data(const uint8_t& data) {
    this->socket.sendall(&data, sizeof(uint8_t));
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al servidor");
    }
}

void ClientProtocol::send_two_byte_data(const uint16_t& data) {
    uint16_t data_to_send = htons(data);
    this->socket.sendall(&data_to_send, sizeof(uint16_t));
    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar datos al servidor");
    }
}

void ClientProtocol::send_string(const std::string& string) {
    uint16_t length = static_cast<uint16_t>(string.size());
    this->send_two_byte_data(length);
    this->socket.sendall(string.c_str(), string.size());

    if (this->socket.is_stream_send_closed()) {
        throw ConnectionClosedException("Error al intentar enviar string al servidor");
    }
}

void ClientProtocol::send_lobby_command(LobbyCommandType command) {
    uint8_t command_byte = static_cast<uint8_t>(command);
    this->send_byte_data(command_byte);
}

void ClientProtocol::send_player_command(PlayerCommandType command) {
    uint8_t command_byte = static_cast<uint8_t>(command);
    this->send_byte_data(command_byte);
}

void ClientProtocol::send_create_game(const CreateGame& create_game) {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::CREATE_GAME);
    this->send_byte_data(header);

    std::string game_name = create_game.game_name;
    map_name_t map_name = static_cast<map_name_t>(create_game.map_name);
    skin_t tt_skin = static_cast<skin_t>(create_game.skins.tt_skin);
    skin_t ct_skin = static_cast<skin_t>(create_game.skins.ct_skin);
    this->send_string(game_name);
    this->send_byte_data(map_name);
    this->send_byte_data(ct_skin);
    this->send_byte_data(tt_skin);
}

void ClientProtocol::send_join_game(const JoinGame& join_game) {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::JOIN_GAME);
    this->send_byte_data(header);
    std::string game_name = join_game.game_name;
    skin_t tt_skin = static_cast<skin_t>(join_game.skins.tt_skin);
    skin_t ct_skin = static_cast<skin_t>(join_game.skins.ct_skin);
    this->send_string(game_name);
    this->send_byte_data(ct_skin);
    this->send_byte_data(tt_skin);
}

void ClientProtocol::send_list_games() {
    uint8_t header = static_cast<uint8_t>(LobbyCommandType::LIST_GAMES);
    this->send_byte_data(header);
}

void ClientProtocol::send_acknowledge(Acknowledge& ack) {
    uint8_t acknowledge_header = static_cast<uint8_t>(ack);
    this->send_byte_data(acknowledge_header);
}

void ClientProtocol::send_move(MoveType& move_type) {
    uint8_t move_command = static_cast<uint8_t>(PlayerCommandType::MOVE);
    uint8_t move_type_byte = static_cast<uint8_t>(move_type);
    this->send_byte_data(move_command);
    this->send_byte_data(move_type_byte);
}

void ClientProtocol::send_buy_weapon(WeaponCode& weapon_code) {
    player_command_t buy_weapon_header =
            static_cast<player_command_t>(PlayerCommandType::BUY_WEAPON);
    weapon_code_t weapon_code_command = static_cast<weapon_code_t>(weapon_code);
    this->send_byte_data(buy_weapon_header);
    this->send_byte_data(weapon_code_command);
}

void ClientProtocol::send_buy_ammo(WeaponType& weapon_type, ammo_t& ammo_count) {
    player_command_t buy_ammo_header = static_cast<player_command_t>(PlayerCommandType::BUY_AMMO);
    weapon_code_t weapon_code_command = static_cast<weapon_code_t>(weapon_type);
    ammo_t ammo_command = static_cast<ammo_t>(ammo_count);
    this->send_byte_data(buy_ammo_header);
    this->send_byte_data(weapon_code_command);
    this->send_two_byte_data(ammo_command);
}

void ClientProtocol::send_reload() {
    player_command_t reload_header = static_cast<player_command_t>(PlayerCommandType::RELOAD);
    this->send_byte_data(reload_header);
}

void ClientProtocol::send_common_shoot(player_command_t& shoot_command, const coordinate_t& mouse_x,
                                       const coordinate_t& mouse_y) {
    this->send_byte_data(shoot_command);
    this->send_two_byte_data(mouse_x);
    this->send_two_byte_data(mouse_y);
}

void ClientProtocol::send_shoot(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    player_command_t shoot_header = static_cast<player_command_t>(PlayerCommandType::SHOOT);
    this->send_common_shoot(shoot_header, mouse_x, mouse_y);
}

void ClientProtocol::send_shoot_burst(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    player_command_t shoot_burst_header =
            static_cast<player_command_t>(PlayerCommandType::SHOOT_BURST);
    this->send_common_shoot(shoot_burst_header, mouse_x, mouse_y);
}

void ClientProtocol::send_plant_bomb() {
    player_command_t plant_bomb_header =
            static_cast<player_command_t>(PlayerCommandType::PLANT_BOMB);
    this->send_byte_data(plant_bomb_header);
}

void ClientProtocol::send_defuse_bomb() {
    player_command_t defuse_bomb_header =
            static_cast<player_command_t>(PlayerCommandType::DEFUSE_BOMB);
    this->send_byte_data(defuse_bomb_header);
}

void ClientProtocol::send_drop() {
    player_command_t drop_header = static_cast<player_command_t>(PlayerCommandType::DROP);
    this->send_byte_data(drop_header);
}

void ClientProtocol::send_equip(EquipType& equip_type) {
    player_command_t equip_header = static_cast<player_command_t>(PlayerCommandType::EQUIP);
    equip_type_t equip_type_command = static_cast<equip_type_t>(equip_type);
    this->send_byte_data(equip_header);
    this->send_byte_data(equip_type_command);
}


void ClientProtocol::send_mouse_position(const coordinate_t& mouse_x, const coordinate_t& mouse_y) {
    player_command_t watch_header = static_cast<player_command_t>(PlayerCommandType::WATCH);
    this->send_byte_data(watch_header);
    this->send_two_byte_data(mouse_x);
    this->send_two_byte_data(mouse_y);
}

void ClientProtocol::read_byte_data(uint8_t& data) {
    uint8_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint8_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El servidor cerró la conexión");
    }
    data = data_readed;
}

void ClientProtocol::read_two_byte_data(uint16_t& data) {
    uint16_t data_readed;
    this->socket.recvall(&data_readed, sizeof(uint16_t));
    if (this->socket.is_stream_recv_closed()) {
        throw ConnectionClosedException("El servidor cerró la conexión");
    }
    data = ntohs(data_readed);
}

void ClientProtocol::read_client_id(player_id_t& player_id) {
    player_id_t id;
    this->read_two_byte_data(id);
    player_id = id;
}

void ClientProtocol::read_position(Position& position) {
    coordinate_t x, y;
    this->read_two_byte_data(x);
    this->read_two_byte_data(y);
    position.x = x;
    position.y = y;
}

void ClientProtocol::read_weapons(std::vector<WeaponImage>& weapons) {
    length_weapons_images_t length_weapons;
    this->read_byte_data(length_weapons);

    for (length_weapons_images_t i = 0; i < length_weapons; ++i) {
        weapon_code_t weapon_code;
        this->read_byte_data(weapon_code);

        uint8_t current_bullets;
        this->read_byte_data(current_bullets);

        uint8_t magazine;
        this->read_byte_data(magazine);

        weapons.emplace_back(
                WeaponImage(static_cast<WeaponCode>(weapon_code), current_bullets, magazine));
    }
}
void ClientProtocol::read_sound(sound_type_t& type, distance_sound_t& distance) {
    this->read_byte_data(type);
    this->read_two_byte_data(distance);
}
void ClientProtocol::read_shoot_sounds(std::vector<SoundShootImage>& sounds) {
    length_heared_sounds_t length_sounds;
    this->read_byte_data(length_sounds);
    for (length_heared_sounds_t i = 0; i < length_sounds; i++) {
        distance_sound_t distance;
        weapon_code_t code;
        this->read_two_byte_data(distance);
        this->read_byte_data(code);
        sounds.emplace_back(SoundShootImage(distance, static_cast<WeaponCode>(code)));
    }
}
void ClientProtocol::read_common_sounds(std::vector<SoundCommonImage>& sounds) {
    length_heared_sounds_t length_sounds;
    this->read_byte_data(length_sounds);
    for (length_heared_sounds_t i = 0; i < length_sounds; i++) {
        sound_type_t type;
        distance_sound_t distance;
        this->read_sound(type, distance);
        sounds.emplace_back(SoundCommonImage(static_cast<SoundType>(type), distance));
    }
}
void ClientProtocol::read_sound_image(SoundImage& sounds) {
    this->read_common_sounds(sounds.common_sounds);
    this->read_shoot_sounds(sounds.shoot_sounds);
}
void ClientProtocol::read_player_image(std::vector<PlayerImage>& players_images) {
    length_players_images_t length_players_images;
    this->read_two_byte_data(length_players_images);

    players_images.clear();
    players_images.reserve(length_players_images);

    for (auto i = 0; i < length_players_images; ++i) {
        player_id_t player_id;
        this->read_two_byte_data(player_id);

        Position position_player;
        this->read_position(position_player);

        health_t health;
        this->read_byte_data(health);
        deaths_t deaths;
        this->read_byte_data(deaths);

        deaths_t kills;
        this->read_byte_data(kills);
        points_t points;
        this->read_two_byte_data(points);

        money_t money;
        this->read_two_byte_data(money);
        money_t collected_money;
        this->read_two_byte_data(collected_money);
        weapon_code_t equipped_weapon_code;
        this->read_byte_data(equipped_weapon_code);

        std::vector<WeaponImage> weapons;
        this->read_weapons(weapons);

        SoundImage sounds;
        this->read_sound_image(sounds);

        team_t team_raw;
        this->read_byte_data(team_raw);
        Team team = static_cast<Team>(team_raw);

        Position position_mouse;
        this->read_position(position_mouse);

        skin_t ct_skin, tt_skin;
        this->read_byte_data(ct_skin);
        this->read_byte_data(tt_skin);

        CounterTerroristSkin ct = static_cast<CounterTerroristSkin>(ct_skin);
        TerroristSkin tt = static_cast<TerroristSkin>(tt_skin);
        Skins skins(ct, tt);

        players_images.emplace_back(
                PlayerImage(player_id, position_player, health, deaths, kills, points, money,
                            collected_money, static_cast<WeaponCode>(equipped_weapon_code),
                            std::move(weapons), team, position_mouse, skins, std::move(sounds)));
    }
}

void ClientProtocol::read_bullets_in_air(std::vector<BulletImage>& bullets_in_air) {
    length_bullets_in_air_t length_bullets;
    this->read_two_byte_data(length_bullets);

    bullets_in_air.clear();
    bullets_in_air.reserve(length_bullets);

    for (length_bullets_in_air_t i = 0; i < length_bullets; ++i) {
        Position initial, end;
        this->read_position(initial);
        this->read_position(end);
        uint8_t width;
        this->read_byte_data(width);
        weapon_code_t weapon_code;
        this->read_byte_data(weapon_code);
        bullets_in_air.emplace_back(
                BulletImage(initial, end, width, static_cast<WeaponCode>(weapon_code)));
    }
}

void ClientProtocol::read_bomb(BombImage& bomb_image) {
    weapon_code_t bomb_code;
    this->read_byte_data(bomb_code);
    bomb_image.weapon_code = static_cast<WeaponCode>(bomb_code);

    Position position;
    this->read_position(position);
    bomb_image.position = position;

    bomb_state_t bomb_state;
    this->read_byte_data(bomb_state);
    bomb_image.state = static_cast<BombState>(bomb_state);
}

void ClientProtocol::read_weapons_dropped(std::vector<WeaponDropped>& weapons_dropped) {
    length_weapons_dropped_t length;
    this->read_byte_data(length);

    weapons_dropped.clear();
    weapons_dropped.reserve(length);

    for (length_weapons_dropped_t i = 0; i < length; ++i) {
        weapon_code_t weapon_code;
        this->read_byte_data(weapon_code);

        Position position;
        this->read_position(position);

        weapons_dropped.emplace_back(WeaponDropped(static_cast<WeaponCode>(weapon_code), position));
    }
}

void ClientProtocol::read_game_state_image(GameStateImage& game_image) {
    game_state_t game_state_raw;
    this->read_byte_data(game_state_raw);
    game_image.state = static_cast<GameState>(game_state_raw);

    round_time_t time;
    this->read_two_byte_data(time);
    game_image.time = time;

    round_t round;
    this->read_byte_data(round);
    game_image.round = round;
}

GameImage ClientProtocol::read_game_image() {
    GameImage game_image;

    this->read_client_id(game_image.client_id);
    this->read_player_image(game_image.players_images);
    this->read_bullets_in_air(game_image.bullets_in_air);
    this->read_bomb(game_image.bomb);
    this->read_weapons_dropped(game_image.dropped_things);
    this->read_game_state_image(game_image.game_state);

    return game_image;
}
