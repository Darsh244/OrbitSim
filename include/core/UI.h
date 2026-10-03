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

public:
  UI(sf::RenderWindow &win);
  void update(sf::Time dt);

  void processEvent(const sf::Event &event);
  bool hasMouseCapture();

  void draw();
  void render();
  void shutdown();
};