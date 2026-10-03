#include "core/UI.h"
#include "imgui-SFML.h"
#include <stdexcept>

UI::UI(sf::RenderWindow &win) : window(win) {
  if (!ImGui::SFML::Init(window))
    throw std::runtime_error("SFML-ImGui failed to initialize");

  const auto size = window.getSize();
  topPanelPos = {0.f, 0.0f};
  topPanelSize = {static_cast<float>(size.x), TOP_PANEL_HEIGHT};

  sidePanelPos = {(size.x - SIDE_PANEL_WIDTH), TOP_PANEL_HEIGHT};
  sidePanelSize = {SIDE_PANEL_WIDTH, (size.y - TOP_PANEL_HEIGHT)};
}

void UI::update(sf::Time dt) { ImGui::SFML::Update(window, dt); }

void UI::processEvent(const sf::Event &event) {
  ImGui::SFML::ProcessEvent(window, event);
}

bool UI::hasMouseCapture() { return ImGui::GetIO().WantCaptureMouse; }

void UI::draw() {
  ImGui::SetNextWindowPos(sidePanelPos);
  ImGui::SetNextWindowSize(sidePanelSize);
  ImGui::Begin("Panel", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoCollapse);
  ImGui::End();

  ImGui::SetNextWindowPos(topPanelPos);
  ImGui::SetNextWindowSize(topPanelSize);
  ImGui::Begin("Panel2", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoCollapse);
  ImGui::End();
}

void UI::render() { ImGui::SFML::Render(window); }

void UI::shutdown() { ImGui::SFML::Shutdown(); }