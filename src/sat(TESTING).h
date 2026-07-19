#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

std::vector<sf::Vector2f> getvertices(sf::Shape& shape) {
    std::vector<sf::Vector2f> vertices;
    for (int i = 0; i < shape.getPointCount(); i++) {
        vertices.push_back(shape.getTransform().transformPoint(shape.getPoint(i)));
    }
    return vertices;
}

std::vector<sf::Vector2f> getaxes(sf::Shape& shape) {
    std::vector<sf::Vector2f> vertices = getvertices(shape);
    std::vector<sf::Vector2f> axes;
    for (int i = 0; i < shape.getPointCount(); i++) {
        sf::Vector2f edge = vertices[i+1] - vertices[i];
        sf::Vector2f normal (-edge.y, edge.x); 
        float length = sqrt(normal.x * normal.x + normal.y * normal.x);
        axes.push_back(normal / length);
    }
    return axes;
}

void drawdebug(sf::RenderWindow& window, std::vector<sf::Vector2f> vertices) {
    for (auto& pos: vertices) {
        sf::CircleShape vertex;
        vertex.setRadius(3.f);
        vertex.setPosition(sf::Vector2f(pos.x, pos.y));
        window.draw(vertex);
    }
}