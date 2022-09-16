#include <SDL2/SDL.h>
#include <cstdlib>
#include <time.h>
#include <snake.h>

using namespace SnakeEngine;

SnakeTarget::SnakeTarget(SDL_Color color, int size, SDL_Point limit) {
    this->color = color;
    this->size = size;
    // Synchronize the size with the window size
    this->limit.x = limit.x / size;
    this->limit.y = limit.y / size;
    this->generateRandomPosition(); // Initialize currentPos
}

SDL_Point SnakeTarget::getCurrentPos() {
    return this->currentPos;
}

void SnakeTarget::generateRandomPosition() {
    // Initialize random
    srand(time(NULL));
    SDL_Point pos;
    // Generate random value for x and y
    pos.x = 0 + (rand() % this->limit.x);
    pos.y = 0 + (rand() % this->limit.y);
    this->currentPos = pos;
}

// Rendering the target according to his size and position
void SnakeTarget::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer,
        this->color.r,
        this->color.g,
        this->color.b,
        this->color.a
    );
    SDL_Rect target = {this->size * this->currentPos.x, this->size * this->currentPos.y, this->size, this->size};
    SDL_RenderFillRect(renderer, &target);
}