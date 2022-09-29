#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);
    int lives = 3;
    int lives2 = 3;
    // Create a bat at the bottom center of the screen
    Bat bat(20, 1080 / 2);
    Bat bat2(1900, 1080 / 2);

    // Create a ball
    Ball ball(1920 / 2, 1080 / 2);

    // Create a Text object called HUD
    Text hud;
    // A cool retro-style font
    Font font;
    font.loadFromFile("Fonds/ka1.ttf");
    // Set the font to our retro-style
    hud.setFont(font);
    // Make it nice and big
    hud.setCharacterSize(75);
    // Choose a color
    hud.setFillColor(Color::White);
    hud.setPosition(600, 20);
    // Here is our clock for timing everything
    Clock clock;

    bool paused = true;

    while (window.isOpen())
    {

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
        }

        if (paused) {
            hud.setPosition(1080 / 2, 20);
            std::stringstream ss;
            ss << "Press ENTER to start";
            hud.setString(ss.str());
        }
        /*
        Handle the player input
        ****************************
        ****************************
        ****************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                // Quit the game when the window is closed
                window.close();
        }

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            bat.moveUp();
        }
        else
        {
            bat.stopUp();
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            bat.moveDown();
        }
        else
        {
            bat.stopDown();
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            bat2.moveUp();
        }
        else
        {
            bat2.stopUp();
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            bat2.moveDown();
        }
        else
        {
            bat2.stopDown();
        }
        /*
        Update the bat, the ball and the HUD
        *****************************
        *****************************
        *****************************
        */
        if (!paused) {
            // Update the delta time
            Time dt = clock.restart();

            bat.update(dt);
            bat2.update(dt);
            ball.update(dt);

            // Update the HUD text
            std::stringstream ss;
            ss << "Lives:" << lives << "        Lives2:" << lives2;
            hud.setString(ss.str());

            if (Keyboard::isKeyPressed(Keyboard::R)) {
                paused = true;
            }

            
        }
        // Handle ball hitting the bottom
        if (ball.getPosition().top < 0 || ball.getPosition().top + ball.getPosition().height > window.getSize().y)
        {
            // reverse the ball direction
            ball.reboundBottomOrTop();


        }


        // Handle ball hitting sides
        if (ball.getPosition().left < 0)
        {
            ball.reboundSides();

            lives--;
            // Check for zero lives
            if (lives <= 0) {

                // reset the lives
                paused = true;
                std::stringstream ss;
                ss << "Player 2 wins";
                hud.setString(ss.str());
            }
        }

        if (
            ball.getPosition().left + ball.getPosition().width >
            window.getSize().x)
        {
            ball.reboundSides();

            lives2--;
            // Check for zero lives
            if (lives2 <= 0) {

                // reset the lives
                paused = true;
                std::stringstream ss;
                ss << "Player 1 wins";
                hud.setString(ss.str());
            }
        }
        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()) || ball.getPosition().intersects(bat2.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundBat();
        }
        /*
        Draw the bat, the ball and the HUD
        *****************************
        *****************************
        *****************************
        */
        window.clear();
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(bat2.getShape());
        window.draw(ball.getShape());
        window.display();
    }
    return 0;
}