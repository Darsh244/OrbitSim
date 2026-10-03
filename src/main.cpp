#include "Simulator.h"

constexpr unsigned WINDOW_WIDTH = 1200;
constexpr unsigned WINDOW_HEIGHT = 800;
constexpr int FPS = 60;

int main() {
  Simulator simulator(WINDOW_WIDTH, WINDOW_HEIGHT);
  simulator.run();
}
