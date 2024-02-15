#ifndef CONFIG_HPP
#define CONFIG_HPP

#define SCREEN_WIDTH 1120
#define SCREEN_HEIGHT 800

#define SCREEN_CENTER_WIDTH SCREEN_WIDTH/2
#define SCREEN_CENTER_HEIGHT SCREEN_HEIGHT/2

#define FPS 60
#define FRAME_DELAY 1000/FPS
#define SPEED 100

#define BALL_TEXTURE_FILE_PATH "../assets/image/ball.png"

// Map
#define MAP_WIDTH 35  //  1120/32
#define MAP_HEIGHT 25 //  800/32

// Grass Tile
#define GRASS_TILE_FILE_PATH "../assets/image/Tiles/grass.png"
#define GRASS_TILE_WIDTH_HEIGHT 16
#define GRASS_TILE_WIDTH_HEIGHT_2_DRAW 64

// ARGENTINA
#define ARGENTINA_WALK "../assets/image/Free_Assets/Footballers/Argentina/walk.png"
#define ARGENTINA_IDLE "../assets/image/Free_Assets/Footballers/Argentina/idle.png"
#define ARGENTINA_FRONT "../assets/image/Free_Assets/Footballers/Argentina/front.png"
#define ARGENTINA_BACK "../assets/image/Free_Assets/Footballers/Argentina/back.png"

// FOOTBALLER STATES
#define IDLE 0
#define WALK_RIGHT 1
#define WALK_FRONT 2
#define WALK_BACK 3


#endif