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

//class player;

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
// 1 = single spike (same size as player)
// 2 = double spike (two spikes right beside each other)"
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
    std::vector<Tile> tilelist;
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
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case '#':
                        new_tile.type = tiletype::ground;
                        new_tile.tile = std::make_unique<ground_>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;   
                    case 'S':
                        new_tile.type = tiletype::spawn;
                        spawn = sf::Vector2f(j*playerdim, i*playerdim);
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'F':
                        new_tile.type = tiletype::exit;
                        finishpoint = sf::Vector2f(i*playerdim, j*playerdim);
                        new_tile.tile = std::make_unique<finish>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case '1':
                        new_tile.type = tiletype::spike;
                        new_tile.tile = std::make_unique<spike>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case '2':
                        new_tile.type = tiletype::doublespike;
                        new_tile.tile = std::make_unique<doublespike>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'L':
                        new_tile.type = tiletype::lava;
                        new_tile.tile = std::make_unique<lava>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'W':
                        new_tile.type = tiletype::water;
                        new_tile.tile = std::make_unique<water>(sf::Vector2f(j*playerdim,i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'Z':
                        new_tile.type = tiletype::zero_g;
                        new_tile.tile = std::make_unique<zero_g>(sf::Vector2f(j*playerdim,i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'B':
                        new_tile.type = tiletype::blackhole;
                        new_tile.tile = std::make_unique<blackhole>(sf::Vector2f(j*playerdim+5, i*playerdim+5));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'P':
                        new_tile.type = tiletype::block_push; //cuz i cant have two 'B' cases
                        new_tile.tile = std::make_unique<block>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case '^':
                        new_tile.type = tiletype::spring;
                        new_tile.tile = std::make_unique<spring>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'O':
                        new_tile.type = tiletype::button;
                        new_tile.tile = std::make_unique<button>(sf::Vector2f(j*playerdim, i*playerdim), buttoncount);
                        buttoncount++;
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'D':
                        new_tile.type = tiletype::door;
                        new_tile.tile = std::make_unique<door>(sf::Vector2f(j*playerdim, i*playerdim), doorcount);
                        doorcount++;
                        tilelist.push_back(std::move(new_tile));
                        break;
                }
            }
        }
    }

    void satCollisionResp(std::vector<sf::Vector2f> verticesobj, std::vector<sf::Vector2f> verticestile, entity& Object) {
        sf::Vector2f mtv = sf::Vector2f(0, 0);
        mtvCheck(verticesobj, verticestile, mtv);
        Object.shape().move(mtv);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) std::cout << mtv.x << "," << mtv.y << "\n";
        if (std::abs(mtv.y) > std::abs(mtv.x)) {
            if (mtv.y < 0 && Object.velocity.y > 0) {
                Object.grounded = true;
                Object.velocity.y = 0;
                landed = true;
            } else if (mtv.y > 0) {
                if (Object.velocity.y < 0) Object.velocity.y = 0;
            }
        } else if (std::abs(mtv.x) > std::abs(mtv.y)) {
            if (mtv.x > 0) {
                if (!walljumped) Object.velocity.x = 0;
                wallhuggingleft = true;
                if (Object.velocity.x < 0) Object.velocity.x = 0;
            } else if (mtv.x < 0) {
                if (!walljumped) Object.velocity.x = 0;
                wallhuggingright = true;
                if (Object.velocity.x > 0) Object.velocity.x = 0;
            }
        }
    }

    void checkCollisions (entity& Object) {
        swimming = false;
        zerogactive = false;
        wallhuggingright = false;
        wallhuggingleft = false;
        landed = false; //PLACEHOLDER


        //BUTTON + DOOR RESETS
        for (auto& pos: tilelist) {
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
        for (auto& pos: tilelist) {
            if (pos.type == tiletype::button) {
                button* button_ = dynamic_cast<button*>(pos.tile.get());
                if (!button_) continue;
                for (auto& other: tilelist) {
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
        for (auto& pos: tilelist) {
            if (pos.type != tiletype::button) continue;
            button* button_ = dynamic_cast<button*>(pos.tile.get());
            if (!button_ || !button_ -> presscheck) continue;

            bool occupied = false;
            for (auto& rest: tilelist) {
                if (rest.type != tiletype::door) continue;
                door* door_ = dynamic_cast<door*>(rest.tile.get());
                if (!door_ || door_ -> id != button_ -> id) continue;
                if (Object.shape().getGlobalBounds().findIntersection(door_ -> collide().getGlobalBounds())) {
                    occupied = true;
                    break;
                }
                for (auto& others: tilelist) {
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
        for (auto& pos: tilelist) {
            if (pos.type != tiletype::button) continue;
            button* button_ = dynamic_cast<button*>(pos.tile.get());
            if (!button_ || (!button_ -> presscheck && !button_ -> pressed)) continue;

            for (auto& other: tilelist) {
                if (other.type != tiletype::door) continue;
                door* door_ = dynamic_cast<door*>(other.tile.get());
                if (door_ && door_ -> id == button_ -> id) {
                    door_ -> opened = true;
                }
            }
        }

        //BLOCK COLLISION
        for (auto& pos: tilelist) {
            //1. BLOCK + PLAYER PUSH LOGIC
            if (pos.type != tiletype::block_push) { continue; }

            block* block_ = dynamic_cast<block*>(pos.tile.get());
            if (!block_) { continue; }
            block_ -> blockgravity = 1800;

            sf::FloatRect blockbounds = block_ -> collide().getGlobalBounds();
            auto blockvertices = getvertices(block_ -> collide());
            sf::FloatRect playerbounds = Object.shape().getGlobalBounds();
            auto playervertices = getvertices(Object.shape());
            if (satCollide(playervertices, blockvertices)) {
                float playercentery = playerbounds.position.y + playerbounds.size.y / 2;
                float playercenterx = playerbounds.position.x + playerbounds.size.x / 2;
                float blocktop = blockbounds.position.y;
                float blockbottom = blockbounds.position.y + blockbounds.size.y;
                float blockleft = blockbounds.position.x;
                float blockright = blockbounds.position.x + blockbounds.size.x;
                if ((playercentery > blocktop && playercentery < blockbottom)) {
                    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && Object.shape().getPosition().x < blockbounds.position.x) {
                        block_ -> velocity.x = trianglepushspeed;
                        Object.velocity.x = trianglepushspeed;
                        Object.grounded = false;
                    } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && Object.shape().getPosition().x > blockbounds.position.x) {
                        block_ -> velocity.x = -trianglepushspeed;
                        Object.velocity.x = -trianglepushspeed;
                        Object.grounded = false;
                    }
                }
                if ((playercenterx > blockleft && playercenterx < blockright)) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && Object.grounded) {
                        block_ -> velocity.y = trianglepushspeed;
                        Object.velocity.y = trianglepushspeed;
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && Object.grounded) {
                        block_ -> velocity.y = -trianglepushspeed;
                        Object.velocity.y = -trianglepushspeed;
                    }
                }
                //this was all claude
                float blockBottom = blockbounds.position.y + blockbounds.size.y;
                float playerTop = playerbounds.position.y;
                float overlapY = blockBottom - playerTop;

                float blockLeft  = blockbounds.position.x;
                float blockRight = blockbounds.position.x + blockbounds.size.x;
                float playerLeft  = playerbounds.position.x;
                float playerRight = playerbounds.position.x + playerbounds.size.x;
                float overlapX = std::min(blockRight, playerRight) - std::max(blockLeft, playerLeft);

                if (overlapY > 0 && overlapY < overlapX && block_ -> velocity.y >= 0) {
                    block_ -> shape().setPosition(sf::Vector2f(block_ -> shape().getPosition().x, playerTop - blockbounds.size.y));
                    block_ -> velocity.y = 0;
                    blockbounds = block_ -> collide().getGlobalBounds();
                }
                //k no more claude
            }
            //2. BLOCK + WORLD COLLISION
            for (auto& rest: tilelist) {
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
                                if (!G) continue;
                                auto verticestile = getvertices(G -> doorblock[0]);
                                satCollisionResp(verticesobj, verticestile, *block_); 
                                break;
                            }                   
                            case tiletype::block_push: {
                            block_ -> velocity.x = 0;
                            //technically not just pasted from claude, but I used its code as inspiration
                            float blockleft  = blockbounds.position.x;
                            float blockright = blockbounds.position.x + blockbounds.size.x;
                            float restleft   = restbounds.position.x;
                            float restright  = restbounds.position.x + restbounds.size.x;
                            float overlapx = std::min(blockright, restright) - std::max(blockleft, restleft);
                            if ((blockbounds.position.y + blockbounds.size.y) - restbounds.position.y > 0 && (blockbounds.position.y + blockbounds.size.y) - restbounds.position.y < overlapx) {
                                block_ -> shape().setPosition(sf::Vector2f(block_ -> shape().getPosition().x, restbounds.position.y - blockbounds.size.y));
                                block_ -> velocity.y = 0;
                                blockbounds = block_ -> collide().getGlobalBounds();
                            }
                            break; }
                            case tiletype::zero_g:
                            block_ -> blockgravity = 0;
                            block_ -> velocity.y *= 0.96;
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
        }

        //PLAYER COLLISION
        for (auto& pos: tilelist) {
            if (pos.type == tiletype::empty || pos.type == tiletype::spawn || !Object.shape().getGlobalBounds().findIntersection(pos.tile -> collide().getGlobalBounds())) { continue; }
            auto playerbounds = getvertices(Object.shape());
            auto tilebounds = getvertices(pos.tile -> collide());

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
                    case tiletype::block_push: {
                        auto verticesobj = getvertices(Object.shape());
                        block* G = dynamic_cast<block*>(pos.tile.get());
                        if (!G) continue;
                        auto verticestile = getvertices(G -> blockblock);
                        satCollisionResp(verticesobj, verticestile, Object);
                    }
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
    }

    void groundCollide(entity& Object, sf::FloatRect& bounds) {
        float topside1 = Object.shape().getPosition().y;
        float leftside1 = Object.shape().getPosition().x;
        float rightside1 = Object.shape().getPosition().x + Object.shape().getGlobalBounds().size.x;
        float bottomside1 = Object.shape().getPosition().y + Object.shape().getGlobalBounds().size.y;

        float topside2 = bounds.position.y;
        float leftside2 = bounds.position.x;
        float rightside2 = bounds.position.x + bounds.size.x;
        float bottomside2 = bounds.position.y + bounds.size.y;

        float topovlp = bottomside2-topside1; //hit from below i.e. knocking on the roof
        float bottomovlp = bottomside1-topside2; //hit from above i.e. landing
        float leftovlp = rightside2-leftside1; //hit on left side
        float rightovlp = rightside1-leftside2; //right hit
        
        //any comments here are for my own sake
        float lowestoverlap = std::min({topovlp, bottomovlp, leftovlp, rightovlp});

        if (topside1 < bottomside2 && bottomside1 > topside2 && leftside1 < rightside2 && rightside1 > leftside2) {
            if (lowestoverlap == topovlp) {
                Object.shape().setPosition(sf::Vector2f(Object.shape().getPosition().x, bottomside2));
                Object.velocity.y = 0;
            } else if (lowestoverlap == bottomovlp) {
                Object.shape().setPosition(sf::Vector2f(Object.shape().getPosition().x, topside2-Object.shape().getGlobalBounds().size.y));
                Object.velocity.y = 0;
                Object.grounded = true;
            } else if (lowestoverlap == rightovlp) {
                Object.shape().setPosition(sf::Vector2f(leftside2-Object.shape().getGlobalBounds().size.x, Object.shape().getPosition().y));
                wallhuggingright = true;
            } else if (lowestoverlap == leftovlp) {
                Object.shape().setPosition(sf::Vector2f(rightside2, Object.shape().getPosition().y));
                wallhuggingleft = true;
            }
        }
    }

    bool predictCollision(sf::Shape& shape, sf::Vector2f transform) {
        auto shapevertices = getvertices(shape);
        for (auto& pos: shapevertices) {
            pos.x += transform.x;
            pos.y += transform.y;
        }

        for (auto& pos: tilelist) {
            if ((pos.type == tiletype::ground || pos.type == tiletype::block_push || pos.type == tiletype::door)) {
                sf::Shape& tile = pos.tile -> collide();
                auto tilevertices = getvertices(tile);
                if (satCollide(shapevertices, tilevertices)) {
                    return true;
                }
            }
        }
        return false;
    }

    void updatemap (float deltatime) {
        for (auto& pos: tilelist) {
            if (pos.type != tiletype::empty && pos.type != tiletype::spawn) {
                pos.tile -> movetile(deltatime);
            }
        }
    }

    void drawmap (sf::RenderWindow& window) {
        for (auto& pos: tilelist) {
            if (pos.type != tiletype::empty && pos.type != tiletype::spawn) {
                pos.tile -> draw(window);
            }
        }
    }
};