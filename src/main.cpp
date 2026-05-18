//
//  main.cpp
//  BooksellersSD — Part 14
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 14: bookMatch, InventoryFile, InputValidator
//

#include "serendipity.h"

InventoryFile invDB("inventory.dat");

int main() {
    if (!invDB.open()) {
        cerr << "ERROR: Could not open inventory file." << endl;
        return 1;
    }

    mainmenu();

    invDB.close();
    return 0;
}
