#ifndef CONFIG_HPP
#define CONFIG_HPP

#pragma once
#include <vector>

#define SCREEN_WIDTH 1120
#define SCREEN_HEIGHT 800

#define SCREEN_CENTER_WIDTH SCREEN_WIDTH/2
#define SCREEN_CENTER_HEIGHT SCREEN_HEIGHT/2

#define FPS 60
#define FRAME_DELAY 1000/FPS
#define SPEED 100

#define MAX_NUM_OF_PLAYERS 3

#define GROUP_MAP 0
#define GROUP_LINE 1
#define GROUP_PLAYER1 2
#define GROUP_PLAYER2 3
#define GROUP_BALL 4



#define BALL_TEXTURE_FILE_PATH "../assets/image/ball.png"

// Map
#define MAP_WIDTH 35  //  1120/32
#define MAP_HEIGHT 37 //  800/32

// Grass Tile
#define GRASS_TILE_FILE_PATH "../assets/image/Tiles/grass.png"
#define GRASS_TILE_WIDTH_HEIGHT 16
#define GRASS_TILE_WIDTH_HEIGHT_2_DRAW 64

// Line
#define LINE_TEXTURE_FILE_PATH "../assets/image/Tiles/line.png"
#define LINE_H_TEXTURE_FILE_PATH "../assets/image/Tiles/line-horizontal.png"
#define LINE1_TEXTURE_FILE_PATH "../assets/image/Tiles/line1.png"
#define LINE2_TEXTURE_FILE_PATH "../assets/image/Tiles/line2.png"

// ARGENTINA
#define ARGENTINA_WALK "../assets/image/Free_Assets/Footballers/Argentina/walk.png"
#define ARGENTINA_IDLE "../assets/image/Free_Assets/Footballers/Argentina/idle.png"
#define ARGENTINA_FRONT "../assets/image/Free_Assets/Footballers/Argentina/front.png"
#define ARGENTINA_BACK "../assets/image/Free_Assets/Footballers/Argentina/back.png"

// BOCAJUNIORS
#define BOCAJUNIORS_WALK "../assets/image/Free_Assets/Footballers/BocaJuniors/walk.png"
#define BOCAJUNIORS_IDLE "../assets/image/Free_Assets/Footballers/BocaJuniors/idle.png"
#define BOCAJUNIORS_FRONT "../assets/image/Free_Assets/Footballers/BocaJuniors/front.png"
#define BOCAJUNIORS_BACK "../assets/image/Free_Assets/Footballers/BocaJuniors/back.png"

// INDEPENDIENTE
#define INDEPENDIENTE_WALK "../assets/image/Free_Assets/Footballers/Independiente/walk.png"
#define INDEPENDIENTE_IDLE "../assets/image/Free_Assets/Footballers/Independiente/idle.png"
#define INDEPENDIENTE_FRONT "../assets/image/Free_Assets/Footballers/Independiente/front.png"
#define INDEPENDIENTE_BACK "../assets/image/Free_Assets/Footballers/Independiente/back.png"

// RIVERPLATE
#define RIVERPLATE_WALK "../assets/image/Free_Assets/Footballers/RiverPlate/walk.png"
#define RIVERPLATE_IDLE "../assets/image/Free_Assets/Footballers/RiverPlate/idle.png"
#define RIVERPLATE_FRONT "../assets/image/Free_Assets/Footballers/RiverPlate/front.png"
#define RIVERPLATE_BACK "../assets/image/Free_Assets/Footballers/RiverPlate/back.png"


// SANLORENZO
#define SANLORENZO_WALK "../assets/image/Free_Assets/Footballers/SanLorenzo/walk.png"
#define SANLORENZO_IDLE "../assets/image/Free_Assets/Footballers/SanLorenzo/idle.png"
#define SANLORENZO_FRONT "../assets/image/Free_Assets/Footballers/SanLorenzo/front.png"
#define SANLORENZO_BACK "../assets/image/Free_Assets/Footballers/SanLorenzo/back.png"

// FOOTBALLER STATES
#define IDLE 0
#define WALK_RIGHT 1
#define WALK_FRONT 2
#define WALK_BACK 3

extern int defaultMap[MAP_HEIGHT][MAP_WIDTH];

extern std::vector<std::tuple<const char*, int, int, int>> ArgentinaFootballerSprite;
extern std::vector<std::tuple<const char*, int, int, int>> BocaFootballerSprite;
extern std::vector<std::tuple<const char*, int, int, int>> IndependienteFootballerSprite;
extern std::vector<std::tuple<const char*, int, int, int>> RiverPlateFootballerSprite;
extern std::vector<std::tuple<const char*, int, int, int>> SanLorenzoFootballerSprite;

#endif