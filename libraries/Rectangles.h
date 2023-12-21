class Rectangles{
    public:
        /*
        Method returns where a passed in point (x and y) is within the rectangle parameters
        of the top left corner of the box (rectX, rectY) and its width (rectWidth) and height
        (rectHeight).
        @author Ayush
        */
        bool static isPointInsideRect(float x, float y, int rectX, int rectY, int rectWidth, int rectHeight) {

            return (x >= rectX && x < rectX + rectWidth && y >= rectY && y < rectY + rectHeight);
        }

        /*
        Method draws a white rectangle with text based off a given name, and (x,y) coordinate of the top
        and the width and height of the rectangle. Also, centers the text based on the length
        @author Jalen
        */
        void static drawRectangleWithText(char name[], int x1, int y1, int width, int height, bool isGreen){

            // Finds length of text
            int nameLength = strlen(name)*12;

            // Finds starting point of text based on the rectangle width and textWidth and x1
            int startText = (width-nameLength)/2+x1;

            // Sets font color to green if isGreen is true, and font color wo white if isGreen is false
            if (isGreen){
                LCD.SetFontColor(GREEN);
            } else{
                LCD.SetFontColor(WHITE);
            }

            // Draws and fills the rectangle based on the parameters passed in
            LCD.DrawRectangle(x1,y1,width,height);
            LCD.FillRectangle(x1,y1,width,height);

            // Sets font color to black
            LCD.SetFontColor(BLACK);

            // Writes name at the points specified
            LCD.WriteAt(name,startText,y1 + height/4);
        }

        /*
        Draws a rectangle either white or yellow based on if isYellow is true,
        sets the font color to white or yellow.
        @author Ayush
        */ 
        void static drawRectangleWhiteOrYellow(int x1, int y1, int width, int height, bool isYellow){
            if (isYellow){
                LCD.SetFontColor(YELLOW);
            } else{
                LCD.SetFontColor(WHITE);
            }
            LCD.DrawRectangle(x1, y1, width, height);
            LCD.FillRectangle(x1, y1, width, height);
        }
        
        /*
        Draws a rectangle either white or green based on if isGreen is true,
        sets the font color to white or yellow.
        @author Ayush
        */ 
        void static drawRectangleWhiteOrGreen(int x1, int y1, int width, int height, bool isGreen){
            if (isGreen){
                LCD.SetFontColor(GREEN);
            } else{
                LCD.SetFontColor(WHITE);
            }
            LCD.DrawRectangle(x1, y1, width, height);
            LCD.FillRectangle(x1, y1, width, height);
        }
};