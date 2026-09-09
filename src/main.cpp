#include "Simulator.h"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr int FPS = 60;

int main() {
  Simulator simulator(WINDOW_WIDTH, WINDOW_HEIGHT);
  simulator.run();
}
