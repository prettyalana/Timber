//
//  main.cpp
//  Timber
//
//  Created by Alana Edwards on 9/2/24.
//

// Include important libraries here
#include <SFML/Graphics.hpp>
#include <iostream>

// Make code easier to type with "using namespace" using namespace sf;
using namespace sf;

// Declare constant variables for the tree's position
const float TREE_HORIZONTAL_POSITION = 570;
const float TREE_VERTICAL_POSITION = -200;

int main()
// This is where the game starts from int main()
{
    // Create a video mode object
    VideoMode vm(VideoMode::getDesktopMode()); // Fullscreen mode
    
    // Create and open a window for the game
    RenderWindow window(vm, "Timber!!!");
    
    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;
    
    // Load a graphic into the texture
    if (!textureBackground.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/background.png")) {
        std::cerr << "Failed to load image: graphics/background.png" << std::endl;
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
    if(!textureTree.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/tree.png")) {
        std::cerr << "Failed to load image: graphics/tree.png" << std::endl;
        return -1; 
    }
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION);
    
    // Prepare the bee
    Texture textureBee;
    if(!textureBee.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/bee.png")) {
        std::cerr << "Failed to load image: graphics/bee.png" << std::endl;
        return -1; 
    }
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(100, 600);

    // Is the bee constantly moving?
    bool activeBee = false;

    // How fast can the bee fly
    float beeSpeed = 0.0f;

    // Make 3 cloud sprites from 1 texture
    Texture textureCloud;

    // Load 1 new texture
    if(!textureCloud.loadFromFile("/Users/alana/alana-fullstackdev/Timber/graphics/cloud.png")) {
        std::cerr << "Failed to load image: graphics/cloud.png" << std::endl;
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
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;
    
    // Main game loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Handle the player input
            if (event.type == Event::Closed)
                window.close();
        }
        
        // Update the scene
        
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


