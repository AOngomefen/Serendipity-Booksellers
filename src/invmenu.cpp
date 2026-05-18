//
//  invmenu.cpp
//  BooksellersSD — Part 13
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 13: BookData class with private members
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

        cout << "Enter Your Choice: ";
        cin >> choice;

        while (choice < 1 || choice > 5) {
            cout << "Please enter a number in the range 1-5: ";
            cin >> choice;
        }

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

    BookData b;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (!readRecord(i, b)) break;
        if (b.isEmpty()) continue;

        char title[51];
        strncpy(title, b.getTitle(), 51);
        // bookTitle is already stored uppercase, so compare directly.
        if (strstr(title, search) != nullptr) {
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
            BookData b;
            readRecord(slot, b);
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
        BookData b;
        for (int i = 0; i < MAX_BOOKS; i++) {
            if (!readRecord(i, b)) break;
            if (b.isEmpty()) { slot = i; break; }
        }

        if (slot == -1) {
            cout << "Inventory is full, no books can be added." << endl;
            return;
        }

        // Re-use b (currently zeroed / empty) to hold the new data.
        char temp[51];

        cout << "Enter Book Title: ";
        cin.getline(temp, 51);
        strUpper(temp);
        b.setTitle(temp);

        cout << "Enter Book ISBN: ";
        cin.getline(temp, 14);
        strUpper(temp);
        b.setISBN(temp);

        cout << "Enter Book Author in the format (Last, First): ";
        cin.getline(temp, 31);
        strUpper(temp);
        b.setAuthor(temp);

        cout << "Enter Book Publisher: ";
        cin.getline(temp, 31);
        strUpper(temp);
        b.setPub(temp);

        cout << "Enter Date Added in the Format (MM-DD-YYYY): ";
        cin.getline(temp, 11);
        b.setDateAdded(temp);

        int qty;
        cout << "Enter Book Quantity on Hand: ";
        cin >> qty;
        b.setQty(qty);

        double val;
        cout << "Enter Book Wholesale Cost: $";
        cin >> val;
        b.setWholesale(val);

        cout << "Enter Book Retail Price: $";
        cin >> val;
        b.setRetail(val);

        writeRecord(slot, b);
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

    BookData b;
    readRecord(slot, b);
    bookinfo(b, FULL);

    char done = 'n';
    do {
        int change = 0;
        cout << "--------------------------------------------------" << endl;
        cout << "Which field do you wish to change?\n";
        cout << "1. Book Title\n2. Book ISBN\n3. Book Author\n4. Book Publisher\n";
        cout << "5. Date Added\n6. Qty on Hand\n7. Wholesale Cost\n8. Retail Price\n";

        while (change < 1 || change > 8) {
            cout << "Please enter a number in the range 1-8: ";
            cin >> change;
        }
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
        writeRecord(slot, b);
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

    BookData b;
    readRecord(slot, b);
    bookinfo(b, FULL);

    char confirm;
    cout << "Are you sure you want to delete this book? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        b.removeBook();         // zeroes the object in memory
        writeRecord(slot, b);   // writes the zeroed record back to the file
        cout << "Book successfully deleted from inventory." << endl;
    } else {
        cout << "Deletion cancelled." << endl;
    }
}
