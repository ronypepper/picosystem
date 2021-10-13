#include <array>

#include "picosystem.hpp"

using namespace picosystem;

struct shape_t {
  int32_t x, y, w, h;
  color_t p;
};

std::array<shape_t, 200> shapes;

void reset() {
  for(auto &s : shapes) {
    s.x = std::rand() % 120;
    s.y = std::rand() % 120;
    s.w = std::rand() % 20;
    s.h = std::rand() % 20;
    s.p = hsv((std::rand() % 100) / 100.0f, 1.0f, 1.0f);
  }
}

void move() {
  for(auto &s : shapes) {
    s.x += std::rand() % 3 - 1;
    s.y += std::rand() % 3 - 1;
    s.w += std::rand() % 3 - 1;
    s.h += std::rand() % 3 - 1;
  }
}

void init() {
  reset();
}

int32_t view = -1;

void update(uint32_t tick) {
  move();

  if(!(tick % 250)) {
    reset();
    view++;

    if(view > 5) {
      view = 0;
    }
  }
}

void label(std::string s) {
  pen(0, 0, 0);
  text(s, 3, 16);
  pen(15, 15, 15);
  text(s, 2, 15);
}

void draw() {
  pen(0, 0, 0);
  clear();

  switch(view) {
    case 0: {
      for(auto &s : shapes) {pen(s.p); frect(s.x, s.y, s.w, s.h);}
      label("Filled rectangles");
    } break;
    case 1: {
      for(auto &s : shapes) {pen(s.p); line(s.x, s.y, s.x + s.w, s.y + s.h);}
      label("Lines");
    } break;
    case 2: {
      uint32_t i = 0;
      for(auto &s : shapes) {sprite(i++, s.x, s.y);}
      label("Sprites");
    } break;
    case 3: {
      for(auto &s : shapes) {pen(s.p); circle(s.x, s.y, s.w / 2);}
      label("Circles");
    } break;
    case 4: {
      for(auto &s : shapes) {pen(s.p); rect(s.x, s.y, s.w, s.h);}
      label("Rectangles");
    } break;
    case 5: {
      for(auto &s : shapes) {pen(s.p); fcircle(s.x, s.y, s.w / 2);}
      label("Filled circles");
    } break;
  }

  // draw title
  pen(15, 15, 15);
  frect(0, 0, 120, 11);
  pen(0, 0, 0);
  text("Shapes Test", 2, 2);


}