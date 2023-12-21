// Defines the screen width
#define SCREEN_WIDTH  319

class LineDrawing {
private:

    // These are predefined so we know where the line starts
    #define lineStartX 160
    #define lineStartY 210

    // Creates two variables used later for updating the variables
    int tempEndX, tempEndY;

public:

    // These represent the x and y of the top of the variable
    int lineEndX = 160, lineEndY = 5;

    // Creates an initial angle of 90 degrees or pi/2 radians
    float angleOfLine = M_PI/2;

    // Finds lineLength using pythagorean theorem
    float lineLength = sqrt(pow(lineEndX-lineStartX,2) + pow(lineEndY-lineStartY,2));

    /*
    Method draws the line using the current coordinates using a white font.
    @author Jalen
    */
    void drawLine() {
        LCD.SetFontColor(WHITE);
        LCD.DrawLine(lineStartX, lineStartY, lineEndX, lineEndY);
    }

    /*
    Updates the line position based off the angleChange variable passed in
    The method works by calling an updateOnAngle method which changes the 
    x and y coordinates, draws black over the current line, and draws white 
    over the new line
    @author Ayush
    */
    void updateLinePosition(float angleChange) {

        /*
        Calls updateOnAngle method which passes in the angleOfLine variable of the class
        plus the angleChange passed in, which changes the tempEndX and tempEndY variables
        */
        updateOnAngle(angleOfLine + angleChange);

        /* 
        We make the sure x end of the temp variables are greater than 0 and less than the screen width
        If so then we update the line
        */

        if (tempEndX > 0 && tempEndX < SCREEN_WIDTH){

            // Sets the font to black and draws over the current line
            LCD.SetFontColor(BLACK);
            LCD.DrawLine(lineStartX, lineStartY, lineEndX, lineEndY);

            // Updates lineEndX and lineEndY to the temp variables
            lineEndX = tempEndX;
            lineEndY = tempEndY;

            // Update the angleOfline variable by adding the angleChange
            angleOfLine += angleChange;

            // Redraws the new line
            drawLine();
        }
    }

    /*
    The method updates the tempEndX to the length of the hypotenuse
    times cos(angle) + the current x positon.
    Next it, updates tempEndY to the current y position minus
    the sin(angle) where angle is passed in.
    @author Jalen
    */
    void updateOnAngle(float angle){
        tempEndX = lineLength*cos(angle) + lineStartX;
        tempEndY = lineStartY - lineLength*sin(angle);
    }
};