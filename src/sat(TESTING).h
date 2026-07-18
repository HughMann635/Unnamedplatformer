#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

std::vector<sf::Vector2f> getvertices(sf::Shape& shape) {
    std::vector<sf::Vector2f> vertices;
    for (int i = 0; i < shape.getPointCount(); i++) {
        vertices.push_back(shape.getTransform().transformPoint(shape.getPoint(i)));
    }
    return vertices;
}