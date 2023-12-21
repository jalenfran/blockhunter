class StoreObject{
    private:

        // Instance variable cost is the cost of the item
        int cost;

        // Two booleans that indicate whether the item has been bought or equipped
        bool hasBought, isEquipped;
    public: 

        // Method construct the StoreObject by setting itemCost to the cost, equipStatus to is Equipped and boughtStatus to hasBought
        // @author Jaln
        StoreObject(int itemCost, bool equipStatus, bool boughtStatus){

            // Sets each variable passed in to the corresponding object variable
            cost = itemCost;
            isEquipped = equipStatus;
            hasBought = boughtStatus;
        }
        
        // Method returns the object value of isEquipped
        // @author Jalen
        bool checkIfEquipped(){
            return isEquipped;
        }

        // Method returns the object value of isBought
        // @author Jalen
        bool checkIfBought(){
            return hasBought;
        }

        // Method sets isEquipped to true
        // @author Jalen
        void equipItem(){
            isEquipped = true;
        }

        // Method sets isEquipped to false
        // @author Jalen
        void unequipItem(){
            isEquipped = false;
        }

        /*
        Method first checks that the item has not already been bought. Next, it makes sure the user has 
        enough credits to buy the item and if so it sets hasBought to true, and reduces the number of credits.
        The method takees a pointer to a Credits object in order to find the current credits.
        @author Ayush
        */
        void buyItem(Credits* credit){

            // Checks if the item has not been bought
            if (!hasBought){

                // Checks if the user has enough credits to buy the item
                if (credit->getCredits() >= cost){

                    // If so we reduce the number of credits 
                    credit->changeCredits(-cost);

                    // We set hasBought to true
                    hasBought = true;
                }
            }
        }

        /*
        Method sets the object's hasBought boolean to the true or false value passed in
        named buy.
        @author Ayush
        */
        void setBuy(bool buy){
            hasBought = buy;
        }
};