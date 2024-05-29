#include <SFML/Graphics.hpp>
#include <math.h>



float interpolate(float a0, float a1, float w){
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; 
    unsigned a = ix, b = iy;
    a *= 3284157443;
 
    b ^= a << s | a >> w - s;
    b *= 1911520717;
 
    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    
    return random;
}

float getIntersectionWeight(sf::Vector2f point, sf::Vector2i intersection){
    // float angle = gradients[intersection.x + gridWidth * intersection.y];
    float angle = randomGradient(intersection.x, intersection.y);

    sf::Vector2f gradient( cos(angle), sin(angle));
    sf::Vector2f distance = point - (sf::Vector2f)intersection ;

    //Finding the dot product between gradient and distance vectors
    float weight = gradient.x * distance.x + gradient.y * distance.y;
    return weight;
};


float perlin(sf::Vector2f point){
    int x0 = (int) point.x;
    int y0 = (int) point.y;

    float sx = point.x - x0;
    float sy = point.y - y0;

    //Get weights for each intersection
    float w0 = getIntersectionWeight(point, sf::Vector2i(x0, y0));
    float w1 = getIntersectionWeight(point, sf::Vector2i(x0 + 1, y0));
    float w2 = getIntersectionWeight(point, sf::Vector2i(x0, y0 + 1));
    float w3 = getIntersectionWeight(point, sf::Vector2i(x0 + 1, y0 + 1));

    float i0 = interpolate(w0, w1, sx);
     float i1 = interpolate(w2, w3, sx);

    float value = interpolate(i0, i1, sy);
    // std::cout << value << std::endl;
    return value;

};