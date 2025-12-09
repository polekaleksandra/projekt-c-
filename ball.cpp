#include "ball.h"
#include <cmath>

Pilka::Pilka(float startX, float startY, float velX, float velY, float r)
    : x(startX), y(startY), vx(velX), vy(velY), radius(r), currentType(BallType::Circle) {

    circleShape.setRadius(radius);
    circleShape.setOrigin(radius, radius);
    circleShape.setPosition(x, y);
    circleShape.setFillColor(sf::Color::White);
    starShape.setPointCount(10);
    float innerR = radius * 0.5f;
    float outerR = radius * 1.2f;
    for (int i = 0; i < 10; ++i) {
        float angle = i * 2 * 3.14159f / 10 - 3.14159f / 2;
        float currR = (i % 2 == 0) ? outerR : innerR;
        starShape.setPoint(i, sf::Vector2f(std::cos(angle) * currR, std::sin(angle) * currR));
    }
    starShape.setPosition(x, y);
    starShape.setFillColor(sf::Color::Yellow);

    heartShape.setPointCount(14);
    
    float scale = radius / 10.0f; 
    heartShape.setPoint(0, sf::Vector2f(0 * scale, -5 * scale)); 
    heartShape.setPoint(1, sf::Vector2f(4 * scale, -8 * scale)); 
    heartShape.setPoint(2, sf::Vector2f(8 * scale, -5 * scale));
    heartShape.setPoint(3, sf::Vector2f(10 * scale, 0 * scale)); 
    heartShape.setPoint(4, sf::Vector2f(8 * scale, 5 * scale));
    heartShape.setPoint(5, sf::Vector2f(5 * scale, 9 * scale));
    heartShape.setPoint(6, sf::Vector2f(0 * scale, 12 * scale)); 
    heartShape.setPoint(7, sf::Vector2f(-5 * scale, 9 * scale));
    heartShape.setPoint(8, sf::Vector2f(-8 * scale, 5 * scale));
    heartShape.setPoint(9, sf::Vector2f(-10 * scale, 0 * scale)); 
    heartShape.setPoint(10, sf::Vector2f(-8 * scale, -5 * scale));
    heartShape.setPoint(11, sf::Vector2f(-4 * scale, -8 * scale)); 

    
    heartShape.setFillColor(sf::Color(255, 105, 180));
    heartShape.setPosition(x, y);
}

void Pilka::setType(BallType type) {
    currentType = type;
}

void Pilka::move() {
    x += vx;
    y += vy;
   
    circleShape.setPosition(x, y);
    starShape.setPosition(x, y);
    heartShape.setPosition(x, y);

    
    if (currentType == BallType::Star) {
        starShape.rotate(5.0f);
    }
    else if (currentType == BallType::Heart) {
        heartShape.rotate(-3.0f); 
    }
}

void Pilka::bounceX() { vx = -vx; }
void Pilka::bounceY() { vy = -vy; }

void Pilka::collideWalls(float width, float height) {
    if (x - radius <= 0) { x = radius; bounceX(); }
    if (x + radius >= width) { x = width - radius; bounceX(); }
    if (y - radius <= 0) { y = radius; bounceY(); }

   
    circleShape.setPosition(x, y);
    starShape.setPosition(x, y);
    heartShape.setPosition(x, y);
}

bool Pilka::collidePaddle(const Paletka& p) {
    sf::FloatRect paddleBounds = p.getGlobalBounds();
    sf::FloatRect ballBounds = getGlobalBounds();

    if (ballBounds.intersects(paddleBounds)) {
        vy = -std::abs(vy);
        y = paddleBounds.top - radius;
        circleShape.setPosition(x, y);
        starShape.setPosition(x, y);
        heartShape.setPosition(x, y);
        return true;
    }
    return false;
}

void Pilka::setState(float newX, float newY, float newVx, float newVy) {
    x = newX; y = newY; vx = newVx; vy = newVy;
    circleShape.setPosition(x, y);
    starShape.setPosition(x, y);
    heartShape.setPosition(x, y);
}

void Pilka::draw(sf::RenderTarget& target) const {
    
    switch (currentType) {
    case BallType::Circle: target.draw(circleShape); break;
    case BallType::Star:   target.draw(starShape); break;
    case BallType::Heart:  target.draw(heartShape); break;
    }
}

sf::FloatRect Pilka::getGlobalBounds() const {
   
    switch (currentType) {
    case BallType::Star:   return starShape.getGlobalBounds();
    case BallType::Heart:  return heartShape.getGlobalBounds();
    default:               return circleShape.getGlobalBounds();
    }
}
