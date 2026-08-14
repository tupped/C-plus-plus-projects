#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <time.h>

using namespace std;
using namespace sf;



struct {
    unsigned int screenWidth = 720;
    unsigned int screenHeight = 480;

    const float paddleBuffer = screenWidth/12;

    const float FPS = 120;

    const int PPM = 250; //PIXEL PER METRE

    


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
    private:
        Font font{"JETBRAINSMONO-VARIABLEFONT_WGHT.TTF"}; //DOES NOT WORK IF FONT FILE IS NOT IN FILE FOLDER 
        int scoreFontSize = 15;

    public:
        bool leftOrRight;

        float x;
        float y = Config.screenHeight/2;

        float length = 5;
        float width = Config.screenHeight/8;

        float vy;

        RectangleShape shape;

        Text paddleScore{font};

        int paddleScoreInt = 0;


    Paddle(bool side){

        paddleScore.setCharacterSize(scoreFontSize);
        paddleScore.setFillColor(Color(255,255,255));

        
        if (side){
            x = Config.paddleBuffer; //IF SIDE IS TRUE/ONE PADDLE IS ON THE LEFT
            paddleScore.setPosition({Config.screenWidth/2 - 15.0f, 15});
        } else {
            x = Config.screenWidth - Config.paddleBuffer; //IF SIDE IS FALSE/ZERO PADDLE IS ON RIGHT
            paddleScore.setPosition({Config.screenWidth/2 + 15.0f, 15});
        }


        shape = RectangleShape({length, width});
        shape.setOrigin({length/2, width/2});
        shape.setPosition({x, y});
        shape.setFillColor(Color(255,255,255));
    }

};

int coinFlip(){
    int randomNumber = rand() % 101;
    // cout << randomNumber << '\n';

    if (randomNumber % 2 == 0){
        // cout << 1 << '\n';
        return 1;
    } else {
        // cout << -1 << '\n';
        return -1;
    }
}


void paddleMove(Paddle& paddle, string direction, float dt){
    int paddleSpeed = 500;

    if (paddle.y < Config.screenHeight - paddle.width/2 && paddle.y > 0 + paddle.width/2){
        if(direction == "UP"){ 
            paddle.y -= paddleSpeed * dt;
            paddle.shape.setPosition({paddle.x, paddle.y});
        } 
        else if (direction == "DOWN") {
            paddle.y += paddleSpeed * dt;
            paddle.shape.setPosition({paddle.x, paddle.y});
        } else {
            cout << "Invalid Direction";
        }
    } else if (paddle.y >= Config.screenHeight - paddle.width/2){
        paddle.y -= paddleSpeed * dt;
    } else if (paddle.y <= 0 + paddle.width/2){
        paddle.y += paddleSpeed * dt;
    }
}

void resetBall(Ball& ball){
    cout << "Resetting";

    for (int i=0; i<1000000001; i++){
        if (i == 1000000000){
        
            ball.x = Config.screenWidth/2;
            ball.y = Config.screenHeight/2;
            
            ball.vx = 1*coinFlip()*Config.PPM;
            ball.vy = 1*coinFlip()*Config.PPM;
        }
    }

}

void ballMove(Ball& ball, Paddle& leftPaddle, Paddle& rightPaddle, float dt){

    ball.x += ball.vx * dt;
    ball.y += ball.vy * dt;

    if (ball.y <= ball.radius){
        ball.vy = ball.vy*-1;
    }
    if (ball.y >= Config.screenHeight + ball.radius){
        ball.vy = ball.vy*-1;
    }
    if (ball.x <= ball.radius){ //LEFT COLLISION
        ball.vx = 0;
        ball.vy = 0;

        
        rightPaddle.paddleScoreInt += 1;
        rightPaddle.paddleScore.setString(to_string(rightPaddle.paddleScoreInt));
        
        resetBall(ball);
        
    }
    if (ball.x >= Config.screenWidth - ball.radius){ //RIGHT COLLISION
        ball.vx = 0;
        ball.vy = 0;
        leftPaddle.paddleScoreInt += 1;
        leftPaddle.paddleScore.setString(to_string(leftPaddle.paddleScoreInt));
        
        resetBall(ball);

    }

    if (ball.x + ball.radius <= leftPaddle.x + leftPaddle.length/2 && ball.x + ball.radius >= leftPaddle.x - leftPaddle.length/2 && ball.y + ball.radius <= leftPaddle.y + leftPaddle.width/2 && ball.y - ball.radius >= leftPaddle.y - leftPaddle.width/2){
        ball.vx = ball.vx*-1;
    }
    if (ball.x - ball.radius >= rightPaddle.x - rightPaddle.length/2 && ball.x - ball.radius <= rightPaddle.x + rightPaddle.length/2 &&  ball.y + ball.radius <= rightPaddle.y + rightPaddle.width/2 && ball.y - ball.radius >= rightPaddle.y - rightPaddle.width/2){
        ball.vx = ball.vx*-1;
    }

    ball.shape.setPosition({ball.x, ball.y});
}


int main(){
    float dt = 1.0f/Config.FPS;

    srand(time(0));

    
    Ball ball{};

   

    Paddle rightPaddle(0);
    Paddle leftPaddle(1);

    ball.vx = 1*coinFlip()*Config.PPM;
    ball.vy = 1*coinFlip()*Config.PPM;

    leftPaddle.paddleScore.setString(to_string(leftPaddle.paddleScoreInt));
    rightPaddle.paddleScore.setString(to_string(rightPaddle.paddleScoreInt));




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
                paddleMove(rightPaddle, "UP", dt);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
                paddleMove(rightPaddle, "DOWN", dt);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::W)){
                paddleMove(leftPaddle, "UP", dt);
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::S)){
               paddleMove(leftPaddle, "DOWN", dt);

            }

            ballMove(ball, leftPaddle, rightPaddle, dt);

            window->clear();

            //RENDER
            window->draw(ball.shape);
            window->draw(leftPaddle.shape);
            window->draw(rightPaddle.shape);
            window->draw(leftPaddle.paddleScore);
            window->draw(rightPaddle.paddleScore);


            window->display();
        }    
    return 0;
}
