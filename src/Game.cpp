#include "Game.hpp"

//ADDNEW: add the tools(windowSize)
//ADDNEW2 add statsDisplay(windowSize)
Game::Game(sf::Vector2f windowSize) : Menu(windowSize), tools(windowSize), statsDisplay(windowSize) {
    try {
        setClickSound(clickSFXPath01);
        //ADDNEW (for sfx and music!!)
        setBgMusic();
        //ADDNEW (for bg)
        setBgTexture(bgTexturePath);
    }
    catch (const std::string& fileName) {
        std::cerr << "Unable to open the file " << fileName << std::endl;
        std::cerr << "Location: Game" << std::endl;
        exit(1);
    }
}

vector<Land*> Game::genrateLandList() {
    vector<Land*>landList = {};
    sf::Vector2f tempPosition;
    int x = 50; int y = 50;
    for (int i = 0; i < 60; i++)
    {
        tempPosition.x = x;
        tempPosition.y = y;
        Land* aland = new  Land(i, tempPosition);
        landList.push_back(aland);
        y += 94;

        if (y > 480) // Here, it checks if the grid doesn't exist and we go back down.
        {
            y = 50;
            x += 74;
        }
    }
    return landList;
}

// This function create a inventory vector which stores all inventory
vector<Inventory*> Game::generateInvenList()
{
    vector<Inventory*> InvenList = {};
    Vector2f aPosition;
    Inventory* aInven = NULL;
    int x = 50; int y = 600;
    for (int i = 0; i < 2; i++)
    {
        aPosition.x = x;
        aPosition.y = y;
        aInven = new Inventory(aPosition, i);
        InvenList.push_back(aInven);
        x += 60;
    }
    return InvenList;
}

// Same as above but with Defender class instead of the old tower class.
//Generate the list of towers. Prebuilds a list of towers to use.
// Used to just add towers to built tower list. Currently, I don't use this, for testing purposes.
vector<Defender*> Game::generateTowerList(vector <Land*> landList)
{
    vector<Defender*> towerList = {};
    sf::Vector2f temp;
    int x = 0;
    int y = 0;
    for (int i = 0; i < 30; i++)
    {
        temp.x = landList[i]->getVector().x;
        temp.y = landList[i]->getVector().y;

        //Tower* aInven = new Tower(temp);
        //towerList.push_back(aInven);
        Defender* aInven = new Defender(temp);
        towerList.push_back(aInven);
    }
    return towerList;

}

//this function cauculate how many towers we could build. Currently I just set it to just return 1, since I haven't made the cost yet.

int Game::howManyTower(int money)  // PROBLEM TO FIX: Add a Cost to the Defender class and replace this function with a defender instead of tower.
{
    /*
    Tower* aTower = new Tower();       // Use this as a reference and replace with Defender instead.
    int cost = aTower->getCost();
    vector<Tower*> TowerList = {};
    int amount = money / cost;
    //return amount;
    */
    return 1; // Just returns 1 for test purposes. Remove this for "amount" instead.

}

// Take a selected land and build the tower on this land. Return the pointer of this tower
// PROBLEM: Issue is dynanmic memory. We need to delete this after!!!
Defender* Game::defenderBuild(Land* aLand)
{
    Vector2f temp;
    temp = aLand->getSprite().getOrigin();
    Defender* aDefender = new Defender(aLand->getVector());
    return aDefender;

}

coinMaker* Game::buildCoinMaker(Land* land)
{
    Vector2f landPosi = land->getVector();
    coinMaker* aMaker = new coinMaker(landPosi);
    return aMaker;
}

void Game::coinCollectin(vector<coinMaker*>& makerList)
{
    int moneyGrowth = 0;
    for (int i = 0; i < makerList.size(); i++)
    {

        if (makerList[i]->howmanyCoininBox() > 0)	//if the coinmaker has coins. 
        {
            moneyGrowth += makerList[i]->clearCoin();	//the groth money += every coinmaker's coin
        }
    }
    money += moneyGrowth;
    return;

}

//ADDNEW I commented out the other wave generator for now
/*
void Game::enmyReminder(string txt, RenderWindow& renderWindow)
{
    Text showWave;
    string show = txt;
    showWave.setFont(font1);
    showWave.setFillColor(sf::Color::Red);
    showWave.setString(show);
    showWave.setPosition(700, 900);
    showWave.setCharacterSize(40);
    showWave.setStyle(sf::Text::Regular);

    renderWindow.draw(showWave);
    return;
}
 */

/*
void Game::randomGenerCats(const vector <Land*>& landList, vector <Attacker*>& allAttackers)
{
    threadLock.lock();
    Vector2f landTempVec;
    srand((unsigned)time(NULL)); //waste memory
    int tempLandIndex;
    tempLandIndex = rand() % 30;
    landTempVec = landList[tempLandIndex]->getVector();
    addAttacker(allAttackers, landList[tempLandIndex]->getVector());
    threadLock.unlock();
    return;
}
 */

/*
int Game::wave(string special)
{
    int catMakerSped;
    if (special == "F")//final wave began at 5th min. speed
    {
        catMakerSped = 5;

    }
    else if (special == "n") //normal
    {
        catMakerSped = 10;
    }
    else
    {
        return 50;
    }
    return catMakerSped;
}
 */

/*
//void Game::regularGenerAttacter(vector <Land*>* aLandList, vector <Attacker*>& allAttackers)
void Game::regularGenerAttacter(MyStruct* ms)
{
    while (gaming)
    {
        //this thread only work when there's no cat corps.
        if (waving == false)
        {
            //1 cats are generated in 5 second
            for (int i = 0; i < 50; i++) //5 second 1 cats.
            {
                if (!gaming)
                    break;
                sleep(milliseconds(100));

            }
            //generate cat on a random line. 
            randomGenerCats(*ms->lands, *ms->attackers);
        }
    }
    ms = nullptr;
}
 */

/*
//void Game::generateAttacter(vector <Land*>* aLandList, vector <Attacker*>& allAttackers)
void Game::generateAttacter(MyStruct* ms)
{
    bool waveSwitch;
    clock_t start, finish;
    clock_t waveStart, waveFinish;
    int secInAMin;
    start = clock();// game begin
    int sec;
    int secInWave;

    while (gaming)
    {
        waving = false;
        finish = clock(); //timing
        sec = (finish - start) / CLOCKS_PER_SEC; // this varible show how many seconds have escaped since game began. 
        secInAMin = sec % 60;//this varible show the seconds of a min.like: the 5th second of the second min.

        waveSwitch = true;
        //wave begain
        while (secInAMin == 5 && sec > 30 && waveSwitch == true)// if thime is 5th second of a min. and it'nt the first min. and switch is on. A wave of cat coming.
        {
            waveGrade++;
            waveStart = clock();				//the wave timer is tiking. I set the length of a wave is 30 second.
            secInWave = 0;
            while (secInWave < 30)				//if the length of a wave is shorter than 30 second.wave continue			
            {
                waving = true;					//waving time is coming. if this global varible is true the regular generater gona stop working.
                if (sec < 3000)					//if the gaming time is shorter than 5 min. we only do the normal wave
                {

                    for (int i = 0; i < wave("n"); i++) //1 second 1 cat.// this is normal wave.
                    {
                        if (!gaming)
                            break;
                        sleep(milliseconds(100));//10* 100 millseconds == 1second

                    }
                    randomGenerCats(*ms->lands, *ms->attackers);
                }
                //the last wave is at 5th min
                else {

                    for (int i = 0; i < wave("F"); i++) //1 second 2 cats.
                    {
                        if (!gaming)
                            break;
                        sleep(milliseconds(100));//5* 100 == 500millsecond == 0.5second
                    }
                    //randomGenerCats(*aLandList, allAttackers);
                    randomGenerCats(*ms->lands, *ms->attackers);
                }
                waveFinish = clock();							//this varible take the lenght of waving time.
                secInWave = (waveFinish - waveStart) / CLOCKS_PER_SEC;
            }
            if (secInWave >= 30)							//if the waving time longer than 30. this wave should stop.
            {
                waveSwitch = false;
                waving = false;

            }

        }
    }
}
 */

//this function draw all the towers which we have alrady built. Currently we don't need this, only for testing purposes.
void Game::drawBuiltDefender(vector <Defender*> builtTowerList, RenderWindow& renderWindow)
{
    for (int i = 0; i < builtTowerList.size(); i++)
    {
        renderWindow.draw(*builtTowerList[i]); ////////// work on this!!!
    }
};

//ADDNEW2 added a bunch of stuff in this function
void Game::simpleAttackerGenerator(vector<Attacker*>& attackers, const vector<Land*>& landList) {
    
    int numCatsPerWave = 8 + currentWave;

    if (waveStart) {
        
        statsDisplay.updateWave(currentWave);
        
        auto temp = generatorClock.restart().asSeconds();
        deltaGenTime += temp;
        waveGenTime += temp;
        
        
        
        //Create time frame of 10-15 seconds
        //ADDNEW : change randomTimeframe into float
        float randomTimeframe = static_cast<float>(rand() % 5 + 10.0f);
        //ADDNEW : the more waves there are, the less the timeframe will be
        randomTimeframe -= currentWave * 0.5f;

        //ADDNEW2 moved this if statement up, changed some stuff
        //so that enemies don't spawn all at once
        //and instead spawn more frequently during a wave
        if (waveGenTime >= static_cast<float>(randomTimeframe) * 5 / difficulty * 1.5f) {
            //ADDNEW count the number of waves
            if (numDogsInBigWave < numCatsPerWave) {
                randomTimeframe *= 0.3f;
                onWave = true;
                //int tempLandIndex = rand() % landList.size();
                //addAttacker(attackers, landList[tempLandIndex]->getVector());
            }
            else {
                numDogsInBigWave = 0;
                waveGenTime = 0.0f;
                currentWave++;
                onWave = false;
            }
        }
        
        if (deltaGenTime >= static_cast<float>(randomTimeframe) / difficulty * 1.5f) {
            int tempLandIndex = rand() % landList.size();
            addAttacker(attackers, landList[tempLandIndex]->getVector());
            deltaGenTime = 0;
            if(onWave) numDogsInBigWave++;
        }

        


    }

}

//ADDNEW2 no long needed:
//This function define a textview that shows the how much money user has.
/*
void Game::showMoney(int money, RenderWindow& renderWindow)
{
    Text showMoney;
    string show = "Money:  " + to_string(money) + "\nScore:  " + to_string(score);
    showMoney.setFont(font1);
    showMoney.setFillColor(sf::Color::Red);
    showMoney.setString(show);
    showMoney.setPosition(1000, 200);
    showMoney.setCharacterSize(20);
    showMoney.setStyle(sf::Text::Regular);
    renderWindow.draw(showMoney);
}
 */

// Draws, erases if out of screen, and updates accordingly.
void Game::gameClock(RenderWindow& window, vector<Collider*>& things) {

    if (things.empty())
    {
        return;
    }
    for (int i = 0; i < things.size(); i++)
    {
        things[i]->updateObject();
        // Add dynamic cast for attacker for game over
        if (dynamic_cast<Attacker*>(things[i]) != nullptr)
        {
            if ((things[i])->getPosition().x > WINDOW_WIDTH + (things[i])->getGlobalBounds().width || (things[i])->getPosition().x < -100)
            {
                gameOver = true;
                return;
                //exit(-420);
            }
        }
        if ((things[i])->getPosition().x > WINDOW_WIDTH + (things[i])->getGlobalBounds().width || (things[i])->getPosition().x < -100)
        {
            things.erase(things.begin() + i);
        }
        else
        {
            //window.draw(*things[i]);


            if (things[i]->getMaker() == true)
            {
                window.draw(*things[i]);
                if (things[i]->howmanyCoininBox() > 0)
                {
                    things[i]->drawCoins(window);
                }

            }
            else {
                threadLock.lock();
                window.draw(*things[i]);
                threadLock.unlock();
            }


        }
    }
}


void Game::checkCollision(vector<Attacker*>& attackers, vector<Bullet*>& bullets, vector<Defender*>& defenders, vector<coinMaker*>& makers)
{
    // Add a temp to all the vectors to ensure never crash!
    if (attackers.empty())
    {
        return;
    }
    bool getOut = false;

    for (unsigned int j = 0; j < attackers.size(); j++)
    {
        for (unsigned int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i]->getGlobalBounds().intersects(attackers[j]->getGlobalBounds()))
            {
                bullets[i]->hurt(*(attackers[j]));
                cout << attackers[j]->getHealth() << endl;
                
                //ADDNEW3 sfx
                if(!muteSfx) bullets[i]->playSfx();
                
                if (attackers[j]->getHealth() <= 0 && !attackers[j]->isOnDefeat())
                {
                    //ADDNEW2 attackers stutter if they're hit multiple times when defeated
                    //it's fixed now.
                    attackers[j]->setDefeated();
                    if(!muteSfx) attackers[j]->sadSound();
                    //attackers.erase(attackers.begin() + j);

                    //Higher difficulty rewards more points!
                    //ADDNEW: changed score values to be more rewarding
                    //adjust it if you feel it's needed : ))
                    switch (difficulty) {
                    case 1:
                        score += 100;
                        break;
                    case 2:
                        score += 200;
                        break;
                    case 3:
                        score += 300;
                        break;
                    }
                    getOut = true;
                }
                bullets.erase(bullets.begin() + i);
                break;
            }
        }
        if (getOut)
        {
            getOut = false;
            break;
        }

        if (attackers.empty())
        {
            return;
        }

        // DEFNDER GONE STOPS RUNNING
        for (unsigned int k = 0; k < defenders.size(); k++)
        {
            if (defenders.empty()) break;
            if (attackers[j]->getGlobalBounds().intersects(defenders[k]->getGlobalBounds()) && defenders[k]->getStatus())
            {
                cout << "Cmere" << endl;
                attackers[j]->setDirection(TWR);
                if (defenders[k]->getHealth() <= 0 && defenders[k]->getStatus())
                {
                    //ADDNEW3 sfx
                    if(!muteSfx) defenders[k]->sadSound();
                    
                    for (unsigned int z = 0; z < attackers.size(); z++)
                    {
                        if (attackers[z]->getGlobalBounds().intersects(defenders[k]->getGlobalBounds()))
                            attackers[z]->setDirection(LEFT);
                    }
                    //defenders.erase(defenders.begin() + k);

                    //****************************
                    //  ISSUE: Repeat setDefeated makes stutter in animation 
                    //****************************

                    defenders[k]->setDefeated();
                    defenders[k]->setStatus();  // Bugs out when this is played, meaning it needs to loop the for loop in line
                                                  // 250 to setDirection back to left since some cats get stuck...

                }

            }
        }

        /*
        for (unsigned int k = 0; k < makers.size(); k++)
        {
            if (makers.empty()) break;
            if (attackers[j]->getGlobalBounds().intersects(makers[k]->getGlobalBounds()) && makers[k]->getStatus())
            {
                cout << "Cmere" << endl;
                attackers[j]->setDirection(TWR);
                if (makers[k]->getHealth() <= 0 && makers[k]->getStatus())
                {
                    for (unsigned int z = 0; z < attackers.size(); z++)
                    {
                        if (attackers[z]->getGlobalBounds().intersects(makers[k]->getGlobalBounds()))
                            attackers[z]->setDirection(LEFT);
                    }


                    makers[k]->setDefeated();
                    makers[k]->setStatus();  // Bugs out when this is played, meaning it needs to loop the for loop in line
                                                  // 250 to setDirection back to left since some cats get stuck...
                }
            }
        }


    }
}
*/
    }
}

void Game::addBullet(vector<Bullet*>& things) {
    cout << "Adding the new boi" << endl;
    auto* temp = new Bullet();
    things.push_back(temp);
    cout << "End of new boi" << endl;
}

int Game::run(RenderWindow& renderWindow) {

    //RenderWindow renderWindow(VideoMode(1000, 1000), "Dogs vs Cats");

    Thread* regular = nullptr; // this is a thread control general enemies(not wave)(Steven)
    gameOver = false;
    score = 0;
    //ADDNEW: reset deltaGenTime waveGenTime and generatorClock
    deltaGenTime = 0.0f;
    waveGenTime = 0.0f;
    generatorClock.restart();
    waveStart = false;
    //ADDNEW: reset money
    money = 200;
    //ADDNEW2 set to countdown and reset number of waves
    statsDisplay.setCountdownMode();
    currentWave = 1;

    sf::Texture textureOfObject;
    textureOfObject.loadFromFile(assetFolder + "bul.png");
    //textureOfObject
    //renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setFramerateLimit(60);

    //ADDNEW: Change the output
    if (!font1.loadFromFile(assetFolder + "Font1.ttf"))
        //cout << "error HAHAHA " << endl;
        cout << "Unable to open font file " << assetFolder + "Font1.ttf" << endl;

    int towerInStore = 2;
    int time = 0;
    Clock* clock = new Clock();
    // define a land
    sf::Vector2f landPoint(50.f, 50.f);
    Land* aLand = new Land(0, landPoint);

    // Land and Inventory Vectors
    vector <Land*> landList;        //vector to store the land, you can think this vector is the grass grid!
    vector<Inventory*> InvenList;

    /* // Unused but left for archive
    vector<Tower*> towerList;        //This ia a vector stores all towers
    vector<Tower*> builtTowerList;// this a vector only stores the towers which has been built;
    */

    // Vectors of the main subjects, allBullets // allAttackers // allDefenders
    vector<Bullet*> allBullets = {};
    vector<Attacker*> allAttackers = {};
    vector<Defender*> allDefenders = {}; // List of all defenders. Could implement this in the future.
    vector<Defender*> builtDefenderList = {}; // Have a seperate list for built Towers to differentiate.

    // Added 3/15
    vector<coinMaker*> builtMaker = {};

    int nInvenselected = -1;        //This int is a counter; represent the Inventory user selected; if user didnt select; it is -1;
    InvenList = generateInvenList();    // creat the Inventory list
    landList = genrateLandList();        // creat land list

    //allDefenders = generateTowerList(landList);    // creat towerList, maybe this can be of use?

    // Line to use for seperating space between inventory and grid? Unsure
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(0, 0)),
        sf::Vertex(sf::Vector2f(500, 500))
    };

    line->color = Color(256, 256, 0);

    // int counter used for selection.
    int nSelected = -1;

    // Temp values used in the main.

    //Tower* pTower = NULL;
    //Tower* pTowerHolder = NULL;
    Defender* tempDefender = NULL;
    Defender* pDefenderHolder = NULL;
    int tempLandIndex;
    sf::Vector2f landTempVec;

    while (!gameOver && renderWindow.isOpen())
    {
        animationDeltaTime = animationClock.restart().asSeconds();
        
        //ADDNEW
        //Play background music
        if(!muteMusic && bgMusic.getStatus() != sf::Sound::Playing) {
            bgMusic.play();
        }
        if(muteMusic && bgMusic.getStatus() != sf::Sound::Stopped) {
            bgMusic.stop();
        }

        while (renderWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                renderWindow.close();
                break;
            case Event::KeyPressed:
                    //ADDNEW get rid of this, we can use shift+m instead ^^
                    /*
                if (Keyboard::isKeyPressed(Keyboard::M))
                {
                    tempLandIndex = rand() % 30;
                    landTempVec = landList[tempLandIndex]->getVector();
                    addAttacker(allAttackers, landList[tempLandIndex]->getVector());  // this should be called with game clock
                }
                     */
                if ((Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift)) && Keyboard::isKeyPressed(Keyboard::X)) {
                    gameOver = true;
                }
                if ((Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift)) && Keyboard::isKeyPressed(Keyboard::S)) {
                    score += 10;
                }
                if ((Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift)) && Keyboard::isKeyPressed(Keyboard::C)) {
                    money += 10;
                }   
                if ((Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift)) && Keyboard::isKeyPressed(Keyboard::M))
                {
                    tempLandIndex = rand() % 30;
                    landTempVec = landList[tempLandIndex]->getVector();
                    addAttacker(allAttackers, landList[tempLandIndex]->getVector());  // this should be called with game clock
                }

                //testing
                    //ADDNEW
                    //NEED TO CHANGE THIS
                    //so, there's a loophole in which the player
                    //can just put coinmakers and stock up on coins
                    //before starting, thus making the game easy
                    
                    //ADDNEW2 Deleted this. Now, there's a countdown before Cats appear.
                    /*
                if (Keyboard::isKeyPressed(Keyboard::S)) {
                    waveStart = true;
                    generatorClock.restart();
                    cout << "START!!" << endl;
                }
                     */
            }
        }
        
        //ADDNEW2 countdown timer!
        if(!waveStart) {
            deltaGenTime += generatorClock.restart().asSeconds();
            statsDisplay.updateCountdown(static_cast<int>(deltaGenTime));
            if(deltaGenTime >= 10.0f) {
                waveStart = true;
                deltaGenTime = 0.0f;
                statsDisplay.setWaveMode();
            }
        }
        
        

        /*
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            //start two thread to generate enemies
            if (!regular)// (non-wave cats)skirmisher
            {
                MyStruct* ms = new MyStruct;
                ms->attackers = &allAttackers;
                ms->lands = &landList;
                //regular = new Thread(&Game::regularGenerAttacter,ms); //regular = new Thread(&Game::regularGenerAttacter,this); ??
                regular->launch();

            }
            if (!a_TGenerate)//(wave cats) corps
            {
                MyStruct* ms = new MyStruct;
                ms->attackers = &allAttackers;
                ms->lands = &landList;
                //a_TGenerate = new Thread(&Game::generateAttacter, ms);
                a_TGenerate->launch();

            }

        }
        */
        renderWindow.clear();
        
        //ADDNEW commented this out for now
        /*
        if (waving == true)
        {
            string wavegraderemind = " Wave " + to_string(waveGrade);
            enmyReminder(wavegraderemind, renderWindow);
        }
        */
        
        //ADDNEW draw the background before land!
        renderWindow.draw(background);
        
        // draw the landList(grid) by a for loop
        for (int i = 0; i < 60; i++)
        {
            renderWindow.draw(landList[i]->getSprite());
        }

        //draw InvenList below the grid
        for (int i = 0; i < 2; i++)
        {
            renderWindow.draw(InvenList[i]->getSprite());
        }
        
        //ADDNEW2 not needed anymore
        //showMoney(money, renderWindow);
        
        //ADDNEW for toolbar and enemy generator
        handleTools(builtDefenderList, landList, renderWindow);
        simpleAttackerGenerator(allAttackers, landList);


        // Checks to see if you clicked a inventory dog.
        if (Mouse::isButtonPressed(sf::Mouse::Left))
        //if (event.type == Event::EventType::MouseButtonPressed)
        {
            Vector2i mousePressPosition = Mouse::getPosition(renderWindow);
            for (int i = 0; i < 2; i++)
            {
                Sprite InvenSp = InvenList[i]->getSprite();
                if (InvenSp.getGlobalBounds().contains(mousePressPosition.x, mousePressPosition.y))// if the range of a inventory contain the position of mouse
                {
                    if (!muteSfx && click.getStatus() != sf::Sound::Playing) click.play();
                    if (towerInStore > 0)
                    {
                        nInvenselected = i;                                                        // the selected Inventory is i
                    }
                    break;
                }
            }

        }

        // Checks where you clicked to select a grid slot to place tower.
        if (Mouse::isButtonPressed(sf::Mouse::Left) && nInvenselected != -1)// mouse event
        //if (event.type == Event::EventType::MouseButtonReleased && nInvenselected != -1)
        {
            Vector2i mouseRepostion = Mouse::getPosition(renderWindow);// get the relative position of mouse (get where custom release button)
            //that's also where user want to build a tower

            for (int i = 0; i < 60; i++)//traverse the land list
            {
                Sprite landSprit = landList[i]->getSprite();
                if (landSprit.getGlobalBounds().contains(mouseRepostion.x, mouseRepostion.y))// if the range of land contain the position of mouse
                {
                    if (!muteSfx && click.getStatus() != sf::Sound::Playing) click.play();
                    nSelected = i;                                                        // the selected land is i
                    break;
                }
            }
        }

        // If you selected a inventory dog AND a grid spot, create and place a tower there.
        if (nSelected >= 0 && nSelected < 60 && nInvenselected<2 && nInvenselected>-1 && landList[nSelected]->getEnpty() == true)// make sure the selected code is inthe range of 0-30, the inventory shouldnt be -1
        {
            tempDefender = defenderBuild(landList[nSelected]);  //
            coinMaker* aMaker = buildCoinMaker(landList[nSelected]);
  
                if (nInvenselected == 0 && money >= tempDefender->getCost())
                {
                    landList[nSelected]->setEmpty(false); //set the empty of a land to false, prevent from being repeatly use
                    //ADDNEW2 set land index
                    tempDefender->setLandIndex(nSelected);
                    builtDefenderList.push_back(tempDefender);


                    //money -= towerList[nSelected]->getCost();		// user' money should minus the cost of selected tower default cost of a tower is 40;
                    //PROBLEM: Work on money ^, consider working on Defender functions with cost members.
                    money -= tempDefender->getCost();
                    nInvenselected = -1;							//now we finish all things we should make nInven back to -1; To prepare for next action;
                    nSelected = -1;									//the selected land should also back to -1 
                    towerInStore = howManyTower(money);			// this statement get how many tower we can build with rest money
                    
                    //ADDNEW3 for sfx
                    if(!muteSfx) tempDefender->bark();

                }
                //money maker

                else if (nInvenselected == 1 && money >= aMaker->getCost())
                {
                    landList[nSelected]->setEmpty(false);
                    //give the land position to get a coinmaker
                    builtMaker.push_back(aMaker);//put the maker in the makerlist
                    money -= aMaker->getCost();	//make coinmaker cost money
                    nSelected = -1;				//selected land is back to -1; for next operation
                    nInvenselected = -1;		//also iventory button back to -1;
                    
                    //NOTE: ADDNEW3
                    //
                    //
                    //Add coinmaker.bark() once it's derived from Defender!
                    //
                    //
                    //
                    //

                }

                else
                {

                }
                nSelected = -1;				//selected land is back to -1; for next operation
                nInvenselected = -1;		//also iventory button back to -1;
                aMaker = nullptr;	//set temp maker to null.
                tempDefender = nullptr;
  
        }

    // Fires every 1 second a bullet. Currently, the fire function creates bullets in the same spot
    // PROBLEM: Makes bullets position in it's constructor take the vector of Tower.

        if (builtDefenderList.size() > 0)  // If the number of towers that have been built is not zero, we fire
        {
            for (unsigned int i = 0; i < builtDefenderList.size(); i++)
            {
                if (clock->getElapsedTime().asMilliseconds() >= 2000)
                {
                    cout << allBullets.size() << endl;
                    if (clock->getElapsedTime().asMilliseconds() >= 2000) {// if time > = 5 sec // Time constraint, ho

                        auto* temp = new Bullet(textureOfObject, builtDefenderList[i]->getPosition());
                        allBullets.push_back(temp);

                        for (unsigned int l = 0; l < allAttackers.size(); l++)
                        {
                            // Purpose is to check for collision in here.
                            if (allAttackers[l]->getGlobalBounds().intersects(builtDefenderList[i]->getGlobalBounds()))
                            {
                                allAttackers[l]->hurt(*(builtDefenderList[i]));
                                cout << builtDefenderList[i]->getHealth() << endl;
                                cout << "HITTEM!! " << "THE DOG HP IS NOW " << builtDefenderList[i]->getHealth() << endl;
                            }
                        }
                    }
                    cout << "End of fire" << endl;
                }
            }

            if (clock->getElapsedTime().asMilliseconds() >= 2000)
            {
                clock->restart();
            }
        }
        // Added 3-15
        if (Keyboard::isKeyPressed(Keyboard::C))
        {

            coinCollectin(builtMaker); //call collection function

        }

        simpleAttackerGenerator(allAttackers,landList);
        //Update Animations and erase defeated Cats/Dogs
        updateAnimations(builtDefenderList, allAttackers, landList);

        // Use this to update, erase, and draw all the respective Bullets, Defenders, and Attackers.
        gameClock(renderWindow, reinterpret_cast<vector<class Collider*> &> (allBullets));
        gameClock(renderWindow, reinterpret_cast<vector<class Collider*> &> (builtDefenderList));
        gameClock(renderWindow, reinterpret_cast<vector<class Collider*> &> (allAttackers));
        gameClock(renderWindow, reinterpret_cast<vector<class Collider*>&> (builtMaker));
        checkCollision(allAttackers, allBullets, builtDefenderList, builtMaker);
        
        //ADDNEW2
        statsDisplay.updateMoney(money);
        statsDisplay.updateScore(score);
        renderWindow.draw(statsDisplay);
        
        renderWindow.display();
    }

    //ADDNEW
    //Stop background music
    if(bgMusic.getStatus() != sf::Sound::Stopped) {
        bgMusic.stop();
    }

    //Clear memory!! (There was memory leak before)
    for (int i = 0; i < allAttackers.size(); i++) {
        delete allAttackers[i];
    }
    for (int i = 0; i < allDefenders.size(); i++) {
        delete allDefenders[i];
    }
    for (int i = 0; i < allBullets.size(); i++) {
        delete allBullets[i];
    }
    for (int i = 0; i < builtDefenderList.size(); i++) {
        delete builtDefenderList[i];
    }
    delete clock;
    delete aLand;
    
    //ADDNEW commented out
    //waveStart = false;
    //bThread = false;

    /*

    while (!bExitThread)		//this make the thread sleep after user close window 
    {
        //sleep(milliseconds(100));
    }
    */

    return 0;
}

void Game::addAttacker(vector<Attacker*>& attackers) {
    auto* temp = new Attacker();
    if(!muteSfx) temp->meow();
    attackers.push_back(temp);
}

void Game::addAttacker(vector<Attacker*>& attackers, Vector2f a) {
    /*
    auto* temp = new Attacker(a);
    attackers.push_back(temp);
     */
    int temp1 = rand() % 3;
    if (temp1 == 0)
    {
        cout << "Lucky 1! " << endl;
        auto* temp = new Attacker(a, assetFolder + "catSprites1.png");
        attackers.push_back(temp);
        if(!muteSfx) temp->meow();
    }
    else if (temp1 == 1)
    {
        cout << "Lucky 2! " << endl;
        auto* temp = new Attacker(a, assetFolder + "catSprites2.png");
        attackers.push_back(temp);
        if(!muteSfx) temp->meow();    }
    else if (temp1 == 2)
    {
        cout << "Lucky 3! " << endl;
        auto* temp = new Attacker(a, assetFolder + "catSprites3.png");
        attackers.push_back(temp);
        if(!muteSfx) temp->meow();
    }
}

//ADDNEW this function shouldnt be needed (it's already inherited from Menu)
//Mutes or unmutes sfx
/*
void Game::toggleMuteSfx() {
    if (muteSfx) {
        muteSfx = false;
    }
    else {
        muteSfx = true;
    }
}
 */

//ADDNEW
//Mutes or unmutes Music
void Game::toggleMuteMusic() {
    if(muteMusic) {
        muteMusic = false;
    } else {
        muteMusic = true;
    }
}

//ADDNEW
//Sets the background music.
void Game::setBgMusic() {
    if(!bgMusic.openFromFile(bgMusicPath)) {
        throw(std::string(bgMusicPath));
    }
    
    bgMusic.setLoop(true);
    bgMusic.setVolume(15.0f);
}

/*********************
 Updates all the animations of Dogs/Cats.
 Erases any defeated ones.
 *********************/
//ADDNEW passes in a vector of landlist
void Game::updateAnimations(vector<Defender*>& defenders, vector<Attacker*>& attackers, vector<Land*>& landList) {

    //Update all Attackers
    for (int i = 0; i < attackers.size(); i++) {
        if (attackers[i]->isDefeated()) {
            threadLock.lock();
            
            //attackers[i]->
            
            delete attackers[i];
            attackers.erase(attackers.begin() + i);
            threadLock.unlock();
            cout << "Cat Dead" << endl;
        }
        else {
            attackers[i]->updateAnimation(animationDeltaTime);
        }
    }

    //Update all Defenders
    for (int i = 0; i < defenders.size(); i++) {
        if (defenders[i]->isDefeated()) {
            
            //ADDNEW: fixed a bug where after being defeated, the land isnt set to empty
            int landIndex = defenders[i]->getLandIndex();
            if(landList.size() > landIndex) {
                //cout << "SET EMPTY" << endl;
                landList[landIndex]->setEmpty(true);
            }
            
            delete defenders[i];
            defenders.erase(defenders.begin() + i);
        }
        else {
            defenders[i]->updateAnimation(animationDeltaTime);
        }
    }

}

//ADDNEW
//Handles the toolbar!
//IMPORTANT: right now the tools are ONLY called for the builtDefenderList.
//hopefully the coinmakers are in the builtDefenderList :')
void Game::handleTools(vector<Defender*>& defenders, vector<Land*>& landList, sf::RenderWindow& window) {
    
    window.draw(tools);
    tools.run(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
    Vector2i mousePressPosition = Mouse::getPosition(window);
    
    //Handle Removal Tool
    if(tools.whistleSelected()) {
        
        //if the mouse starts to click
        if(mouseStartClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mouseStartClick = false;
            if(!muteSfx) click.play();
            
            for(int i = 0; i < landList.size(); i++) {
                
                if((landList[i]->getSprite()).getGlobalBounds().contains(mousePressPosition.x, mousePressPosition.y)) {
                    //Check if the mouse is clicking on a Defender
                    for(int j = 0; j < defenders.size(); j++) {
                        
                        if(defenders[j]->getGlobalBounds().contains(mousePressPosition.x, mousePressPosition.y)) {
                            
                            //Delete Defender
                            delete defenders[j];
                            defenders.erase(defenders.begin() + j);
                            
                            //Set Land to empty
                            landList[i]->setEmpty(true);
                            
                            //Refund money
                            money += tools.getWhistleRefund();
                            
                            tools.deselectAll();
                        }
                    }
                }
            }
             
            
        } else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseStartClick) {
            mouseStartClick = true;
            tools.deselectAll();
        }
    }
    
    
    //Handle Health Tool
    if(tools.healthSelected()) {
        if(mouseStartClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mouseStartClick = false;
            if(!muteSfx) click.play();
            
            for(int i = 0; i < defenders.size(); i++) {
                
                //Check if a defender is clicked
                if(defenders[i]->getGlobalBounds().contains(mousePressPosition.x, mousePressPosition.y)) {
                    
                    //Check if money is enough
                    if(money >= tools.getHealthCost()) {
                        
                        //TEMPORARY VALUE, will balance later haha, make sure it's not op
                        (*defenders[i]).increaseHealth(100);
                        
                        money -= tools.getHealthCost();
                        
                    }
                    
                }
            }
            tools.deselectAll();
            
        }
        
    } else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseStartClick) {
        mouseStartClick = true;
        tools.deselectAll();
    }
    
}
