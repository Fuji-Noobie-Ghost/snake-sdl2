#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <snake.h>

using namespace SnakeEngine;

Snake::Snake(SDL_Color color, int size, SDL_Point limit) {
    this->color = color;
    this->size = size;
    // Synchronize the size with the window size
    this->limit.x = limit.x / size;
    this->limit.y = limit.y / size;
}

Snake::~Snake() {
    std::cout << "Destruction" << std::endl;
}

// Init Snake with 4 parts
void Snake::init() {
    this->direction = {1, 0};
    for(int i = 0; i < 4; i++)
        this->queue.push_back({i, 0});
}

// This will set new position for each part of the snake according to the current direction
void Snake::update() {
    // The Head is responsible of the snake's move
    for(std::vector<SDL_Point>::iterator it = this->queue.begin(); it != this->queue.end(); it++) {
        // If the current element is the head, actually the head is the last element
        // Then we need to update his position according to the current direction
        if(it + 1 == this->queue.end()) {
            (*it).x += this->direction.x;
            (*it).y += this->direction.y;
        }
        else *it = *(it + 1); // The new position of the part is the previous position of the next part
    }
}

// Graphics Rendering
void Snake::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer,
        this->color.r,
        this->color.g,
        this->color.b,
        this->color.a
    );

    // Draw Rectangle for each part of the snake
    // Adding 1 pixel as margin
    for(std::vector<SDL_Point>::iterator it = this->queue.begin(); it != this->queue.end(); it++) {
        SDL_Rect part = {this->size * (*it).x + 1, this->size * (*it).y + 1, this->size - 1, this->size - 1};
        SDL_RenderFillRect(renderer, &part);
    }
}

// Keyboard Event Handler
void Snake::setDirection(SDL_Keycode key) {
    switch (key) {
        case SDLK_LEFT: // Left: x = -1 and y = 0 because we need to decrement the x pos
            if(this->direction.x == 0) this->direction = {-1, 0};
            break;

        case SDLK_RIGHT: // Right: x = 1 and y = 0 because we need to increment the x pos
            if(this->direction.x == 0) this->direction = {1, 0};
            break;

        case SDLK_UP: // Up: x = 0 and y = -1 because we need to decrement the y pos
            if(this->direction.y == 0) this->direction = {0, -1};
            break;

        case SDLK_DOWN:  // Down: x = 0 and y = 1 because we need to increment the y pos
            if(this->direction.y == 0) this->direction = {0, 1};
            break;

        default: break;
    }
}

// The Head of the Snake is the last element of the Queue
SDL_Point Snake::getHead() {
    return *(this->queue.end() - 1);
}

// Head Collision Detection with a point
bool Snake::collideWith(SDL_Point collider) {
    SDL_Point head = this->getHead();
    return head.x == collider.x && head.y == collider.y;
}

// Head Collision detection with the window's limit
bool Snake::isOut() {
    SDL_Point head = this->getHead();
    return head.x < 0 || head.y < 0 || head.x >= this->limit.x || head.y >= this->limit.y;
}

void Snake::add(SDL_Point newItem) {
    this->queue.push_back(newItem);
}

bool Snake::testBodyCollision(SDL_Point point, bool isHead) {

    // Test all part of the snake's body
    for(std::vector<SDL_Point>::iterator it = this->queue.begin(); it != this->queue.end(); it++) {
        if (isHead && it + 3 == this->queue.end()) break;

        if ((*it).x == point.x && (*it).y == point.y)
            return true;
    }
    return false;
}