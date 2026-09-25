# Unnamed Platformer - WIP! NOT FINISHED!!!
A 2D platformer game in which you play as a square in outer space traversing through 30 levels, gaining the ability to turn into various shapes along the way, each with their own powers!

-> insert a gameplay gif here

Watch the 100% walkthrough of the game here: [I'll add the link here eventually]

Play the game here: [I'll add the link here eventually]

Rephrase the above ones?


## So what's in the game?
- 30 distinct, challenging levels
- 5 different playable shapes, each with a distinct powerup
- "Easy to learn, hard to master"-type controls (think Celeste)
- Coins scattered throughout each level as an extra collectible
- Level timers, death counts, and more
- Hand-made SFX and artwork

## How does it work?
This game was made using purely C++ and the Simple and Fast Multimedia Library (SFML), which is a low-level graphics library used for rendering 2D graphics and shapes as well as basic SFX and the like. I did not use any external game engines, such as Godot or Unity, to create this project.
Relying solely on C++ and SFML was limiting because the scope of things you can actually do is not the largest; however it's still possible to create simple visual effects using its various features. Additionally, simply using C++ and SFML is enough to create a fully functional, fun-to-play game, as this game proves you do not need external game engines to make something enjoyable to play.
The shapeshifting feature is (in my opinion) quite a unique feature compared to other platformers. To create this system, I set a master entity class which includes all objects affected by physics (i.e. pushable blocks and players). This branches into the player sub-class, which branches further into sub-classes for each individual playable shape. Each contains the various playstyle quirks and visual appearances associated with each shape, and in the main game loop, an instance of the player is set to a square by default using std::make_unique<square>(). Whenever a switch occurs, make_unique<>() is run again with the according shape. Every frame runs a position and velocity capture so that when a switch occurs, it's easy to transfer the position and velocity by overriding the reset from shape creation. 
Another key aspect is the collision system. This game uses Separating Axis Theorem (SAT) collision, which checks if axes of two polygons intersect to determine collision, rather than Axis-Aligned Bounding Box (AABB) collision, which checks if the edges of two bounding rectangles overlap to determine collision. Using SAT collision was crucial for the game, as it uses multiple regular polygons that are often being rotated and AABB checks would result in erroneous [    ]. All collision-related functions and logic are stored in collisions.h, such as returning vertices and axes of an object, translating objects by the Minimum Translation Vector (MTV) so they stop colliding, and checking if axes intersect i.e. if shapes are even colliding to begin with. Additionally, the rotation feature ties in well with the collision. There are two primary types of rotation in the game: rolling and tipping. Rolling logic is straightforward, simply using SFML's transformation system on each shape; settling down to a flat face is another rotation feature, but it's more of a sub-feature in rolling. Tipping is a more complex endeavor, involving:
- detecting whether or not a shape's midpoint is located directly above open air, 
- deciding which direction it should tip, 
- tipping the shape in that direction, and 
- deciding when the shape enters a freefall state and doesn't need to keep forcibly tipping.