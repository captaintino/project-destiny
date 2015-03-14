# Test Plan #

## Test Start Game ##
  1. Enter a username in the white box above the “Start Game” button on the main menu
  1. Click the “Start Game” button
  1. On the screen you should see a moving screen with a ship controlled by your mouse and asteroids, aliens, and projectiles moving towards your ship. You should also see a calculating score in the upper right side of the window.
## Test Collision Detection ##
  1. Maneuver your mouse to crash into an alien, asteroid, or projectile.
  1. You should see the game stop and your ship explode.
## Test Escape at End of Game ##
  1. Press the escape button on your keyboard.
  1. You should be taken back to the main menu.
  1. The game will not save when you press the escape button after crashing.
## Test Instruction Window ##
  1. On the main menu click the “Instructions” button.
  1. You should see a window with game instructions and a “Back to Menu” button on the bottom of the window.
  1. Click the “Back to Menu” button. The window should close and you should be taken back to the main menu.
## Test Highscore Window ##
  1. On the main menu, click the “High Scores” button.
  1. You should see a window with 5 rows of usernames and high scores and a “Back to Menu” button on the bottom of the window.
  1. Click the “Back to Menu” button, You should be taken back to the main menu.
## Test the Multiplayer Functionality and Window ##
  1. On the main menu click “Multiplayer.”
  1. You should see a “Connect” button, a box with your username, a box for you to type your desired hosts’ name into, and a “Refresh” button along the top of the window with a “Back to Menu” button on the bottom of the window.
  1. Run the Chatserver executable from the current directory.
  1. Type nothing into the "host" textbox and  “Connect” to get other players’ information from the server. The server window should give a status report if connected. If not a message entitled “Uh Oh” containing “Unable to connect to server.” should pop up in your program’s Multiplayer window.
  1. If successfully connected, you should see a list of other users: their username, score, state (alive/dead), and current level in the game in rows going down the Multiplayer window.
  1. Click the “Refresh” button to update other users’ information. You should see the users’ information refresh itself going down the screen.
  1. Click the “Back to Menu” button on the bottom of the window to return to the main menu.
## Test Load Game Functionality ##
  1. Follow the Test Start Game instructions then instead of crashing, press the escape key while you are still alive.
  1. This action should save your game and take you back to the main menu.
  1. On the main menu, click the “Load Game” button. You should begin the game where you last saved it.
## Test Cheat Mode ##
  1. On the main menu, click beside “Cheat Mode” to select the cheat mode status to on.
  1. On selecting the “On” position, a new box should appear below “Cheat Mode” allowing you to select the desired level you want to jump to.
  1. Select level 3 and click the “Start Game” button on the main menu.
  1. You should be taken to level 3 in the game.
  1. Run your ship over an asteroid, alien, and/or projectile. Nothing should happen and gameplay should continue as usual. Your score will not be saved to the high scores list while on cheat mode.




|Pages|[Screen Shots](ScreenShots.md)|[Test Plan](TestPlan.md)|[Instructions](Instructions.md)|[Bugs](Bugs.md)|[Roles](Roles.md)|[Features](Features.md)|[Road Map](RoadMap.md)|[Project Proposal](ProjectProposal.md)|
|:----|:-----------------------------|:-----------------------|:------------------------------|:--------------|:----------------|:----------------------|:---------------------|:-------------------------------------|