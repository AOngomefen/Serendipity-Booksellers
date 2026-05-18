//
//  mainmenu.cpp
//  BooksellersSD — Part 15
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 15: Inheritance, InventoryBook, SoldBook
//

#include "serendipity.h"

int mainmenu() {
    int choice = 0;

    do {
        cout << "--------------------------------------------------" << endl;
        cout << setw(30) << "Serendipidty Booksellers\n";
        cout << setw(30) << "       Main Menu\n";
        cout << endl;
        cout << "1. Cashier Module\n";
        cout << "2. Inventory Database Module\n";
        cout << "3. Report Module\n";
        cout << "4. Exit\n";
        cout << endl;

        choice = InputValidator::getInt("Enter Your Choice: ", 1, 4);

        switch (choice) {
            case 1:
                cout << "You chose option 1: Cashier Module" << endl;
                cout << "--------------------------------------------------" << endl;
                cashier();
                break;
            case 2:
                cout << "You chose option 2: Inventory Database" << endl;
                cout << "--------------------------------------------------" << endl;
                invmenu();
                break;
            case 3:
                cout << "You chose option 3: Report Module" << endl;
                cout << "--------------------------------------------------" << endl;
                reports();
                break;
            case 4:
                cout << "You chose option 4: Exit! Bye Bye." << endl;
                cout << "--------------------------------------------------" << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
