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

// Make code easier to type with "using namespace";
using namespace sf;
using namespace std;

// Declare constant variables for the tree's position
const float TREE_HORIZONTAL_POSITION = 570;
const float TREE_VERTICAL_POSITION = -200;

int main()
// This is where the game starts from int main()
{
    string playerName = "Player1";
    string message = "Welcome to the game, " + playerName + "!";
    cout << message << endl;


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

    // Make 3 cloud sprites from 1 texture
    Texture textureCloud;

    // Load 1 new texture
    if (!textureCloud.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/cloud.png"))
    {
        cerr << "Failed to load image: graphics/cloud.png" << endl;
        return -1;
    }

    // Create 3 new sprites with the textureCloud
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    // Position clouds on the left side of the screen
    // at different heights
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 150);
    spriteCloud3.setPosition(0, 300);

    // Are the clouds currently on the screen?
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    // How fast is each cloud?
    float cloud1Speed = 0;
    float cloud2Speed = 0;
    float cloud3Speed = 0;

    // Variables to control time itself
    // Declare an object of the Clock type and name it clock
    Clock clock;

    // Track whether game is running
    bool paused = true;

    // Main game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            // Handle the player input
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        // Start the game
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
        {
            paused = false;
        }

        // Update the scene
        
        if (!paused)
        {
            

        // Measure time
        // Declare an object of the Time type and name it dt and use it to store the value returned by the clock.restart() function
        Time dt = clock.restart();

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
            if(spriteBee.getPosition().x < -100) 
            {
                beeActive = false;
            }
        }

        // Manage the clouds
        //Cloud 1
        if (!cloud1Active)
        {
            // How fast is the cloud moving?
            srand((int)time(0) * 10); // * 10 to the result returned by time(0) ensures we always get a different seed for each of the clouds
            cloud1Speed = (rand() % 200);

            // How high is the cloud?
            srand((int)time(0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition(-200, height);
            cloud1Active = true;
        }
        else 
        {
            // Move the cloud
            spriteCloud1.setPosition(
            spriteCloud1.getPosition().x +
            (cloud1Speed * dt.asSeconds()),
            spriteCloud1.getPosition().y);

            // Has the cloud reached the right-hand edge of the screen?
            if(spriteCloud1.getPosition().x > 1920)
            {
                cloud1Active = false;
            }
        }


        //Cloud 2
        if (!cloud2Active)
        {
            // How fast is the cloud moving?
            srand((int)time(0) * 20); 
            cloud2Speed = (rand() % 200);

            // How high is the cloud?
            srand((int)time(0) * 20);
            float height = (rand() % 300) - 150;
            spriteCloud2.setPosition(-200, height);
            cloud2Active = true;
        }
        else 
        {
            // Move the cloud
            spriteCloud2.setPosition(
            spriteCloud2.getPosition().x +
            (cloud2Speed * dt.asSeconds()),
            spriteCloud2.getPosition().y);

            // Has the cloud reached the left-hand edge of the screen?
            if(spriteCloud2.getPosition().x > 1920)
            {
                cloud2Active = false;
            }
        }

        //Cloud 3
        if (!cloud3Active)
        {
            // How fast is the cloud moving?
            srand((int)time(0) * 30); // * 10 to the result returned by time(0) ensures we always get a different seed for each of the clouds
            cloud3Speed = (rand() % 200);

            // How high is the cloud?
            srand((int)time(0) * 30);
            float height = (rand() % 450) - 150;
            spriteCloud3.setPosition(-200, height);
            cloud3Active = true;
        }
        else 
        {
            // Move the cloud
            spriteCloud3.setPosition(
            spriteCloud3.getPosition().x +
            (cloud3Speed * dt.asSeconds()),
            spriteCloud3.getPosition().y);

            // Has the cloud reached the left-hand edge of the screen?
            if(spriteCloud3.getPosition().x > 1920)
            {
                cloud3Active = false;
            }
        }
        } // End if(!paused)

        // Draw the scene

        // Clear everything from the last frame window.clear();
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);

        // Draw the clouds
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        // Draw the tree
        window.draw(spriteTree);

        // Draw the bee
        window.draw(spriteBee);

        // Show everything we just drew window.display();
        window.display();
    }

    return 0;
}
