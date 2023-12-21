class Credits{
    private:

        // Object variable that represents how many credits the user has
        int numCredits;

        // Used for animation
        int animationFrame = 0;
        float timeSinceLastAnimation = 0;

    public:

        // Whenever a credits object is created, the numCredits variable updates to what is written on the text file
        Credits(){

            // Calls a method that updates the object variable numCredits from a text file
            importCredits();
        }

        /*
        Animation based on https://www.vectorstock.com/royalty-free-vector/pixel-art-style-isolated-coin-for-retro-vector-34500826,
        where coinTwo, coinThree, coinFour all drawn by Ayush, this funciton created
        by Jalen.
        */
        void displayAnimation(int x, int y){
            if (TimeNow() - timeSinceLastAnimation >= 0.150){
                LCD.SetFontColor(SCARLET);
                LCD.FillRectangle(x-7,y-7,16,16);
                switch (animationFrame){
                    case 0:
                        drawCoinTwo(x, y);
                        break;
                    case 1:
                        drawCoinThree(x, y);
                        break;
                    case 2:
                        drawCoinFour(x,y);
                        break;
                    case 3:
                        drawCoinThree(x,y);
                        break;
                    case 4:
                        drawCoinTwo(x,y);
                        break;
                    case 5:
                        drawCoin(x,y);
                        animationFrame = -1;
                }
                animationFrame++;
                timeSinceLastAnimation = TimeNow();
            }
        }

        /*
        Draws a coin based on the center passed in from (x,y). The pixel art is  based on
        https://www.pixilart.com/art/coin-spinning-f1c65f5536fe039.
        @author Ayush.
        */
        
        static void drawCoin(int x, int y){

            // Gold color
            LCD.SetFontColor(0xFFDD19);
            LCD.DrawRectangle(x-4,y-5,10,12);
            LCD.FillRectangle(x-4,y-5,10,12);
            LCD.DrawLine(x-5,y-4,x-5,y+5);
            LCD.DrawLine(x-6,y-2,x-6,y+3);
            LCD.DrawLine(x-2,y-6,x+3,y-6);
            LCD.DrawLine(x-2,y+7,x+3,y+7);
            LCD.DrawLine(x+6,y-4,x+6,y+5);
            LCD.DrawLine(x+7,y-2,x+7,y+3);

            LCD.SetFontColor(BLACK);
            LCD.DrawLine(x-7,y-2,x-7,y+4);
            LCD.DrawLine(x-6,y-4,x-6,y-3);
            LCD.DrawLine(x-6,y+4,x-6,y+5);
            LCD.DrawPixel(x-5,y-5);
            LCD.DrawPixel(x-5,y+6);
            LCD.DrawLine(x-4,y-6,x-3,y-6);
            LCD.DrawLine(x-4,y+7,x-3,y+7);
            LCD.DrawLine(x-2,y-7,x+3,y-7);
            LCD.DrawLine(x-2,y+8,x+3,y+8);
            LCD.DrawLine(x+4,y-6,x+5,y-6);
            LCD.DrawLine(x+4,y+7,x+5,y+7);
            LCD.DrawPixel(x+6,y-5);
            LCD.DrawPixel(x+6,y+6);
            LCD.DrawLine(x+7,y-4,x+7,y-3);
            LCD.DrawLine(x+7,y+5,x+7,y+4);
            LCD.DrawLine(x+8,y-2,x+8,y+3);

            LCD.SetFontColor(WHITE);
            LCD.DrawLine(x-2,y-5,x+3,y-5);
            LCD.DrawLine(x-1,y-3,x-1,y+4);
            LCD.DrawLine(x,y-3,x+1,y-3);
            LCD.DrawLine(x-4,y-4,x-4,y-3);
            LCD.DrawPixel(x-3,y-4);
            LCD.DrawLine(x-5,y-2,x-5,y+4);
            LCD.DrawPixel(x-4,y+4);
            LCD.DrawPixel(x+4,y-4);

        }
        
        /*
        Draws second coin based on animation by Ayush.
        */
        static void drawCoinTwo(int x, int y){
            // Gold color
            LCD.SetFontColor(0xFFDD19);
            LCD.DrawLine(x-5,y-3,x-5,y+3);
            LCD.DrawLine(x-4,y+5,x-4,y-5);
            LCD.DrawLine(x+5,y-3,x+5,y+3);
            LCD.FillRectangle(x-3,y-6,7,13);
            LCD.DrawLine(x+4,y+5,x+4,y-5);

            // Draws Black
            LCD.SetFontColor(BLACK);
            LCD.DrawLine(x-6,y+3,x-6,y-3);
            LCD.DrawLine(x+6,y+3,x+6,y-3);
            LCD.DrawLine(x-5,y+5,x-5,y+4);
            LCD.DrawLine(x+5,y+5,x+5,y+4);
            LCD.DrawLine(x-5,y-5,x-5,y-4);
            LCD.DrawLine(x+5,y-5,x+5,y-4);
            LCD.DrawPixel(x-4,y+6);
            LCD.DrawPixel(x-4,y-6);
            LCD.DrawPixel(x+4,y+6);
            LCD.DrawPixel(x+4,y-6);
            LCD.DrawLine(x-3,y-7,x+3,y-7);
            LCD.DrawLine(x-3,y+7,x+3,y+7);

            //Draws white
            LCD.SetFontColor(WHITE);
            LCD.DrawLine(x-2,y+5,x+3,y+5);
            LCD.DrawLine(x+4,y+4,x+4,y-3);
            LCD.DrawLine(x+3,y-4,x+3,y-5);
            LCD.DrawLine(x-2,y+1,x-2,y-1);
            LCD.DrawLine(x-1,y-1,x-1,y-3);
            LCD.DrawPixel(x,y-3);
            LCD.DrawPixel(x+1,y-2);

            // Dark Gold color
            LCD.SetFontColor(0xEA9F0C);
            LCD.DrawLine(x-4,y+3,x-4,y-4);
            LCD.DrawLine(x-3,y-5,x+2,y-5);
            LCD.DrawLine(x-3,y+5,x-3,y+4);
            LCD.DrawLine(x+2,y+1,x+2,y-1);
            LCD.DrawLine(x+1,y+3,x+1,y+1);
            LCD.DrawPixel(x,y+3);
            LCD.DrawPixel(x-1,y+2);
        }

        /*
        Third coin for animation, made by Ayush.
        */
        static void drawCoinThree(int x, int y){

            // Gold color
            LCD.SetFontColor(0xFFDD19);
            LCD.FillRectangle(x-2,y-6,5,13);
            LCD.DrawLine(x-4,y+4,x-4,y-4);
            LCD.DrawLine(x-3,y+5,x-3,y-5);
            LCD.DrawLine(x+4,y+4,x+4,y-4);
            LCD.DrawLine(x+3,y+5,x+3,y-5);

            LCD.SetFontColor(BLACK);
            LCD.DrawLine(x-5,y+4,x-5,y-4);
            LCD.DrawLine(x+5,y+4,x+5,y-4);
            LCD.DrawPixel(x-4,y-5);
            LCD.DrawPixel(x-4,y+5);
            LCD.DrawPixel(x+4,y-5);
            LCD.DrawPixel(x+4,y+5);
            LCD.DrawPixel(x-3,y-6);
            LCD.DrawPixel(x-3,y+6);
            LCD.DrawPixel(x+3,y-6);
            LCD.DrawPixel(x+3,y+6);
            LCD.DrawLine(x-2,y-7,x+2,y-7);
            LCD.DrawLine(x-2,y+7,x+2,y+7);

            // Draws white
            LCD.SetFontColor(WHITE);
            LCD.DrawLine(x-1,y+2,x-1,y-3);
            LCD.DrawPixel(x,y-3);
            LCD.DrawPixel(x+2,y-5);
            LCD.DrawLine(x-1,y+5,x+2,y+5);
            LCD.DrawLine(x+3,y+4,x+3,y-4);

            // Dark Gold color
            LCD.SetFontColor(0xEA9F0C);
            LCD.DrawLine(x-3,y+4,x-3,y-4);
            LCD.DrawLine(x-2,y-5,x+1,y-5);
            LCD.DrawLine(x+1,y+3,x+1,y-2);
            LCD.DrawPixel(x-2,y+5);
            LCD.DrawPixel(x,y+3);
        }

        /*
        Fourth coin animation, made by Ayush.
        */
        static void drawCoinFour(int x, int y){
            LCD.SetFontColor(0xFFDD19);
            LCD.FillRectangle(x, y-6, 2, 13);

            LCD.SetFontColor(WHITE);
            LCD.DrawPixel(x,y+1);
            LCD.DrawPixel(x+1, y+2);

            LCD.SetFontColor(BLACK);
            LCD.DrawLine(x-1,y+6,x-1,y-6);
            LCD.DrawLine(x+2,y+6,x+2,y-6);
            LCD.DrawLine(x-1,y+7,x+2,y+7);
            LCD.DrawLine(x-1,y-7,x+2,y-7);

            // Dark Gold color
            LCD.SetFontColor(0xEA9F0C);
            LCD.DrawPixel(x,y-3);
            LCD.DrawPixel(x+1, y-2);
        }

        /*
        Method takes a parameter called num, and then changes the object variable
        numCredits to numCredits + num.
        @author Ayush.
        */
        void changeCredits(int num){
            numCredits += num;
        }

        /*
        Method resets the object variable numCredits to 0.
        @author Ayush
        */
        void resetCredits(){
            numCredits = 0;
        }

        /*
        Method returns an integer value to the object variable numCredits.
        @author Ayush
        */
        int getCredits(){
            return numCredits;
        }

        /*
        Method opens up text file "stats/credits.txt" for reading, makes sure the file opened successfully
        and if so reads the first integer in the text file and sets it to numCredits. Otherwise, we set
        numCredits to 0. Lastly, we close the text file
        @author Jalen
        */
        void importCredits(){

            // Opens up "stats/credits.txt" file for reading
            FEHFile *fptr = SD.FOpen("stats/credits.txt", "r");

            // Checks to make sure the file opened successfully
            if (fptr != NULL){

                // Scans for an integer and changes numCredits to that value
                SD.FScanf(fptr, "%d", &numCredits);
            } else{

                // Otherwise if not oopened successfully assigns numCredits to 0.
                numCredits = 0;
            }

            // Closes the file.
            SD.FClose(fptr);
        }

        /*
        Method opens up text file "stats/credits.txt" for writing, makes sure the file opened successfully
        and if so writes numCredits to the text file. Afterwards, we close the file.
        @author Ayush.
        */
        void exportCredits(){

            // Opens up "stats/credits.txt" file for writing
            FEHFile *fptr = SD.FOpen("stats/credits.txt", "w");

            // Checks to make sure the file opened successfully
            if (fptr != NULL){

                // Writes the value of numCredits to the file.
                SD.FPrintf(fptr, "%d", numCredits);
            }

            // Closes the file
            SD.FClose(fptr);
        }
};