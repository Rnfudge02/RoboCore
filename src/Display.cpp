//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Display Module - Developed by Robert Fudge, 2023

//Header file include
#include "../include/Display.hpp"

//Display constructor
Display::Display(int displayUsed, std::string fontName) {
    //Set up file logging
    file = new File("Display");

    //Initialize messages for logging
    initMessages();

    //Get font name for font loading
    std::string fontPath = "./resources/fonts/" + fontName;

    //Notify user that display constructor is called
    std::cout << DISPLAY_CONSTRUCTING << std::endl;
    file->log(DISPLAY_CONSTRUCTING);

    //Set display in use
    displayInUse = displayUsed;

    //Attempt to initialize SDL, if initialization fails, notify user of error and set isRunning to false
    std::cout << SDL_INITIALIZING << std::endl;
    file->log(SDL_INITIALIZING);
    
    if ((SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0)) {

        //Notify user that SDL was successfully initialized
        std::cout << SDL_INIT_SUCCESSFUL << std::endl;
        file->log(SDL_INIT_SUCCESSFUL);

        //Attempt to initialize SDL_Image, if initialization fails, notify user of error and set isRunning to false
        std::cout << SDL_IMAGE_INITIALIZING << std::endl;
        file->log(SDL_IMAGE_INITIALIZING);

        if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG) {

            //Notify user that SDL_Image was successfully initialized
            std::cout << SDL_IMAGE_INIT_SUCCESSFUL << std::endl;
            file->log(SDL_IMAGE_INIT_SUCCESSFUL);

            //Attempt to initialize SDL_TTF, if initialization fails, notify user of error and set isRunning to false
            std::cout << SDL_TTF_INITIALIZING << std::endl;
            file->log(SDL_TTF_INITIALIZING);

            if (TTF_Init() == 0) {

                //Notify user that SDL_TTF was successfully initialized
                std::cout << SDL_TTF_INIT_SUCCESSFUL << std::endl;
                file->log(SDL_TTF_INIT_SUCCESSFUL);

                //Load fontset for SDL_TTF
                font = TTF_OpenFont(fontPath.c_str(), 24);

                //Attempt to acquire display properties, if acquisition fails, attempt to create window and renderer with default parameters
                std::cout << DISPLAY_PROPERTIES_RETRIEVING << std::endl;
                file->log(DISPLAY_PROPERTIES_RETRIEVING);

                if (SDL_GetCurrentDisplayMode(displayInUse, &displayMode) == 0) {
                    //
                    std::cout << DISPLAY_PROPERTIES_RETRIEVED << std::endl;
                    file->log(DISPLAY_PROPERTIES_RETRIEVED);

                    displayModeValid = true;

                    //Call protected initialization functions
                    handleWindowandRenderer(displayMode.w, displayMode.h);
                    initGUI(displayMode.w, displayMode.h);
                    initTextures();
                    initColours();
                }

                //If display properties could not be retrieved, create window and renderer in SD
                else {
                    std::cerr << DISPLAY_PROPERTIES_NOT_RETRIEVED << std::endl;
                    file->log(DISPLAY_PROPERTIES_NOT_RETRIEVED);

                    displayModeValid = false;

                    //Call protected initialization functions
                    handleWindowandRenderer(SD_W, SD_H);
                    initGUI(SD_W, SD_H);
                    initTextures();
                    initColours();
                }

                //Set renderer background color to gray for SDL_RenderClear
                SDL_SetRenderDrawColor(renderer, 90, 90, 90, SDL_ALPHA_OPAQUE);

                //Notify user that display constructor is finished
                std::cout << DISPLAY_CONSTRUCTED << std::endl;
                file->log(DISPLAY_CONSTRUCTED);
            }

            //If SDL_TTF could not be initialized, get error and notify user
            else {
                const char* errMsg = TTF_GetError();
                std::cerr << SDL_TTF_INIT_NOT_SUCCESSFUL << std::endl << errMsg << std::endl;
                file->log(SDL_TTF_INIT_NOT_SUCCESSFUL + std::to_string('\n') + std::string(errMsg));

                isRunning = false;
            }
        }

        //If SDL_Image could not be initialized, get error and notify user
        else {
            const char* errMsg = IMG_GetError();
            std::cerr << SDL_IMAGE_INIT_NOT_SUCCESSFUL << std::endl << errMsg << std::endl;
            file->log(SDL_IMAGE_INIT_NOT_SUCCESSFUL + std::to_string('\n') + std::string(errMsg));

            isRunning = false;
        }
    }

    //If SDL could not be initialized, get error and notify user
    else {
        const char* errMsg = SDL_GetError();
        std::cerr << SDL_INIT_NOT_SUCCESSFUL << std::endl << errMsg << std::endl;
        file->log(SDL_INIT_NOT_SUCCESSFUL + std::to_string('\n') + std::string(errMsg));

        isRunning = false;
    }
}

//Display destructor
Display::~Display() {
    //Notify user that display destructor has been called
    std::cout << DISPLAY_DESTRUCTING << std::endl;
    file->log(DISPLAY_DESTRUCTING);

    //Destroy Textures
    SDL_DestroyTexture(cam1Texture);
    SDL_DestroyTexture(cam2Texture);
    SDL_DestroyTexture(cam3Texture);

    SDL_DestroyTexture(defaultTexture);
    
    SDL_DestroyTexture(terminalTexture);
    SDL_DestroyTexture(fileTexture);

    //Close font and call TTF_Quit()
    TTF_CloseFont(font);
    TTF_Quit();

    //Destroy window and renderer objects, and call SDL_Quit()
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    //Notify user that display destruction was successful
    std::cout << DISPLAY_DESTRUCTED << std::endl;
    file->log(DISPLAY_DESTRUCTED);

    //Close file
    delete file;
}

//Display implementation of pure virtual update() inherited from Observer
void Display::update(const std::string &message) {
    if (message.find('Q') != std::string::npos || message.find('q') != std::string::npos) {
        std::cout << "QUIT" << std::endl;
        isRunning = false;
    }
}

//Function to handle SDL_QUIT
void Display::handleQuit() {
    //Create a SDL event
    SDL_Event event;

    //Run SDL_PollEvent until there are no events left to poll
    while(SDL_PollEvent(&event)) {
        //Switch based on event stored in event variable
        switch(event.type) {
        default:
            break;

        //Handle window closing
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }
}

//Function to draw GUI
void Display::drawGUI() {
    //Clear renderer
    SDL_RenderClear(renderer);

    //Copy textures to renderer for drawing
    SDL_RenderCopy(renderer, cam1Texture, NULL, &cam1Rect);
    SDL_RenderCopy(renderer, cam2Texture, NULL, &cam2Rect);
    SDL_RenderCopy(renderer, cam3Texture, NULL, &cam3Rect);

    SDL_RenderCopy(renderer, defaultTexture, NULL, &defaultRect);

    SDL_RenderCopy(renderer, terminalTexture, NULL, &terminalRect);
    SDL_RenderCopy(renderer, fileTexture, NULL, &fileRect);

    //Draw renderer to screen
    SDL_RenderPresent(renderer);
}

//Pass images to display for GUI drawing
void Display::passToRenderer(cv::Mat frame, int frameNum) {
    switch(frameNum) {
        default:
            std::cout << PASS_TO_RENDERER_FAILED << std::endl;
            file->log(PASS_TO_RENDERER_FAILED);

            return;

        case 1:
            cam1Texture = createTextureFromMat(frame);
            return;

        case 2:
            cam2Texture = createTextureFromMat(frame);
            return;
        
        case 3:
            cam3Texture = createTextureFromMat(frame);
            return;

        case 4:
            defaultTexture = createTextureFromMat(frame);
            return;

        case 5:
            terminalTexture = createTextureFromMat(frame);
            return;

        case 6:
            fileTexture = createTextureFromMat(frame);
            return;

    }
}

//Pass textures to display for GUI drawing (overloaded with SDL_Texture)
void Display::passToRenderer(SDL_Texture* texture, int frameNum) {
    switch(frameNum) {
        default:
            std::cout << PASS_TO_RENDERER_FAILED << std::endl;
            file->log(PASS_TO_RENDERER_FAILED);

            return;

        case 1:
            cam1Texture = texture;
            return;

        case 2:
            cam2Texture = texture;
            return;
        
        case 3:
            cam3Texture = texture;
            return;

        case 4:
            defaultTexture = texture;
            return;

        case 5:
            terminalTexture = texture;
            return;

        case 6:
            fileTexture = texture;
            return;
    }
}

//Function to render folder information
void Display::renderFolder(SDL_Color colour) {
    //Get directory data from instance of File module
    std::string dirData = file->getDirData();

    //If current string returned is the same as the last string, nothing new to render so return
    if (lastDirData.compare(dirData) == 0) {
        return;
    }

    //Update string holding last directory data and create a texture from the text retrieved
    lastDirData = dirData;
    fileTexture = createTextureFromText(dirData, colour, 1);
}

//Matrix to texture conversion helper function
SDL_Texture* Display::createTextureFromMat(cv::Mat image) {
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STREAMING, image.cols, image.rows);
    SDL_UpdateTexture(texture, NULL, (void*)image.data, image.step1());

    if (texture == NULL) {
        std::cout << TEXTURE_FROM_MAT_FAILED << std::endl;
        file->log(TEXTURE_FROM_MAT_FAILED);
    }

    return texture;
}

//Text to texture conversion helper function
SDL_Texture* Display::createTextureFromText(std::string str, SDL_Color colour, int flags) {

    int elementW = 0;

    switch (flags) {
    default:
        elementW = 400;
        break;

    case 1:
        elementW = origFileRect.w;
        break;

    case 2:
        elementW = origTerminalRect.w;
        break;
    }

    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, str.c_str(), colour, elementW);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int tempW;
    int tempH;

    Uint32 f = SDL_PIXELFORMAT_BGR24;
    SDL_QueryTexture(texture, &f, NULL,&tempW,&tempH);

    //Use switch to resize Rects to prevent blurring of text
    switch (flags) {
    default:
        break;

    case 1:
        fileRect.w = tempW;
        fileRect.h = tempH;

        //If text gets too long prevent resizing outside of original boundaries (doesn't need to be done with width as text wrapping handles that)
        if (fileRect.h > origFileRect.h) {

        }

        break;

    case 2:
        terminalRect.w = tempW;
        terminalRect.h = tempH;

        //If text gets too long prevent resizing outside of original boundaries (doesn't need to be done with width as text wrapping handles that)
        if (terminalRect.h > origTerminalRect.h) {

        }

        break;
    }

    //If texture creation fails notify user
    if(texture == NULL) {
        std::cout << TEXTURE_FROM_TEXT_FAILED << std::endl;
        file->log(TEXTURE_FROM_TEXT_FAILED);
    }

    return texture;
}

//Function to check display status
bool Display::getStatus() {
    return isRunning;
}

//Function to get display id
int Display::getDisplay() {
    return displayInUse;
}

//Function to get display width
int Display::getWidth() {
    //If display mode was successfully retrived, return displayMode.w
    if (displayModeValid) {
        return displayMode.w;
    }

    //Else return default width the window was created with
    else {
        return SD_W;
    }
}

//Get screen height function
int Display::getHeight() {
    //If display mode was successfully retrived, return displayMode.h
    if (displayModeValid) {
        return displayMode.h;
    }

    //Else return default height the window was created with
    else {
        return SD_H;
    }
}

//Window and render creation helper function
void Display::handleWindowandRenderer(int width, int height) {
    //Notify user that window is being created
    std::cout << SDL_WINDOW_CREATING << std::to_string(width) << "x" << std::to_string(height) << std::endl;
    file->log(SDL_WINDOW_CREATING + std::to_string(width) + "x" + std::to_string(height));

    //Attempt to create window, if creation fails, send error to std::cerr and set isRunning to false
    window = SDL_CreateWindow("RoboCore GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN);
    
    //If window creation was successful
    if (window != NULL) {
        //Notify user that window creation was successful
        std::cout << SDL_WINDOW_CREATED << std::to_string(width) << "x" << std::to_string(height) << std::endl;
        file->log(SDL_WINDOW_CREATED + std::to_string(width) + "x" + std::to_string(height));

        //Notify user that program is attempting to create hardware accelerated renderer
        std::cout << SDL_RENDERER_HW_CREATING << std::endl;
        file->log(SDL_RENDERER_HW_CREATING);

        //Attempt to create renderer using hardware acceleration, if creation fails, send error to std::cerr and attempt to create window using software rendering
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        //If hardware accelerated renderer creation was successful
        if (renderer != NULL) {
            //
            std::cout << SDL_RENDERER_HW_CREATED << std::endl;
            file->log(SDL_RENDERER_HW_CREATED);

            isRunning = true;
        }

        //If hardware accelerated renderer failed
        else {
            //Notify user that hardware accelerated rendereer creation failed
            std::cerr << SDL_RENDERER_HW_NOT_CREATED << std::endl;
            file->log(SDL_RENDERER_HW_NOT_CREATED);

            //
            std::cout << SDL_RENDERER_SW_CREATING;
            file->log(SDL_RENDERER_SW_CREATING);

            //Attempt to create renderer using software rendering, if initialization fails, send error to std::cerr and set isRunning to false
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

            //If software renderer creation was successful
            if (renderer != NULL) {
                //
                std::cout << SDL_RENDERER_SW_CREATED << std::endl;
                file->log(SDL_RENDERER_SW_CREATED);

                isRunning = true;
            }

            //If software renderer failed
            else {
                std::cerr << SDL_RENDERER_SW_NOT_CREATED << std::endl;
                file->log(SDL_RENDERER_SW_NOT_CREATED);
                
                isRunning = false;
            }
        }
    }

    //If window creation failed
    else {
        std::cerr << SDL_WINDOW_NOT_CREATED << std::endl;
        file->log(SDL_WINDOW_NOT_CREATED);

        isRunning = false;
    }
}

//GUI initialization helper function
void Display::initGUI(int width, int height) {
    //Notify user that GUI elements are initializing
    std::cout << GUI_INITIALIZING << std::endl;
    file->log(GUI_INITIALIZING);

    //Identify number of borders in GUI
    int numBorderX = 4;
    int numBorderY = 4;

    //Calculate the screen borders
    int borderX = int(width/48);
    int borderY = int(height/72);

    //Calculate element sizes
    int elementW = (width - (numBorderX * borderX))/4;
    int elementH = (height - (numBorderY * borderY))/4;

    //Assign correct sizes for elements

    //Cam1 - top left corner
    cam1Rect.x = borderX;
    cam1Rect.y = borderY;
    cam1Rect.w = elementW;
    cam1Rect.h = elementH;

    //Cam2 - to the left of Cam1
    cam2Rect.x = 2 *borderX + cam1Rect.w;
    cam2Rect.y = borderY;
    cam2Rect.w = elementW;
    cam2Rect.h = elementH;

    //Cam3 - below Cam1
    cam3Rect.x = borderX;
    cam3Rect.y = 2 * borderY + cam1Rect.h;
    cam3Rect.w = elementW;
    cam3Rect.h = elementH;

    //User - diagonal to Cam1
    defaultRect.x = 2 * borderX + cam1Rect.w;
    defaultRect.y = 2 * borderY + cam1Rect.h;
    defaultRect.w = elementW;
    defaultRect.h = elementH;

    //Terminal - Right side of screen

    //Original Terminal Rectangle
    origTerminalRect.x = 3 * borderX + cam1Rect.w + cam2Rect.w;
    origTerminalRect.y = borderY;
    origTerminalRect.w = 2 * elementW;
    origTerminalRect.h = height - 2 * borderY;

    //Modifiable Terminal Rectangle
    terminalRect.x = 3 * borderX + cam1Rect.w + cam2Rect.w;
    terminalRect.y = borderY;
    terminalRect.w = 2 * elementW;
    terminalRect.h = height - 2 * borderY;

    //File - Bottom of screen, stretching from left side to border between File and Terminal

    //Original File Rectangle
    origFileRect.x = borderX;
    origFileRect.y = 3 * borderY + cam1Rect.h + cam3Rect.h;
    origFileRect.w = width - terminalRect.w - 3 * borderX;
    origFileRect.h = 2* elementH;

    //Modifiable File Rectangle
    fileRect.x = borderX;
    fileRect.y = 3 * borderY + cam1Rect.h + cam3Rect.h;
    fileRect.w = width - terminalRect.w - 3 * borderX;
    fileRect.h = 2 * elementH;

    //Check that the math worked correctly
    int verifyX =  4 * borderX + cam1Rect.w + cam2Rect.w + terminalRect.w;
    int verifyY = 4 * borderY + cam1Rect.h + cam3Rect.h + fileRect.h;

    //If the math does not work correctly then notify user of a fatal error with the display
    if (verifyX != width || verifyY != height) {
        std::cerr << GUI_INIT_NOT_SUCCESSFUL << std::endl;
        file->log(GUI_INIT_NOT_SUCCESSFUL);

        isRunning = false;
    }

    //Notify user that GUI initialization was successful
    std::cout << GUI_INIT_SUCCESSFUL << std::endl;
    file->log(GUI_INIT_SUCCESSFUL);
}

//Initialize default textures
void Display::initTextures() {
    std::cout << TEXTURES_LOADING << std::endl;
    file->log(TEXTURES_LOADING);

    cam1Texture = IMG_LoadTexture(renderer, "./resources/images/Camera1.png");
    cam2Texture = IMG_LoadTexture(renderer, "./resources/images/Camera2.png");
    cam3Texture = IMG_LoadTexture(renderer, "./resources/images/Camera3.png");

    defaultTexture = IMG_LoadTexture(renderer, "./resources/images/Default.png");

    terminalTexture = IMG_LoadTexture(renderer, "./resources/images/Terminal.png");
    fileTexture = IMG_LoadTexture(renderer, "./resources/images/File.png");

    if (!(cam1Texture == NULL || cam2Texture == NULL || cam3Texture == NULL || defaultTexture == NULL || terminalTexture == NULL || fileTexture == NULL)) {
        std::cout << TEXTURES_LOAD_SUCCESSFUL << std::endl;
        file->log(TEXTURES_LOAD_SUCCESSFUL);
    }

    else {
        std::cout << TEXTURES_LOAD_NOT_SUCCESSFUL << std::endl;
        file->log(TEXTURES_LOAD_NOT_SUCCESSFUL);
    }
}

//Initialize messages for logging purposes
void Display::initMessages() {
    DISPLAY_CONSTRUCTING = "Info: Display constructor called";
    DISPLAY_CONSTRUCTED = "Info: Display constructor successful";

    SDL_INITIALIZING = "Info: Initializing SDL";
    SDL_INIT_SUCCESSFUL = "Info: SDL successfully initialized";
    SDL_INIT_NOT_SUCCESSFUL = "Error (FATAL): Could not initialize SDL";

    SDL_IMAGE_INITIALIZING = "Info: Initializing SDL_Image";
    SDL_IMAGE_INIT_SUCCESSFUL = "Info: SDL_Image successfully initialized";
    SDL_IMAGE_INIT_NOT_SUCCESSFUL = "Error (FATAL): Could not initialize SDL_Image";

    SDL_TTF_INITIALIZING = "Info: Initializing SDL_TTF";
    SDL_TTF_INIT_SUCCESSFUL = "Info: SDL successfully initialized SDL_TTF";
    SDL_TTF_INIT_NOT_SUCCESSFUL = "Error (FATAL): Could not initialize SDL_TTF";

    DISPLAY_PROPERTIES_RETRIEVING = "Info: Retrieving display properties";
    DISPLAY_PROPERTIES_RETRIEVED = "Info: Display properties sucessfully retrieved";
    DISPLAY_PROPERTIES_NOT_RETRIEVED = "Error (NON-FATAL): Could not retrieve display properties, falling back to " + std::to_string(SD_W) + "x" + std::to_string(SD_H);

    PASS_TO_RENDERER_FAILED = "Error (Non-Fatal): Could not pass image to renderer, was the right index specified?";

    SDL_WINDOW_CREATING = "Info: Creating window with resolution ";
    SDL_WINDOW_CREATED = "Info: Window created successfully with resolution ";
    SDL_WINDOW_NOT_CREATED = "Error (FATAL): Could not create window";

    SDL_RENDERER_HW_CREATING = "Info: Creating hardware-accelerated renderer";
    SDL_RENDERER_HW_CREATED = "Info: Hardware-accelerated renderer created successfully";
    SDL_RENDERER_HW_NOT_CREATED = "Error (NON-FATAL): Could not create hardware-accelerated renderer";

    SDL_RENDERER_SW_CREATING = "Info: Creating software renderer";
    SDL_RENDERER_SW_CREATED = "Info: Software renderer created successfully";
    SDL_RENDERER_SW_NOT_CREATED = "Error (FATAL): Could not create software renderer";

    GUI_INITIALIZING = "Info: Initializing GUI elements";
    GUI_INIT_SUCCESSFUL = "Info: GUI elements successfully initialized";
    GUI_INIT_NOT_SUCCESSFUL = "Error (FATAL): GUI elements could not be initialized, sum of element dimensions were outside of margin of error";

    TEXTURES_LOADING = "Info: Loading default textures";
    TEXTURES_LOAD_SUCCESSFUL = "Info: Textures successfully loaded";
    TEXTURES_LOAD_NOT_SUCCESSFUL = "Error (NON-FATAL): Textures could not be loaded";

    TEXTURE_FROM_MAT_FAILED = "Error (NON-FATAL): Could not create texture from opencv matrix";
    TEXTURE_FROM_TEXT_FAILED = "Error (NON-FATAL): Could not create texture from text";

    DISPLAY_DESTRUCTING = "Info: Display deconstructor called";
    DISPLAY_DESTRUCTED = "Info: Display successfully destroyed\n\nEOF";
}

//Initialize colours for later use
void Display::initColours() {
    WHITE = {255, 255, 255, 0};
    BLACK = { 0, 0, 0, 0};
    RED = {255, 0, 0, 0};
    GREEN = {0, 255, 0, 0};
    BLUE = {0, 0, 255, 0};
    YELLOW = {255, 255, 0, 0};
    MAGENTA = {255, 0, 255, 0};
    CYAN = {0, 255, 255, 0};
}

//End Display.cpp