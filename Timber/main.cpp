//
//  main.cpp
//  Timber
//
//  Created by Alana Edwards on 9/2/24.
//

// Include important libraries here
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Audio.hpp>

// Make code easier to type with "using namespace";
using namespace sf;
using namespace std;

// Declare a constant int called NUM_BRANCHES and set the value to 6
const int NUM_BRANCHES = 6;

// Declare an array of Sprite objects called branches 
Sprite branches[NUM_BRANCHES]; // Stores 6 values

// Where is the player/branch?
// Left or Right
// Declare an enum called side with three possible values
enum class side {LEFT, RIGHT, NONE};

// initialize an array of sideTypes that stores 6 values 
// Each value is the type side and can be hold the values LEFT, RIGHT, or NONE
side branchPositions[NUM_BRANCHES]; 

// Function declaration
void updateBranches(int seed)
{
    // Move all the branches down one place
    for(int j = NUM_BRANCHES - 1; j > 0; j--) {
        branchPositions[j] = branchPositions[j - 1];
    }

    // Spawn a new branch at position 0
    // LEFT, RIGHT, or NONE
    srand((int)time(0)+seed);
    int r = (rand() % 5);

    switch(r) {
        case 0:
            branchPositions[0] = side::LEFT;
            break;
        case 1: 
            branchPositions[1] = side::RIGHT;
            break;
        default:
            branchPositions[0] = side::NONE;
            break;
    }
}

// Declare constant variables for the tree's position
const float TREE_HORIZONTAL_POSITION = 570;
const float TREE_VERTICAL_POSITION = -200;

int main()
// This is where the game starts from int main()
{
    // Prepare the sound
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("/Users/alana/alana-fullstackdev/Timber/sounds/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    SoundBuffer gameOverBuffer;
    gameOverBuffer.loadFromFile("/Users/alana/alana-fullstackdev/Timber/sounds/death.wav");
    Sound gameOver;
    gameOver.setBuffer(gameOverBuffer);

    // Out of time 
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("/Users/alana/alana-fullstackdev/Timber/sounds/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    // Create a video mode object
    VideoMode vm(VideoMode::getDesktopMode()); // Fullscreen mode

    // Create and open a window for the game
    RenderWindow window(vm, "Timber!!!");

    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // Load a graphic into the texture
    if (!textureBackground.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/background.png"))
    {
        cerr << "Failed to load image: graphics/background.png" << endl;
        return -1; // Exit if image loading fails
    }

    // Create a sprite spriteBackground;
    Sprite spriteBackground;

    // Attach the texture to the sprite spriteBackground.
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen sppriteBackground.
    spriteBackground.setPosition(0, 0);

    // Make a tree sprite
    Texture textureTree;
    if (!textureTree.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/tree.png"))
    {
        cerr << "Failed to load image: graphics/tree.png" << endl;
        return -1;
    }
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION);

    // Prepare the bee
    Texture textureBee;
    if (!textureBee.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/bee.png"))
    {
        cerr << "Failed to load image: graphics/bee.png" << endl;
        return -1;
    }
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(100, 600);

    // Is the bee constantly moving?
    bool beeActive = false;

    // How fast can the bee fly
    float beeSpeed = 0.0f;


    // Declare a constant int called NUM_CLOUDS and set the value to 3
    const int NUM_CLOUDS = 3;

    // Declare an array of Sprite objects called clouds
    Sprite clouds[NUM_CLOUDS]; // Stores 3 values

    bool cloudsActive[NUM_CLOUDS];

    int cloudSpeeds[NUM_CLOUDS];

    // Make 3 cloud sprites from 1 texture
    Texture textureCloud;

    // Load 1 new texture
    if (!textureCloud.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/cloud.png"))
    {
        cerr << "Failed to load image: graphics/cloud.png" << endl;
        return -1;
    }

    for (int i = 0; i < NUM_CLOUDS; i++ ) {
        clouds[i].setTexture(textureCloud);
        clouds[i].setPosition(-300, i * 150);
        cloudsActive[i] = false;
        cloudSpeeds[i] = 0;
    }

    // Variables to control time itself
    // Declare an object of the Clock type and name it clock
    Clock clock;

    // Time bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 50;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1440 / 2) - timeBarStartWidth / 2, 750);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    // Track whether game is running
    bool paused = true;

    // Draw some text
    int score = 0;

    // SFML Text object
    Text messageText;
    Text scoreText;
    Text gameOverText;

    // Choose a font
    Font font;

    font.loadFromFile("/Users/alana/alana-fullstackdev/Timber/fonts/KOMIKAP_.ttf");

    // Set the font to our text object
    messageText.setFont(font);
    scoreText.setFont(font);

    // Set the font to our message
    messageText.setString("Press enter to start!");
    scoreText.setString("Score = 0");

    // Assign a size and make it really big
    messageText.setCharacterSize(80);
    scoreText.setCharacterSize(50);

    // Choose a color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    // Position the text
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left +
                              textRect.width / 2.0f,
                          textRect.top +
                              textRect.height / 2.0f);

    messageText.setPosition(1920 / 2.5f, 1080 / 2.5f);
    scoreText.setPosition(20, 20);

    // Prepare the 5 branches 
    // Create an object of the Texture type called textureBranch 
    Texture textureBranch;

    // Load the branch graphic into the texture
    textureBranch.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/branch.png");

    // Set the texture for each branch sprite
    for(int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition( -2000, -2000);

        // Set the sprite's position to the center of the screen
        // The branch sprite can be spun around without changing the position
        branches[i].setOrigin(100, 10);
    }

    // Prepare the player 
    Texture texturePlayer;
    // Load the player graphic into the texture 
    texturePlayer.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/player.png");
    // Create a sprite 
    Sprite spritePlayer;
    // Set the texture to the sprite
    spritePlayer.setTexture(texturePlayer);
    //Set the sprite's position
    spritePlayer.setPosition(580, 720);
    
    // The player starts on the left
    side playerSide = side::LEFT;

    // Prepare the axe 
    Texture textureAxe;
    textureAxe.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/axe.png");

    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);

    spriteAxe.setPosition(700, 830);

    // Line the axe up with the tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // Prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    // Some other useful log related variable 
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    bool acceptInput = false;

    // Main game loop
    while (window.isOpen())
    {
        // Declare an object of type Event called event
        Event event;
        while (window.pollEvent(event)) // Call the window.pollEvent function and pass in the new object, event
        {

            if (event.type == Event::KeyReleased && !paused)
            {
                // Listen for key presses again
                acceptInput = true; 

                // hide the axe 
                spriteAxe.setPosition(2000,
                    spriteAxe.getPosition().y);
            }

            // Handle the player's input
            if (event.type == Event::Closed || event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        // Start the game
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
        {
            paused = false;

            // Reset the time and the score
            score = 0;
            timeRemaining = 6;

            // Make all the branches disappear 
            for (int i = 1; i < NUM_BRANCHES; i++ ) 
            {
                branchPositions[i] = side::NONE;
            }

            // Move the player into position
            spritePlayer.setPosition(500, 720);

            acceptInput = true;
        }

        // Wrap the player controls to
        // Make sure we are accepting input 
        if (acceptInput) 
        {
            // More code here next...

            // First handle pressing the right cursor key
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right) 
            {
                playerSide = side::RIGHT;

                score ++;

                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;

                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);

                spritePlayer.setPosition(1200, 720);

                // Update the branches
                updateBranches(score);

                // Set the log flying to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                logSpeedY = true;

                acceptInput = false;

                // Play a chop sound
                chop.play();
            }
            
            // Handle the left cursor key
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left)
            {
                playerSide = side::LEFT;

                score ++;

                // Add to the amount of time remaining
                timeRemaining += (2 / score) + .15;

                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);

                spritePlayer.setPosition(580, 720);

                // Update the branches
                updateBranches(score);

                // Set the log flying
                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                logSpeedY = true;

                acceptInput = false;

                // Play a chop sound
                chop.play();
            }
        }

        // Update the scene
        Time dt;
        if (!paused)
        {
            // Measure time
            // Declare an object of the Time type and name it dt and use it to store the value returned by the clock.restart() function
            dt = clock.restart();

            // Subtract from the amount of time remaining
            timeRemaining -= dt.asSeconds();

            // resize up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond *
                                         timeRemaining,
                                     timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                // Pause the game
                paused = true;

                // Change the message shown to the player
                messageText.setString("Out of time!!");

                // Reposition the text based on the new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + 
                textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);

                messageText.setPosition(1440 / 2.0f, 900 / 2.0f);

                // Play the out of time sound
                outOfTime.play();
            }

            // Setup the bee
            if (!beeActive)
            {
                // How fast is the bee?
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                // How high is the bee
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else
            {
                // Move the bee
                spriteBee.setPosition(
                    spriteBee.getPosition().x -
                        (beeSpeed * dt.asSeconds()),
                    spriteBee.getPosition().y);

                // Has the bee reached the left-hand edge of the screen?
                if (spriteBee.getPosition().x < -100)
                {
                    beeActive = false;
                }
            }

            // Manage the clouds
            // Cloud 1
            if (!cloudsActive[0])
            {
                // How fast is the cloud moving?
                srand((int)time(0) * 10); // * 10 to the result returned by time(0) ensures we always get a different seed for each of the clouds
                cloudSpeeds[0] = (rand() % 200);

                // How high is the cloud?
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                clouds[0].setPosition(-200, height);
                cloudsActive[0] = true;
            }
            else
            {
                // Move the cloud
                clouds[0].setPosition(
                    clouds[0].getPosition().x +
                        (cloudSpeeds[0] * dt.asSeconds()),
                    clouds[0].getPosition().y);

                // Has the cloud reached the right-hand edge of the screen?
                if (clouds[0].getPosition().x > 1920)
                {
                    cloudsActive[0] = false;
                }
            }

            // Cloud 2
            if (!cloudsActive[1])
            {
                // How fast is the cloud moving?
                srand((int)time(0) * 20);
                cloudSpeeds[1] = (rand() % 200);

                // How high is the cloud?
                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                clouds[1].setPosition(-200, height);
                cloudsActive[1] = true;
            }
            else
            {
                // Move the cloud
                clouds[1].setPosition(
                    clouds[1].getPosition().x +
                        (cloudSpeeds[1] * dt.asSeconds()),
                    clouds[1].getPosition().y);

                // Has the cloud reached the left-hand edge of the screen?
                if (clouds[1].getPosition().x > 1920)
                {
                    cloudsActive[1] = false;
                }
            }

            // Cloud 3
            if (!cloudsActive[2])
            {
                // How fast is the cloud moving?
                srand((int)time(0) * 30); // * 10 to the result returned by time(0) ensures we always get a different seed for each of the clouds
                cloudSpeeds[2] = (rand() % 200);

                // How high is the cloud?
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                clouds[2].setPosition(-200, height);
                cloudsActive[2] = true;
            }
            else
            {
                // Move the cloud
                clouds[2].setPosition(
                    clouds[2].getPosition().x +
                        (cloudSpeeds[2] * dt.asSeconds()),
                    clouds[2].getPosition().y);

                // Has the cloud reached the left-hand edge of the screen?
                if (clouds[2].getPosition().x > 1920)
                {
                    cloudsActive[2] = false;
                }
            }
        } // End if(!paused)

        // Update the score text
        std::stringstream ss;
        ss << "Score = " << score;
        scoreText.setString(ss.str());

        // Update the branch sprites 
        for (int i = 0; i < NUM_BRANCHES; i++) {
            float height = i * 150; // First branch will have a height of 0 and the sixth will have a height of 750

            if (branchPositions[i] == side::LEFT) 
            {
                // Move the sprite to the left side 
                branches[i].setPosition(610, height);

                // Flip the sprite around
                branches[i].setRotation(180);
            }
            else if (branchPositions[i] == side::RIGHT)
            {
                // Move the sprite to the right side
                branches[i].setPosition(1330, height);

                // Set the sprite rotation to normal
                branches[i].setRotation(0);
            }
            else 
            {
                // Hide the branch 
                branches[i].setPosition(3000, height);
            }
        } 
        
        // Handle a flying log
        if (logActive) 
        {
            spriteLog.setPosition(
                spriteLog.getPosition().x +
                (logSpeedX * dt.asSeconds()),

                spriteLog.getPosition().y +
                (logSpeedY * dt.asSeconds())
            );

            // Has the log reached the right side?
            if (spriteLog.getPosition().x < -100 ||
                spriteLog.getPosition().y > 2000)
            {
                // Set it ready to be a new log next frame 
                logActive = false;
                spriteLog.setPosition(810, 720);
            }
        }
        
        // Has the player been hit by a branch?
        if (branchPositions[5] == playerSide)
        {
            // Game over 
            paused = true; 
            acceptInput = false;

            // Hide the player
            spritePlayer.setPosition(2000, 600);

            // Change the text of message
            messageText.setString("GAME OVER!!");

            // Center it on screen
            FloatRect textRect = messageText.getLocalBounds();

            messageText.setOrigin(textRect.left + 
            textRect.width / 2.0f, 
            textRect.top + textRect.height / 2.0f);

            messageText.setPosition(1440 / 2.0f,
            900 / 2.0f);

            gameOver.play();
        }
        
        // End if(!paused)



        // Draw the scene

        // Clear everything from the last frame window.clear();
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);

        // Draw the clouds
        window.draw(clouds[0]);
        window.draw(clouds[1]);
        window.draw(clouds[2]);

        // Draw the branches 
        for (int i = 0; i < NUM_BRANCHES; i++) 
        {
            window.draw(branches[i]);
        }

        // Draw the tree
        window.draw(spriteTree);

        // Draw the player
        window.draw(spritePlayer);

        // Draw the axe 
        window.draw(spriteAxe);

        // Draw the log 
        window.draw(spriteLog);

        // Draw the bee
        window.draw(spriteBee);

        // Draw the score
        window.draw(scoreText);

        // Draw the timebar
        window.draw(timeBar);

        if (paused)
        {
            // Draw our message
            window.draw(messageText);
        }

        // Show everything we just drew window.display();
        window.display();
    }

    return 0;
}
