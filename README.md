🛡️ Tank Strategy Game
A tactical, 2-player turn-based tank combat game developed in C. Players navigate a grid-based battlefield, destroy obstacles, and use advanced ballistics to eliminate their opponent.

🕹️ Game Features
Turn-Based Strategy: Players take turns deciding whether to maneuver for a better position or launch an attack.

Destructible Environment: The battlefield is filled with walls (X) that can be strategically destroyed to open lines of fire.

Advanced Weapon Systems:

Normal Fire: A standard direct-line shot.

Ricochet Fire: A sophisticated projectile that bounces off borders at 90-degree angles (up to 5 bounces), allowing for trick shots around corners.

Airdrop Bomb: A high-impact area-of-effect attack that targets a 3x3 grid with a randomized destruction pattern.

Dynamic Win/Loss Conditions: Win by hitting the enemy, but lose instantly if you hit yourself with a ricochet or a poorly placed airdrop!

Draw Logic: If all destructible walls are cleared without a winner, the game ends in a draw.

🛠️ Technical Overview
Language: C (C99/C11 compatible)

Key Concepts: 2D Arrays, Structs, Pointers, Procedural Logic, and Randomized Algorithms.

Modular Design: The project is split into separate logic (tank_game.c), headers (tank_game.h), and the main execution loop (main.c).

🎮 How to Play
Once the game starts, you will see an 11x11 battlefield surrounded by safety borders.

Board Legend:
# — Indestructible Border

X — Destructible Wall

O — Player Tank

— Empty Path

Action Menu:
Move: Choose a direction (1-Up, 2-Right, 3-Down, 4-Left) and the number of steps. You will stop automatically if you hit a wall or the enemy.

Normal Fire: Fires a straight shot in a chosen direction.

Ricochet Fire: Fires a shot that "turns right" every time it hits the border.

Airdrop Bomb: Input target coordinates. A 3x3 area will be bombarded with a 50% chance of impact per tile.

Exit: Close the game.

📂 Project Structure
main.c — Entry point containing the game loop and turn management.

tank_game.c — Implementation of movement, firing physics, and board initialization.

tank_game.h — Constants, struct definitions (Position), and function prototypes.
