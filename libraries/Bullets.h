#include "FEHSD.h"
#include <string.h>

class Bullets{
    private:
        // Creates default coordinates of (160,202), with a radius of 10 and reload of 1000ms
        float bulletX = 160, bulletY = 202;
        int bulletRadius = 10, bulletReload = 1000;

        // Represents the current indexes of what is equipped
        int currentIndexes[3] = {0,0,0};
    public:

        // Clear funciton that resets the bullet to its starting poiint and type
        void clear(){
            updateBulletType(currentIndexes);
            bulletX = 160;
        }

        /*
        Method sketches out the bullet, using the color from the first index of the currentIndexes array
        Then, draws the circle with the object variables, bulletX, bulletY, and bulletRadius
        @author Ayush
        */
        void displayBullet(){
            // Draws a red bullet based on the current bullet coordinates, and the bullet radius
            switch (*currentIndexes){
                case 0:
                    LCD.SetFontColor(RED);
                    break;
                case 1:
                    LCD.SetFontColor(BLUE);
                    break;
                case 2: 
                    LCD.SetFontColor(GREEN);
                    break;
                case 3:
                    LCD.SetFontColor(ORANGE);
                    break;
                case 4:
                    LCD.SetFontColor(YELLOW);
            }
            LCD.DrawCircle(bulletX, bulletY,bulletRadius);
            LCD.FillCircle(bulletX, bulletY,bulletRadius);
        }

        // Method returns the value of the bullet x posiition
        // @author Jalen
        float getBulletX(){
            return bulletX;
        }

        // Method returns the value of the bullet y position
        // @author Jalen
        float getBulletY(){
            return bulletY;
        }
        
        // Method returns the value of the bullet radius
        // @author Jalen
        int getBulletRadius(){
            return bulletRadius;
        }


        /*
        Method takes in two parameters, incrementalX and incrementalY. These variables update the object
        variables bulletX and bulletY to incrementally increase the bullets position, (important for animations)
        @author Ayush
        */
        void partialBulletUpdater(float incrementalX, float incrementalY){
            bulletX += incrementalX;
            bulletY += incrementalY;
        }

        /*
        Method updates the bullet based off a pointer passed in, the first index updates the color equipped,
        the second index updates the bulletReload speed, and the third updates the bullet radius.
        The method utilizes a switch case to turn the numbers passed in to actual values.
        @author Jalen
        */
        void updateBulletType(int* currentEquipped){

            // Sets the first index passed in to the first index of the currentEquipped array
            *currentIndexes = *currentEquipped;

            // Sets the second index passed in to the second index of the currentEquipped array
            *(currentIndexes+1) = *(currentEquipped+1);

            // Sets the third index passed in to the third index of the currentEquipped array
            *(currentIndexes+2) = *(currentEquipped+2);

            // Switch case that alters the bulletReload speed in (ms) based on the index
            switch (*(currentIndexes+1)){
                case 0:
                    bulletReload = 2500;
                    break;
                case 1:
                    bulletReload = 2000;
                    break;
                case 2: 
                    bulletReload = 1500;
                    break;
                case 3:
                    bulletReload = 1000;
                    break;
                case 4:
                    bulletReload = 500;
            }

            // Switch case that alters the bulletRadius in px based on the index
            switch (*(currentIndexes+2)){
                case 0:
                    bulletRadius = 8;
                    break;
                case 1:
                    bulletRadius = 9;
                    break;
                case 2: 
                    bulletRadius = 10;
                    break;
                case 3:
                    bulletRadius = 11;
                    break;
                case 4:
                    bulletRadius = 12;
            }

            // Updates the new bulletY coordinate based on the radius
            bulletY = 210 - bulletRadius;
        }

        // Method returns the bullet reload speed
        int getBulletReload(){
            return bulletReload;
        }

};