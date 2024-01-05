#pragma once
#include <string>
#include <array>

namespace GameConfig
{
    inline const std::string WINDOW_NAME = "Battle City";
    inline const int SCREEN_WIDTH = 1024;
    inline const int SCREEN_HEIGHT = 1024;
    inline const int FRAME_LIMIT = 60;
    inline const std::string FONT_PATH = "sfml_assets/fonts/joystix monospace.ttf";
    inline const std::string TILES_TEXTURE_PATH = "sfml_assets/textures/tileset.png";
    inline const std::string BULLET_TEXTURE_PATH = "sfml_assets/textures/bullet.png";
    inline const std::string EAGLE_TEXTURE_PATH = "sfml_assets/textures/eagle.png";
    inline const std::string MAP_FILE_PATH = "core_assets/maps/map.txt";
    inline const std::string TANK_TEXTURE_PATH = "sfml_assets/textures/tank.png";
    inline const std::array<std::string, 3> OPTIONS = { "1 player", "2 players", "Exit" };

    const uint32_t MAP_TILE_SIZE = 64;
    constexpr int INITIAL_TANK_POS_X = 256;
    constexpr int INITIAL_TANK_POS_Y = 256;

    constexpr int TANK_SPEED = 3;
    constexpr float BULLET_SPEED = 10;

    enum class MoveDirection {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
}