#include "Simulator.h"
#include "core/CelestialBody.h"
#include "physics/PhysicsEngine.h"
#include "renderer/Renderer.h"
#include <SFML/Window/WindowEnums.hpp>
#include <iostream>

Simulator::Simulator(unsigned windowWidth, unsigned windowHeight)
    : window(sf::VideoMode({windowWidth, windowHeight}), "OrbitSim",
             sf::Style::Titlebar | sf::Style::Close),
      ui(window) {

  window.setFramerateLimit(60);
  engine = PhysicsEngine();
  timer = Timer();
}

void Simulator::run() {
  while (window.isOpen() && !shouldWindowClose) {
    timer.update();
    while (const std::optional event = window.pollEvent()) {
      ui.processEvent(*event);
      handleEvent(
          *event); // handleEvent expects a sf::Event, event is std::optional
    }
    ui.update(timer.getdeltaTimeSFML());
    handlePhysics();

    window.clear();
    ui.draw();
    handleRendering();
    window.display();
  }

  ui.shutdown();
  window.close();
}

void Simulator::handlePhysics() {
  engine.resetAcceleration(); // if you dont reset then acceleration will
                              // continuously accumulate, instead of being
                              // recalculated for current state
  engine.calculateGravity();
  engine.moveBodies(timer.getDeltaTime()); // uses time since last frame
  engine.calculateCollisions();
}

void Simulator::handleRendering() {
  for (auto &body : engine.getBodies()) {
    Renderer::draw(window, body, camera);
  }
  if (isSpawningBody && !canSpawnBody) {
    Renderer::drawLine(window, currentSpawiningBodyPosition, velocityLineEndPos,
                       camera);
  }
  ui.render();
}

void Simulator::handleEvent(const sf::Event &event) {
  if (ui.hasMouseCapture())
    return; // dont allow spawning or camera controls when cursor inside ui

  if (event.is<sf::Event::Closed>()) {
    shouldWindowClose = true;
  }

  else if (event.is<sf::Event::MouseButtonPressed>()) {
    const auto *mouseButtonPressed =
        event.getIf<sf::Event::MouseButtonPressed>();
    sf::Vector2f mousePos(mouseButtonPressed->position);
    if (mouseButtonPressed->button == sf::Mouse::Button::Left &&
        !camera.getIsClicking()) {
      camera.handleClick(mousePos);
    } else if (mouseButtonPressed->button == sf::Mouse::Button::Right &&
               canSpawnBody && !isSpawningBody) {
      sf::Vector2f spawnPosition = camera.giveWorldPos(
          mousePos); // the position stored in CelestialBodies
                     // is their world position
      currentSpawiningBodyPosition = spawnPosition;
      velocityLineEndPos =
          spawnPosition; // start with zero veloity untill mouse is dragged
      isSpawningBody = true;
      canSpawnBody = false;
    }
  }

  else if (event.is<sf::Event::MouseMoved>()) {
    const auto *mouseMoved = event.getIf<sf::Event::MouseMoved>();
    sf::Vector2f mousePos(mouseMoved->position);
    if (camera.getIsClicking())
      camera.handleDrag(mousePos);
    else if (isSpawningBody && !canSpawnBody) {
      sf::Vector2f mouseWorldPos = camera.giveWorldPos(mousePos);
      velocityLineEndPos = calculateVelocityLineEndPos(mouseWorldPos);
    }
  }

  else if (event.is<sf::Event::MouseWheelScrolled>()) {
    const auto *mouseScrolled = event.getIf<sf::Event::MouseWheelScrolled>();
    sf::Vector2f mousePos(mouseScrolled->position);
    camera.handleScroll(mousePos, mouseScrolled->delta);
  }

  else if (event.is<sf::Event::MouseButtonReleased>()) {
    const auto *mouseButtonReleased =
        event.getIf<sf::Event::MouseButtonReleased>();
    sf::Vector2f mousePos(mouseButtonReleased->position);
    if (mouseButtonReleased->button == sf::Mouse::Button::Left &&
        camera.getIsClicking()) {
      camera.handleMouseRelease(mousePos);
    } else if (isSpawningBody && !canSpawnBody) {
      sf::Vector2f velocity = velocityLineEndPos - currentSpawiningBodyPosition;
      spawnTestBodyWithVelocity(velocity);
      isSpawningBody = false;
      canSpawnBody = true;
    }
  }
}
sf::Vector2f Simulator::calculateVelocityLineEndPos(sf::Vector2f &mousePos) {
  sf::Vector2f vectorToVelocityLineEndPos =
      currentSpawiningBodyPosition - mousePos;
  return (currentSpawiningBodyPosition + vectorToVelocityLineEndPos);
}

void Simulator::spawnTestBodyWithVelocity(const sf::Vector2f &v) {
  engine.add(CelestialBody(50, 20, currentSpawiningBodyPosition, v));
}