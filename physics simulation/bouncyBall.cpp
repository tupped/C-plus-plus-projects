#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


using namespace std;
using namespace sf;

const int PPM = 100;
const float g = 9.8 * PPM;

unsigned int screenWidth = 720;
unsigned int screenHeight = 480;


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
 

void updatePhysics(vector<Body>& bodies, float dt){
    for (auto& b : bodies){
        
     
        
        b.vy += g * dt;
        
        b.x += b.vx * dt;
        b.y += b.vy * dt;

        //COLLISION DETECTION FOR EDGES

        // BOTTOM EDGE
        if (b.y + b.radius > screenHeight){
            b.y = screenHeight - b.radius;

            if (b.vy > 0){
                b.vy = b.vy * b.restitution * -1;
            }

        }
        //RIGHT EDGE
        if (b.x + b.radius > screenWidth){
            b.x = screenWidth - b.radius;

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


        b.shape.setPosition({b.x, b.y});

    }

}

int main(){

    float dt = 1.0f/60.0f;

    Body ballOne(screenWidth/2, screenHeight/2, -20*PPM, -10*PPM, 50, 10, 0.9, Color(0,0,255)); 

    vector<Body> bodies;

    bodies.push_back(ballOne);

    RenderWindow* window = new RenderWindow(VideoMode({screenWidth, screenHeight}), "Simulacrum");

    window->setFramerateLimit(60);
    
    while (window->isOpen()){ 
        while (const optional event = window->pollEvent()){
            if (event->is<Event::Closed>()){
                window->close();
            }
        }
        //EVERYTHING HERE HAPPENS EVERY FRAME IE DO THE LOOP HERE \/\/\/
        updatePhysics(bodies, dt);
        
        window->clear(); //ALL DRAWING HAPPENS BETWEEN CLEAR AND DISPLAY

        for (auto& b : bodies){
            window->draw(b.shape);
        }

        window->display();
    }

    delete window;
    return 0;
}