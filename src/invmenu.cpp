//
//  invmenu.cpp
//  BooksellersSD — Part 16
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 16: Exceptions, Templates, and the STL
//

#include "serendipity.h"

int invmenu() {
    int choice = 0;

    do {
        cout << "--------------------------------------------------" << endl;
        cout << setw(30) << "Serendipidty Booksellers\n";
        cout << setw(30) << "   Inventory Database\n";
        cout << endl;
        cout << "1. Look Up a Book\n";
        cout << "2. Add a Book\n";
        cout << "3. Edit a Book's Record\n";
        cout << "4. Delete a Book\n";
        cout << "5. Return to the Main Menu\n";
        cout << endl;

        choice = InputValidator::getInt("Enter Your Choice: ", 1, 5);

        switch (choice) {
            case 1: cout << "--------------------------------------------------" << endl; lookUpBook(); break;
            case 2: cout << "--------------------------------------------------" << endl; addBook();    break;
            case 3: cout << "--------------------------------------------------" << endl; editBook();   break;
            case 4: cout << "--------------------------------------------------" << endl; deleteBook(); break;
            case 5:
                cout << "Returning to Main Menu..." << endl;
                cout << "--------------------------------------------------" << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}

/*__________________________________________________________________*/

static int findBook(const char* prompt) {
    char search[51];
    cout << prompt;
    cin.ignore(1000, '\n');
    cin.getline(search, 51);
    strUpper(search);

    InventoryBook b;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (!invDB.readRecord(i, b)) break;
        if (b.isEmpty()) continue;

        if (b.bookMatch(search)) {
            cout << "Found: " << b.getTitle() << endl;
            cout << "Is this the book you are looking for? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
                return i;
        }
    }
    cout << "--- Book not found in inventory :( ---" << endl;
    return -1;
}

/*__________________________________________________________________*/
void lookUpBook() {
    cout << "You Selected Look Up a Book!" << endl;
    char again = 'y';

    do {
        cout << "--------------------------------------------------" << endl;
        int slot = findBook("Enter partial or full book title: ");
        if (slot != -1) {
            InventoryBook b;
            invDB.readRecord(slot, b);
            bookinfo(b, FULL);
        }

        cout << "Do you have another book to search (y/n)? : ";
        cin >> again;
    } while (again == 'y' || again == 'Y');
}

/*__________________________________________________________________*/
void addBook() {
    cout << "You Selected Add a Book!" << endl;
    char again = 'y';
    cin.ignore(1000, '\n');

    do {
        cout << "--------------------------------------------------" << endl;

        // Find the first empty slot in the file.
        int slot = -1;
        InventoryBook b;
        for (int i = 0; i < MAX_BOOKS; i++) {
            if (!invDB.readRecord(i, b)) break;
            if (b.isEmpty()) { slot = i; break; }
        }

        if (slot == -1) {
            cout << "Inventory is full, no books can be added." << endl;
            return;
        }

        // Re-use b (currently zeroed / empty) to hold the new data.
        char temp[51];

        InputValidator::getString("Enter Book Title: ", temp, 51);
        strUpper(temp);
        b.setTitle(temp);

        InputValidator::getString("Enter Book ISBN: ", temp, 14);
        strUpper(temp);
        b.setISBN(temp);

        InputValidator::getString("Enter Book Author in the format (Last, First): ", temp, 31);
        strUpper(temp);
        b.setAuthor(temp);

        InputValidator::getString("Enter Book Publisher: ", temp, 31);
        strUpper(temp);
        b.setPub(temp);

        InputValidator::getString("Enter Date Added in the Format (MM-DD-YYYY): ", temp, 11);
        b.setDateAdded(temp);

        int qty;
        qty = InputValidator::getInt("Enter Book Quantity on Hand: ", 0, 9999);
        b.setQty(qty);

        double val;
        val = InputValidator::getDouble("Enter Book Wholesale Cost: $");
        b.setWholesale(val);

        val = InputValidator::getDouble("Enter Book Retail Price: $");
        b.setRetail(val);

        invDB.writeRecord(slot, b);
        cout << "--- Book saved to inventory! ---" << endl;

        cout << "Do you have another book to add (y/n)? : ";
        cin >> again;
        cin.ignore(1000, '\n');

    } while (again == 'y' || again == 'Y');
}

/*__________________________________________________________________*/
void editBook() {
    cout << "You Selected Edit a Book!" << endl;
    cout << "--------------------------------------------------" << endl;

    int slot = findBook("Enter partial or full book title to edit: ");
    if (slot == -1) return;

    InventoryBook b;
    invDB.readRecord(slot, b);
    bookinfo(b, FULL);

    char done = 'n';
    do {
        cout << "--------------------------------------------------" << endl;
        cout << "Which field do you wish to change?\n";
        cout << "1. Book Title\n2. Book ISBN\n3. Book Author\n4. Book Publisher\n";
        cout << "5. Date Added\n6. Qty on Hand\n7. Wholesale Cost\n8. Retail Price\n";

        int change = InputValidator::getInt("Enter choice: ", 1, 8);
        cin.ignore(1000, '\n');

        char temp[51];
        switch (change) {
            case 1: cout << "Enter New Book Title: ";         cin.getline(temp, 51); strUpper(temp); b.setTitle(temp);     break;
            case 2: cout << "Enter New ISBN: ";               cin.getline(temp, 14); strUpper(temp); b.setISBN(temp);      break;
            case 3: cout << "Enter New Author: ";             cin.getline(temp, 31); strUpper(temp); b.setAuthor(temp);    break;
            case 4: cout << "Enter New Publisher: ";          cin.getline(temp, 31); strUpper(temp); b.setPub(temp);       break;
            case 5: cout << "Enter New Date (MM-DD-YYYY): ";  cin.getline(temp, 11);                 b.setDateAdded(temp); break;
            case 6: { int q;    cout << "Enter New Qty: ";         cin >> q; b.setQty(q);        break; }
            case 7: { double w; cout << "Enter New Wholesale: $";  cin >> w; b.setWholesale(w);  break; }
            case 8: { double r; cout << "Enter New Retail: $";     cin >> r; b.setRetail(r);     break; }
        }

        // Write the updated record back to the file.
        invDB.writeRecord(slot, b);
        cout << "--- Record updated! ---" << endl;

        cout << "Done changing? (y/n): ";
        cin >> done;
        cin.ignore(1000, '\n');
    } while (done == 'n' || done == 'N');
}

/*__________________________________________________________________*/

void deleteBook() {
    cout << "You Selected Delete a Book!" << endl;
    cout << "--------------------------------------------------" << endl;

    int slot = findBook("Enter partial or full book title to delete: ");
    if (slot == -1) return;

    InventoryBook b;
    invDB.readRecord(slot, b);
    bookinfo(b, FULL);

    char confirm;
    cout << "Are you sure you want to delete this book? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        b.removeBook();
        invDB.writeRecord(slot, b);
        cout << "Book successfully deleted from inventory." << endl;
    } else {
        cout << "Deletion cancelled." << endl;
    }
}
