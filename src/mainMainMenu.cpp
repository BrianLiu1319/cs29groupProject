#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Animation.hpp"
#include "StartMenu.hpp"
#include "Score.hpp"
#include "Date.hpp"
#include "HighScoreEntry.hpp"
#include "Game.hpp"
//ADDNEW
#include "GameOver.hpp"

using namespace std;

int main() {
    
    /*********************************
    Create a RenderWindow and Game
    *********************************/
    //ADDNEW: don't resize, i'm afraid itll break the menus... and add the sf::Style::Close so the player can close the window!
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Dogs vs Cats", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(30);
    Game dogsVsCats(static_cast<sf::Vector2f>(window.getSize()));
    
    /*********************************
    Set up necessary stuff
    *********************************/
    StartMenu startMenu(static_cast<sf::Vector2f>(window.getSize()));
    HighScoreEntry highScoreEntryBox(static_cast<sf::Vector2f>(window.getSize()));
    //unsigned int score = 99999;
    Score temp;
    //bool muteMusic = false;
    //bool muteSfx = false;
    int state;
    
    //ADDNEW
    GameOver gameOverScreen(static_cast<sf::Vector2f>(window.getSize()));
    
    /*********************************
    Set up the clock
    *********************************/
    float deltaTime = 0.0f;
    sf::Clock clock;
    
    /*********************************
     The current state of the game.
     - menu
     - play game
     - enter high score
     - game over
     *********************************/
    //ADDNEW: add gameOver to the enum
    enum states { menu, playGame, gameOver, enterHighScore };
    states gameState = menu;
    
    /*********************************
    Start the game
    *********************************/
    while(window.isOpen()) {
        
        deltaTime = clock.restart().asSeconds();
        
        sf::Event evnt;
        while(window.pollEvent(evnt)) {
            if(evnt.type == sf::Event::Closed) {
                window.close();
            }
            if(gameState == enterHighScore && evnt.type == sf::Event::TextEntered) {
                if (evnt.text.unicode == 8 || (evnt.text.unicode > 31 && evnt.text.unicode < 127)) {
                    highScoreEntryBox.enterText(static_cast<char>(evnt.text.unicode));
                }
            }
        }
    
        window.clear();
        
        
        
        switch(gameState) {
            case menu:
                window.draw(startMenu);
                state = startMenu.run(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
                
                //ADDNEW: comment out the old switch statement, use this instead.
                switch(state) {
                    case 0: gameState = playGame; break;
                    //case 1:
                    case 2:
                        //Mute/unmute Music
                        dogsVsCats.toggleMuteMusic();
                        break;
                    case 3:
                        //Mute/unmute SFX
                        highScoreEntryBox.toggleMuteSfx();
                        dogsVsCats.toggleMuteSfx();
                        gameOverScreen.toggleMuteSfx();
                        break;
                    case 4:
                        //difficulty++;
                        dogsVsCats.increaseDifficulty();
                        break;
                    case 5:
                        //difficulty--;
                        dogsVsCats.decreaseDifficulty();
                        break;
                }
                
                break;
            
                           
            case playGame:
                
                dogsVsCats.run(window);
                //ADDNEW: change to gameOver, not menu
                //gameState = menu;
                gameState = gameOver;
                temp.setScore(dogsVsCats.getScore());
                highScoreEntryBox.setScoreValue(dogsVsCats.getScore());
                
               break;
                
                
            //ADDNEW: add this case gameOver
            case gameOver:
                gameOverScreen.setScore(dogsVsCats.getScore());
                window.draw(gameOverScreen);
                if(gameOverScreen.run(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                    if(startMenu.isHighScore(temp)) {
                        gameState = enterHighScore;
                        highScoreEntryBox.setScoreValue(dogsVsCats.getScore());
                    } else {
                        gameState = menu;
                    }
                }
                
                deltaTime = clock.restart().asSeconds();
                
                break;
                
            case enterHighScore:
                
                window.draw(highScoreEntryBox);
                if(highScoreEntryBox.run(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), deltaTime)) {
                    gameState = menu;
                    temp = highScoreEntryBox.getScore();
                    startMenu.updateScores(temp);
                }
                
                
                break;
                
        }
        window.display();
    }
}
