#include <iostream>
#include <random>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "perlin.hpp"

int main()
{
    const int windowWidth = 1000;
    const int windowHeight =  1000;

    const int gridHeight = 200;
    const int gridWidth = 200;
    

    sf::Uint8* pixels = new sf::Uint8[windowWidth * windowHeight * 4];

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    
    // loop over random gradients, generating the perlin values and writing them to a texture
    for (int x = 0; x < windowWidth; x++)
    {
        for (int y = 0; y < windowHeight; y++)
        {
        int index = (y * windowWidth + x) * 4;
        // std::cout <<  x * scaleX<< "   " <<  y * scaleY << std::endl;

        float value = 0;
 
            float freq = 1;
            float amp = 1;
 
            for (int i = 0; i < 12; i++)
            {
                 value += perlin(sf::Vector2f(x * freq /gridWidth, y * freq /gridHeight )) * amp;
                  freq *= 2;
                amp /= 2;
            }
        if (value > 1.0f)
            value = 1.0;
        if(value < -1.0f)
            value = -1.0f;
        int colour = (int)(((value + 1.0f) * 0.5f) *255);
            pixels[index] = colour;
            pixels[index + 1] = colour;
            pixels[index + 2] = colour;
            pixels[index + 3] = 255;

        }        
    }

    sf::Texture texture;
    sf::Sprite sprite;

    texture.create(windowWidth, windowHeight);
    texture.update(pixels);
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

