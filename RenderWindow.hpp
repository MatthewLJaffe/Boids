#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


class RenderWindow
{
    public:
        RenderWindow(const RenderWindow&) = delete;
        static int WIDTH;
        static int HEIGHT;
        static RenderWindow& Instance();
        SDL_Texture* loadTexture(const char* filePath);
        void cleanUp();
        void clear();
        void render(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, double angle);
        void drawLine(int x1, int y1, int x2, int y2);
        void display();
        void setScale(float x, float y);
        SDL_Texture* createFontTexture(SDL_Surface* textSurf);
        void drawPoint(float x, float y);
    private:
        RenderWindow();
        std::vector<SDL_Texture*> textures;
        SDL_Window* window;
        SDL_Renderer* renderer;
};