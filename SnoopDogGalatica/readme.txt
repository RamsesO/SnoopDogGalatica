Overall Class Hierarchy
					Gravity----------
									|
									|
									|
Collision - Entity - Shape ----------- Warbird 
					        | 
						     -- Missile
					        | 
						     -- Planet --- Moon
					        | 
					         -- Sun

============================================== PHASE 2 ============================================ 

Missile Sites
	* A model for missile sites are created
	* They are very easily spotted 
	* They are located on top of Unum and Secundus
	* They have bounding radius of about 30 

Cameras
	* Warbird's camera now moves with the ship as the ship is moved by controller
	* Warbird's camera is located back and up of the ship looking forward from behind of the ship

Ship Movements
	* Warbird's can be controlled by Arrow Keys 
	* Pressing on Arrow keys will move the warbird 
	* Not pressing on Arrow keys will halt any movement of the warbird
	* 'S' key triggers speed shifts
	* 'W' key triggers ship warping to the Camera of Unum and Duo
	* 'g' key will trigger gravity take in effect on the warbird. pressing 'g' key once again will 
		stop the effect of gravity
Missile
	* Warbird(9) and missile sites(5) are loaded with missiles now.
	* 'f' key press will trigger Warbird's missile to be fired 
	* Missile Sites will detect if the Warbird is near within detection range (3000) and fire missile to warbird
	* Once missiles are fired, missiles will move forward until smart aiming activation, which will take 200 updates. 
	* Missile will automatically blow up at 2000 updated frames. 
	* When Missile's smart aiming is activated, Missile will find target and move toward target only 
		if target exist within detection range.
	* When the missile's smart aiming is not active, missile will not be tested for collisions
	* Remaining count of missiles from each location is displayed on the window.

Time Quantum 
	* TQ can be changed by user with 'T' key press
		* TQ Very Large = Debug mode
		* TQ Large 		= Trainee mode
		* TQ Average 	= Pilot mode
		* TQ fast 		= Ace mode
	* The game will start in Ace mode

Pass or Resign 


============================================== PHASE 1 ============================================ 

Ruber System 
	Snoop Dog Galatica has Sun(Ruber) and two planets(Unum and Duo) orbiting around XZ plane of the Sun. 
	And Duo has two moons(Primus and Secundus) orbiting around XZ plane of the Duo

Animation
	The Ruber system simulation happens in the fixed interval timer's Time Quantum (5 or 40 ms).
	With different time quantum the animation becomes faster/slower accordingly.

Model
	All shapes of sun, planets, moons are properly loaded and animated
	Missile and Warbird model is also loaded properly and located at the designated location.

Camera
	Front and Top Camera is located in a fixed location according to the specification.
	Ship, Unum and Duo camera is situated to follow the rotation and translation of each planet. 






