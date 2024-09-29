//
//  main.cpp
//  Timber
//
//  Created by Alana Edwards on 9/2/24.
//

// Include important libraries here
#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace" using namespace sf;
using namespace sf;

int main()
// This is where the game starts from int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);

    // Create and open a window for the game
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
    
    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;
    
    // Load a graphic into the texture textureBackground.
    textureBackground.loadFromFile("graphics/background.png");
    
    // Create a sprite spriteBackground;
    Sprite spriteBackground;
    
    // Attach the texture to the sprite spriteBackground.
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen sppriteBackground.
    spriteBackground.setPosition(0,0);
    
    // Main game loop
    while (window.isOpen())
    {

        // Handle the player input

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
    }

    // Update the scene

    // Draw the scene

    // Clear everything from the last frame window.clear();

    // Draw our game scene here
    window.draw(spriteBackground);
    
    // Show everything we just drew window.display();

    return 0;
}
