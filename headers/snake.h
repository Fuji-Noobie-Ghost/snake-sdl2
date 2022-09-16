#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <SDL2/SDL.h>
#include <vector>

namespace SnakeEngine {
    class Snake {
        private:
            SDL_Color color;
            int size;
            std::vector<SDL_Point> queue; // List containing position of each part
            SDL_Point direction;
            SDL_Point limit;

        public:

            /**
             * Create a new Snake
             * @param color The snake color
             * @param size The size of a part
             * @param windowSize The actual window size
             */
            Snake(SDL_Color, int, SDL_Point);
            /**
             * Destructor of the snake
             */
            ~Snake();

            /**
             * Init the snake list and direction
             */
            void init();

            /**
             * Update the snake position according to his current direction
             */
            void update();

            /**
             * Render the snake into the current renderer
             * @param renderer The rendering context
             */
            void render(SDL_Renderer*);
            
            /**
             * @return The current position of the head
             */
            SDL_Point getHead();

            /**
             * Update the snake direction according to the key pressed
             * @param keyCode The Key Code of the key pressed
             */
            void setDirection(SDL_Keycode);

            /**
             * Check if the head collide with a point
             * @param point The point to check the collision with
             */
            bool collideWith(SDL_Point);

            /**
             * Check if the head collide with the window's limit
             */
            bool isOut();

            /**
             * Add new item to the snake after eating the target
             * @param targetPos The target position
             */
            void add(SDL_Point);

            /**
             * Test if the snake's body collide with a specific point
             * @param point The collider point
             * @param isHead Set to true if you want to test the collision with the snake's head
             */
            bool testBodyCollision(SDL_Point, bool);
    };

    class SnakeTarget {
        private:
            SDL_Color color;
            int size;
            SDL_Point limit;
            SDL_Point currentPos;

        public:

            /**
             * Create a new Snake Target
             * @param color The target color
             * @param size The size of a part
             * @param windowSize The actual window size
             */
            SnakeTarget(SDL_Color, int, SDL_Point);

            SDL_Point getCurrentPos();

            /**
             * Generate random position for the Snake Target
             */
            void generateRandomPosition();

            /**
             * Render the target into the current renderer
             * @param renderer The rendering context
             */
            void render(SDL_Renderer*);
    };
}

#endif