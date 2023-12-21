class Stats{
    private:
        //Defines cumulative hits, misses, shots, gamesPlayed, and percentage all cumulative
        int hits = 0, misses = 0, shots = 0, gamesPlayed = 0, percentage = 0;

        // Stats for achievments
        int boughtItems = 0, challengesWon = 0, challengesPlayed = 0;

        // Defines the menu starting x coordinate, and the top y coordinates of each box
        int menuItemX1 = 85, achievementsY1 = 125, highScoreY1 = 150, resetY1 = 175, backY1 = 200;

        // Next defines the default box width and box height
        int BOX_WIDTH = 150, BOX_HEIGHT = 20;

        // Creates high score array for the 3 time levels, 0-15s, 1-30s, 2-60s
        int highScores[3] = {0,0,0};

    public:

        /*
        Method first draws a rectangular outline ecompassing cumulative stats and then
        proceed to draw, the hits, misses, shots, games played, and percentage all to the 
        screen in a white font
        @author Ayush
        */
        void display(){
            LCD.Clear();
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(40,3,240,110);

            LCD.WriteAt("Hits: ",45,10);
            LCD.WriteAt(hits,240,10);

            LCD.WriteAt("Misses: ",45,30);
            LCD.WriteAt(misses,240,30);

            LCD.WriteAt("Shots: ",45,50);
            LCD.WriteAt(shots,240,50);

            LCD.WriteAt("Games Played:",45,70);
            LCD.WriteAt(gamesPlayed,240,70);

            LCD.WriteAt("Hit Percentage:",45,90);
            LCD.WriteAt(percentage,240,90);

            // Draws each item by calling its starting x, y, width, height, using the method
            Rectangles::drawRectangleWithText("Achievements", menuItemX1, achievementsY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("High Scores", menuItemX1, highScoreY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("Reset", menuItemX1, resetY1, BOX_WIDTH, BOX_HEIGHT, false);
            Rectangles::drawRectangleWithText("Back", menuItemX1, backY1, BOX_WIDTH, BOX_HEIGHT, false);
        }

        // Draws a box and writes each time along with itis corresponding high score
        // @author Ayush
        void displayHighScores(){
            LCD.Clear();

            LCD.SetFontColor(WHITE);

            LCD.DrawRectangle(85, 3, 150, 90);
            LCD.WriteAt("High Scores", 94, 10);
            LCD.WriteAt("15s: ", 90, 30);
            LCD.WriteAt(highScores[0], 170, 30);

            LCD.WriteAt("30s: ", 90, 50);
            LCD.WriteAt(highScores[1], 170, 50);

            LCD.WriteAt("60s: ", 90, 70);
            LCD.WriteAt(highScores[2], 170, 70);
        }

        // Method takes in gameHits, gameShots and then adds to the total, and updates the percentage and
        // increments gamesPlayed
        // Method returns if there is a new high score
        // @author Jalen
        bool addGameStats(int gameHits, int gameShots, int time){
            misses += gameShots - gameHits;
            hits += gameHits;
            shots += gameShots;
            gamesPlayed++;
            percentage = (100.0*hits)/shots;

            bool isHighScore = false;

            // Figures out what time interval we are on and checks if there is a new high score
            switch (time){
                case 15:
                    if (gameHits > highScores[0]){
                        highScores[0] = gameHits;
                        isHighScore = true;
                    } 
                    break;
                case 30:
                    if (gameHits > highScores[1]){
                        highScores[1] = gameHits;
                        isHighScore = true;
                    }
                    break;
                case 60:
                    if (gameHits > highScores[2]){
                        highScores[2] = gameHits;
                        isHighScore = true;
                    }
            }

            // Returns whether there is a new high score
            return isHighScore;
        }

        // Resets all stats back to zero
        // @author Jalen
        void statsReset(){
            hits = 0, misses = 0, shots = 0, gamesPlayed = 0, percentage = 0;
            highScores[0] = 0, highScores[1] = 0, highScores[2] = 0, boughtItems = 0;
            challengesWon = 0, challengesPlayed = 0;
        }

        /*
        Method opens up "stats/stats.txt", checks if it opened successfully, and if so assigns each 
        class variable to the values written in the file iin order. Then it closes the file.
        @author Ayush
        */
        void importStats(){

            // Opens up a file named "stats/stats.txt" for reading
            FEHFile *fptr = SD.FOpen("stats/stats.txt", "r");

            // Checks if the file opened up successfully
            if (fptr != NULL){

                // If so then five integers are scanned in and then adjust the object values
                // for hits, misses, shots, gamesPlayed, and percentage
                SD.FScanf(fptr, "%d %d %d %d %d %d %d %d", &hits, &misses, &shots, &gamesPlayed, &percentage, highScores, highScores+1, highScores+2);
                SD.FScanf(fptr, "%d %d %d", &boughtItems, &challengesWon, &challengesPlayed);
            }

            // Closes the file
            SD.FClose(fptr);
        }

        /*
        Method opens up "stats/stats.txt", checks if it opened successfully, and if so it writes each
        class variable to the file in order and then closes the file.
        @author Ayush
        */
        void exportStats(){

            // Opens up a file named "stats/stats.txt" for writing
            FEHFile *fptr = SD.FOpen("stats/stats.txt", "w");

            // Checks if the file opened up successfuly
            if (fptr != NULL){

                // Writes hits, misses, shots, gamesPlayed, and percetange to the file in order
                SD.FPrintf(fptr, "%d %d %d %d %d %d %d %d", hits, misses, shots, gamesPlayed, percentage, highScores[0], highScores[1], highScores[2]);
                SD.FPrintf(fptr, " %d %d %d", boughtItems, challengesWon, challengesPlayed);
            }

            // Closes the file
            SD.FClose(fptr);
        }

        /*
        Method is for the achievements class which exports the data needed into an array passed in
        Index 0 - games, 1 - items bought, 2 - hits, 3 - high scores, 4 - misses, 5 - challenges played, 6 - challenges won
        @author Jalen
        */
       void getStatsForAchievements(int* array){
            *array = gamesPlayed;
            *(array + 1) = boughtItems;
            *(array + 2) = hits;

            // Finds the highest score by iterating through the highScores array
            int highestScore = highScores[0];
            for (int i = 1; i < 3; i++){
                if (highScores[i] > highestScore){
                    highestScore = highScores[i];
                }
            }
            *(array+3) = highestScore;
            *(array+4) = misses;
            *(array+5) = challengesPlayed;
            *(array+6) = challengesWon;
       }

        // Increments the challengesPlayed variable
        // @author Jalen
       void incrementChallengesPlayed(){
            challengesPlayed++;
       }


        // Increments the challengesWon variable
        // @author Jalen
       void incrementChallengesWon(){
            challengesWon++;
       }

        // increments the number of items bought
        // @author Jalen
       void incrementItemsBought(){
            boughtItems++;
       }

        /*
        Method takes in a pointer to an array and checks the x and y coordinates being touched,
        and then checks if the boxes are in the x range, and if so checks if within the y range
        of all the boxes, returns if one of the rectangles are touched.
        @author Ayush
        */
        bool handleTouchEvents(int* array){

            // Defines two floats to detect where the user is touching
            float xTouch,yTouch;

            // Clears touch buffer
            LCD.ClearBuffer();

            bool hasTouched = false;

            if (LCD.Touch(&xTouch, &yTouch)){

                hasTouched = true;

                if (Rectangles::isPointInsideRect(xTouch,yTouch, menuItemX1, achievementsY1, BOX_WIDTH, BOX_HEIGHT)){
                    *array= true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch, menuItemX1, highScoreY1, BOX_WIDTH, BOX_HEIGHT)){
                    *(array+1) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch, menuItemX1, resetY1, BOX_WIDTH, BOX_HEIGHT)){
                    *(array+2) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch, menuItemX1, backY1, BOX_WIDTH, BOX_HEIGHT)){
                    *(array+3) = true;
                } else{
                    hasTouched = false;
                }
            }

            return hasTouched;
        }
};