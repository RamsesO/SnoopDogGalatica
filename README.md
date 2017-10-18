# Snoop Dogg Galatica
>The dankest solar system that no one has ever seen.

## Warbird Simulation Overview

### Ruber System

* Planets and Objects
    * Sun (Ruber)
    * Planet #1 (Unum)
        * Missile Site #1
    * Planet #2 (Duo)
        * Moon #1 (Primus)
        * Moon #2 (Secundus)
            * Missile Site #2
    * Spaceship

* Animation
    * Sun in the center
    * Unum and Duo rotate around the Sun on the XZ axis
        * x-axis = length
        * y-axis = height
        * z-axis = depth
    * The moons orbit Duo at the XZ axis
    * Use the fixed interval timer's Time Quantum (TQ) to call an update function for each "simulation update frame" to “update” the planet and moon orbits.
    * There are two different TQ
        * 5 milliseconds (fast)
        * 40 milliseconds (ace)
            * 25 updates per seconds
            * Unum should rotate every 8 seconds around Ruber

* Cameras
    * Static Cameras
        * Front
        * Top
    * Dynamic Cameras
        * Ship View
        * Unum View
            * Unum will rotate towards the camera
        * Duo View
            * Duo will rotate towards the camera
        
* Shaders
    * Use "simpleVertex.glsl" and the "simpleFragment.glsl" shader programs
    * You will create your own shaders in Phase #3

* Missiles
    * Ship has 9 missiles
    * Each missile defense site has 5 missiles
    * Missiles must be contained in a bounding sphere radius of 25
    * Models can't be spherical
    * Are homing missiles and can track

* Information Display
    * Must contain
        * Missile Counts
        * Update rate (U/S)
        * Frame rate (F/S)
        * Current view (camera)
    * Example
        * `Warbird 7 Unum 5 Secundus 0 U/S 25 F/S 321 View Duo`

## Phase #1

* Have planets and moons orbiting Ruber
* Have the Front, Top, Unum and Duo cameras
* You should have warbird and 1 missile at (4900, 1000, 4850)

## Phase #2

* Missile Sites
    * Model for missile sites should be created
    * Missile sites should be located at the top (highest Y value) of the planet
    * Missile sites should have a bounding radius of about 30

* Cameras
    * Warbird's camera should move with the ship
    * Shows the ship from behind

* Ship Movement
    * Ship can move frontward and backward
    * Ship has 3 speeds that can be toggled with key s
        * 10
        * 50
        * 200
    * Ship has 3 rotation thrusters with rotation speed 0.02f 
        * at
        * up
        * right
    * Ship can also warp to planets to one of the 2 planetary cameras
        * unum
        * duo

* Missile Movement
    * Should have a radius of 25
    * Ship has 9 missiles
        * Fired by the f key
        * Cadet can't fire another missile until the current missile is detonated
    * Missile site has 5 missiles
        * Missiles fire in the direction of the rotation
        * Missiles are fired when the ship is in the detection range
    * Missile's tracking system does not activate until 200 updates
    * All missiles that do not hit exit for 2000 update frames
    * Missiles detonate on collision
        * You do not have to simulate/visualize the explosion

* Time Quantum
    * Should have a "stepped" update
    * The TQ (cadet type) should be  and have 4 values
        * TQ very large (debug)
        * TQ large (trainee)
        * TQ average (pilot)
        * TQ fast (ace)

* Pass or resign
    * Cadet passes flight training by destroying both missile sites
        * "Cadet passes flight training"
    * If cadet resigns
        * "Cadet resigns from War College"
