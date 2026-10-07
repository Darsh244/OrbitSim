#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui.h>

class UI {
  sf::RenderWindow &window;

  ImVec2 topPanelPos;
  ImVec2 topPanelSize;
  static constexpr float TOP_PANEL_HEIGHT = 50.0f;

  ImVec2 sidePanelPos;
  ImVec2 sidePanelSize;
  static constexpr float SIDE_PANEL_WIDTH = 200.0f;

  // input variables
  float input_mass;
  float input_radius;
  float input_simulation_speed;
  static constexpr float DEFAULT_INPUT_MASS = 50.0f;
  static constexpr float DEFAULT_INPUT_RADIUS = 20.0f;
  static constexpr float DEFAULT_SIMULATION_SPEED = 1.0f;

public:
  UI(sf::RenderWindow &win);
  void update(sf::Time dt);

  void processEvent(const sf::Event &event);
  bool hasMouseCapture();

  void draw();
  void render();
  void shutdown();

  // getters
  float getInputMass() const { return input_mass; }
  float getInputRadius() { return input_radius; }
  float getSimulationSpeed() { return input_simulation_speed; }
};