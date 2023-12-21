class RandomObj{
    private:

        // Default position is (0,0)
        float xPosition = 0, yPosition = 0;

        // Defines diameter of 12
        int diameter = 12;

        // Defines x and y rates for the speed the random object travels
        float xRate, yRate;

        /*
        Method returns true, if the random number yields right,
        and false if the object should go left.
        */
        bool randIsRight(){

            // Finds a random number either 0 or 1
            int zeroOrOne = rand() % 2;

            // Creates a deafult value of isRight as false
            bool isRight = false;

            // If the random number is 1, then is Right is true
            if (zeroOrOne == 1){
                isRight = true;
            }

            // Returns isRight boolean
            return isRight;
        }
        
    public:

        /*
        Method first uses randIsRight method to find
        if the initial xPosition should be 0 or 319.
        Also, determines what the rate should be (3.5 is somewhat close 319/80).
        @author Jalen
        */
        void initializeRandObject(){

            // Checks if the random object should start from the right of left
            if (randIsRight()){

                // If right, xPosition starts at 319, and will decrease by 21.27
                xPosition = 319;
                xRate = -3.5;
            } else {

                // If left, xPosition starts at 0, and will increase by 21.27
                xPosition = 0;
                xRate = 3.5;
            }

            // The y position will start from [30,129]
            yPosition = rand() % 100+30;

            // The rate is this between [0.5,1] (negative because we want it to fly up)
            yRate = -(rand() % 2 + 1)/2.0;
        }

        // Method updates the position by the xRate and yRate set
        // @author Ayush
        void updatePosition(){
            xPosition += xRate;
            yPosition += yRate;
        }

        // Method displays a rectangle, using the current x and y posiiton and a height and width of the diameter set
        // @author Ayush
        void display(){

            // Sets font color to blue
            LCD.SetFontColor(BLUE);

            // Draws and then fills a rectanlge from the given parameters
            LCD.DrawRectangle(xPosition,yPosition,diameter,diameter);
            LCD.FillRectangle(xPosition,yPosition,diameter,diameter);
        }

        /*
        Method checks if the random object and the bullet passed in are touching by using the 
        distance between the center of the bullet and the center of the random object.
        If the distance between both are less than or equal to the sum of their radii,
        then the method returns true, otherwise false.
        @author Jalen
        */
        bool isCollision(Bullets currentBullet){
            
            // Finds bullet center
            float bulletCenterX = currentBullet.getBulletX();
            float bulletCenterY = currentBullet.getBulletY();

            // Finds RandomObj center
            float randomObjCenterX = xPosition + diameter/2;
            float randomObjCenterY = yPosition + diameter/2;

            // Finds distance
            float distance = sqrt(pow(bulletCenterX-randomObjCenterX,2)+pow(bulletCenterY-randomObjCenterY,2));

            // Returns if the distance is less than or equal to the sum of the radii
            return distance <= currentBullet.getBulletRadius() + diameter/2;
        }

        /*
        Changes the rate that the objects move based on difficulty
        @author Ayush
        */
        void setDifficulty(bool isHard){
            if (isHard){
                xRate *= 2;
                yRate *= 2;  
            }
        }
};