#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include "body.h"
#include <optional>
#include <SFML/Graphics.hpp>
#include "physicsSolver.h"
using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "C++ Gravity Engine");
    window.setFramerateLimit(60);
    vector<body> a;
    a.push_back(body(1000000.0f, 40.0f, 600.0f, 400.0f));
    a.push_back(body(5000.0f, 15.0f, 600.0f, 250.0f));
    a[1].dxv = 81.65f;
    a.push_back(body(5000.0f, 15.0f, 600.0f, 100.0f));  
    a[2].dxv = 57.73f;
    // a.push_back(body(5000.0f,15.0f,600.0f,50.0f));
    // a[3].dxv = 100.69f;    
    auto previousTime = chrono::high_resolution_clock::now();
    PhysicsSolver physicsEngine;
    while(window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        auto currentTime = chrono::high_resolution_clock::now();
        chrono::duration<float> elapsedTime = currentTime - previousTime;
        float dt = elapsedTime.count();
        previousTime = currentTime; 
        physicsEngine.PhysicsStep(a,dt);
        window.clear(sf::Color::Black);
        for (const auto& i : a) {
            sf::CircleShape shape(i.r);
            shape.setOrigin({i.r, i.r}); 
            shape.setPosition({i.x, i.y}); 
            shape.setFillColor(sf::Color::White);  
            window.draw(shape); 
        }
        window.display();
    }
}
// 