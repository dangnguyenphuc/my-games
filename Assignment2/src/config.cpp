#include "../include/config.hpp"

int defaultMap[MAP_HEIGHT][MAP_WIDTH] = {
  { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
  { 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 }
};

std::vector<std::tuple<const char*, int, int, int>> ArgentinaFootballerSprite {
      std::make_tuple(ARGENTINA_IDLE, IDLE, 4, 100),
      std::make_tuple(ARGENTINA_WALK, WALK_RIGHT, 4, 100),
      std::make_tuple(ARGENTINA_FRONT, WALK_FRONT, 4, 100),
      std::make_tuple(ARGENTINA_BACK, WALK_BACK, 4, 100)
};

std::vector<std::tuple<const char*, int, int, int>> BocaFootballerSprite {
      std::make_tuple(BOCAJUNIORS_IDLE, IDLE, 4, 100),
      std::make_tuple(BOCAJUNIORS_WALK, WALK_RIGHT, 4, 100),
      std::make_tuple(BOCAJUNIORS_FRONT, WALK_FRONT, 4, 100),
      std::make_tuple(BOCAJUNIORS_BACK, WALK_BACK, 4, 100)
};

std::vector<std::tuple<const char*, int, int, int>> IndependienteFootballerSprite {
      std::make_tuple(INDEPENDIENTE_IDLE, IDLE, 4, 100),
      std::make_tuple(INDEPENDIENTE_WALK, WALK_RIGHT, 4, 100),
      std::make_tuple(INDEPENDIENTE_FRONT, WALK_FRONT, 4, 100),
      std::make_tuple(INDEPENDIENTE_BACK, WALK_BACK, 4, 100)
};

std::vector<std::tuple<const char*, int, int, int>> RiverPlateFootballerSprite {
      std::make_tuple(RIVERPLATE_IDLE, IDLE, 4, 100),
      std::make_tuple(RIVERPLATE_WALK, WALK_RIGHT, 4, 100),
      std::make_tuple(RIVERPLATE_FRONT, WALK_FRONT, 4, 100),
      std::make_tuple(RIVERPLATE_BACK, WALK_BACK, 4, 100)
};

std::vector<std::tuple<const char*, int, int, int>> SanLorenzoFootballerSprite {
      std::make_tuple(SANLORENZO_IDLE, IDLE, 4, 100),
      std::make_tuple(SANLORENZO_WALK, WALK_RIGHT, 4, 100),
      std::make_tuple(SANLORENZO_FRONT, WALK_FRONT, 4, 100),
      std::make_tuple(SANLORENZO_BACK, WALK_BACK, 4, 100)
};
