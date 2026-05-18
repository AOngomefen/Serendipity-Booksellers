//
//  main.cpp
//  BooksellersSD — Part 16
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 16: Exceptions, Templates, and the STL
//

#include "serendipity.h"

InventoryFile invDB("inventory.dat");

int main() {
    try {
        if (!invDB.open()) {
            throw runtime_error("FATAL: Unable to open inventory file 'inventory.dat'. "
                                "Check that the file exists and is not locked by another process.");
        }

        mainmenu();

        invDB.close();
    }
    catch (const runtime_error& e) {
        cerr << "\n*** CRITICAL ERROR ***" << endl;
        cerr << e.what() << endl;
        cerr << "Program will now terminate." << endl;
        return 1;
    }

    return 0;
}
