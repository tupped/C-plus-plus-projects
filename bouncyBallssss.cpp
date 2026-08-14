#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <cstdlib>


using namespace std;
using namespace sf;

struct {
    const int PPM = 100; //Pixels per Metre
    const float g = 9.8 * PPM;
    const int numberOfBodies = 500;
    const int subSteps = 1;
    const int FPS = 120;

    unsigned int screenWidth = 2400;
    unsigned int screenHeight = 1100;

} Config;

int coinFlip(){
    int randomNumber = rand() % 101;

    if (randomNumber % 2 == 0){
        return 1;
    } else {
        return -1;
    }
    
}



class Body {
    public:
        float x,y; 
        float vx, vy;
        float radius;
        float mass;
        float restitution;
        CircleShape shape;

    Body(float x_, float y_, float vx_, float vy_, float radius_, float mass_, float restitution_, sf::Color colour){     //CONSTRUCTOR
        x = x_;
        y = y_;
        vx = vx_;
        vy = vy_;
        radius = radius_;
        mass = mass_;
        restitution = restitution_;
        shape = CircleShape(radius);
        shape.setOrigin({radius, radius});
        shape.setPosition({x, y});
        shape.setFillColor(colour);
    }        
        
};

float dotProduct(float x1, float y1, float x2, float y2){
    float dotProduct = x1*x2 + y1*y2;

    return dotProduct;
}
 
Color randomColour(){
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    return Color(r,g,b);
}



void updatePhysics(vector<Body>& bodies, float dt){
    for (auto& b : bodies){
        
        b.vy += Config.g * dt;
        
        b.x += b.vx * dt;
        b.y += b.vy * dt;

        //COLLISION DETECTION FOR EDGES

        // BOTTOM EDGE
        if (b.y + b.radius > Config.screenHeight){
            b.y = Config.screenHeight - b.radius;

            if (b.vy > 0){
                b.vy = b.vy * b.restitution * -1;
            }

        }
        //RIGHT EDGE
        if (b.x + b.radius > Config.screenWidth){
            b.x = Config.screenWidth - b.radius;

            if (b.vx > 0){
                b.vx = b.vx * b.restitution * -1;
            }
        }
        //LEFT EDGE
        if (b.x - b.radius < 0){
            b.x = b.radius;

            if (b.vx < 0){
                b.vx = b.vx * b.restitution * -1;
            }
        }
        //TOP EDGE
        if (b.y - b.radius < 0){
            b.y = b.radius;

            if (b.vy < 0){
                b.vy = b.vy * b.restitution * -1;
            }
        }

        //COLLISION BETWEEN BODIES
        for (auto & b2 : bodies){
            if (&b != &b2 && b.radius + b2.radius >= sqrtf(pow(b.x - b2.x, 2) + pow(b.y - b2.y, 2))){
                
                float dx = b.x - b2.x;
                float dy = b.y - b2.y; 

                float distance = sqrtf(pow(dx, 2) + pow(dy, 2));

                if (distance < 0.0001f){
                    
                    float tinyNudge = 0.1;

                    b.y += tinyNudge;
                    b.x += tinyNudge;
                    b2.x -= tinyNudge;
                    b2.y -= tinyNudge;
                    break;
                }

             
                

                float normalX = dx/distance;
                float normalY = dy/distance;

                float tangentialX = -1 *normalY;
                float tangentialY = normalX;

                
                
                float v1n = dotProduct(b.vx, b.vy, normalX, normalY);
                float v2n = dotProduct(b2.vx, b2.vy, normalX, normalY);

                float v1t = dotProduct(b.vx, b.vy, tangentialX, tangentialY);
                float v2t = dotProduct(b2.vx, b2.vy, tangentialX, tangentialY);

                float m1 = b.mass;
                float m2 = b2.mass;

                float e = b.restitution;

                float radiiSum = b.radius + b2.radius;

                b.x += ((radiiSum - distance)/2)*normalX;
                b.y += ((radiiSum - distance)/2)*normalY;

                b2.x -= ((radiiSum - distance)/2)*normalX;
                b2.y -= ((radiiSum - distance)/2)*normalY;

                b.vx = (m1*v1n + m2*v2n + e*m2*(v2n - v1n))/(m1 + m2)* normalX + v1t * tangentialX;
                b2.vx = (m1*v1n + m2*v2n + e*m1*(v1n - v2n))/(m2 + m1) * normalX + v2t * tangentialX;

                b.vy = (m1*v1n + m2*v2n + e*m2*(v2n - v1n))/(m1 + m2) * normalY + v1t * tangentialY;
                b2.vy = (m1*v1n + m2*v2n + e*m1*(v1n - v2n))/(m2 + m1) * normalY + v2t * tangentialY;



            }
        }


        b.shape.setPosition({b.x, b.y});

    }

}

int main(){
    bool restart = false;

    do {
        restart = false;

        float dt = 1.0f/Config.FPS;

        vector<Body> bodies;

        //LOTS OF BALLS LOOP
        for (int i = 0; i <= Config.numberOfBodies; i++){

            //RANDOMISATION

            int randomX = rand() % Config.screenWidth;
            int randomY = rand() % Config.screenHeight;

            int randomDirection = coinFlip();

            int randomVX = rand() % 30 * Config.PPM * randomDirection;
            int randomVY = rand() % 30 * Config.PPM * randomDirection;

            int randomRadius = (rand() % 10) + 2;


            
            // SETTINGS \/\/\/\/

            int xPos = randomX;
            int yPos = randomY;
        
            int initVX = randomVX;
            int initVY = randomVY;

            int radius = 10;

            int allBallMass = 10;

            float allBallRestitution = 0.9; 

            Color colour = randomColour();
        
            Body b(xPos, yPos, initVX, initVY, radius, allBallMass, allBallRestitution, colour); 

            bodies.push_back(b);
        }


        RenderWindow* window = new RenderWindow(VideoMode({Config.screenWidth, Config.screenHeight}), "Simulacrum");

        window->setFramerateLimit(Config.FPS);
        
        while (window->isOpen()){ 
            while (const optional event = window->pollEvent()){
                if (event->is<Event::Closed>()){
                    window->close();
                }
            }
            //EVERYTHING HERE HAPPENS EVERY FRAME IE DO THE LOOP HERE \/\/\/
            for (int i = 0; i < Config.subSteps; i++){
                updatePhysics(bodies, dt);
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Key::R)){
                restart = true;
                window->close();
            }

            window->clear(); //ALL DRAWING HAPPENS BETWEEN CLEAR AND DISPLAY

            for (auto& b : bodies){
                window->draw(b.shape);
            }

            window->display();
        }

        delete window;
    } while(restart);   
    return 0;
}