#pragma once
#include "core/BodyInfo.h"
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

  // inspector window
  ImVec2 inspectorPanelSize;
  static constexpr float INSPECTOR_WIDTH = 215.0f;
  static constexpr float INSPECTOR_HEIGHT = 165.0f;
  static constexpr float INSPECTOR_OFFSET_X = 15.0f;
  static constexpr float INSPECTOR_OFFSET_Y = 15.0f;

  bool inspectorMoved = false;
  bool inspectorCloseRequested = false;
  bool inspectorResized = false;

public:
  UI(sf::RenderWindow &win);
  void update(sf::Time dt);

  void processEvent(const sf::Event &event);
  bool hasMouseCapture();

  void draw(const bool isPaused);
  void render();
  void shutdown();
  void resetUI();

  // inspector window
  void showBodyInfo(const BodyInfo &info, const float anchorX,
                    const float anchorY);
  bool consumeInspectorClose();
  void resetInspectorLayout();

  // getters
  float getInputMass() const { return input_mass; }
  float getInputRadius() { return input_radius; }
  float getSimulationSpeed() { return input_simulation_speed; }
};