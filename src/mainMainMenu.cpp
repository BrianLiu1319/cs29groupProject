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

using namespace std;

//const std::string spriteSheet = assetFolder + "dog01.png";

int main() {
    
    /*********************************
    Create a RenderWindow and Game
    *********************************/
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Dogs vs Cats", sf::Style::Titlebar | sf::Style::Resize);//sf::Style::Close);
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
    
    /*********************************
    Set up the clock
    *********************************/
    float deltaTime = 0.0f;
    sf::Clock clock;
    
    //just some testing for animation I did last time:
    /*
    sf::Sprite tempSprite;
    sf::Texture spriteTexture;
    if(!spriteTexture.loadFromFile(spriteSheet)) {
        std::cerr << "JDLHFJDHFDJHD" << std::endl;
        exit(1);
    }
    tempSprite.setTexture(spriteTexture);
    tempSprite.setScale(0.4f, 0.4f);
    
    //test animation
    Animation spriteAnimator(&spriteTexture, sf::Vector2u(10, 5), 1.0f / 6.0f);
    spriteAnimator.setNumOfSpritesInRow(1, 8);
     */
    
    
    /*********************************
     The current state of the game.
     - menu
     - play game
     - enter high score
     - game over
     *********************************/
    enum states { menu, playGame, enterHighScore };
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
                
                switch(state) {
                    case 0: gameState = playGame; break;
                    //case 1:
                    //case 2:
                    case 3:
                        highScoreEntryBox.toggleMuteSfx();
                        dogsVsCats.toggleMuteSfx();
                        break;
                        
                }
                //note to self: after integration, make sure "enterHighScore" is only triggered if the player has achieved a high score (use the isHighScore function in mainMenu to check)
                
                //temporary animation for testing:
                //spriteAnimator.setLoop(false);
                //spriteAnimator.update(3, deltaTime);
                //tempSprite.setTextureRect(spriteAnimator.uvRect);
                //window.draw(tempSprite);
                
                break;
            
                           
            case playGame:
                
                dogsVsCats.run(window);
                gameState = menu;
                temp.setScore(dogsVsCats.getScore());
                highScoreEntryBox.setScoreValue(dogsVsCats.getScore());
                
                if(startMenu.isHighScore(temp)) {
                    gameState = enterHighScore;
                    highScoreEntryBox.setScoreValue(dogsVsCats.getScore());
                } else {
                    gameState = menu;
                }
                
                deltaTime = clock.restart().asSeconds();
                 
                            
               //insert main game here!!!!
               
               //temporary animation for testing:
                /*
                spriteAnimator.setLoop(true);
                spriteAnimator.update(1, deltaTime);
                tempSprite.setTextureRect(spriteAnimator.uvRect);
                window.draw(tempSprite);
                 */
               
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