#include "LineDrawing.h"
#include "Bullets.h"

class PlayScreen{
    private:
        // Creates an aimLine object of the LineDrawing class
        LineDrawing aimLine;

        // Left verticies
        int leftX1 = 100, leftY1 = 229, leftX2 = 120, leftY2 = 239, leftY3 = 219;

        // Right verticies
        int rightX1 = 200, rightY1 = 239, rightY2 = 219, rightX2 = 220, rightY3 = 229;

        // Creates the shoot button coordinates, height and width
        int shootXLeft = 130, shootWidth = 60, shootHeight = 20, shootYTop = 219;
        
    public:

        // Creates bullet object
        Bullets currentBullet;

        /*
        Method first clears the screen and draws an initial line, draws the circles, and shoot box.
        @author Jalen
        */
        void display(bool canShoot){
            // Clears the screen
            LCD.Clear();

            // Change background color
            LCD.SetBackgroundColor(BLACK);

            // Uses a white font color to draw the line, draw circles, and a the shoot button
            LCD.SetFontColor(WHITE);
            aimLine.drawLine();
            Rectangles::drawRectangleWithText("SHOOT", shootXLeft,shootYTop,shootWidth,shootHeight, canShoot);
            drawTriangle(leftX1,leftY1,leftX2,leftY2,leftX2,leftY3);
            drawTriangle(rightX1,rightY1,rightX1,rightY2,rightX2,rightY3);
        }

        // Function to draw a triangle given three vertices (x1, y1), (x2, y2), and (x3, y3)
        // @author Ayush
        void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {

            // Sets font color to white
            LCD.SetFontColor(WHITE);

            // Draw lines connecting the three vertices to form a triangle
            LCD.DrawLine(x1, y1, x2, y2);
            LCD.DrawLine(x2, y2, x3, y3);
            LCD.DrawLine(x3, y3, x1, y1);
        }

        // Method updates the line based off if the value is right
        // @author Ayush
        void lineUpdater(bool isRight){

            // The angleIncrementer value is pi/12 radians or 15 degrees
            float angleIncrementer = 1.0/12*M_PI;

            /* 
            If the updater is right we call updateLinePosition method
            with a positive angleIncrementer value, otherwise negative
            */

            if (isRight){
                aimLine.updateLinePosition(-angleIncrementer);
            } else {
                aimLine.updateLinePosition(angleIncrementer);
            }
        }

        // Methods gets the incremental value based a pointer to an aray
        // @author Ayush
        void getIncremental(float* a){

            // endX is the value of lineEndX from aimLine object and endY is lineEndY
            float endX = aimLine.lineEndX;
            float endY = aimLine.lineEndY;

            // The first index is the difference from the top x coordinate and 160 divided by 20
            *a = (endX-160)/10.0;

            // The second index is the difference from the top y coordinate and 220 divided by 20
            *(a+1) = (endY-220)/10.0;
        }

        /*
        Method takes in a pointer to an array and checks the x and y coordinates being touched,
        and then checks if the triangles have been touched, and then the shoot rectangle
        @author Jalen
        */
        bool handleTouchEvents(int* a) {

            // Uses temp variables x and y and calls the touch method that updates them
            float x, y;

            // Modifies x and y
            LCD.Touch(&x,&y);

            bool hasTouched = false;

            if (LCD.Touch(&x,&y)){

                hasTouched = true;

                // First checks if the left triangle is being touched
                if (isPointInsideTriangle(x, y, leftX1, leftY1, leftX2, leftY2, leftX2, leftY3)) {
                    *a = true;
                }

                // Checks if the right triangle is being touched
                else if (isPointInsideTriangle(x, y, rightX1, rightY1, rightX1, rightY2, rightX2, rightY3)) {
                    *(a + 1) = true;
                }

                // Checks if the shoot box is being touched
                else if (abs(x-shootXLeft-shootWidth/2) < shootWidth/2 && abs(y-shootYTop-shootHeight/2) < shootHeight/2){
                    *(a+2) = true;
                }  else{
                    hasTouched = false;
                }
            }

            return hasTouched;

        }

        // References https://blogs.sas.com/content/iml/2023/06/21/barycentric-coordinates.html#:~:text=If%20all%20barycentric%20coordinates%20for,a%20vertex%20of%20the%20triangle.
        // Function to check if a point (xTouch, yTouch) is inside the triangle defined by the vertices (x1, y1), (x2, y2), and (x3, y3)
        // @author Jalen
        bool isPointInsideTriangle(float xTouch, float yTouch, float x1, float y1, float x2, float y2, float x3, float y3) {

            // Compute barycentric coordinates based on algorithm
            float detT = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);
            float alpha = ((y2 - y3) * (xTouch - x3) + (x3 - x2) * (yTouch - y3)) / detT;
            float beta = ((y3 - y1) * (xTouch - x3) + (x1 - x3) * (yTouch - y3)) / detT;
            float gamma = 1.0 - alpha - beta;

            // Check if the point is inside the triangle
            return alpha >= 0 && beta >= 0 && gamma >= 0;
        }
};