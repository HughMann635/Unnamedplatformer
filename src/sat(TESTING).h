#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <limits>

inline std::vector<sf::Vector2f> getvertices(sf::Shape& shape) {
    std::vector<sf::Vector2f> vertices;
    for (int i = 0; i < shape.getPointCount(); i++) {
        vertices.push_back(shape.getTransform().transformPoint(shape.getPoint(i)));
    }
    return vertices;
}

inline std::vector<sf::Vector2f> getaxes(std::vector<sf::Vector2f>& vertices) {
    std::vector<sf::Vector2f> axes;
    for (int i = 0; i < vertices.size(); i++) {
        sf::Vector2f edge = vertices[(i+1) % vertices.size()] - vertices[i];
        sf::Vector2f normal (-edge.y, edge.x); 
        float length = sqrt(normal.x * normal.x + normal.y * normal.y);
        axes.push_back(normal / length);
    }
    return axes;
}

inline void drawdebug(sf::RenderWindow& window, std::vector<sf::Vector2f> vertices) {
    for (auto& pos: vertices) {
        sf::CircleShape vertex;
        vertex.setRadius(1.f);
        vertex.setOrigin(sf::Vector2f(1.f, 1.f));
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

struct Range {
public:
    float min, max;
};

inline Range projection (std::vector<sf::Vector2f>& vertices, sf::Vector2f axis) {
    float min = vertices[0].x * axis.x + vertices[0].y * axis.y;
    float max = min;
    for (auto& pos: vertices) {
        float product = pos.x * axis.x + pos.y * axis.y;
        if (product < min) {
            min = product; 
        } if (product > max) {
            max = product;
        }
    }
    return {min, max};
}

inline bool satCollide (std::vector<sf::Vector2f>& vertices1, std::vector<sf::Vector2f>& vertices2) {
    auto axes1 = getaxes(vertices1);
    auto axes2 = getaxes(vertices2);

    for (auto& pos: axes1) {
        Range project1 = projection(vertices1, pos);
        Range project2 = projection(vertices2, pos);
        if (project1.max < project2.min || project2.max < project1.min) return false;
    }
    for (auto& pos: axes2) {
        Range project1 = projection(vertices1, pos);
        Range project2 = projection(vertices2, pos);
        if (project1.max < project2.min || project2.max < project1.min) return false;
    }

    return true;
}

inline bool mtvCheck (std::vector<sf::Vector2f>& vertices1, std::vector<sf::Vector2f>& vertices2, sf::Vector2f& mtv) {
    auto axes1 = getaxes(vertices1);
    auto axes2 = getaxes(vertices2);
    std::vector<sf::Vector2f> allaxes;
    allaxes.insert(allaxes.end(), axes1.begin(), axes1.end());
    allaxes.insert(allaxes.end(), axes2.begin(), axes2.end());
    float lowestovlp = std::numeric_limits<float>::max();
    sf::Vector2f lowestaxis;

    for (auto& pos: allaxes) {
        Range project1 = projection(vertices1, pos);
        Range project2 = projection(vertices2, pos);
        float overlap = std::min(project1.max, project2.max) - std::max(project1.min, project2.min);
        if (overlap < 0) return false;
        if (overlap < lowestovlp) {
            lowestovlp = overlap;
            lowestaxis = pos;
        }
    }

    sf::Vector2f center1 = sf::Vector2f(0.f, 0.f);
    sf::Vector2f center2 = sf::Vector2f(0.f, 0.f);
    for (auto& pos: vertices1) {
        center1 += pos;
    }
    for (auto& pos: vertices2) {
        center2 += pos;
    }
    center1 /= static_cast<float>(vertices1.size());
    center2 /= static_cast<float>(vertices2.size());
    sf::Vector2f direction = center1 - center2;

    float dotproduct = direction.x * lowestaxis.x + direction.y * lowestaxis.y;
    if (dotproduct < 0) lowestaxis *= -1.f; 

    mtv = lowestaxis * lowestovlp;
    return true;
}