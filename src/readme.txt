These are my latest files (for organization).

------------------------------------------------------

CHANGES LOG:
March 3, 2021
- Changed Main Menu to look like the latest concept (which you can see in the concept folder).
- Moved all file paths into MainMenu.cpp (so that main is less cluttered).
- Added SettingsMenu. All the buttons are working except the mute sfx and mute music.
March 4, 2021
- Added How To Play. Everything is working now (can move pages).
- Fixed minor issues.
- Added Credits.
- Created a class (StartMenu) to manage all the Menu classes, so main is very simple now! (easy to integrate :))
March 5, 2021
- Added the High Scores panel. File IO is working.
- Added exception handling (for file io)
- High Scores is working!! It can update, etc.
- Note: documentation may not be complete right now... I'll work on that.
March 9, 2021
- Added the ability to input player name after achieving high score.
March 10, 2021
- Tried to integrate the menus into the main game and it works! I'll continue updating it as the main game is updated—no need to worry about this.
- Moved the main game to a class of its own (simplifies the main a lot). Again, will update as the game is updated.
- Also added a "score" to the main game. It updates when a Cat is defeated. (+100 pts per Cat as of now).
March 11. 2021
- Fixed file io error. (Problem was caused by having a member variable std::string in Score, and there's troubling reading it from bin file... now it saves it as a char array)
- Added the ability to mute music and sfx!!

------------------------------------------------------

CURRENTLY WORKING ON:
- Ability to change difficulty
- Integrating animation for base class
- Game Over screen
- Ability to pause 

WILL WORK ON SOON:
- Improving main game UI
- Getting the final images for the How To Play page

MIGHT WORK ON LATER (when there's time):
- Variations of Dog/Cat sprite
- Add some kind of water gun to the Dog sprite? so the bullets don't emerge out of nowhere hahaha
- Other possible optimizations

------------------------------------------------------

Other notes:
- The Animation class works very similarly to Hilze Vonck's YouTube tutorial, so you can refer to that on how it works. Some additions however:
    - It is possible for different rows to have a different amount of sprites
    - It is possible to not loop the animation (e.g. if a Cat/Dog is defeated, you wouldn't want to loop the defeat animation:'). )
    - Can check if the animation is currently on the last frame (which I think can help when deleting a Cat/Dog after being defeated)
- Ask me if you have any questions!! ^^
