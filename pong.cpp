#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;



struct {
    unsigned int screenWidth = 720;
    unsigned int screenHeight = 480;

    const float paddleBuffer = screenWidth/12;

    const float FPS = 60;

}Config;

class Ball {
    public:
        float radius = 5;

        float x = Config.screenWidth/2;
        float y = Config.screenHeight/2;

        float vx;
        float vy;

        CircleShape shape;

    Ball(){

        shape = CircleShape(radius);
        shape.setOrigin({radius,radius});
        shape.setPosition({x, y});
        shape.setFillColor(Color(255,255,255));

    }

};

class Paddle {
    public:
        bool leftOrRight;

        float x;
        float y = Config.screenHeight/2;

        float length = 5;
        float width = Config.screenHeight/8;

        float vy;

        RectangleShape shape;

    Paddle(bool side){

        if (side){
            x = Config.paddleBuffer; //IF SIDE IS TRUE/ONE PADDLE IS ON THE LEFT
        } else {
            x = Config.screenWidth - Config.paddleBuffer; //IF SIDE IS FALSE/ZERO PADDLE IS ON RIGHT
        }


        shape = RectangleShape({length, width});
        shape.setOrigin({length/2, width/2});
        shape.setPosition({x, y});
        shape.setFillColor(Color(255,255,255));
    }

};

void paddleMove(Paddle& paddle, string direction){
    int paddleSpeed = 5;

    if (paddle.y < Config.screenHeight - paddle.width/2 && paddle.y > 0 + paddle.width/2){
        if(direction == "UP"){ 
            paddle.y -= paddleSpeed;
            paddle.shape.setPosition({paddle.x, paddle.y});
        } 
        else if (direction == "DOWN") {
            paddle.y += paddleSpeed;
            paddle.shape.setPosition({paddle.x, paddle.y});
        } else {
            cout << "Invalid Direction";
        }
    } else if (paddle.y >= Config.screenHeight - paddle.width/2){
        paddle.y -= paddleSpeed;
    } else if (paddle.y <= 0 + paddle.width/2){
        paddle.y += paddleSpeed;
    }
}




int main(){
    float dt = 1.0f/Config.FPS;

    
    Ball ball{};

    Paddle rightPaddle(0);
    Paddle leftPaddle(1);
    


    RenderWindow* window = new RenderWindow(VideoMode({Config.screenWidth, Config.screenHeight}), "Pong");

        window->setFramerateLimit(Config.FPS);
        
        while (window->isOpen()){ 
            while (const optional event = window->pollEvent()){
                if (event->is<Event::Closed>()){
                    window->close();
                }
         
         
            }
            //PUT GAME LOOP HERE
            
            
            if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
                paddleMove(rightPaddle, "UP");
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                paddleMove(rightPaddle, "DOWN");
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::W)){
                paddleMove(leftPaddle, "UP");
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::S)){
               paddleMove(leftPaddle, "DOWN");

            }


        

            window->clear();

            //RENDER
            window->draw(ball.shape);
            window->draw(leftPaddle.shape);
            window->draw(rightPaddle.shape);


            window->display();
        }    
    return 0;
}
