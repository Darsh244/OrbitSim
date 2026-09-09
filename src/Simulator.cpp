#include "Simulator.h"
#include "physics/PhysicsEngine.h"
#include "renderer/Renderer.h"

Simulator::Simulator(unsigned windowWidth, unsigned windowHeight) {
  window =
      sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Window");
  window.setFramerateLimit(60);
  engine = PhysicsEngine();
}

void Simulator::run() {
  sf::Clock clock;
  clock.start();
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent())
      handleEvent(
          *event); // handleEvent expects a sf::Event, even is std::optional

    window.clear();

    for (auto &body : engine.getBodies()) {
      Renderer::draw(window, body);
    }
    window.display();
  }
}

void Simulator::handleEvent(const sf::Event &event) {
  if (event.is<sf::Event::Closed>()) {
    window.close();
  }
}