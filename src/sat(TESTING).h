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

std::vector<sf::Vector2f> getaxes(std::vector<sf::Vector2f> vertices) {
    std::vector<sf::Vector2f> axes;
    for (int i = 0; i < vertices.size(); i++) {
        sf::Vector2f edge = vertices[(i+1) % vertices.size()] - vertices[i];
        sf::Vector2f normal (-edge.y, edge.x); 
        float length = sqrt(normal.x * normal.x + normal.y * normal.y);
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
    std::vector<sf::Vector2f> axes = getaxes(vertices);
    for (int i = 0; i < vertices.size(); i++) {
        sf::Vector2f pt1 = vertices[i];
        sf::Vector2f pt2 = vertices[(i+1) % vertices.size()];
        sf::Vector2f midpoint = (pt1+pt2)/2.f;
        sf::Vector2f axis = midpoint + axes[i] * 25.f;
        sf::Vertex v1;
        v1.position = midpoint;
        v1.color = sf::Color::Magenta;
        sf::Vertex v2;
        v2.position = axis;
        v2.color = sf::Color::Magenta;

        sf::Vertex axisline[2] = { v1, v2 };
        window.draw(axisline, 2, sf::PrimitiveType::Lines);
    }
}