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
#include "../Sounds/SoundManager.h"
#include "../Sounds/SoundShoot.h"
#include "../Weapons/IInteractuable.h"
#include "../Weapons/SpecialWeapons.h"
typedef struct PlayerEntity {
    std::weak_ptr<ICanInteract> player;
    Position position;
} player_entity_t;

typedef struct ColliderDamage {
    std::unique_ptr<Collider> collider;
    std::function<damage_t(float)> damage_calculator;
    width_t width;
    chance_hit_t chance_hit;
    WeaponCode code;
} collider_damage_t;


class CollisionManager {
    std::vector<Position>& collision_pos;
    std::map<player_id_t, player_entity_t>& players_in_map;
    std::vector<std::pair<player_id_t, ColliderDamage>> damages_collider;
    std::pair<Position, std::shared_ptr<Bomb>>& bomb;
    std::map<Position, std::shared_ptr<IInteractuable>> dropped_things;
    std::vector<BulletImage> bullets_image;
    SoundManager& sound_manager;
    bool player_in(const Position& pos);
    bool hit(const chance_hit_t chance_hit);
    void add_bullet_image(const Vector2f& initial_pos, const Vector2f& final_pos,
                          const ColliderDamage& collider_info);
    Position get_hit_pos(Position& initial, Position& end);
    void find_nearest(const std::vector<PlayerEntity>& players_affected, const Vector2f& origin,
                      PlayerEntity& nearest, Vector2f& pos_nearest, float& min_distance);
    void find_players_in(player_id_t caster, ColliderDamage& collider_damage,
                         std::vector<PlayerEntity>& players_affected);
    void damage_nearest(PlayerEntity& nearest, PlayerEntity& caster, damage_t damage,
                        chance_hit_t chance_hit);
    bool check_bullet_wall(const Vector2f& initial_pos, const Vector2f& final_pos,
                           const ColliderDamage& collider_info);
    void check_weapon_stepped(PlayerEntity& player);

    void check_damage_collider(player_id_t caster, ColliderDamage& collider);
    void check_bomb_stepped(PlayerEntity& player);

public:
    explicit CollisionManager(std::vector<Position>& collision_pos,
                              std::map<player_id_t, player_entity_t>& players_in_map,
                              std::pair<Position, std::shared_ptr<Bomb>>& bomb,
                              SoundManager& sound_manager):
            collision_pos(collision_pos),
            players_in_map(players_in_map),
            bomb(bomb),
            sound_manager(sound_manager) {}
    bool check_movement(player_id_t id, const Position& next_position);
    void check_damage();
    bool is_a_collision(const Position& pos);
    void drop(Position& player_position, std::shared_ptr<IInteractuable>& dropable);
    void add_damage_collider(player_id_t id, ColliderDamage& collider_damage);
    void reset_dropped_things() { dropped_things.clear(); }
    std::vector<WeaponDropped> get_dropped_things_images();
    std::vector<BulletImage> get_bullets_image();
};

#endif  // COLLISION_MANAGER_H_
