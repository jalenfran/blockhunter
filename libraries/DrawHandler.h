#include "InitialScreen.h"
#include "Stats.h"
#include "PlayScreen.h"
#include "RandomObj.h"
#include "Credits.h"
#include "Store.h"
#include "StoreObject.h"
#include "Achievements.h"

// Displays first screen
class DrawHandler{
    private:
        InitialScreen firstScreen;

        // Initialize variables for the difficulty, time, and start box
        // First makes level difficulty
        int easyX = 90, hardX = 170, diffY = 50, diffWidth = 60, diffHeight = 20;
        
        // Next makes time coordinates
        int timeWidth = 40, timeHeight = 20, fifteenX = 80, thirtyX = 140, sixtyX = 200, timeY = 100;

        // Makes challenge modes
        int challengeWidth = 60, challengeHeight = 20, lowX = 50, midX = 130, highX = 210, challengeY = 150;
        
        // Last start button
        int startX = 65, startY = 180, startWidth = 80, startHeight = 20;

        // Add a Stats object named statBox for tracking cumulative statistics and methods
        Stats statBox;

        // Creates a credits object
        Credits credit; 

        // Creates a store object
        Store store;

        // Creates an achievement object
        Achievements achievement;

        // Makes a store object array of colors, that goes from red, blue, green, orange, yellow in order.
        StoreObject colorBullets[5] = {StoreObject(0,true, true), StoreObject(50, false, false), StoreObject(100, false, false), StoreObject(150, false, false),  StoreObject(200, false, false)};

        // Makes a store object array of reload times, that goes from 1000ms, 750ms, 500ms, 300ms, to 250ms.
        StoreObject reloadBullets[5] = {StoreObject(0,true, true), StoreObject(50, false, false), StoreObject(100, false, false), StoreObject(150, false, false),  StoreObject(200, false, false)};

        // Makes a store object array of radii, that goes from 8px, 9px, 10px, 11px, to 12px.
        StoreObject radiusBullets[5] = {StoreObject(0,true, true), StoreObject(50, false, false), StoreObject(100, false, false), StoreObject(150, false, false),  StoreObject(200, false, false)};

        // Finds current of each variable, first index represents color, second is for reload speed, and third is radius
        int currentEquipped[3] = {0,0,0};
        
        
    public:

        // Sets constructor for DrawHandler object, which calls the initialize method
        DrawHandler(){

            // Calls initialize method
            initialize();
        }

        /*
        Method imports and adjusts what has been equipped, bought, and what stats were present from previous games.
        @author Jalen
        */
        void initialize(){

            // Imports and adjusts the objects that were equipped previously.
            importEquipped();

            // Imports and adjusts the objects that were bought previously.
            importBought();

            // Imports and adjusts the user stats.
            statBox.importStats();

            // Imports achievements
            achievement.importAchievements();
        }

        /*
        This method essentially displays the InitialScreen object (firstScreen) so that each of the 7
        buttons are dispalyed. Next it creates an array and calls a method that checks if a button was
        pressed. Then it runs a loop until the exit boolean is true.
        If the stats button is pressed then the stats are displayed, and if the reset button is pressed
        then the stats are reset. Next, the instructions box displays instructions and credits displays credits.
        Lastly, the quit function exits the program.
        @author Ayush
        */
        void run(){

            // Displays the firstScreen
            firstScreen.display();

            // Displays the coin
            credit.drawCoin(10,10);

            // Display the number of credits right next to the coin pixel art
            LCD.SetFontColor(WHITE);
            LCD.WriteAt(credit.getCredits(),22,4);

            // Creates an array for the four buttons used to see if the user is touching any of them
            bool handlerFirstScreen[7] = {false, false, false, false, false, false, false};

            Sleep(0.15);

            // Loop will run until the play button is pressed
            bool exit = false;

            while (!exit){

                // Updates handlerFirstScreen array to check if any of the buttons have been pressed
                if (!firstScreen.handleTouchEvents(handlerFirstScreen)){

                    // Checks if play button is pressed
                    if (handlerFirstScreen[0]){

                        // Displays the actual game
                        getDifficultyAndTime();

                        // Sets touching the button back to false and exits while loop
                        handlerFirstScreen[0] = false;
                        exit = true;

                    } else if (handlerFirstScreen[1]){
                        
                        // Checks if the store button was pressed and if so calls a method
                        handleStore();
                        handlerFirstScreen[1] = false;
                        exit = true;
                    } else if (handlerFirstScreen[2]){

                        // Checks if see stats is pressed and then displays stats using statsDisplay method
                        statsDisplay();
                        handlerFirstScreen[2] = false;
                        exit = true;
                    }else if (handlerFirstScreen[3]){

                        // Checks if reset button is pressed and if so prompts an are you sure box
                        LCD.SetFontColor(BLACK);
                        LCD.FillRectangle(60,50,200,100);
                        LCD.SetFontColor(WHITE);
                        LCD.WriteAt("Are you sure you",60,50);
                        LCD.WriteAt("wish to erase", 60, 70);
                        LCD.WriteAt("all user data?", 60, 90);
                        LCD.SetFontColor(SCARLET);
                        Rectangles::drawRectangleWithText("Yes", 100, 120, 50, 25, false);
                        Rectangles::drawRectangleWithText("No", 160, 120, 40, 25, false);

                        // Boolean to track if the yes or no button is pressed
                        bool resetExit = false;

                        Sleep(0.2);

                        // Runs until a button is pressed
                        while (!resetExit){
                            float x,y;
                            if (LCD.Touch(&x,&y)){
                                if (Rectangles::isPointInsideRect(x,y,100,120,50,25)){
                                    reset();
                                    resetExit = true;
                                } else if (Rectangles::isPointInsideRect(x,y,160,120,40,25)){
                                    resetExit = true;
                                }
                            }
                        }
                        exit = true;

                    }else if (handlerFirstScreen[4]){

                        // Checks if instructions are pressed and if so calls seeInstructions method
                        seeInstructions();

                        handlerFirstScreen[4] = false;
                        exit = true;
                    }else if (handlerFirstScreen[5]){

                        // Checks if the credits was pressed and then calls function if so
                        seeCredits();
                        exit = true;

                        handlerFirstScreen[5] = false;
                    }else if (handlerFirstScreen[6]){
                        
                        // Lastly checks if the user press quit and if so calls quit().
                        quit();
                    }
                }
            }
        }

        /*
        Method goes through and resets everything, credits, stats, bought items, and sets equipped items to default,
        also resets all the achievements.
        @author Jalen
        */
        void reset(){

            // Resets each currentEquipped index to 0
            currentEquipped[0] = 0, currentEquipped[1] = 0, currentEquipped[2] = 0;

            // Resets all the statistics
            statBox.statsReset();

            // For loop to iterate through the 3 object arrays
            for (int i = 0; i < 3; i++){

                // Creates a temporary StoreObject pointer named object
                StoreObject* object;

                // Checks if first iteration and assigns object to colorBullets
                // if second reloadBullets, and lastly, radiusBullets
                if (i == 0){
                    object = &colorBullets[0];
                } else if (i == 1){
                    object = &reloadBullets[0];
                } else {
                    object = &radiusBullets[0];
                }

                // iterates from 1-4 and sets the object in the array bought status to false
                for (int i = 1; i < 5; i++){
                    object[i].setBuy(false);
                }

                // Equips the first object in each array
                object[0].equipItem();
            }

            // Resets achievements
            achievement.reset();

            // Resets the credits
            credit.resetCredits();
        }

        /*
        This method displays a goodbye message to the screen with a white font, pauses for 2 seconds
        and then exits the program.
        @author Ayush
        */
        void quit(){

            // FIrst set color to white
            LCD.SetFontColor(WHITE);

            // Clear the screen and write goodbye
            LCD.Clear();
            LCD.WriteAt("Goodbye!",10,10);

            // Exports all the users data
            credit.exportCredits();
            exportBoughtItems();
            statBox.exportStats();
            exportCurrentEquipped();
            achievement.exportAchievements();

            // Pause 2 seconds and then exit the program
            Sleep(2.0);
            exit(0);
        }

        /*
        This method first calls a method which graphically gathers the difficulty and time from
        the array passed in and then displays the initial playScreen. Then it creates an array that will
        handle whether one of the 3 inputs are being touched. It gets an initial time that the
        game starts at and it changes how many frames a random object will take based on the difficulty.
        If the user presses the shoot button the bullet will incrementally adjust along with the 
        random object incrementally increasing until they either collide, or the bullet reaches the 
        end of its path. If they do collide they enter a collision animation where they fall straight 
        downward at a constant rate (somewhat like gravity). The bullet can shoot like a projectile
        (ignoring real-life gravity) based on how the aim lines are. The aim lines can only be moved every
        200 ms to avoid them moving too much. The game runs consistently until the current time minus
        the initial time is greater than the time alotted based off the user input. For each frame,
        the time and hit count are rewriteen. Once the game is done running the current game stats
        are then added to the statsBox object created with the class, and the game stats
        are displayed on a screen for 5 seconds before exiting to the main menu. Also, whether the
        hits left or or htis is displayed depends on if there is a challenge.
        @author Jalen
        */
        void playDisplay(int timeAndDiff[4]){

            // tracks how many hits are left if challenge mode
            int hitsLeft = -1;

            // tracks how many credits the player earns
            int creditsEarned = 0;

            // Finds if there is a challenge
            if (timeAndDiff[2] != -1){
                hitsLeft = timeAndDiff[3];
                statBox.incrementChallengesPlayed();
            }

            // isHard evaluates to true if the first element in the array is 1, false otherwise
            bool isHard = timeAndDiff[0] == 1;

            // The timeLimit is assigned to the second element in the array gathereed from the GUI
            int timeLimit = timeAndDiff[1];

            // Next we create a PlayScreen object
            PlayScreen playScreen;

            // Updates bullet
            playScreen.currentBullet.updateBulletType(currentEquipped);

            /*
            Creates a handlerPlayScreen array that will check if each of the buttons are pressed
            */
            int handlerPlayScreen[3] = {false, false, false};

            // Sets the timeInitial variable to the current time in seconds
            float timeInitial = TimeNow();

            // Creates a counter to find which iteration of the random object animation we are on
            int randFrameCount = 0;

            // Creates a counter to find which iteration of the bullet object animation we are on
            int bulletFrameCount = 0;

            // Initializes a max amount of frame iterations for the random object that is based on
            // difficulty, will be elaborated on below
            int MAX_RANDOM_ITERATIONS;

            // If the difficulty is hard there will be 40 frames, 80 otherwise
            if (isHard){
                MAX_RANDOM_ITERATIONS = 40;
            } else {
                MAX_RANDOM_ITERATIONS = 80;
            }

            // Creates a randomObj that represents the block flying in
            RandomObj randObject;

            // Used to see how long ago each of the buttons were pressed
            // Or for the shoot button when the animation allows it
            float timeFromShoot = 0, timeFromLeft = 0, timeFromRight = 0;

            // Creates booleans (automatically false) that track if we are in a bullet or collision animation
            bool hasFired = false, collisionAnimation = false;

            // Variables are used to track where the bullet is 
            float bulletX, bulletY, bulletRadius;

            // Variables are used for stat tracking how many hits and shots there are
            int gameHits = 0, gameShots = 0;

            // Reload time
            float reloadTime = playScreen.currentBullet.getBulletReload()/1000.0;

            /*
            First we create an array that will help decide 
            how much we increment the x and y of the bullet 
            based on the current line drawn
            */
            float incrementals[2];

            // Runs until this loop has run for the time limit
            while (TimeNow() - timeInitial < timeLimit){

                // Boolean tracks if the current time and the time from the shoot button is greater than equal
                // to the reload time
                bool canShoot = (TimeNow()-timeFromShoot) >= reloadTime;

                /*
                Checks if the random frame animation is a multiple of our max (based off difficulty), if so we 
                then use the initializeRandObject method to start it over
                */ 
                if (randFrameCount % MAX_RANDOM_ITERATIONS == 0){
                    randObject.initializeRandObject();
                    randObject.setDifficulty(isHard);
                }

                /*
                Passes in the handlerPlayScreen array created earlier into
                the handleTouchEvents method that will check if any of the buttons are pressed
                the 0 index represents the left button, 1 represents the right
                and 2 represents the shoot button
                */
                // Tests to see if the handler returned an input
                if (!playScreen.handleTouchEvents(handlerPlayScreen)){

                    // This checks if the shoot button has been pressed
                    if (handlerPlayScreen[2]){

                        /*
                        Checks multiple conditions before we start firing
                        First, make sure we are not currently animating a collision, next make
                        sure the bullet is not currently in a firing animation, and last make sure
                        the canShoot boolean is true
                        */
                        if (!collisionAnimation && !hasFired && canShoot){

                            // We pass that array into a method that alters the array for the values we want
                            playScreen.getIncremental(incrementals);

                            // Increment the gameShots and sets hasFired to true and updates timeFromShoot to current time
                            gameShots++;
                            hasFired = true;
                            timeFromShoot = TimeNow();
                                
                        }
                        // Set the shoot button pressed to false so we don't automatically run this again
                        handlerPlayScreen[2] = false;
                        
                    } else if (handlerPlayScreen[0]){

                        // Checks if its been 200 ms since the last time the line moved
                        if (TimeNow() - timeFromLeft >= 0.2){

                            // Updates line to move left
                            playScreen.lineUpdater(false);

                            // Updates the time since the line moved left
                            timeFromLeft = TimeNow();
                        }
                        handlerPlayScreen[0] = false;
                    } else if (handlerPlayScreen[1]){

                        // Checks if it has been 200 ms since the last time the line moved
                        if (TimeNow() - timeFromRight >= 0.2){

                            // Updates line to move right
                            playScreen.lineUpdater(true);

                            // Updates the time since the line last moved
                            timeFromRight = TimeNow();
                        }
                        handlerPlayScreen[1] = false;
                    } 
                }

                // Checks if the bullet is touching the random object and that we are not currently in an animation
                if (!collisionAnimation && randObject.isCollision(playScreen.currentBullet)){

                    // If yes we change the randFrameCount to 0 as we want to reset it for after the animation
                    randFrameCount = 0;

                    // Next we change bulletX, bulletY, and bulletRadius so that we can later aniimate
                    bulletX = playScreen.currentBullet.getBulletX();
                    bulletY = playScreen.currentBullet.getBulletY();
                    bulletRadius = playScreen.currentBullet.getBulletRadius();

                    // We tell the program we are currently animating a collision
                    collisionAnimation = true;

                    // Increment gameHits since a collision happened
                    gameHits++;

                    // Decrements hitsLeft only if we are greater than 0
                    if (hitsLeft > 0){
                        hitsLeft--;
                    }

                    // We set the bulletFrameCount back to 0, since we want to reset animation
                    // and we tell the program that we are no longer in a firing animation
                    bulletFrameCount = 0;
                    hasFired = false;
                }

                // Checks if we are in a firing animation
                if (hasFired){ 

                    // Checks if we have done 10 frames or less
                    if (bulletFrameCount < 10){

                        // If so we incrememnt the bullet position for the next animation
                        playScreen.currentBullet.partialBulletUpdater(incrementals[0],incrementals[1]);

                        // Then we tell the program that we have done another bullet frame
                        bulletFrameCount++;
                    } else {

                        // If we have done 10 frames we want to reset the bullet coordinates
                        // and end the firing animation, and reset it for future
                        // also we adjust the last time we shot for the delay implemented above
                        playScreen.currentBullet.clear();
                        hasFired = false;
                        bulletFrameCount = 0;
                    }
                }

                // We now display the playScreen
                playScreen.display(canShoot);

                // Variable finds how much time is left and converts it to an int
                int timeLeft = (int)(TimeNow() - timeInitial);

                // Change font to Scarlet 
                LCD.SetFontColor(SCARLET);

                // We then rewrite how much time is left in the upper left corner
                LCD.WriteAt("Time:", 0, 0);
                LCD.WriteAt(timeLimit-timeLeft, 60, 0);

                // We display the current hit count in the bottom left corner
                if (timeAndDiff[2] != -1){
                    LCD.WriteAt("Hits Left:", 164, 0);
                    LCD.WriteAt(hitsLeft, 284, 0);
                } else{
                    LCD.WriteAt("Hits:", 224, 0);
                    LCD.WriteAt(gameHits, 284, 0);
                }

                // Check if we are in a collision animation
                if (collisionAnimation){

                    // Checks if we should animate the next frame based on boundaries
                    if (bulletY <= 210 - bulletRadius){
                        
                        // Draws a green bullet that is constantly updated moving downwards
                        LCD.SetFontColor(GREEN);
                        LCD.DrawCircle(bulletX,bulletY,bulletRadius);
                        LCD.FillCircle(bulletX,bulletY,bulletRadius);
                        bulletY += bulletRadius;
                    } else{

                        // We no longer want to animate so we tell the program we are done
                        // And also update the bullet coordinates and the time from when
                        // we last shot
                        collisionAnimation = false;
                        playScreen.currentBullet.clear();
                    }
                } else {

                    //This is executed when the program is not currently animating collision

                    // We display the bullet
                    playScreen.currentBullet.displayBullet();
                    
                    // Next we update the poisition of the random object created before
                    randObject.updatePosition();

                    // We display the new version
                    randObject.display();

                    //Update the current iteration
                    randFrameCount++;
                }

                /*
                IMPORTANT: Uncomment the sleep line below depending on how fast the machine
                is. If easy mode is going too fast then use this, otherwise hard will be 
                impossible. Since, the code does so much it gets slowed down depending on
                what runs it. The amount is personal preference.
                */

               // Sleep(10);
            }

            // Adds game stats to our statBox object
            bool newHighScore = statBox.addGameStats(gameHits,gameShots, timeAndDiff[1]);

            // Adds credits based off difficulty
            if (isHard){
                creditsEarned += gameHits * 20;
            } else{
                creditsEarned += gameHits * 5;
            }

            // Checks if hitsLeft is equal to 0, if so the user wins the challenge
            if (hitsLeft == 0){
                creditsEarned += timeAndDiff[2] * 2;
                statBox.incrementChallengesWon();
            }

            // Changes the credits based on how many credits the user earned
            credit.changeCredits(creditsEarned);

            // Calls end game stats method
            displayEndGameStats(gameHits, gameShots, newHighScore, creditsEarned);
        }

        /*
        Method takes in four parameters, gameHits and gameShots, newHighScore, and newCoins.
        First the method clears the screen and draws a box encompassing the game stats.
        Then it displays Game Stats at the top, and then shots the hits, misses,
        shots, and hit percentage and then sleeps for 5 seconds.
        @author Ayush
        */
        void displayEndGameStats(int gameHits, int gameShots, bool newHighScore, int newCoins){
            
            // Sets a scarlet background color and clears the screen and draws a box
            LCD.SetBackgroundColor(SCARLET);
            LCD.Clear();
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(40,3,240,110);

            // Writes all the game stats in the box
            LCD.WriteAt("Game Stats", 100, 10);
            LCD.WriteAt("Hits: ",45,30);
            LCD.WriteAt(gameHits,240,30);
            LCD.WriteAt("Misses: ",45,50);
            LCD.WriteAt(gameShots-gameHits,240,50);
            LCD.WriteAt("Shots: ",45,70);
            LCD.WriteAt(gameShots,240,70);
            LCD.WriteAt("Hit Percentage:",45,90);
            LCD.WriteAt((int)100*gameHits/gameShots,240,90);

            // Checks if there is a new high score, and if so writes it
            if (newHighScore){
                LCD.WriteAt("NEW HIGH SCORE", 76, 120);
            }

            // Draws play again and main menu boxes
            Rectangles::drawRectangleWithText("Play Again", 95, 155, 130, 25, false);
            Rectangles::drawRectangleWithText("Main Menu", 100, 190, 120, 25, false);

            // Creates variables x, and y to track user touches
            float x,y;

            // Boolean to track if the back button is pressed
            bool back = false;

            // Writes in a white font color the coins gained
            LCD.SetFontColor(WHITE);
            LCD.WriteAt(newCoins, 18, 134);

            // Runs indefinitely until the back button is pressed
            while (!back){
                
                // Displays the credit animation
                credit.displayAnimation(10,140);
                
                // Checks if the user clicks
                if (LCD.Touch(&x,&y)){

                    // Checks if play again is pressed, if so goes back to getDifficultyAndTime()
                    if (Rectangles::isPointInsideRect(x,y,95,155,130,25)){
                        getDifficultyAndTime();
                    } else {

                        // Back is then set to if the back button is being pressed so the loop can exit
                        back = Rectangles::isPointInsideRect(x,y,100,190,120,25);
                    }
                }
            }
        }
        
        /*
        This method displays all the cumulative statistics and then checks
        if any of the buttons are pressed. If the back button is pressed we
        go back to the original menu, if the achievements button is pressed, the
        achievements screen displays. If the high scores button is pressed, then all
        the high scores are displayed. All is done until the back button is pressed.
        @author Jalen
        */
        void statsDisplay(){

            // Displays statBox
            statBox.display();

            // Creates an array that keeps track of if any of the buttons are pressed
            int handlerStatsScreen[4] = {false, false, false, false};
            
            // Sleeps before scanning for input
            Sleep(0.15);

            // Method runs until the back button is pressed
            while (!handlerStatsScreen[3]){

                // Scans if there is any input and updates the handlerStatsScreen array
                if (statBox.handleTouchEvents(handlerStatsScreen)){

                    // If the achievement button is pressed
                    if (handlerStatsScreen[0]){
                        
                        // Updates the achivements by passing in the current stats
                        achievement.updateAchievements(statBox);

                        // displays the first achievement pane
                        achievement.displayPaneOne();

                        // Redisplays the stats menu
                        statsDisplay();

                        // Done so the loop breaks to avoid issues with the recrusive call above
                        handlerStatsScreen[3] = true;

                    } else if (handlerStatsScreen[1]){

                        // Checks if high scores menu is pressed and if so displays them
                        statBox.displayHighScores();

                        // Draws a back button
                        Rectangles::drawRectangleWithText("Back", 140, 120, 60, 25, false);

                        bool back = false;
                        float x,y;

                        // Loop runs indefinitely until sleep button is pressed
                        while (!LCD.Touch(&x,&y) || !Rectangles::isPointInsideRect(x,y,140,120,60,25));

                        // Redisplays the stats box
                        statsDisplay();
                        
                        // Done to avoid recrusive call issues
                        handlerStatsScreen[3] = true;
                    } else if (handlerStatsScreen[2]){

                        // Checks if reset button is pressed if so we reset
                        statBox.statsReset();

                        // Clears the screen
                        LCD.Clear();

                        // Redisplays the stats screen
                        statBox.display();
                        handlerStatsScreen[2] = false;
                    } 
                }
            }
        }

        /*
        Method displays the instructions for playing the game
        @author Ayush
        */
        void seeInstructions(){
            LCD.Clear();

            LCD.WriteRC("How to play the game",0,0);
            LCD.WriteRC("Press play to play",1,0);
            LCD.WriteRC("challenges or games.",2,0);
            LCD.WriteRC("All challenges are 60",3,0);
            LCD.WriteRC("seconds and have a",4,0);
            LCD.WriteRC("variable amounts of hits.",5,0);
            LCD.WriteRC("Earn credits from hits and",6,0);
            LCD.WriteRC("challenges and spend them",7,0);
            LCD.WriteRC("in the shop for upgrades.",8,0);
            LCD.WriteRC("Track your progress with",9,0);
            LCD.WriteRC("achievements and high",10,0);
            LCD.WriteRC("scores in the stats menu.",11,0);



            Rectangles::drawRectangleWithText("Back", 135, 210, 50, 25, false);

            float x,y;
            
            // Loop runs indefinitely until back button is pressed
            while (!LCD.Touch(&x,&y) || !Rectangles::isPointInsideRect(x,y,135,210,50,25));
        }

        /*
        This method writes to the screen the credits for the game.
        @author Ayush
        */
        void seeCredits(){

            float x = 0,y = 0;
            

            // Checks if credits is pressed
            LCD.Clear();
            LCD.SetFontColor(WHITE);
            LCD.WriteLine("Authors");
            LCD.WriteLine("Jalen Francis");
            LCD.WriteLine("Ayush Chakravarty");

            LCD.WriteLine("References:");
            LCD.WriteLine("FEH Proteus Library");
            LCD.WriteLine("Coin Art: Nemo123-pixilart.com");

            Rectangles::drawRectangleWithText("Back", 135, 180, 50, 25, false);

            Sleep(0.15);

            // Loop runs indefinitely until back button is pressed
            while (!LCD.Touch(&x,&y) || !Rectangles::isPointInsideRect(x,y,135,180,50,25));
        }

        /*
        Method finds the difficulty and time for the game and updates it into the array passed in. 
        The first index becomes the difficulty level, where 1 is hard, and 0 is easy, and the 
        second index becomes the time. The method checks if any of the buttons are pressed,
        if a difficulty level is pressed then that gets a green background, and the others get a white background.
        Same thing goes for the time buttons. Once the start button is pressed, then the method
        makes sure a time and difficulty level are entered, and then updates the current array.
        This method manages drawing the boxes, changing the color of the boxes, and checking if they are presseed,
        all by calling other methods.
        @author Jalen
        */
        void getDifficultyAndTime(){

            // returns if returned or not
            bool returnToMenu = false;

            // First draws the original boxes using the drawTimeAndDifficulty() method
            drawTimeAndDifficulty();

            // Sleeps to delay touches
            Sleep(0.15);

            // Variable that keeps track if the current inputs are valid to start
            bool isValid = false;

            // Starts at -1, indicating user has not put a level, 0 is easy, 1 is hard
            int diffLevel = -1;

            // Starts at -1 meaning user needs a time, otherwise representing time in seconds
            int timeLimit = -1;

            // Keeps track of challenge cost
            int challengeCost = -1;

            // Tracks how many hits we need
            int hitsNeeded = -1;

            // boolean to adjust the other boxes to challenge mode
            bool inChallengeMode = false;

            // Adjust to regular mode
            bool normalMode = false;

            // Creates an array that handles if any of the boxes are being touched
            bool handleTouchArray[10] = {false, false, false, false, false, false, false, false, false, false};

            // Tracks back button
            bool back = false;

            // Loops runs indefinitely until the user presses start and has valid selections or the back button is pressed
            while (!(isValid || back)){

                // First calls a method that modifies the array if any of the boxes are being touched
                if (handleTouchEventsTimeAndDiff(handleTouchArray)){

                    if (handleTouchArray[0]){

                        // Checks if easy is being touched and sets diffLevel to 0
                        diffLevel = 0;
                        normalMode = true;
                        handleTouchArray[0] = false;

                    } else if (handleTouchArray[1]){

                        // Checks if easy is being touched and sets diffLevel to 1
                        diffLevel = 1;
                        normalMode = true;
                        handleTouchArray[1] = false;
                    } else if (handleTouchArray[2]){

                        // Checks if 15s box is being touched and sets timeLimit to 15
                        timeLimit = 15;
                        normalMode = true;
                        handleTouchArray[2] = false;
                    } else if (handleTouchArray[3]){

                        // Checks if 30s box is being touched and sets timeLimit to 30
                        timeLimit = 30;
                        normalMode = true;
                        handleTouchArray[3] = false;
                    } else if (handleTouchArray[4]){

                        // Checks if 60s box is being touched and sets timeLimit to 60
                        timeLimit = 60;
                        normalMode = true;
                        handleTouchArray[4] = false;
                    } 
                    
                    else if (handleTouchArray[5]){
                        // Checks if 100 coin challenge is pressed

                        // Updates challenge cost and htis needed count
                        challengeCost = 100;
                        hitsNeeded = 20;

                        inChallengeMode = true;
                        handleTouchArray[5] = false;
                    } else if (handleTouchArray[6]){
                        // Checks if 250 coin challenge is pressed

                        // Updates challenge cost and htis needed count
                        challengeCost = 250;
                        hitsNeeded = 25;

                        inChallengeMode = true;
                        handleTouchArray[6] = false;
                    } else if (handleTouchArray[7]){
                        // Checks if 500 coin challenge is pressed

                        // Updates challenge cost and htis needed coutn
                        challengeCost = 500;
                        hitsNeeded = 40;

                        inChallengeMode = true;
                        handleTouchArray[7] = false;
                    }  else if (handleTouchArray[8]){

                        // Sets back to true and re runs
                        back = true;
                        run();
                    }
                    
                    else if (handleTouchArray[9]){

                        // Checks if the start button is pressed
                        // Makes isValid the vale of if timeLimit and diffLevel are not equal to -1
                        // Essentially this makes sure the user has chosen a time and difficulty
                        isValid = (timeLimit != -1) && (diffLevel != - 1);

                        // Checks if challenge cost is selected
                        if (challengeCost != -1){

                            // First checks if the user has enough credits
                            if (credit.getCredits() >= challengeCost){

                                // If so updates credits count and sets isValid to true
                                credit.changeCredits(-challengeCost);
                                isValid = true;

                                // Sets a time limit of 60 for challenges
                                timeLimit = 60;

                                /*
                                Sets the difficulty of easy for challenge
                                cost of 100 and hard otherwise
                                */
                                if (challengeCost == 100){
                                    diffLevel = 0;
                                } else {
                                    diffLevel = 1;
                                }
                            } else {

                                // If the user does not have enough credits then displays more credits 
                                // for 200 ms
                                LCD.SetFontColor(WHITE);
                                LCD.WriteAt("More Credits", 150, 200);
                                Sleep(200);
                                LCD.SetFontColor(SCARLET);
                                LCD.FillRectangle(150,200,144,17);
                            }
                        }

                        // Checks if the isValid boolean is true and then calls the play display with 
                        // the approiate values
                        if (isValid){
                            int array[4] = {diffLevel, timeLimit, challengeCost, hitsNeeded};
                            playDisplay(array);
                        }
                        handleTouchArray[9] = false;
                    }

                    // Checks if we are in challenge mode
                    if (inChallengeMode){

                        // Sets timeLimit and diffLevel to -1
                        timeLimit = -1;
                        diffLevel = -1;
                        inChallengeMode = false;
                    }
                    if (normalMode){

                        // Sets challengeCost to -1
                        challengeCost = -1;
                        normalMode = false;
                    }
                }

                // Draws each text box where it is green or white depending on if its condition to be selected is true
                Rectangles::drawRectangleWithText("Easy", easyX,diffY,diffWidth,diffHeight,diffLevel==0);
                Rectangles::drawRectangleWithText("Hard", hardX,diffY,diffWidth,diffHeight,diffLevel==1);
                Rectangles::drawRectangleWithText("15s", fifteenX,timeY,timeWidth,timeHeight,timeLimit==15);
                Rectangles::drawRectangleWithText("30s", thirtyX,timeY,timeWidth,timeHeight,timeLimit==30);
                Rectangles::drawRectangleWithText("60s", sixtyX,timeY,timeWidth,timeHeight,timeLimit==60);
                Rectangles::drawRectangleWithText("100  ", lowX,challengeY,challengeWidth,challengeHeight,challengeCost==100);
                Rectangles::drawRectangleWithText("250  ", midX,challengeY,challengeWidth,challengeHeight,challengeCost==250);
                Rectangles::drawRectangleWithText("500  ", highX,challengeY,challengeWidth,challengeHeight,challengeCost==500);

                // Draws each coin for the challenge boxes
                Credits::drawCoin(lowX+45,challengeY+10);
                Credits::drawCoin(midX+45,challengeY+10);
                Credits::drawCoin(highX+45,challengeY+10);
            }
        }

        /*
        Method draws each box needed for each level of difficulty, time, and the start button to begin the game
        @author Ayush
        */
        void drawTimeAndDifficulty(){
            LCD.Clear();

            // Displays the coin
            credit.drawCoin(10,10);

            // Display the number of credits right next to the coin pixel art
            LCD.SetFontColor(WHITE);
            LCD.WriteAt(credit.getCredits(),22,4);

            // Displays difficulty, time, and challenges
            LCD.WriteAt("Difficulty", 100, 30);
            LCD.WriteAt("Time Limits",  94, 80);
            LCD.WriteAt("Challenge Mode", 76, 130);
            
            // For each box calls drawRectangleWithText() method using variables
            // defined in the class and with its approriate label.
            Rectangles::drawRectangleWithText("Easy", easyX,diffY,diffWidth,diffHeight, false);
            Rectangles::drawRectangleWithText("Hard", hardX,diffY,diffWidth,diffHeight, false);

            Rectangles::drawRectangleWithText("15s", fifteenX, timeY, timeWidth, timeHeight, false);
            Rectangles::drawRectangleWithText("30s", thirtyX, timeY, timeWidth, timeHeight, false);
            Rectangles::drawRectangleWithText("60s", sixtyX, timeY, timeWidth, timeHeight, false);

            // Draws challenge boxes
            Rectangles::drawRectangleWithText("100  ", lowX, challengeY, challengeWidth, challengeHeight, false);
            Rectangles::Rectangles::drawRectangleWithText("250  ", midX, challengeY, challengeWidth, challengeHeight, false);
            Rectangles::drawRectangleWithText("500  ", highX, challengeY, challengeWidth, challengeHeight, false);
            Credits::drawCoin(lowX+45,challengeY+10);
            Credits::drawCoin(midX+45,challengeY+10);
            Credits::drawCoin(highX+45,challengeY+10);

            // Draws the back and start boxes
            Rectangles::drawRectangleWithText("Back", startX, startY, startWidth, startHeight, false);
            Rectangles::drawRectangleWithText("Start", startX+startWidth+30, startY, startWidth, startHeight, false);
        }

        // Method handles whether each of the rectangles are being touched and updates the array passed in
        // @author Ayush
        bool handleTouchEventsTimeAndDiff(bool* array){

            // Initialize two floats to find position
            float xTouch, yTouch;

            // boolean that tracks if has been touched
            bool hasTouched = false;

            // Clears buffer
            LCD.ClearBuffer();
            /*
             Next goes down the list for each box to find if any of them are being touched
             if a single one of them is, then the corresponding index is set to true
            */
            if (LCD.Touch(&xTouch,&yTouch)){
                hasTouched = true;
                if (Rectangles::isPointInsideRect(xTouch,yTouch,easyX,diffY,diffWidth,diffHeight)){
                    *array = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,hardX,diffY,diffWidth,diffHeight)){
                    *(array+1) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,fifteenX,timeY,timeWidth,timeHeight)){
                    *(array+2) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,thirtyX,timeY,timeWidth,timeHeight)){
                    *(array+3) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,sixtyX,timeY,timeWidth,timeHeight)){
                    *(array+4) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,lowX,challengeY,challengeWidth,challengeHeight)){
                    *(array+5) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,midX,challengeY,challengeWidth,challengeHeight)){
                    *(array+6) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,highX,challengeY,challengeWidth,challengeHeight)){
                    *(array+7) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,startX,startY,startWidth,startHeight)){
                    *(array+8) = true;
                } else if (Rectangles::isPointInsideRect(xTouch,yTouch,startX+startWidth+30, startY, startWidth, startHeight)){
                    *(array+9) = true;
                } else {
                    hasTouched = false;
                }
            }
            return hasTouched;
        }

        /*
        Method displays a store menu that depending on how the store menu is touched displays the next
        shopping menu, like colors, reload times, and radii.
        @author Jalen
        */
        void handleStore(){

            // Displays the store menu
            store.display();

            // Displays the coin
            Credits::drawCoin(10,10);

            // Display the number of credits right next to the coin pixel art
            LCD.SetFontColor(WHITE);
            LCD.WriteAt(credit.getCredits(),22,4);

            Sleep(150);

            // boolean to track if back button is pressed
            bool back = false;

            // Scans for more input until the back button is pressed
            while (!back){

                // Array to find if any buttons were touched
                bool handleStoreTouch[4] = {false, false, false, false};

                // Checks if any buttons are pressed
                if (store.handleTouchEvents(handleStoreTouch)){
                    // Checks if any buttons are pressed, if 0 index is true - work with colors, 1 - reload time, 2 - radius, 3 - back
                    if (handleStoreTouch[0]){
                        handleShoppingMenu(colorBullets, 0);
                        handleStoreTouch[0] = false;
                    } else if (handleStoreTouch[1]){
                        handleShoppingMenu(reloadBullets, 1);
                        handleStoreTouch[1] = false;
                    } else if (handleStoreTouch[2]){
                        handleShoppingMenu(radiusBullets, 2);
                        handleStoreTouch[2] = false;
                    } else if (handleStoreTouch[3]){
                        handleStoreTouch[3] = false;
                        back = true;
                    }
                }

                // Avoids overloading
                Sleep(0.01);
            }
        }
        
        /*
        Method displays and handles object arrays based on the type we give it.
        The type represents which shopping menu where 0 is colors, 1 is reload times, and 3 is radius.
        Then until the back button is pressed the store menu is displays and updated based on what store
        object is selected by the user. if the user tries to buy something they cannot afford
        more credits is displayed.
        @author Ayush
        */
        void handleShoppingMenu(StoreObject objectArray[], int type){

            // First number represents which object we are working with, second is what the button functions as
            // and the last number represents whether the last button has been touched
            // for the second number 0 means back, 1 means equip, and 2 means buy
            int currentStatus[4] = {-1, 0, 0, -1};

            // Boolean is used to detect whether the back button has been pressed
            bool back = false;

            // Creates a pointer that points to a 7 character array
            char (*textBoxPointer)[7];

            /*
            Creates an array of 5 strings of length 7 and changes the pointer to point to it.
            The character array created changes based on type where type 0 is colors, 1 is reload time, and 2 is radius.
            */
            if (type == 0){
                char textBoxes[5][7] = {"Red", "Blue", "Green", "Orange", "Yellow"};
                textBoxPointer = textBoxes;
            } else if (type == 1){
                char textBoxes[5][7] = {"2500ms", "2000ms", "1500ms", "1000ms", "500ms"};
                textBoxPointer = textBoxes;
            } else {
                char textBoxes[5][7] = {"8px", "9px", "10px", "11px", "12px"};
                textBoxPointer = textBoxes;
            }

            // Displays the store menu based on the 2D textBoxes array that textBoxPointer points to
            // and currentStatus[1] decides which button we want to display
            store.displayStoreMenu(textBoxPointer);

            // Runs until the boolean back is true
            while (!back){

                // Updates the store menu, where the 2D character array is passed and currentStatus[0]
                // represents which object the user currently has selected
                if (currentStatus[0] != -1 && currentStatus[3] != currentStatus[0]){
                    store.updateStoreMenuItemBoxes(currentStatus[0], currentStatus[1], textBoxPointer, &currentStatus[3]);
                    currentStatus[3] = currentStatus[0];
                }
                
                // Redraws over the credits amount in case there is a change
                LCD.SetFontColor(SCARLET);
                LCD.FillRectangle(22,4,60,17);

                // Display the number of credits right next to the coin pixel art
                // Displays the coin
                credit.drawCoin(10,10);
                LCD.SetFontColor(WHITE);
                LCD.WriteAt(credit.getCredits(),22,4);

                // Handles what buttons are pressed for each menu based on the currentStatus array and objectArray we are on
                handleShoppingMenuTouches(currentStatus, objectArray);

                // Checks if multipurpose button is pressed
                if (currentStatus[2] == 1){
                    if (currentStatus[1] == 0){
                        // Checks if button was pressed while back was displayed
                        break;
                    } else if (currentStatus[1] == 1){
                        // Checks if equip item is pressed

                        // Equips current item and unequips the previous versoin
                        objectArray[currentStatus[0]].equipItem();
                        objectArray[currentEquipped[type]].unequipItem();

                        // Sets the current equipped index of the type passed in to the item currently selected
                        currentEquipped[type] = currentStatus[0];
                    } else if (currentStatus[1] == 2){
                        // Checks if buy item is pressed

                        // Tries to buy the item
                        objectArray[currentStatus[0]].buyItem(&credit);

                        // Checks if the object was not successfully bought
                        if (!objectArray[currentStatus[0]].checkIfBought()){

                            // Writes for 200ms  more credits
                            LCD.SetFontColor(WHITE);
                            LCD.WriteAt("More Credits",140,180);
                            Sleep(200);

                            // Draws over 
                            LCD.SetFontColor(SCARLET);
                            LCD.FillRectangle(140,180,144,17);
                            
                        } else{

                            // Increments the items bought
                            statBox.incrementItemsBought();
                        }
                    }
                    currentStatus[2] = 0;
                    
                    // Updates currentStatus[1] based on if the object is bought, equipped, or N/A
                    updateButton(currentStatus, &objectArray[currentStatus[0]]);

                    // Sleep function to give the user time so it does not instantaneously,
                    // buy -> equip -> buy
                    Sleep(150);
                    
                    switch(currentStatus[1]){
                        case 0:
                            Rectangles::drawRectangleWithText("Back", 200, 200, 60, 25, false);
                            break;
                        case 1:
                            Rectangles::drawRectangleWithText("Equip", 200, 200, 60, 25, false);
                            break;
                        case 2:
                            Rectangles::drawRectangleWithText("Buy", 200, 200, 60, 25, false);
                    }
                }

                // Sets back boolean to if the multipurpose button is pressed and if the item is equipped
                back = (currentStatus[1] == 0 && currentStatus[2] == 1);
            }

            // Calls handleStore() again after loop ended (back button was pressed)
            handleStore();
        }

        /*
        Method takes in a variable named status, and a pointer to a StoreObject array. It then
        checks if any store buttons are pressed and finds current selection if it is touched
        and updates the current button.
        @author Ayush
        */
        void handleShoppingMenuTouches(int* status, StoreObject* objectArray){

            // Array that tracks if anything is touched
            bool handleShoppingTouches[6] = {false, false, false, false, false, false};

            // Keeps track of current selection
            int selection = -1;

            // Checks if the handleStoreMenuTouchEvents returns true and modifies the array
            if (store.handleStoreMenuTouchEvents(handleShoppingTouches)){

                // Modifies selection depending on what item box is pressed
                if (handleShoppingTouches[0]){
                    handleShoppingTouches[0] = false;
                    selection = 0;
                } else if (handleShoppingTouches[1]){
                    selection = 1;
                    handleShoppingTouches[1] = false;
                } else if (handleShoppingTouches[2]){
                    selection = 2;
                    handleShoppingTouches[2] = false;
                } else if (handleShoppingTouches[3]){
                    selection = 3;
                    handleShoppingTouches[3] = false;
                } else if (handleShoppingTouches[4]){
                    selection = 4;
                    handleShoppingTouches[4] = false;
                } else if (handleShoppingTouches[5]){

                    // Checks if multipurpose button is pressed
                    *(status+2) = 1;
                }
                if (selection != -1){

                    // Sets the first index of status to selection
                    *status = selection;

                    // Updates the value of status[0] of the object array passed in
                    updateButton(status, (objectArray+*status));
                }
            }
        }

        /*
        Takes a pointer in to status, and a pointer to a store object. It then
        modifies the second index of status depending on if the item has been bought or equipped
        @author Jalen
        */
        void updateButton(int* status, StoreObject* obj){

            // Checks if item is bought
            if (obj->checkIfBought()){

                // Then checks if item is equipped
                if (obj->checkIfEquipped()){

                    // Mulitpurpose button is back
                    *(status+1) = 0;
                } else{

                    // Mulitpurpose button is Equip
                    *(status+1) = 1;
                }
            } else {
                // Mulitpurpose button is buy
                *(status+1) = 2;
            }
        }

        /*
        Method exports to a file in the stats folder named "equippedItems.txt". Each index of the currentEquipped
        array is printed in order of color, reload, then radius.
        @author Jalen
        */
        void exportCurrentEquipped(){

            // First we write to the "equippedItems.txt" file
            FEHFile *fptr = SD.FOpen("stats/equippedItems.txt", "w");

            // Makes sure it opened successfully
            if (fptr != NULL){

                // Writes each index of currentEquipped to the text file
                SD.FPrintf(fptr, "%d %d %d", currentEquipped[0], currentEquipped[1], currentEquipped[2]);
            }

            // Closes the file
            SD.FClose(fptr);
        }

        /*
        Method imports from "equippedItems.txt". Each index of the currentEquipped is set to 
        each item written to the file in order of color, reload, and radius. Also, unequips 
        what is currently equipped.
        @author Jalen
        */
        void importEquipped(){

            // Opens up "equippedItems.txt" for writing
            FEHFile *fptr = SD.FOpen("stats/equippedItems.txt", "r");

            // Makes sure file opened successfully
            if (fptr != NULL){

                // Unequips each item before import
                colorBullets[currentEquipped[0]].unequipItem();
                reloadBullets[currentEquipped[1]].unequipItem();
                radiusBullets[currentEquipped[2]].unequipItem();

                // Scans file and sets the value to each currentEquipped index
                SD.FScanf(fptr, "%d %d %d", currentEquipped, currentEquipped+1, currentEquipped+2);

                // Equips each appropriate index
                colorBullets[currentEquipped[0]].equipItem();
                reloadBullets[currentEquipped[1]].equipItem();
                radiusBullets[currentEquipped[2]].equipItem();
            } 

            // Closes file
            SD.FClose(fptr);
        }

        /*
        Method writes to "boughtItems.txt". First iterates through each index
        of colorBullets and checks if it has been bought and if so writes the index.
        Does similar process for reloadBullets array except prints the index + 5,
        and radiusBullets of i+10.
        @author Ayush
        */
        void exportBoughtItems(){

            // Open up "boughtItems.txt" for writing
            FEHFile *fptr = SD.FOpen("stats/boughtItems.txt", "w");

            // Checks if file opened successfully
            if (fptr != NULL){

                // Iterates through color bullets
                for (int i = 0; i < 5; i++){
                    if (colorBullets[i].checkIfBought()){
                        SD.FPrintf(fptr, "%d ", i);
                    }
                } 

                // Iterates through reloat bullets
                for (int i = 0; i < 5; i++){
                    if (reloadBullets[i].checkIfBought()){
                        SD.FPrintf(fptr, "%d ", i+5);
                    }
                }

                // Iterates through radius bullets
                for (int i = 0; i < 5; i++){
                    if (radiusBullets[i].checkIfBought()){
                        SD.FPrintf(fptr, "%d ", i+10);
                    }
                }
            }

            // Closes file
            SD.FClose(fptr);
        }

        /*
        Method reads "boughtItems.txt". Runs indefinitely until we reach the 
        end of the file, and then set an int variable temp to the number
        scanned in. Checks if temp is less than 5, if so sets temp index of colorBullets
        to buy, for less than 10, sets temp-5 index of reloadBullets to buy, and 
        otherwise sets temp-10 index of radiusBullets to buy.
        @author Ayush
        */
        void importBought(){

            // First we scan through the "boughtItems.txt" file
            FEHFile *fptr = SD.FOpen("stats/boughtItems.txt", "r");

            // Checks if file opened successfully
            if (fptr != NULL){

                // Runs until we reach to the end of the file
                while (!SD.FEof(fptr)){

                    // Creates a temp variable to scan to
                    int temp;
                    SD.FScanf(fptr, "%d", &temp);

                    // Checks if temp less than 5
                    if (temp < 5){
                        colorBullets[temp].setBuy(true);
                    } else if (temp < 10){
                        // Otherwise checks if temp less than 10
                        temp -= 5;
                        reloadBullets[temp].setBuy(true);
                    } else {
                        // otherwise run this
                        temp -= 10;
                        radiusBullets[temp].setBuy(true);
                    }
                }
            }
            // Closes the file
            SD.FClose(fptr);
        }
};