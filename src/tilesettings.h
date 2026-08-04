#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "vars.h"
#include "tiletypes.h"
#include "players.h"
#include "sat(TESTING).h"

enum class tiletype {
    //Basic tile types
    empty,
    spawn,
    exit,
    ground,
    //Obstacles / non-player entities
    spike,
    doublespike,
    block_push,
    spring,
    blackhole,
    button,
    door,
    //Environments
    lava,
    water,
    zero_g
};

struct Tile {
    tiletype type;
    std::unique_ptr<tileTypes> tile;
};

//TILE CODES
// * = empty
// # = solid
// S = spawn point
// F = finish point
// 1 = single spike (same size as player) POINTED DOWN
// 2 = single spike POINTED LEFT 
// 3 = single spike POINTED UP
// 4 = single spike POINTED RIGHT
// 5 = double spike (two spikes right beside each other) POINTED DOWN
// 6 = double spike POINTED LEFT
// 7 = double spike POINTED UP
// 8 = double spike POINTED RIGHT
// 5 = 
// L = lava
// W = water
// Z = zero-g zone
// B = black hole
// P = pushable block
// ^ = spring
// O = button (looks like a circle so yeah)
// D = door

class tilemap {
public:
    std::vector<Tile> statictilelist;
    std::vector<Tile> dynamictilelist;
    sf::Vector2f spawn;
    sf::Vector2f finishpoint;

    void loadmap (std::string level) {
        int buttoncount = 0;
        int doorcount = 0;
        for (int i = 0; i < 36; i++) {
            for (int j = 0; j < 65; j++) {
                if (level[i*65+j] == '\n') {
                    continue;
                }
                char tilecode = level[i*65+j];
                Tile new_tile;
                switch (tilecode) {
                    case '*': 
                        new_tile.type = tiletype::empty;
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '#':
                        new_tile.type = tiletype::ground;
                        new_tile.tile = std::make_unique<ground_>(sf::Vector2f(j*playerdim, i*playerdim));
                        statictilelist.push_back(std::move(new_tile));
                        break;   
                    case 'S':
                        new_tile.type = tiletype::spawn;
                        spawn = sf::Vector2f(j*playerdim+(playerdim/2), i*playerdim+(playerdim/2));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case 'F':
                        new_tile.type = tiletype::exit;
                        new_tile.tile = std::make_unique<finish>(sf::Vector2f(j*playerdim, i*playerdim));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '1':
                        new_tile.type = tiletype::spike;
                        new_tile.tile = std::make_unique<spike>(sf::Vector2f(j*playerdim, i*playerdim));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '2':
                        new_tile.type = tiletype::spike;
                        new_tile.tile = std::make_unique<spike>(sf::Vector2f(j*playerdim, i*playerdim));
                        new_tile.tile -> collide().move(sf::Vector2f(20, 0));
                        new_tile.tile -> collide().rotate(sf::degrees(90));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '3':
                        new_tile.type = tiletype::spike;
                        new_tile.tile = std::make_unique<spike>(sf::Vector2f(j*playerdim, i*playerdim));
                        new_tile.tile -> collide().move(sf::Vector2f(20, 20));
                        new_tile.tile -> collide().rotate(sf::degrees(180));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '4':
                        new_tile.type = tiletype::spike;
                        new_tile.tile = std::make_unique<spike>(sf::Vector2f(j*playerdim, i*playerdim));
                        new_tile.tile -> collide().move(sf::Vector2f(0, 20));
                        new_tile.tile -> collide().rotate(sf::degrees(270));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '5':
                        new_tile.type = tiletype::doublespike;
                        new_tile.tile = std::make_unique<doublespike>(sf::Vector2f(j*playerdim, i*playerdim), 0);
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '6':
                        new_tile.type = tiletype::doublespike;
                        new_tile.tile = std::make_unique<doublespike>(sf::Vector2f(j*playerdim, i*playerdim), 90);
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '7':
                        new_tile.type = tiletype::doublespike;
                        new_tile.tile = std::make_unique<doublespike>(sf::Vector2f(j*playerdim, i*playerdim), 180);
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case '8':
                        new_tile.type = tiletype::doublespike;
                        new_tile.tile = std::make_unique<doublespike>(sf::Vector2f(j*playerdim, i*playerdim), 270);
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case 'L':
                        new_tile.type = tiletype::lava;
                        new_tile.tile = std::make_unique<lava>(sf::Vector2f(j*playerdim, i*playerdim));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case 'W':
                        new_tile.type = tiletype::water;
                        new_tile.tile = std::make_unique<water>(sf::Vector2f(j*playerdim,i*playerdim));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case 'Z':
                        new_tile.type = tiletype::zero_g;
                        new_tile.tile = std::make_unique<zero_g>(sf::Vector2f(j*playerdim,i*playerdim));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case 'B':
                        new_tile.type = tiletype::blackhole;
                        new_tile.tile = std::make_unique<blackhole>(sf::Vector2f(j*playerdim+5, i*playerdim+5));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case 'P':
                        new_tile.type = tiletype::block_push; //cuz i cant have two 'B' cases
                        new_tile.tile = std::make_unique<block>(sf::Vector2f(j*playerdim, i*playerdim));
                        dynamictilelist.push_back(std::move(new_tile));
                        break;
                    case '^':
                        new_tile.type = tiletype::spring;
                        new_tile.tile = std::make_unique<spring>(sf::Vector2f(j*playerdim, i*playerdim));
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case 'O':
                        new_tile.type = tiletype::button;
                        new_tile.tile = std::make_unique<button>(sf::Vector2f(j*playerdim, i*playerdim), buttoncount);
                        buttoncount++;
                        statictilelist.push_back(std::move(new_tile));
                        break;
                    case 'D':
                        new_tile.type = tiletype::door;
                        new_tile.tile = std::make_unique<door>(sf::Vector2f(j*playerdim, i*playerdim), doorcount);
                        doorcount++;
                        statictilelist.push_back(std::move(new_tile));
                        break;
                }
            }
        }
    }

    void satCollisionResp(std::vector<sf::Vector2f> verticesobj, std::vector<sf::Vector2f> verticestile, entity& Object) {
        player* player_ = dynamic_cast<player*>(&Object);
        block* block_ = dynamic_cast<block*>(&Object);
        sf::Vector2f mtv = sf::Vector2f(0, 0);
        mtvCheck(verticesobj, verticestile, mtv);
        Object.shape().move(mtv);
        if (std::abs(mtv.y) > std::abs(mtv.x)) {
            if (mtv.y < 0 && Object.velocity.y > 0) {
                Object.grounded = true;
                Object.velocity.y = 0;
                if (player_) landed = true;
                if (block_) block_ -> grounded = true;
            } else if (mtv.y > 0) {
                Object.velocity.y = 0;
            }
        } else if (std::abs(mtv.x) > std::abs(mtv.y)) {
            if (mtv.x > 0) {
                if (!walljumped) Object.velocity.x = 0;
                if (player_) wallhuggingleft = true;
            } else if (mtv.x < 0) {
                if (!walljumped) Object.velocity.x = 0;
                if (player_) wallhuggingright = true;
            }
        }
        if (!player_) Object.velocity.x = 0;
    }

    void checkCollisions (entity& Object) {
        
        //STATE VAR RESETS
        swimming = false;
        zerogactive = false;
        wallhuggingright = false;
        wallhuggingleft = false;
        landed = false; //PLACEHOLDER
        for (auto& pos: dynamictilelist) {
            block* block_ = dynamic_cast<block*>(pos.tile.get());
            block_ -> grounded = false;
        }

        //BUTTON + DOOR RESETS
        for (auto& pos: statictilelist) {
            if (pos.type == tiletype::button) {
                button* button_ = dynamic_cast<button*>(pos.tile.get());
                if (!button_) {
                    continue;
                } else {
                    button_ -> pressed = false;
                }
            }
            if (pos.type == tiletype::door) {
                door* door_ = dynamic_cast<door*>(pos.tile.get());
                if (!door_) {
                    continue;
                } else {
                    door_ -> opened = false;
                }
            }
        }

        //BUTTON CHECK
        for (auto& pos: statictilelist) {
            if (pos.type == tiletype::button) {
                button* button_ = dynamic_cast<button*>(pos.tile.get());
                if (!button_) continue;
                for (auto& other: dynamictilelist) {
                    if ((other.type == tiletype::block_push) && other.tile -> collide().getGlobalBounds().findIntersection(button_ -> collide().getGlobalBounds())) {
                        button_ -> pressed = true;
                        button_ -> presscheck = true;
                    }
                    if (Object.shape().getGlobalBounds().findIntersection(button_ -> collide().getGlobalBounds())) {
                        button_ -> pressed = true;
                        button_ -> presscheck = true;
                    }
                }
            }
        }

        //DOOR SAFETY CHECK
        //y'know how an elevator door doesn't close on your hand
        //yeah this is like that
        for (auto& pos: statictilelist) {
            if (pos.type != tiletype::button) continue;
            button* button_ = dynamic_cast<button*>(pos.tile.get());
            if (!button_ || !button_ -> presscheck) continue;

            bool occupied = false;
            for (auto& rest: statictilelist) {
                if (rest.type != tiletype::door) continue;
                door* door_ = dynamic_cast<door*>(rest.tile.get());
                if (!door_ || door_ -> id != button_ -> id) continue;
                if (Object.shape().getGlobalBounds().findIntersection(door_ -> collide().getGlobalBounds())) {
                    occupied = true;
                    break;
                }
                for (auto& others: dynamictilelist) {
                    if (others.type != tiletype::block_push) continue;
                    if (others.tile -> collide().getGlobalBounds().findIntersection(door_ -> collide().getGlobalBounds())) {
                        occupied = true;
                        break;
                    }
                }
                if (!occupied) {
                    door_ -> opened = false;
                    button_ -> presscheck = false;
                }
            }
        }

        //DOOR CHECK
        for (auto& pos: statictilelist) {
            if (pos.type != tiletype::button) continue;
            button* button_ = dynamic_cast<button*>(pos.tile.get());
            if (!button_ || (!button_ -> presscheck && !button_ -> pressed)) continue;

            for (auto& other: statictilelist) {
                if (other.type != tiletype::door) continue;
                door* door_ = dynamic_cast<door*>(other.tile.get());
                if (door_ && door_ -> id == button_ -> id) {
                    door_ -> opened = true;
                }
            }
        }

        //PLAYER ENV. DETECTION
        //need this since player collision checks happen after block checks but player-block pushing logic changes in zero g
        auto playerverts_ = getvertices(Object.shape());
        for (auto& pos: statictilelist) {
            if (!pos.tile || pos.type != tiletype::water && pos.type != tiletype::zero_g) continue;
            if (satCollide(playerverts_, getvertices(pos.tile -> collide()))) {
                if (pos.type == tiletype::water) swimming = true;
                if (pos.type == tiletype::zero_g) zerogactive = true;
            }
        }

        //BLOCK COLLISION
        for (auto& pos: dynamictilelist) {
            block* block_ = dynamic_cast<block*>(pos.tile.get());
            if (!block_) { continue; }
            block_ -> blockgravity = 1800;
            sf::FloatRect blockbounds = block_ -> collide().getGlobalBounds();
            auto blockvertices = getvertices(block_ -> collide());
            sf::FloatRect playerbounds = Object.shape().getGlobalBounds();
            auto playervertices = getvertices(Object.shape());

            //1. BLOCK + WORLD COLLISION
            for (auto& rest: statictilelist) {
                if (pos.tile != rest.tile && rest.type != tiletype::empty && rest.type != tiletype::spawn) {
                    sf::FloatRect restbounds = rest.tile -> collide().getGlobalBounds();
                    if (!blockbounds.findIntersection(restbounds)) { continue; }
                    else {
                        switch (rest.type) {
                            case tiletype::ground: {
                                auto verticesobj = getvertices(block_ -> collide());
                                ground_* G = dynamic_cast<ground_*>(rest.tile.get());
                                if (!G) continue;
                                auto verticestile = getvertices(G -> ground_block);
                                satCollisionResp(verticesobj, verticestile, *block_); 
                                break;
                            }
                            case tiletype::door: {
                                auto verticesobj = getvertices(block_ -> collide());
                                door* G = dynamic_cast<door*>(rest.tile.get());
                                if (!G || G->opened) continue;
                                auto verticestile = getvertices(G -> doorblock[0]);
                                satCollisionResp(verticesobj, verticestile, *block_); 
                                break;
                            }
                            case tiletype::zero_g:
                            block_ -> blockgravity = 0;
                            block_ -> velocity.y *= 0.87;
                            break;
                            case tiletype::water:
                            case tiletype::lava:
                            block_ -> blockgravity = 500;
                            break;
                            case tiletype::button: {
                            button* button_ = dynamic_cast<button*>(rest.tile.get());
                            if (button_) button_ -> pressed = true;
                            break; }
                            default:
                            break;
                        }
                    }
                }
            }
            for (auto& rest: dynamictilelist) {
                if (pos.tile == rest.tile) continue;
                block* G = dynamic_cast<block*>(rest.tile.get());
                if (!G) continue;
                sf::FloatRect blockbounds = pos.tile -> collide().getGlobalBounds();
                sf::FloatRect tilebounds = G -> collide().getGlobalBounds();
                if (!blockbounds.findIntersection(tilebounds)) continue;
                auto verticesobj = getvertices(block_ -> collide());
                auto verticestile = getvertices(G -> blockblock);
                //satCollisionResp(verticesobj, verticestile, *block_);
                satCollisionResp(verticestile, verticesobj, *G);
            }

            //2. BLOCK + PLAYER  LOGIC
            float playercentery = playerbounds.position.y + playerbounds.size.y / 2;
            float playercenterx = playerbounds.position.x + playerbounds.size.x / 2;
            float blocktop = blockbounds.position.y;
            float blockbottom = blockbounds.position.y + blockbounds.size.y;
            float blockleft = blockbounds.position.x;
            float blockright = blockbounds.position.x + blockbounds.size.x;
            if (satCollide(playervertices, blockvertices)) {
                if ((playercentery > blocktop && playercentery < blockbottom)) {
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && Object.shape().getPosition().x < blockbounds.position.x) {
                        sf::FloatRect obstaclecheck = sf::FloatRect(sf::Vector2f(blockright+0.01, blocktop + 0.5), sf::Vector2f(0.05, blockbounds.size.y-1));
                        bool obstacleright = false;
                        for (auto& rest: statictilelist) {
                            if (pos.tile == rest.tile || !rest.tile) continue;
                            if (rest.type == tiletype::ground || rest.type == tiletype::door) {
                                if (obstaclecheck.findIntersection(rest.tile -> collide().getGlobalBounds())) {
                                    obstacleright = true;
                                    break;
                                }
                            }
                        }
                        for (auto& rest: dynamictilelist) {
                            if (pos.tile == rest.tile || !rest.tile) continue;
                            if (rest.type == tiletype::block_push) {
                                if (obstaclecheck.findIntersection(rest.tile -> collide().getGlobalBounds())) {
                                    obstacleright = true;
                                    break;
                                }
                            }
                        }
                        if (!obstacleright) {
                            block_ -> velocity.x = pushspeed;
                            Object.velocity.x = pushspeed;
                            Object.grounded = false;
                        }
                    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && Object.shape().getPosition().x > blockbounds.position.x) {
                        sf::FloatRect obstaclecheck = sf::FloatRect(sf::Vector2f(blockleft-0.06, blocktop + 0.5), sf::Vector2f(0.05, blockbounds.size.y - 1));
                        bool obstacleleft = false;
                        for (auto& rest: statictilelist) {
                            if (pos.tile == rest.tile || !rest.tile) continue;
                            if (rest.type == tiletype::ground || rest.type == tiletype::door) {
                                if (obstaclecheck.findIntersection(rest.tile -> collide().getGlobalBounds())) {
                                    obstacleleft = true;
                                    break;
                                }
                            }
                        }
                        for (auto& rest: dynamictilelist) {
                            if (pos.tile == rest.tile || !rest.tile) continue;
                            if (rest.type == tiletype::block_push) {
                                if (obstaclecheck.findIntersection(rest.tile -> collide().getGlobalBounds())) {
                                    obstacleleft = true;
                                    break;
                                }
                            }
                        }
                        if (!obstacleleft) {
                            block_ -> velocity.x = -pushspeed;
                            Object.velocity.x = -pushspeed;
                            Object.grounded = false;   
                        }
                    }
                }

                if ((playercenterx > blockleft && playercenterx < blockright)) {
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && Object.shape().getPosition().y < blockbounds.position.y) {
                        sf::FloatRect obstaclecheck = sf::FloatRect(sf::Vector2f(blockleft + 0.5, blockbottom + 0.05), sf::Vector2f(blockbounds.size.x - 1, 0.05));
                        bool obstaclebelow = false;
                        for (auto& rest: statictilelist) {
                            if (pos.tile == rest.tile || !rest.tile) continue;
                            if (rest.type == tiletype::ground || rest.type == tiletype::door) {
                                if (obstaclecheck.findIntersection(rest.tile -> collide().getGlobalBounds())) {
                                    obstaclebelow = true;
                                    break;
                                }
                            }
                        }
                        for (auto& rest: dynamictilelist) {
                            if (pos.tile == rest.tile || !rest.tile) continue;
                            if (rest.type == tiletype::block_push) {
                                if (obstaclecheck.findIntersection(rest.tile -> collide().getGlobalBounds())) {
                                    obstaclebelow = true;
                                    break;
                                }
                            }
                        }
                        if (!obstaclebelow) {
                            block_ -> velocity.y = pushspeed;
                            Object.velocity.y = pushspeed;
                            Object.grounded = false;
                        }
                        else {
                            if (Object.velocity.y < 0) Object.velocity.y = 0;
                        }
                    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && Object.shape().getPosition().y > blockbounds.position.y && zerogactive) {
                        sf::FloatRect obstaclecheck = sf::FloatRect(sf::Vector2f(blockleft + 0.5, blocktop - 0.07), sf::Vector2f(blockbounds.size.x - 1, 0.07));
                        bool obstacletop = false;
                        for (auto& rest: statictilelist) {
                            if (pos.tile == rest.tile || !rest.tile) continue;
                            if (rest.type == tiletype::ground || rest.type == tiletype::door) {
                                if (obstaclecheck.findIntersection(rest.tile -> collide().getGlobalBounds())) {
                                    obstacletop = true;
                                    break;
                                }
                            }
                        }
                        for (auto& rest: dynamictilelist) {
                            if (pos.tile == rest.tile || !rest.tile) continue;
                            if (rest.type == tiletype::block_push) {
                                if (obstaclecheck.findIntersection(rest.tile -> collide().getGlobalBounds())) {
                                    obstacletop = true;
                                    break;
                                }
                            }
                        }
                        if (!obstacletop) {
                            block_ -> velocity.y = -pushspeed;
                            Object.velocity.y = -pushspeed;
                            Object.grounded = false;   
                        } 
                    }
                }
            }
            if ((playercenterx > blockleft && playercenterx < blockright) && Object.shape().getPosition().y - 10 > block_ -> blockblock.getPosition().y) { blockonhead = true; }
        }

        //PLAYER COLLISION
        for (auto& pos: statictilelist) {
            if (pos.type == tiletype::empty || pos.type == tiletype::spawn || !Object.shape().getGlobalBounds().findIntersection(pos.tile -> collide().getGlobalBounds())) { continue; }
            auto playerbounds = getvertices(Object.shape());
            std::vector<sf::Vector2f> tilebounds;
            if (pos.type == tiletype::door) {
                door* G = dynamic_cast<door*>(pos.tile.get());
                if (!G || G->opened) continue;
                tilebounds = getvertices(G->doorblock[0]);
            } else tilebounds = getvertices(pos.tile -> collide());

            if (!satCollide(playerbounds, tilebounds)) { continue; }
            else {
                switch (pos.type) {
                    case tiletype::empty:
                    break;
                    case tiletype::ground: {
                        auto verticesobj = getvertices(Object.shape());
                        ground_* G = dynamic_cast<ground_*>(pos.tile.get());
                        if (!G) continue;
                        auto verticestile = getvertices(G -> ground_block);
                        satCollisionResp(verticesobj, verticestile, Object);
                    }
                    break;
                    case tiletype::door: {
                        auto verticesobj = getvertices(Object.shape());
                        door* G = dynamic_cast<door*>(pos.tile.get());
                        if (!G) continue;
                        auto verticestile = getvertices(G -> doorblock[0]);
                        satCollisionResp(verticesobj, verticestile, Object);
                    }
                    break;
                    case tiletype::spike:
                    case tiletype::lava:
                    case tiletype::blackhole:
                    restart = true;
                    break;
                    case tiletype::doublespike: {
                        doublespike* G = dynamic_cast<doublespike*>(pos.tile.get());
                        auto spikevertices = getvertices(G->collide());
                        if (G && satCollide(getvertices(Object.shape()), spikevertices)) restart = true;
                        auto spikevertices2 = getvertices(G->getspike2());
                        if (G && satCollide(getvertices(Object.shape()), spikevertices2)) restart = true;
                        break;
                    }
                    case tiletype::exit:
                    newlevel = true;
                    break;
                    case tiletype::water:
                    swimming = true;
                    break;
                    case tiletype::zero_g:
                    zerogactive = true;
                    break;
                    case tiletype::spring:
                    Object.velocity.y = -1000.f;
                    walljumpcancel = true;
                    jumpcount = 1;
                    break;
                    case tiletype::button: {
                    button* button_ = dynamic_cast<button*>(pos.tile.get());
                    if (button_) button_ -> pressed = true;
                    break; }
                    default: 
                    break;
                }
            }
        }
        for (auto& pos: dynamictilelist) {
            block* block_ = dynamic_cast<block*>(pos.tile.get());
            if (!block_) continue;
            auto playerbounds = getvertices(Object.shape());
            auto tilebounds = getvertices(block_ -> blockblock);
            if (!satCollide(playerbounds, tilebounds)) { continue; }
            sf::Vector2f mtv = sf::Vector2f(0, 0);
            mtvCheck(playerbounds, tilebounds, mtv);
            if (std::abs(mtv.y) > std::abs(mtv.x) && mtv.y > 0) {
                block_ -> velocity.y = 0;
                block_ -> grounded = true;
                block_ -> blockblock.move(sf::Vector2f(0, -mtv.y));
            } else {
                satCollisionResp(playerbounds, tilebounds, Object);
            }
        }
    }

    bool predictCollision(sf::Shape& shape, sf::Vector2f transform) {
        auto shapevertices = getvertices(shape);
        for (auto& pos: shapevertices) {
            pos.x += transform.x;
            pos.y += transform.y;
        }

        for (auto& pos: statictilelist) {
            if ((pos.type == tiletype::ground || pos.type == tiletype::door)) {
                sf::Shape& tile = pos.tile -> collide();
                door* G = dynamic_cast<door*>(pos.tile.get());
                std::vector<sf::Vector2f> tilevertices;
                if (pos.type == tiletype::door) {
                    if (!G || G -> opened) continue;
                } 
                tilevertices = getvertices(tile);
                if (satCollide(shapevertices, tilevertices)) {
                    return true;
                }
            }
        }
        for (auto& pos: dynamictilelist) {
            sf::Shape& tile = pos.tile -> collide();
            std::vector<sf::Vector2f> tilevertices = getvertices(tile);
            if (satCollide(shapevertices, tilevertices)) {
                return true;
            }
        }
        return false;
    }

    bool cliffCheck (sf::Vector2f vertex) {
        sf::FloatRect groundpoint = sf::FloatRect(sf::Vector2f(vertex.x - 1, vertex.y), sf::Vector2f(2.f, 2.f));
        for (auto& pos: statictilelist) {
            if (pos.type == tiletype::ground || pos.type == tiletype::door) {
                sf::FloatRect groundbounds = pos.tile -> collide().getGlobalBounds();
                if (groundpoint.findIntersection(groundbounds)) return true;
            }
        }
        for (auto& pos: dynamictilelist) {
            sf::FloatRect groundbounds = pos.tile -> collide().getGlobalBounds();
            if (groundpoint.findIntersection(groundbounds)) return true;
        }
        return false;
    }

    void updatemap (float deltatime) {
        for (auto& pos: dynamictilelist) {
            pos.tile -> movetile(deltatime);
        }
    }

    void drawmap (sf::RenderWindow& window) {
        for (auto& pos: dynamictilelist) {
            pos.tile -> draw(window);
        }
        for (auto& pos: statictilelist) {
            if (pos.type != tiletype::empty && pos.type != tiletype::spawn) {
                pos.tile -> draw(window);
            }
        }
    }
};