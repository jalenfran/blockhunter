class Store{
    private: 

        // Defines item box dimensions and coordinates, and y coordinates for color, time, and size
        int itemX = 85, itemWidth = 160, itemHeight = 25, colorY = 50, timeY = 90, sizeY = 130;

        // Defines coordinates for back the back button
        int backX = 140, backY = 170, backWidth = 50, backHeight = 25;

        // Store menu dimensions and coordinates
        int menuItemX = 10, item1Y = 30, item2Y = 60, item3Y = 90, item4Y = 120, item5Y = 150, menuItemWidth = 80, menuItemHeight = 25;

        // Creates Credits objects for each store item
        Credits coinOne, coinTwo, coinThree, coinFour, coinFive;

    public: 

        // Draws rectangles filled with text for the shopping menu options
        // @author Ayush
        void display(){
            LCD.Clear();
            Rectangles::drawRectangleWithText("Bullet Color", itemX,colorY, itemWidth, itemHeight, false);
            Rectangles::drawRectangleWithText("Reload Time", itemX,timeY, itemWidth, itemHeight, false);
            Rectangles::drawRectangleWithText("Bullet Radius", itemX,sizeY, itemWidth, itemHeight, false);
            Rectangles::drawRectangleWithText("Back", backX,backY, backWidth, backHeight, false);
        }

        /*
        Method takes in two parameters, status and a 2D character array. First the method
        first clear the screen and then draws coins with its cost next to each item box. Then,
        it draws each item box based off the coordinates defined within the class. 
        For each item, it writes the string associated with the appropriate row of the textBoxes parameter.
        Then based on the status passed in, the method draws a different rectangle in the bottom right corner
        if status is 0, then back, or 1- equip, 2 - buy.
        @author Jalen
        */
        void displayStoreMenu(char textBoxes[5][7]){

            // Clears the screen
            LCD.Clear();


            // Changes font color to white
            LCD.SetFontColor(WHITE);

            // Writes text next to each box displaying the cost of the item
            LCD.WriteAt("0", menuItemX+menuItemWidth+5,item1Y+6);
            LCD.WriteAt("50", menuItemX+menuItemWidth+5,item2Y+6);
            LCD.WriteAt("100", menuItemX+menuItemWidth+5,item3Y+6);
            LCD.WriteAt("150", menuItemX+menuItemWidth+5,item4Y+6);
            LCD.WriteAt("200", menuItemX+menuItemWidth+5,item5Y+6);

            // Draws the rectangle with the appropriate row of the textBoxes parameter and itemY variable
            Rectangles::drawRectangleWithText(textBoxes[0],menuItemX,item1Y,menuItemWidth,menuItemHeight, false);
            Rectangles::drawRectangleWithText(textBoxes[1],menuItemX,item2Y,menuItemWidth,menuItemHeight, false);
            Rectangles::drawRectangleWithText(textBoxes[2],menuItemX,item3Y,menuItemWidth,menuItemHeight, false);
            Rectangles::drawRectangleWithText(textBoxes[3],menuItemX,item4Y,menuItemWidth,menuItemHeight, false);
            Rectangles::drawRectangleWithText(textBoxes[4],menuItemX,item5Y,menuItemWidth,menuItemHeight, false);

            // Draws a rectangle at (200,200) with a width of 60 and height of 25 based on if it
            // what the status is. Status: 0-back, 1-equip, 2-buy.
            Rectangles::drawRectangleWithText("Back", 200, 200, 60, 25, false);
        }

        /*
        Method takes in a boolean array and then sets each index of the array to true based on if the region
        is being touched. This is decided by passing in the xTouch and yTouch variables into a method
        along with the coordinates and condition for each appropriate rectangle. This method is useful
        for the shopping menu like, picking the colors, radius, or reload time.
        @author Ayush
        */
        bool handleStoreMenuTouchEvents(bool* array){
            // Initialize two floats to find position
            float xTouch, yTouch;

            // Clears touch buffer
            LCD.ClearBuffer();

            bool touched = false;

            // Displays coins for credit amounts
            coinOne.displayAnimation(menuItemX+menuItemWidth+25, item1Y+12);
            coinTwo.displayAnimation(menuItemX+menuItemWidth+38, item2Y+12);
            coinThree.displayAnimation(menuItemX+menuItemWidth+50, item3Y+12);
            coinFour.displayAnimation(menuItemX+menuItemWidth+50, item4Y+12);
            coinFive.displayAnimation(menuItemX+menuItemWidth+50, item5Y+12);

            // Change those number based off where the proteus is being touched
            
            if (LCD.Touch(&xTouch,&yTouch)){

                touched = true;

                /*
                Next goes down the list for each box to find if any of them are being touched
                if a single one of them is, then the corresponding index is set to true.
                */
                if (Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX,item1Y,menuItemWidth,menuItemHeight)){
                    *array = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX,item2Y,menuItemWidth,menuItemHeight)){
                    *(array+1) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX,item3Y,menuItemWidth,menuItemHeight)){
                    *(array+2) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX,item4Y,menuItemWidth,menuItemHeight)){
                    *(array+3) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,menuItemX,item5Y,menuItemWidth,menuItemHeight)){
                    *(array+4) = true;
                } else if (Rectangles::isPointInsideRect(xTouch, yTouch, 200, 200, 60, 25)){
                    *(array+5) = true;
                } else {
                    touched = false;
                }
            }
            return touched;
        }
        // Method handles whether each of the rectangles are being touched and updates the array passed in
        // This method is used for the original shopping menu to find which category to shop for.
        // @author Ayush
        bool handleTouchEvents(bool* array){

            // Initialize two floats to find position
            float xTouch, yTouch;

            bool hasTouched = true;

            // Change those number based off where the proteus is being touched
            if (LCD.Touch(&xTouch, &yTouch)){
                /*
                Next goes down the list for each box to find if any of them are being touched
                if a single one of them is, then the corresponding index is set to true
                */
                if (Rectangles::isPointInsideRect(xTouch,yTouch,itemX,colorY,itemWidth,itemHeight)){
                    *array = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,itemX,timeY,itemWidth,itemHeight)){
                    *(array+1) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,itemX,sizeY,itemWidth,itemHeight)){
                    *(array+2) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,backX,backY,backWidth,backHeight)){
                    *(array+3) = true;
                } else{
                    hasTouched = false;
                }
            }

            return hasTouched;
        }

        /*
        This method takes in a variable named status, and a 2D character array represetning the text.
        First, a temporary y variable is created which will figure out which y coordinate should be used
        to change the color of a text box. Next a temporary character array is created. The method first
        checks that status is a number greater than 0, and if so it runs a switch case checking for multiple conditions.
        The status is meant for finding which box is being referenced when redrawing, and the textBoxes array passed in
        stores which string to use when redrawing. Lastly, the changeColor method is called which will change the color
        of the box the user hovers over with the new conditions.
        @author Jalen
        */
        void updateStoreMenuItemBoxes(int index, int status, char textBoxes[5][7], int* oldSelection){

            // Creates temporary variables tempY and character array name
            int tempY;
            int tempOldY;
            char name[7];
            char nameOld[7];

            // First checks that status is a number 0 or greater
            if (index > -1){

                // Test for cases 0-4 of the status variable
                // For each case, we change the tempY to the y coordinate of the box
                // and we copy the corresponding string to the name array
                switch (index){

                    // Case 0 indicates we are dealing with the first box
                    case 0:
                        tempY = item1Y;
                        strcpy(name, textBoxes[0]);
                        break;

                    // Case 1 indicates the second box
                    case 1:
                        tempY = item2Y;
                        strcpy(name, textBoxes[1]);
                        break;
                    
                    //The third box
                    case 2:
                        tempY = item3Y;
                        strcpy(name, textBoxes[2]);
                        break;

                    // The fourth box
                    case 3:
                        tempY = item4Y;
                        strcpy(name, textBoxes[3]);
                        break;

                    // The fifth box
                    case 4:
                        tempY = item5Y;
                        strcpy(name, textBoxes[4]);
                }
                // Lastly we call the change color method using the new coordinates and name.
                Rectangles::drawRectangleWithText(name, menuItemX, tempY, menuItemWidth, menuItemHeight, true);
            }

            if (*oldSelection > -1){

                // Test for cases 0-4 of the status variable
                // For each case, we change the tempY to the y coordinate of the box
                // and we copy the corresponding string to the name array
                switch (*oldSelection){

                    // Case 0 indicates we are dealing with the first box
                    case 0:
                        tempOldY = item1Y;
                        strcpy(nameOld, textBoxes[0]);
                        break;

                    // Case 1 indicates the second box
                    case 1:
                        tempOldY = item2Y;
                        strcpy(nameOld, textBoxes[1]);
                        break;
                    
                    //The third box
                    case 2:
                        tempOldY = item3Y;
                        strcpy(nameOld, textBoxes[2]);
                        break;

                    // The fourth box
                    case 3:
                        tempOldY = item4Y;
                        strcpy(nameOld, textBoxes[3]);
                        break;

                    // The fifth box
                    case 4:
                        tempOldY = item5Y;
                        strcpy(nameOld, textBoxes[4]);
                }
                Rectangles::drawRectangleWithText(nameOld, menuItemX, tempOldY, menuItemWidth, menuItemHeight, false);
                *oldSelection = -1;
            }
            // Draws a rectangle at (200,200) with a width of 60 and height of 25 based on if it
            // what the status is. Status: 0-back, 1-equip, 2-buy.
            if (status == 0){
                Rectangles::drawRectangleWithText("Back", 200, 200, 60, 25, false);
            } else if (status == 1){
                Rectangles::drawRectangleWithText("Equip", 200, 200, 60, 25, false);
            } else if (status ==2){
                Rectangles::drawRectangleWithText("Buy", 200, 200, 60, 25, false);
            }
        }
};