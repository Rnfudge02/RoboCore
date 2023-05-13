//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Display Module - Developed by Robert Fudge, 2023

//Display.hpp include guard
#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

//Macros containing default SD screen dimensions
#define SD_W 720
#define SD_H 576

//SDL header includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//OpenCV header include
#include <opencv2/opencv.hpp>

//Observer header include
#include "../include/Observer.hpp"

//File header include (Technically not best practice but no other way to implement)
#include "../include/File.hpp"

//Display class
class Display : public Observer {
public:
    //Public functions

    //Constructor and destructor
    Display(int displayUsed = 0, std::string fontName = "");
    ~Display();

    //Input and data handling functions
    virtual void update(const std::string &message) override;
    void handleQuit();

    //Rendering functions
    void drawGUI();

    //Methods for passing in images to render
    void passToRenderer(cv::Mat frame, int frameNum = 4);
    void passToRenderer( SDL_Texture* texture, int frameNum = 4);

    //Method for rendering folder information
    void renderFolder(SDL_Color colour);

    //Methods for creating textures from various inputs
    SDL_Texture* createTextureFromMat(cv::Mat image);
    SDL_Texture* createTextureFromText(std::string str, SDL_Color colur, int flags = 0);

    //Display information functions
    bool getStatus();
    bool isModeValid();
    int getDisplay();
    int getWidth();
    int getHeight();

    //Font Colors
    SDL_Color WHITE;
    SDL_Color BLACK;
    SDL_Color RED;
    SDL_Color GREEN;
    SDL_Color BLUE;
    SDL_Color YELLOW;
    SDL_Color MAGENTA;
    SDL_Color CYAN;

protected:
    //Protected members

    //File object (for logging purposes)
    File* file;

    //String holding last directory data
    std::string lastDirData;

    //String Messages
    std::string DISPLAY_CONSTRUCTING;
    std::string DISPLAY_CONSTRUCTED;

    std::string SDL_INITIALIZING;
    std::string SDL_INIT_SUCCESSFUL;
    std::string SDL_INIT_NOT_SUCCESSFUL;

    std::string SDL_IMAGE_INITIALIZING;
    std::string SDL_IMAGE_INIT_SUCCESSFUL;
    std::string SDL_IMAGE_INIT_NOT_SUCCESSFUL;

    std::string SDL_TTF_INITIALIZING;
    std::string SDL_TTF_INIT_SUCCESSFUL;
    std::string SDL_TTF_INIT_NOT_SUCCESSFUL;

    std::string DISPLAY_PROPERTIES_RETRIEVING;
    std::string DISPLAY_PROPERTIES_RETRIEVED;
    std::string DISPLAY_PROPERTIES_NOT_RETRIEVED;

    std::string PASS_TO_RENDERER_FAILED;

    std::string SDL_WINDOW_CREATING;
    std::string SDL_WINDOW_CREATED;
    std::string SDL_WINDOW_NOT_CREATED;

    std::string SDL_RENDERER_HW_CREATING;
    std::string SDL_RENDERER_HW_CREATED;
    std::string SDL_RENDERER_HW_NOT_CREATED;

    std::string SDL_RENDERER_SW_CREATING;
    std::string SDL_RENDERER_SW_CREATED;
    std::string SDL_RENDERER_SW_NOT_CREATED;

    std::string GUI_INITIALIZING;
    std::string GUI_INIT_SUCCESSFUL;
    std::string GUI_INIT_NOT_SUCCESSFUL;

    std::string TEXTURES_LOADING;
    std::string TEXTURES_LOAD_SUCCESSFUL;
    std::string TEXTURES_LOAD_NOT_SUCCESSFUL;

    std::string TEXTURE_FROM_MAT_FAILED;
    std::string TEXTURE_FROM_TEXT_FAILED;
    
    std::string DISPLAY_DESTRUCTING;
    std::string DISPLAY_DESTRUCTED;

    //State variables
    bool isRunning;
    int displayInUse;
    bool displayModeValid;

    //SDL members
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_DisplayMode displayMode;

    //TrueType Font for use in window
    TTF_Font* font;

    //SDL_Rects for GUI rendering
    SDL_Rect cam1Rect;
    SDL_Rect cam2Rect;
    SDL_Rect cam3Rect;

    SDL_Rect defaultRect;

    //Original SDL_Rects for Terminal and File, actual Rects will be resized
    SDL_Rect origTerminalRect;
    SDL_Rect origFileRect;

    //Dynamic SDL_Rects for Terminal and File, will need to be resized in text rendering function, which is done by the user passing flags
    SDL_Rect terminalRect;
    SDL_Rect fileRect;

    //SDL_Texture pointers to hold textures for rendering
    SDL_Texture* cam1Texture;
    SDL_Texture* cam2Texture;
    SDL_Texture* cam3Texture;

    SDL_Texture* defaultTexture;

    SDL_Texture* terminalTexture;
    SDL_Texture* fileTexture;

    //Protected methods
    void handleWindowandRenderer(int width, int height);
    void initGUI(int width, int height);
    void initTextures();
    void initMessages();
    void initColours();

private:

};

#endif  //End Display.hpp