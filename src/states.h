#pragma once

#include <SFML/Graphics.hpp>
#include "vars.h"
#include "scenes.h"

#include <string>

enum class State {
    mainmenu,
    playing,
    pause,
    levelselect
};

inline State state = State::mainmenu;