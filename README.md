# SFML-project-Xonix
Our implemintation of Xonix, in Poke'mon version

We created the Xonix Pacman game, in Poke'mon version (original game: https://www.pacxon.net/)
We used the OOP principles of inheritance, polymorphism, as well as our knowledge of data structures, the STD, algorithms, exceptions and design templates.
For the graphics, we used the SFML library. 

Selection in the opening menu is done with the mouse. The character is controlled using the arrow keys. 
You can stop the game by pressing the space bar. 
The goal is to occupy at least 80% of the territory. 
If an enemy hits the character, the player loses a life. 
If the enemy "infects" a green rail and it turns red, and the character touches the red part, the player loses a life.
The character can pick "gifts" which give various bonuses - freezing the enemies, giving the character 1 more HP, making the enemies "ediables" (so they disappear), and boosting up the character's speed for a limited time.


We used the dynamic programming Flood Fill algorithm to color the occupied territory
For this, we defined 5 states of a tile:
1) Occupied (blue), belongs to the character.
2) Potential (green), will be turned into Occupied if the player succeed. 
3) Dangerous (red), an enemy touched this tile, if the character hits that, the player loses 1 HP.
4) Free
5) EnemyArea
Both Free and EnemyArea are transparent. EnemyArea is "infected".

Before the algorithm runs, we changing every EnemyArea to Free ("cleanse").
In our version of the algorithm, the algorithm gets a refference to the board, the coordinates (i, j) of an enemy on the board, the new occupation state and the old one.
For each tile (i, j) in the board, the algorithm checks the tiles around it. 
If the tile is Free, the algorithm "infects" it - changing its state to EnemyArea.
Then, every tile which is NOT "infected", turns into Occupied.

This way, the tiles which stayed Free, must be blocked by Occupied tiles, meaning the player captured this area, therefore it should be turned into Occupied.


Known bugs:
Rarely, an enemy "getting stuck" inside a tile. Most of the time it frees itself after a few seconds.
