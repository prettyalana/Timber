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
const float TREE_HORIZONTAL_POSITION = 810;
const float TREE_VERTICAL_POSITION = 0;

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
    spriteBee.setPosition(0, 800);

    // Is the bee constantly moving?
    bool activeBee = false;

    // How fast can the bee fly
    float beeSpeed = 0.0f;

    
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
        
        // Show everything we just drew window.display();
        window.display();
    }
    
    return 0;
}


