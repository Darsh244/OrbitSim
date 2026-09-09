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
  float oldTime = clock.getElapsedTime().asSeconds();
  while (window.isOpen()) {
    float currentTime = clock.getElapsedTime().asSeconds();
    float dT = currentTime - oldTime;
    oldTime = currentTime;

    while (const std::optional event = window.pollEvent()) {
      handleEvent(
          *event); // handleEvent expects a sf::Event, even is std::optional
    }

    engine.moveBodies(dT);
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