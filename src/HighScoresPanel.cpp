#include "HighScoresPanel.hpp"

/*********************************
 Draws the high scores panel.
 *********************************/
void HighScoresPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(panel);
    target.draw(scoresText);
}

/*********************************
Constructor.
 Sets up everything according to the
 window size.
 Calls a function to read in an
 existing High Scores file.
*********************************/
HighScoresPanel::HighScoresPanel(sf::Vector2f windowSize) {
    sf::Vector2f buttonSize(windowSize.x / 1920.0f * 600.0f, windowSize.y / 1080.0f * 135.0f);
    sf::Vector2f centerButtonPos(windowSize.x / 1920.0f * 1350.0f - buttonSize.x / 2, windowSize.y / 1080.0f * 700.0f - buttonSize.y / 2);

    try {
        setPanelTexture(panelTexturePath);
        setFont(fontPath);
    } catch (const std::string& fileName) {
        std::cerr << "Unable to open file " << fileName << std::endl;
        std::cerr << "Location: HighScoresPanel "<< std::endl;
        exit(1);
    }
    
    panel.setSize(sf::Vector2f(buttonSize.x, buttonSize.y * 3.7f));
    panel.setPosition(sf::Vector2f(centerButtonPos.x, centerButtonPos.y - buttonSize.y * 4.0f));
    
    scoresText.setCharacterSize(static_cast<unsigned int>(panel.getSize().y / 18));
    scoresText.setLineSpacing(1.5f);
    scoresText.setFillColor(sf::Color(107, 16, 16));
    scoresText.setPosition(panel.getPosition().x + scoresText.getCharacterSize() * 1.2f, panel.getPosition().y + scoresText.getCharacterSize() * 3.0f);
    
    try {
        readHighScoresFile();
    } catch (const std::string& fileName) {
        std::cout << "Unable to open existing high scores file " << fileName << std::endl;
        std::cout << "Starting game with a new high scores panel." << std::endl;
    }
}

/*********************************
Reads in a High Scores file.
 Stores the scores into the multiset.
 Throws the name of the file if it
 is missing.
*********************************/
void HighScoresPanel::readHighScoresFile() {
    std::ifstream fin(highScoreFilePath.c_str(), std::ios::binary);
    int numScores = 0;
    Score temp;
    
    if(!fin) {
        throw(std::string(highScoreFilePath));
    }

    while(fin.peek() != EOF && numScores < maxScores) {
        fin.read(reinterpret_cast<char *>(&temp), sizeof(Score));
        scores.insert(temp);
        numScores++;
    }
    
    fin.close();
    
    updateScoresText();
}

/*********************************
Writes the multiset of Scores
 into a file. (Clears the original
 file first).
*********************************/
void HighScoresPanel::writeHighScoresFile() {
    remove(highScoreFilePath.c_str());
            
    std::ofstream fout(highScoreFilePath.c_str(), std::ios::binary);
    if(!fout) {
        std::cout << "Unable to open output file " << highScoreFilePath << std::endl;
        exit(1);
    }
        
    for(auto i = scores.cbegin(); i != scores.cend(); i++) {
        fout.write(reinterpret_cast<const char *>(&(*i)), sizeof(Score));
    }
    
    fout.close();
}

/*********************************
Updates the High Scores Panel
 with a new score.
Deletes the lowest score
 if the number of scores exceeds
 the maximum number of scores.
Calls the function to write the
 new scores into the file.
*********************************/
void HighScoresPanel::update(const Score& s) {
    
    scores.insert(s);
    
    if(scores.size() > maxScores) {
        auto pos = scores.end();
        pos--;
        scores.erase(pos);
    }
        
    updateScoresText();
    
    writeHighScoresFile();
}

/*********************************
Sets the texture for the panel.
 Throws the path of file if it isn't found.
*********************************/
void HighScoresPanel::setPanelTexture(std::string path) {
    if(!panelTexture.loadFromFile(path.c_str())) {
        throw(std::string(path));
    }
    panel.setTexture(&panelTexture);
}

/*********************************
Sets the font for the text.
 Throws the path of file if it isn't found.
*********************************/
void HighScoresPanel::setFont(std::string path) {
    if(!textFont.loadFromFile(path.c_str())) {
        throw(std::string(path));
    }
    scoresText.setFont(textFont);
}

/*********************************
Updates the scores text that will
 be displayed according to the scores data
 currently stored.
*********************************/
void HighScoresPanel::updateScoresText() {
    std::ostringstream output;
    int curr = 1;
    for(auto i = scores.cbegin(); i != scores.cend(); i++, curr++) {
        output << std::left << std::setw(3) << std::to_string(curr);
        output << static_cast<std::string>(*i) << "\n";
    }
    scoresText.setString(output.str());
}

/*********************************
Compares a given score with the scores
 that are stored.
Returns true if the given score is higher
 than some stored score, returns false
 if it is lower than all stored scores.
*********************************/
bool HighScoresPanel::isHighScore(const Score& s) const {
    bool isHigh = false;
    
    if(scores.size() < maxScores) {
        isHigh = true;
    } else {
        for(auto i = scores.cbegin(); i != scores.cend() && isHigh == false; i++) {
            if(s > (*i)) {
                isHigh = true;
            }
        }
    }
    
    return isHigh;
}
