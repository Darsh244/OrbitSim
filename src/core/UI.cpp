#include "core/UI.h"
#include "core/SimConfig.h"
#include "imgui-SFML.h"
#include <imgui.h>
#include <stdexcept>

UI::UI(sf::RenderWindow &win) : window(win) {
  if (!ImGui::SFML::Init(window))
    throw std::runtime_error("SFML-ImGui failed to initialize");

  const auto size = window.getSize();
  topPanelPos = {0.f, 0.0f};
  topPanelSize = {static_cast<float>(size.x), TOP_PANEL_HEIGHT};

  sidePanelPos = {(size.x - SIDE_PANEL_WIDTH), TOP_PANEL_HEIGHT};
  sidePanelSize = {SIDE_PANEL_WIDTH, (size.y - TOP_PANEL_HEIGHT)};

  inspectorPanelSize = {INSPECTOR_WIDTH, INSPECTOR_HEIGHT};

  input_mass = DEFAULT_INPUT_MASS;
  input_radius = DEFAULT_INPUT_RADIUS;
  input_simulation_speed = DEFAULT_SIMULATION_SPEED;
}

void UI::update(sf::Time dt) { ImGui::SFML::Update(window, dt); }

void UI::processEvent(const sf::Event &event) {
  ImGui::SFML::ProcessEvent(window, event);
}

bool UI::hasMouseCapture() { return ImGui::GetIO().WantCaptureMouse; }

void UI::draw(const bool isPaused, SimConfig &config) {
  ImGui::SetNextWindowPos(sidePanelPos);
  ImGui::SetNextWindowSize(sidePanelSize);
  ImGui::Begin("Panel", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoCollapse);
  ImGui::InputFloat("Mass", &input_mass, 0.0f, 0.0f, "%g");
  ImGui::InputFloat("Radius", &input_radius, 0.0f, 0.0f, "%g");

  if (ImGui::Button("Settings"))
    requestedSettingsOpen = true;

  ImGui::End();

  ImGui::SetNextWindowPos(topPanelPos);
  ImGui::SetNextWindowSize(topPanelSize);
  ImGui::Begin("Panel2", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
  ImGui::SliderFloat(
      "Simulation Speed", &input_simulation_speed, 0.1f, 5.0f, "%.2fx",
      ImGuiSliderFlags_Logarithmic | ImGuiSliderFlags_AlwaysClamp);

  if (isPaused) {
    ImGui::TextColored(ImVec4(1.0, 0, 0, 1), "Paused");
  }
  ImGui::End();

  if (requestedSettingsOpen) {
    uiRequestedPause = true;
    showSettings(config);
  }
}

void UI::showBodyInfo(const BodyInfo &info, const float anchorX,
                      const float anchorY) {

  ImVec2 wantedPos = {anchorX + INSPECTOR_OFFSET_X,
                      anchorY + INSPECTOR_OFFSET_Y};

  if (!inspectorMoved) {
    ImGui::SetNextWindowPos(wantedPos);
  }
  if (!inspectorResized) {
    ImGui::SetNextWindowSize(inspectorPanelSize);
  }

  bool open = true;
  ImGui::Begin("Inspector", &open);

  ImVec2 size = ImGui::GetWindowSize();
  if (!inspectorResized && (size.x - inspectorPanelSize.x != 0 ||
                            size.y - inspectorPanelSize.y != 0)) {
    inspectorResized = true;
  }

  if (!inspectorMoved && !inspectorResized && ImGui::IsWindowFocused() &&
      ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
    inspectorMoved = true;
  }

  ImGui::SeparatorText("Identity");
  ImGui::Text("Id: %d", info.id);
  ImGui::Text("Mass: %.2f", info.mass);
  ImGui::Text("Radius: %.2f", info.radius);

  ImGui::SeparatorText("Motion");
  ImGui::Text("Position: (%.2f, %.2f)", info.position.x, info.position.y);
  ImGui::Text("Velocity: (%.2f, %.2f)", info.velocity.x, info.velocity.y);
  ImGui::Text("Speed: %.2f", info.speed);

  ImGui::SeparatorText("Derived");
  ImGui::Text("Momentum: (%.2f, %.2f)", info.momentum.x, info.momentum.y);
  ImGui::Text("Kinetic Energy: %.2f ", info.kineticEnergy);

  ImGui::End();

  if (!open) {
    inspectorCloseRequested = true;
    resetInspectorLayout();
  }
}
void UI::resetInspectorLayout() {
  inspectorResized = false;
  inspectorMoved = false;
}

bool UI::consumeInspectorClose() {
  bool requested = inspectorCloseRequested;
  inspectorCloseRequested = false;
  return requested;
}

void UI::showSettings(SimConfig &config) {
  ImGui::Begin("Settings", &requestedSettingsOpen);
  ImGui::SliderFloat("G", &config.G, 0.1f, 10000.0f, "%.2f",
                     ImGuiSliderFlags_Logarithmic |
                         ImGuiSliderFlags_AlwaysClamp);
  ImGui::Checkbox("Gravity enabled", &config.gravityEnabled);
  ImGui::End();

  if (!requestedSettingsOpen)
    uiRequestedPause = false;
}

void UI::render() { ImGui::SFML::Render(window); }

void UI::shutdown() { ImGui::SFML::Shutdown(); }

void UI::resetUI() {
  input_mass = DEFAULT_INPUT_MASS;
  input_radius = DEFAULT_INPUT_RADIUS;
  input_simulation_speed = DEFAULT_SIMULATION_SPEED;
  inspectorCloseRequested = false;
  resetInspectorLayout();
}