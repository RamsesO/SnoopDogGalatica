
	* Warning

		* Skybox does not work all the time
		* You may need to comment the skybox out to make it work
	* Class Structure

		* Shape

			* Handles all the 3d objects in our project

				* Initializing a shape
				* Displaying a shape
				* Simple commands that apply to all 3d objects
		* Signal

			* A place for classes to interact with each other

				* Used to handle game events like detection and death
		* Collision

			* Used to handle collisions in our project
			* More of an interface

				* Where child classes usually override the functions collision provides
		* Entity

			* Extends

				* Signal
				* Collision
			* Used to handle players and NPCs

				* Health
				* missileCount
				* isEnemy
				* isDead
			* All entities can Signal and can Collide
		* Gravity

			* Handles all the gravity in the game
			* Applied to Objects that wish to be affected by gravity
		* MissileSite

			* Extends

				* Shape
				* Entity
			* Class to handle all the interactions and functionalities of the missile sites in the game
		* WarBird

			* Extends

				* Shape
				* Entity
				* Gravity
			* Class to handle all the interactions and functionalities of the ship in the game
		* Missile

			* Extends

				* Shape
				* Gravity
				* Collision
				* Signal
			* Class to handle all the interactions and functionalities of the missile in the game
		* Sun

			* Extends

				* Shape
			* Class to handle all the interactions and functionalities of the Sun
		* Planet

			* Extends

				* Shape
			* Class to handle all the interactions and functionalities of the Planet
		* Moon

			* Extends

				* Planet
			* Class to handle all the interactions and functionalities of the Moon
		* PlanetCam

			* Class for planetary cameras
		* WarbirdCam

			* Class for warbird cameras
		* Models

			* A class to handle all the model interactions 
		* Skybox

			* A class for skybox
	* Extra Stuff

		* Dynamic Skybox

			* The skybox transforms to the size of the project matrix
		* Fabulous Models

			* The dankest models of them all
		* You spin me right round, baby right round

			* Sun, planets, and moons all rotate upon their axis
			* Planets and moons exhibit axial tilt (its up isn't straight, but angled), just like in real life
		* KAMIKAZE ATTACK

			* You can use WarBird as a missile and attack the missile site

				* This is why missile sites are larger, so it would be easier to execute
				* Though you also die
		* Real Gravity

			* When activated all planets emit gravity
			* Uses Newton's law of universal gravitation

				* So our gravity has acceleration

					* The farther you are the exponentially smaller the gravity
					* The closer you are the exponentially larger the gravity
			* Warbird and missiles are affected by gravity

				* Missiles only begin being affected by gravity after activation since gravity is really strong near celestial bodies
		* If they touch, THEY COLLIDE!

			* With the exception of planets, moons and suns

				* Missiles can destroy each other
				* Missiles die on planet, moon, sun hit
				* Warbird dies on planet, moon, sun hit
			* PENALIZING STUPIDITY

				* You can get hit with your own missiles

					* Missile Sites
					* Warbird
				* Missiles are set to explode after 10 updates so you don't get killed when firing a missile
		* OMAE WA MOU SHINDERU (your already dead)

			* Missiles do not go hunting dead missile sites and ships
			* If they cannot find a target missiles will continue to go to a straight line
			* When choosing a target they select one closest to them within their own detection range (not the missile site)

				* Missile sites detection range are used for firing the missile, not tracking
		* Inertia Drives

			* Ship is installed with inertia drives
			* Forward and backwards are now replaced by accelerate forward (positive accel) and accelerate backward (negative accel)

				* When you have positive acceleration and you accelerate backwards you decelerate
				* Likewise when you have negative acceleration and you accelerate forwards you decelerate
			* This means you can go forward/backwards while turning
			* Pressing S now means your change the acceleration constant

				* 2
				* 4
				* 6
			* No terminal velocity means you can go SANIC FAST
		* Real physics is bad game-play

			* Space is a vacuum therefore if you accelerate you will not lose velocity (no air resistance)
			* Decelerating is not fun therefore an acceleration decay rate is added
		* FUN MISSILES

			* Slow start missile

				* Missile starts at a slow pace upon release
				* When missiles activate it moves at a fast rate
			* Impatient missiles

				* Faster to activate and faster to die

