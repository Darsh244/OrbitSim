# OrbitSim

A C++ N-body gravity simulator built with SFML and Dear ImGui. You spawn bodies with a mass, radius, and starting velocity, then watch them attract each other, orbit, slingshot, and merge in real time. Gravity strength, simulation speed, and the unit scaling can all be changed while it runs.

<!-- ![OrbitSim demo](asset/docs/OrbitSim_Demo.gif) -->

## What it does

- Simulates Newtonian gravity between every pair of bodies, updated every frame.
- Lets you spawn a body anywhere by right-clicking, then dragging to set its starting velocity, with a live line showing where it will head.
- Merges bodies that touch into a single body, conserving momentum.
- Lets you pan and zoom the camera freely, with the zoom centered on your cursor.
- Lets you click any body to open an inspector showing its mass, radius, position, velocity, speed, momentum, and kinetic energy, updated live as it moves.
- Lets you pause, reset, and change the simulation speed and physics constants at any time.

## Why

Most gravity demos show you one fixed scenario. This one is built to be played with. Because mass, radius, velocity, and the gravitational constant are all adjustable, you can set up the same starting conditions and change only one thing, such as the strength of gravity or the mass of a single body, and see exactly how the outcome changes. The inspector makes it easy to check the numbers behind what you're seeing, such as how total momentum is preserved across a merge.

## Physics

- **Gravity**: every pair of bodies attracts with a force of `G * m1 * m2 / r²`, directed along the line between them. The resulting acceleration is accumulated for each body from all the others, then reset every frame so it is always calculated from the current state.
- **Integration**: velocity is updated from acceleration first, then position is updated from the new velocity (semi-implicit Euler). This is more stable for orbits than updating position with the old velocity.
- **Collisions**: two bodies collide when the distance between their centers is less than or equal to the sum of their radii. Colliding bodies merge into one body.
- **Merging**: the merged body's mass is the sum of the two masses, its velocity is the momentum-weighted average (so total momentum is conserved), and it appears at the center of mass of the pair. Its radius is chosen so the merged body's area equals the sum of the two original areas.
- **Unit scaling**: the settings window has a kg-per-mass-unit and a meters-per-pixel value that scale the gravity calculation, so you can experiment with different unit systems. The inspector always displays raw simulation units.

## Controls

- **Right click and drag**: spawn a body at the click position. Drag away from the direction you want it to travel, like pulling back a slingshot, and release to launch it.
- **Left click on a body**: open the inspector for that body.
- **Left click and drag on empty space**: pan the camera.
- **Scroll wheel**: zoom in and out around the cursor.
- **Space**: pause or resume the simulation.
- **R**: reset the whole simulation.
- The side panel sets the mass and radius used for newly spawned bodies, and has a button that opens the settings window.
- The top panel has a simulation speed slider.
- The settings window changes the gravitational constant, the unit scaling, and whether gravity is enabled. The simulation pauses while it is open.

The inspector follows its body as it moves. You can drag it, resize it, or close it, and it closes on its own if the body it is tracking merges into another one.

## Architecture

The project is split into a few independent pieces that only talk to each other through small interfaces:

- **PhysicsEngine** owns every `CelestialBody` and the `SimConfig`. It handles gravity, movement, collisions, and merging, and is the only place that knows about the physics. It has no knowledge of rendering, the camera, or the UI. It reports information about a body through a plain `BodyInfo` struct.
- **CelestialBody** is a simple data holder for a body's id, mass, radius, position, velocity, acceleration, and color.
- **SimConfig** holds the simulation constants (G, the unit scaling values, and the gravity toggle) so the UI can edit them without knowing how the physics uses them.
- **Camera** only converts between world and screen coordinates and tracks panning and zoom. Bodies live in world space, and the camera decides where they appear on screen.
- **Renderer** draws a body or a line given a window and a camera. It is stateless and never modifies anything.
- **UI** wraps Dear ImGui. It draws the panels, the inspector, and the settings window, and reports user input back to the simulator through getters and flags. It knows nothing about how gravity or collisions work.
- **Timer** provides the time elapsed between frames.
- **Simulator** owns the window and the main loop, and coordinates between all of the above: it feeds events to the UI and camera, steps the physics, and tells the renderer what to draw.

Because the physics engine never touches pixels and the UI never touches physics internals, changing how bodies are drawn or adding a new UI panel does not require changes to the simulation code.

## Building

This project uses CMake and depends on SFML 3, Dear ImGui, and ImGui-SFML.

```bash
cmake -S . -B build
cmake --build build
```

## Running

```bash
./build/bin/OrbitSim
```

## TODO

- The simulation speed slider currently tops out at 5x. Adding a much faster time step would make it practical to watch slow, wide orbits play out.
- Add a way to search for and locate bodies in the simulator, so you can find a body that has drifted off screen and jump the camera to it.
