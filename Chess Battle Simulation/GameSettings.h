#pragma once
#include "SFML/Graphics.hpp"
#include "Model.h"
#include "Node.h"
using namespace sf;
class GameSettings
{
public:
    static int VOLUME;
    static int FPS;
    static int POOLSIZE;
    static int POOLSEED;
    static int RESOLUTION;
    static int PLAYER_HEALTH;
    static int PLAYER_MONEY;
    static int CPU_HEALTH;
    static int CPU_MONEY;
    static bool DAMAGE_ENABLE;
    static int AVAILABLE_ID;
    static Vector2f MAP[8][8];
    static Node MOVEMENT_MAP[8][8];
    static FloatRect MAP_BOUNDS;
    static Vector2f SUBMAP[8];
    static FloatRect SUB_BOUNDS;
    static Model MODELS[6];
};