#include "Assets.hpp"

Assets& Assets::Instance()
{
    static Assets assets;
    return assets;
}

void Assets::loadAssets()
{
    loadImages();
    loadFonts();
}

void Assets::loadImages()
{
    RenderWindow &rw = RenderWindow::Instance();
    testSprite = rw.loadTexture("Assets/Images/TestSprite.png");
    triangleSprite = rw.loadTexture("Assets/Images/newTriangle.png");
    triangleSpriteGreen = rw.loadTexture("Assets/Images/greenTriangle.png");
    triangleSpriteYellow = rw.loadTexture("Assets/Images/yellowTriangle.png");
    predatorSprite = rw.loadTexture("Assets/Images/predatorTriangle.png");
    green = rw.loadTexture("Assets/Images/green.png");
    foodSprite = rw.loadTexture("Assets/Images/Food.png");
    boundarySprite = rw.loadTexture("Assets/Images/boundary.png");
    sliderSprite = rw.loadTexture("Assets/Images/Slider.png");
    knobSprite = rw.loadTexture("Assets/Images/Knob.png");
}

void Assets::loadFonts()
{
    font = TTF_OpenFont("Assets/Fonts/OpenSans-Regular.ttf", 24);
}

void Assets::closeFonts()
{
    TTF_CloseFont(font);
}

Assets::Assets() {}
