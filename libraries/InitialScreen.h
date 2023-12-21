#include "Rectangles.h"

// Displays first screen
class InitialScreen{

    private:    
        // Defines the menu starting x coordinate, and the top y coordinates of each box
        int menuItemX1 = 85, playY1 = 20, storeY1 = 50, statsY1 = 80, resetY1 = 110, instructY1 = 140, creditsY1 = 170, quitY1 = 200;

        // Next defines the default box width and box height
        int BOX_WIDTH = 150, BOX_HEIGHT = 20;
    public:

        /*
        The method displays the play screen with each menu box.
        @author Jalen
        */
        void display(){

            // Sets background color to scarlet for the display
            LCD.SetBackgroundColor(SCARLET);

            // We clear the current screen and set the font to white
            LCD.Clear();
            LCD.SetFontColor(WHITE);

            // Draws game Title
            LCD.WriteAt("BLOCK HUNTER", 85, 0);
            
            // Draws each item by calling its starting x, y, width, height, using the method
            Rectangles::drawRectangleWithText("Play", menuItemX1, playY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("Store", menuItemX1, storeY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("See Stats", menuItemX1, statsY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("Reset", menuItemX1, resetY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("Instructions", menuItemX1, instructY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("Credits", menuItemX1, creditsY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("Quit", menuItemX1, quitY1, BOX_WIDTH, BOX_HEIGHT, false);
        }

        /*
        Method takes in a pointer to an array and checks the x and y coordinates being touched,
        and then checks if the boxes are in the x range, and if so checks if within the y range
        of all the boxes.
        @author Jalen
        */
        bool handleTouchEvents(bool* array){

            // Defines two floats to detect where the user is touching
            float xTouch,yTouch;

            // Clears touch buffer
            LCD.ClearBuffer();

            // First checks if the touch is in x range
            bool inXRange = xTouch >= menuItemX1 && xTouch <= menuItemX1 + BOX_WIDTH;

            // Boolean keeps track of if a button was touched
            bool foundTouch = false;

            // Checks if screen was clicked
            if (LCD.Touch(&xTouch, &yTouch)){
                
                // Initially sets it to true, but if none of the rectangles are touched, then it turns to false
                foundTouch = true;

                /*
                Checks if each menu box is touched
                */
                if (Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX1,playY1,BOX_WIDTH,BOX_HEIGHT)){
                    *(array) = true;
                } else if ((Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX1,storeY1,BOX_WIDTH,BOX_HEIGHT))){
                    *(array+1) = true;
                } else if ((Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX1,statsY1,BOX_WIDTH,BOX_HEIGHT))){
                    *(array+2) = true;
                } else if ((Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX1,resetY1,BOX_WIDTH,BOX_HEIGHT))){
                    *(array+3) = true;
                } else if ((Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX1,instructY1,BOX_WIDTH,BOX_HEIGHT))){
                    *(array+4) = true;
                } else if ((Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX1,creditsY1,BOX_WIDTH,BOX_HEIGHT))){
                    *(array+5) = true;
                } else if ((Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX1,quitY1,BOX_WIDTH,BOX_HEIGHT))){
                    *(array+6) = true;
                } else {
                    foundTouch = false;
                }
            }

            // Returns the foundTouch boolean
            return foundTouch;
        }
};