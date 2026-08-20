#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <numbers>
#include <iostream>


//SETTINGS
//-----------------------------
unsigned int screenWidth = 800;
unsigned int screenHeight = 600;

std::string windowTitle = "SAT Collision Test";

int FPS = 60;
float dt = 1.0f/FPS;

int PPM = 100;
//-----------------------------

class Shape {
    public:
        sf::Vector2f position;
        
        sf::Vector2f velocity;

        std::size_t sideNumber;

        sf::ConvexShape shape;

        sf::Angle rotation;

        std::vector<sf::Vector2f> corners;

        float size;

        int shapeNumber;

    Shape(float size_, sf::Vector2f position_, sf::Angle rotation_, std::size_t sideNumber_, sf::Color colour, int shapeNumber_){

        size = size_;

        sideNumber = sideNumber_;

        position = position_;

        rotation = rotation_;

        shapeNumber = shapeNumber_;

        shape = sf::ConvexShape(sideNumber_);

        shape.setPosition(position);

        shape.setFillColor(colour);

        shape.setRotation(rotation);

        for (int i = 0; i < (int)sideNumber; i++){
            float angle = i * (2 * std::numbers::pi) / sideNumber;
            sf::Vector2f pointPos = {size * std::sin(angle), size * std::cos(angle)};
            corners.push_back(pointPos);

        }

        for (size_t i = 0; i < corners.size(); i++){
            shape.setPoint(i, corners[i]);
        }


    }

    void move(){
        float movementSpeed = 5*PPM;

        if (shapeNumber == 1){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            position.y -= movementSpeed * dt;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                position.y += movementSpeed * dt;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                position.x -= movementSpeed * dt;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
                position.x += movementSpeed * dt;       
            }
        } else if (shapeNumber == 2){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            position.y -= movementSpeed * dt;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
                position.y += movementSpeed * dt;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
                position.x -= movementSpeed * dt;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
                position.x += movementSpeed * dt;       
            }
        }
        
        shape.setPosition(position);
    }

    void rotate(){
        float rotationSpeed = 3 * PPM;

        if (shapeNumber == 1){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
                rotation += sf::degrees(rotationSpeed) * dt;
            }

        } else if (shapeNumber == 2){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)){
                rotation += sf::degrees(rotationSpeed) * dt;
            }
        }
        
        shape.setRotation(rotation);
    }


};




int main(){


   std::vector<Shape> shapes = {
        Shape{30, sf::Vector2f(400.f, 300.f), sf::degrees(10.f), 3, sf::Color(250,100,0), 1},
        Shape{30, sf::Vector2f(100, 100), sf::degrees(90.0f), 5, sf::Color(0,90,130), 2}
    };


    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({screenWidth, screenHeight}), windowTitle);

    window->setFramerateLimit(FPS);

    while (window->isOpen()){
        while(const std::optional event = window->pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window->close();
            }
        }

        for (auto& shape : shapes){
            shape.move();
            shape.rotate();
        }

        window->clear();

        //RENDER STUFF HERE
        for (auto& shape: shapes){
            window->draw(shape.shape);
        }


        window->display();

    }


    return 0;
}





