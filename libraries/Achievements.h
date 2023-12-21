class Achievements{
    private: 
        
        // Defines a boolean array for every single achievement
        bool achievements[15] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

        // Defines parameters for each achievement pane
        int paneHeight = 40, paneWidth = 220, paneX = 50, item1Y = 25, item2Y = 75, item3Y = 125;

        // Defines parameters for the back and next buttons
        int backHeight = 25, backWidth = 60, backX = 50, backY = 180;
        int nextHeight = 25, nextWidth = 60, nextX = 210, nextY = 180;

    public:

        //Method that runs a check on each boolean value and updates it based on the stats imported from stats
        // @author Ayush
        void updateAchievements(Stats stats){

            // Creates a stats array that contains the current stats 
            // Index 0 - games, 1 - items bought, 2 - hits, 3 - high scores, 4 - misses, 5 - challenges played, 6 - challenges won
            int importantStats[7];
            stats.getStatsForAchievements(importantStats);

            /*
            Goes down and checks if each index of the achievements array is false, if so re-evaluates to see 
            if it should be true.
            */

            // Pixel Pioneer
            if (!achievements[0]){

                // Checks if 1 or more games have been played
                achievements[0] = importantStats[0] >= 1;
            } 
            // Inaugural Acquisition
            if (!achievements[1]){

                // Checks if one or more items have been played
                achievements[1] = importantStats[1] >= 1;
            }
            // Game Decimator
            if (!achievements[2]){

                // Checks if 10 games have been played
                achievements[2] = importantStats[0] >= 10;
            }
            // Munitions Maestro
            if (!achievements[3]){

                // Checks if 50 total hits
                achievements[3] = importantStats[2] >= 50;
            }
            // Ammo Annarchist 
            if (!achievements[4]){

                // Checks if 100 total hits
                achievements[4] = importantStats[2] >= 100;
            }
            // Aimless Amigo
            if (!achievements[5]){

                // Checks if 50 total misses
                achievements[5] = importantStats[4] >= 50;
            }
            // Target Tantrum
            if (!achievements[6]) {

                // Checks if 100 total misses
                achievements[6] = importantStats[4] >= 100;
            }
            // Hitman Hurricane
            if (!achievements[7]){

                // Checks if 25 hits in a game
                achievements[7] = importantStats[3] >= 25;
            }
            // Ruthless Rainmaker
            if (!achievements[8]){

                // Checks if 50 hits in one game
                achievements[8] = importantStats[3] >= 50;
            }
            // Casino Clown
            if (!achievements[9]){

                // Checks if 5 challenges have been lost
                achievements[9] = importantStats[5] - importantStats[6] >= 5;
            }
            // Dicey Delight
            if (!achievements[10]){

                // Checks if 10 challenges have been completed
                achievements[10] = importantStats[5] >= 10;
            }
            // Lucky Lark
            if (!achievements[11]){

                // Checks if 5 or more challenges have been won
                achievements[11] = importantStats[6] >= 5;
            }
            // Jackpot Juggernaut
            if (!achievements[12]){

                // Checks if 10 or more challenges have been won
                achievements[12] = importantStats[6] >= 10;
            }
            // Shopaholic
            if (!achievements[13]){

                // Checks if each item is bought (12 items bought)
                achievements[13] = importantStats[1] == 12;
            }
            // Get a life
            if (!achievements[14]){
                achievements[14] = achievements[10] && achievements[4] && achievements[6] && achievements[8];
                achievements[14] = achievements[14] && achievements[11] && achievements[13];
            }
        }

        /*
        Method that writes and centers the name and description for each box based on the startY passed in.
        @author Jalen
        */
        void writeAchievementNameAndDescription(char name[], char description[], int startY){

            // Sets font color to black
            LCD.SetFontColor(BLACK);

            // Finds length of the name passed in and description
            int nameWidth = strlen(name)*12, descriptionWidth = strlen(description)*12;

            // Finds where they should start so that they are centered
            int nameXStart = (paneWidth-nameWidth)/2+paneX;
            int descriptionXStart = (paneWidth-descriptionWidth)/2+paneX;

            // Writes each name and description based on nameXStart, descriptionXStart and the startY.
            LCD.WriteAt(name, nameXStart, startY+2);
            LCD.WriteAt(description, descriptionXStart, startY+21);
        }

        /*
        Draws multiple white or yellow rectangles depending on if the specific achievement is true. It also
        displays each the text and a description for each achievement. Also draws a back or next button,
        that keeps track of if we should go to the previous menu or next pane.
        @author Jalen
        */
        void displayPaneOne(){

            // Clears screen and sets font color to white
            LCD.Clear();
            LCD.SetFontColor(WHITE);

            // Writes achievements menu
            LCD.WriteAt("Achievements", 88, 5);

            // Draws rectangles, either yellor or white depending on if the achievement has been obtained
            Rectangles::drawRectangleWhiteOrYellow(paneX,item1Y, paneWidth, paneHeight, achievements[0]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item2Y, paneWidth, paneHeight, achievements[1]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item3Y, paneWidth, paneHeight, achievements[2]);

            // Writes each name and description along with its appropriate y index
            writeAchievementNameAndDescription("Pixel Pioneer", "Play 1 Game", item1Y);
            writeAchievementNameAndDescription("Retail Rookie", "Buy 1 Item", item2Y);
            writeAchievementNameAndDescription("Game Decimator", "Play 10 Games", item3Y);

            // Draws the back and next buttons
            Rectangles::drawRectangleWithText("Back", backX,backY, backWidth, backHeight, false);
            Rectangles::drawRectangleWithText("Next", nextX,nextY, nextWidth, nextHeight, false);

            // Booleans to keep track of if the back or next button has been pressed
            bool back = false;
            bool next = false;

            // Sleeps before checking input
            Sleep(0.15);

            // Runs indefinitely until the back or next button is pressed
            while (!(back || next)){
                float x,y;

                // Checks if clicked
                if (LCD.Touch(&x,&y)){

                    // checks if clicked on back
                    if (Rectangles::isPointInsideRect(x,y,backX,backY, backWidth, backHeight)){
                        back = true;
                    } else if (Rectangles::isPointInsideRect(x,y,nextX,nextY, nextWidth, nextHeight)){
                        // checks if clicked on next

                        displayPaneTwo();
                        next = true;
                    }
                }
            }
        }

        /*
        Draws multiple white or yellow rectangles depending on if the specific achievement is true. It also
        displays each the text and a description for each achievement. Also draws a back or next button,
        that keeps track of if we should go to the previous pane or next pane.
        @author Jalen
        */
        void displayPaneTwo(){

            // Clears screen and sets font color to white
            LCD.Clear();
            LCD.SetFontColor(WHITE);

            // Writes achievements menu
            LCD.WriteAt("Achievements", 88, 5);

            // Draws rectangles, either yellor or white depending on if the achievement has been obtained
            Rectangles::drawRectangleWhiteOrYellow(paneX,item1Y, paneWidth, paneHeight, achievements[3]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item2Y, paneWidth, paneHeight, achievements[4]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item3Y, paneWidth, paneHeight, achievements[5]);

            // Writes each name and description along with its appropriate y index
            writeAchievementNameAndDescription("Munitions Maestro", "50 Hits", item1Y);
            writeAchievementNameAndDescription("Ammo Anarchist", "100 Hits", item2Y);
            writeAchievementNameAndDescription("Aimless Amigo", "50 misses", item3Y);
            
            Rectangles::drawRectangleWithText("Back", backX,backY, backWidth, backHeight, false);
            Rectangles::drawRectangleWithText("Next", nextX,nextY, nextWidth, nextHeight, false);

            bool exit = false;
            Sleep(0.15);
            while (!exit){
                float x,y;
                if (LCD.Touch(&x,&y)){
                    if (Rectangles::isPointInsideRect(x,y,backX,backY, backWidth, backHeight)){
                        displayPaneOne();
                        exit = true;
                    } else if (Rectangles::isPointInsideRect(x,y,nextX,nextY, nextWidth, nextHeight)){
                        displayPaneThree();
                        exit = true;
                    }
                }
            }
        }

        /*
        Draws multiple white or yellow rectangles depending on if the specific achievement is true. It also
        displays each the text and a description for each achievement. Also draws a back or next button,
        that keeps track of if we should go to the previous pane or next pane.
        @author Jalen
        */
        void displayPaneThree(){

            // Clears screen and sets font color to white
            LCD.Clear();
            LCD.SetFontColor(WHITE);

            // Writes achievements menu
            LCD.WriteAt("Achievements", 88, 5);

            // Draws rectangles, either yellor or white depending on if the achievement has been obtained
            Rectangles::drawRectangleWhiteOrYellow(paneX,item1Y, paneWidth, paneHeight, achievements[6]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item2Y, paneWidth, paneHeight, achievements[7]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item3Y, paneWidth, paneHeight, achievements[8]);
            
            // Writes each name and description along with its appropriate y index
            writeAchievementNameAndDescription("Target Tantrum", "100 Misses", item1Y);
            writeAchievementNameAndDescription("Hitman Hurricane", "25 hits in a game", item2Y);
            writeAchievementNameAndDescription("Ruthless Rainmaker", "50 hits in a game", item3Y);

            Rectangles::drawRectangleWithText("Back", backX,backY, backWidth, backHeight, false);
            Rectangles::drawRectangleWithText("Next", nextX,nextY, nextWidth, nextHeight, false);

            bool back = false;
            bool next = false;
            Sleep(0.15);
            while (!(back || next)){
                float x,y;
                if (LCD.Touch(&x,&y)){
                    if (Rectangles::isPointInsideRect(x,y,backX,backY, backWidth, backHeight)){
                        displayPaneTwo();
                        back = true;
                    } else if (Rectangles::isPointInsideRect(x,y,nextX,nextY, nextWidth, nextHeight)){
                        displayPaneFour();
                        next = true;
                    }
                }
            }
        }

        /*
        Draws multiple white or yellow rectangles depending on if the specific achievement is true. It also
        displays each the text and a description for each achievement. Also draws a back or next button,
        that keeps track of if we should go to the previous pane or next pane.
        @author Jalen
        */
        void displayPaneFour(){

            // Clears screen and sets font color to white
            LCD.Clear();
            LCD.SetFontColor(WHITE);

            // Writes achievements menu
            LCD.WriteAt("Achievements", 88, 5);

            // Draws rectangles, either yellor or white depending on if the achievement has been obtained
            Rectangles::drawRectangleWhiteOrYellow(paneX,item1Y, paneWidth, paneHeight, achievements[9]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item2Y, paneWidth, paneHeight, achievements[10]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item3Y, paneWidth, paneHeight, achievements[11]);

            // Writes each name and description along with its appropriate y index
            writeAchievementNameAndDescription("Casino Clown", "Lose 5 Challenges", item1Y);
            writeAchievementNameAndDescription("Dicey Delight", "Do 10 Challenges", item2Y);
            writeAchievementNameAndDescription("Lucky Lark", "Win 5 Challenges", item3Y);

            Rectangles::drawRectangleWithText("Back", backX,backY, backWidth, backHeight, false);
            Rectangles::drawRectangleWithText("Next", nextX,nextY, nextWidth, nextHeight, false);

            bool back = false;
            bool next = false;
            Sleep(0.15);
            while (!(back || next)){
                float x,y;
                if (LCD.Touch(&x,&y)){
                    if (Rectangles::isPointInsideRect(x,y,backX,backY, backWidth, backHeight)){
                        displayPaneThree();
                        back = true;
                    } else if (Rectangles::isPointInsideRect(x,y,nextX,nextY, nextWidth, nextHeight)){
                        displayPaneFive();
                        next = true;
                    }
                }
            }
        }

        /*
        Draws multiple white or yellow rectangles depending on if the specific achievement is true. It also
        displays each the text and a description for each achievement. Also draws a back or next button,
        that keeps track of if we should go to the previous pane or next pane.
        @author Jalen
        */
        void displayPaneFive(){

            // Clears screen and sets font color to white
            LCD.Clear();
            LCD.SetFontColor(WHITE);

            // Writes achievements menu
            LCD.WriteAt("Achievements", 88, 5);

            // Draws rectangles, either yellor or white depending on if the achievement has been obtained
            Rectangles::drawRectangleWhiteOrYellow(paneX,item1Y, paneWidth, paneHeight, achievements[12]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item2Y, paneWidth, paneHeight, achievements[13]);
            Rectangles::drawRectangleWhiteOrYellow(paneX,item3Y, paneWidth, paneHeight, achievements[14]);

            // Writes each name and description along with its appropriate y index
            writeAchievementNameAndDescription("Jackpot Juggernaut", "Win 10 Challenges", item1Y);
            writeAchievementNameAndDescription("Shopaholic", "Buy every item", item2Y);
            writeAchievementNameAndDescription("GET A LIFE", "Achieve Everything", item3Y);

            Rectangles::drawRectangleWithText("Back", backX,backY, backWidth, backHeight, false);

            Sleep(0.15);

            float x,y;
            while (!(LCD.Touch(&x,&y) && Rectangles::isPointInsideRect(x,y,backX,backY, backWidth, backHeight)));
            displayPaneFour();
        }

        // Iterates through each index in the achievements array and sets them to false
        void reset(){
            for (int i = 0; i < 15; i++){
                achievements[i] = false;
            }
        }

        /*
        Method opens up "stats/achievements.txt", checks if it opened successfully, and if so sets a tempIndex variable
        equal to -1 by default, scans an integer into tempIndex until we reach the end of the file. If tempIndex is not
        equal to -1, then that index of achievements is set to true.
        @author Ayush
        */
        void importAchievements(){

            // Opens up a file named "stats/achievements.txt" for reading
            FEHFile *fptr = SD.FOpen("stats/achievements.txt", "r");

            // Checks if the file opened up successfully
            if (fptr != NULL){
                int tempIndex = -1;
                while (!SD.FEof(fptr)){
                    SD.FScanf(fptr, "%d", &tempIndex);
                    if (tempIndex != -1){
                        achievements[tempIndex] = true;
                    }
                }
            }

            // Closes the file
            SD.FClose(fptr);
        }

        /*
        Method writes to "stats/achievements.txt", checks if it opened successfully, and if so iterates from 0 to 14
        and checks if the index of achivements is true and if so it prints it out the the file.
        @author Jalen.
        */
        void exportAchievements(){

            // First we scan through "stats/achievements.txt"
            FEHFile *fptr = SD.FOpen("stats/achievements.txt", "w");

            // Checks if file opened successfully
            if (fptr != NULL){

                // Iterates from 0-14
                for (int i = 0; i < 15; i++){

                    // Checks if the index of achievements is true
                    if (achievements[i]){

                        // If so prints it to the file
                        SD.FPrintf(fptr, "%d ", i);
                    }
                }
            }

            // Closes the file
            SD.FClose(fptr);
        }
};