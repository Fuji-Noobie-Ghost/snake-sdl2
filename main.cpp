#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <snake.h>

#define CENTER SDL_WINDOWPOS_CENTERED
#define MILLIS 1000.0
#define FRAMERATE 10.0
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500
#define ITEM_SIZE 20

using namespace std;
using namespace SnakeEngine;

void update(SDL_Renderer* renderer) {
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

int main(int argc, char** argv) {
    // Initialize graphics interface
    SDL_Init(SDL_INIT_VIDEO);
    // Create a SDL window centered
    SDL_Window* window = SDL_CreateWindow("Snake", CENTER, CENTER, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    // Create a renderer that will renderer all the graphics settings
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_SOFTWARE);

    /* Snake Initialization */
    SDL_Color snakeColor = {255, 255, 0, 255}; // rgba Yellow
    // Creating a snake that will run on the current window
    Snake* snake = new Snake(snakeColor, ITEM_SIZE, {WINDOW_WIDTH, WINDOW_HEIGHT});
    snake->init();

    // Create a snake target
    SDL_Color targetColor = {0, 0, 255, 255}; // rgba Blue color
    SnakeTarget* target = new SnakeTarget(targetColor, ITEM_SIZE, {WINDOW_WIDTH, WINDOW_HEIGHT});

    bool quit = false; // Usefull for quit event
    int score = 0;

    while (!quit) {
        SDL_Event e; // Main Event Target
        SDL_PollEvent(&e); // Pass the current Event to the event target
        // if the player clicked on the exit button or press ESC
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) quit = true;
        
        if(e.type == SDL_KEYDOWN) snake->setDirection(e.key.keysym.sym);

        // The snake collide with the limit of the window
        // Or snake collide with himself
        if(snake->isOut() || snake->testBodyCollision(snake->getHead(), true)) quit = true;
        
        else {
            // Check if the snake eat the target XD
            if(snake->collideWith(target->getCurrentPos())) {
                // Add the target to snake
                snake->add(target->getCurrentPos());
                
                // Generate target position until it doesn't collide with the snake's body
                do {
                    target->generateRandomPosition();
                } while (snake->testBodyCollision(target->getCurrentPos(), false));

                score++;
            }
            else snake->update(); // Update snake's position
            
            snake->render(renderer); // Render the snake
            target->render(renderer); // Render the target
            SDL_Delay(1000 / FRAMERATE); // Wait for a specific delay
        }

        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255); // Dark color for the background
        update(renderer); // Update the screen
    }

    cout << "\n\n\t\tGAME OVER" << endl;
    cout << "\t\tScore: " << score << "\n\n";

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
