#ifndef COLLISION_MANAGER_H_
#define COLLISION_MANAGER_H_
#include <algorithm>
#include <map>
#include <memory>
#include <random>
#include <utility>
#include <vector>

#include "../../../common/game_image.h"
#include "../../../common/utility.h"
#include "../Colliders/Colliders.h"
#include "../Player/ICanInteract.h"
#include "../Weapons/IInteractuable.h"
#include "../Weapons/SpecialWeapons.h"

typedef struct PlayerEntity {
    std::weak_ptr<ICanInteract> player;
    Position position;
} player_entity_t;

typedef struct ColliderDamage {
    std::unique_ptr<Collider> collider;
    std::function<uint8_t(float)> damage_calculator;
    // Aca puede estar la probabilidad de daño
} collider_damage_t;

class CollisionManager {
    std::vector<Position>& collision_pos;
    std::map<player_id_t, player_entity_t>& players_in_map;
    std::vector<std::pair<player_id_t, ColliderDamage>> damages_collider;
    std::pair<Position, std::shared_ptr<Bomb>>& bomb;
    std::map<Position, std::shared_ptr<IInteractuable>> dropped_things;
    std::vector<BulletImage> bullets_image;
    void add_bullet_image(const Vector2f& initial_pos, const Vector2f& final_pos);
    Position get_hit_pos(Position& initial, Position& end);
    void check_damage_players(player_id_t caster, ColliderDamage& collider_damage,
                              std::vector<PlayerEntity>& players_affected);
    bool check_bullet_wall(const Vector2f& initial_pos, const Vector2f& final_pos);
    void check_weapon_stepped(PlayerEntity& player);
    void check_damage_collider(player_id_t caster, ColliderDamage& collider);
    void check_bomb_stepped(PlayerEntity& player);

public:
    explicit CollisionManager(std::vector<Position>& collision_pos,
                              std::map<player_id_t, player_entity_t>& players_in_map,
                              std::pair<Position, std::shared_ptr<Bomb>>& bomb):
            collision_pos(collision_pos), players_in_map(players_in_map), bomb(bomb) {}
    bool check_movement(player_id_t id, const Position& next_position);
    void check_damage();
    bool is_a_wall(coordinate_t x, coordinate_t y);
    void drop(Position& player_position, std::shared_ptr<IInteractuable>& dropable);
    void add_damage_collider(player_id_t id, ColliderDamage& collider_damage);
    void reset_dropped_things() { dropped_things.clear(); }
    std::vector<WeaponDropped> get_dropped_things_images();
    std::vector<BulletImage> get_bullets_image();
};

#endif  // COLLISION_MANAGER_H_
