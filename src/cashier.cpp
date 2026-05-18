//
//  cashier.cpp
//  BooksellersSD — Part 15
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 15: Inheritance, InventoryBook, SoldBook
//

#include "serendipity.h"

int cashier() {
    char date[20];
    cin.ignore();
    cout << "What is the Date: ";
    cin.getline(date, 20);

    int numTitles;
    numTitles = InputValidator::getInt("How many titles is the customer purchasing? ", 1, 20);

    SoldBook* cart = new SoldBook[numTitles];
    int* slots = new int[numTitles];
    int booksListed = 0;

    SoldBook::resetTotal();

    for (int t = 0; t < numTitles; t++) {
        char search[14];
        cout << "Enter ISBN for title " << (t + 1) << ": ";
        cin >> search;

        int found = -1;
        InventoryBook b;
        for (int i = 0; i < MAX_BOOKS; i++) {
            if (!invDB.readRecord(i, b)) break;
            if (!b.isEmpty() && strcmp(b.getISBN(), search) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            cout << "--- Book not found in inventory :( ---" << endl;
            cout << "--------------------------------------------------" << endl;
            t--;
            continue;
        }

        invDB.readRecord(found, b);
        cout << "--------------------------------------------------" << endl;
        cout << "Name: " << b.getTitle()
             << "  Price: $" << fixed << setprecision(2) << b.getRetail()
             << "  Available Qty: " << b.getQty() << endl;
        cout << "--------------------------------------------------" << endl;

        int qty;
        cout << "What quantity would you like to purchase?: ";
        cin >> qty;

        while (qty > b.getQty()) {
            cout << "Limited inventory! Max purchasable: " << b.getQty() << endl;
            cout << "Enter new quantity: ";
            cin >> qty;
        }

        // Copy inventory data into the SoldBook
        cart[booksListed].setTitle(b.getTitle());
        cart[booksListed].setISBN(b.getISBN());
        cart[booksListed].setAuthor(b.getAuthor());
        cart[booksListed].setPub(b.getPub());
        cart[booksListed].setDateAdded(b.getDateAdded());
        cart[booksListed].setQty(b.getQty());
        cart[booksListed].setWholesale(b.getWholesale());
        cart[booksListed].setRetail(b.getRetail());

        cart[booksListed].setQtySold(qty);
        cart[booksListed].calcTax();
        cart[booksListed].calcSubtotal();

        slots[booksListed] = found;
        booksListed++;

        cout << "--- Book added to cart! ---" << endl;
    }

    // Display sales slip
    cout << endl;
    cout << "--- Opening Checkout! ---" << endl;
    cout << "Date: " << date << endl << endl;
    cout << setw(3) << "Qty "
         << left << setw(17) << "ISBN"
         << left << setw(32) << "Title"
         << left << setw(10) << "Price"
         << left << setw(10) << "Total" << endl;
    cout << "--------------------------------------------------------------------------------\n";

    cout << fixed << setprecision(2);
    for (int i = 0; i < booksListed; i++) {
        cout << setw(3)  << cart[i].getQtySold()
             << left << setw(17) << cart[i].getISBN()
             << left << setw(32) << cart[i].getTitle()
             << left << setw(10) << format("${:.2f}", cart[i].getRetail())
             << left << setw(10) << format("${:.2f}", cart[i].getSubtotal())
             << endl;

        // Update inventory quantity
        InventoryBook inv;
        invDB.readRecord(slots[i], inv);
        inv.setQty(inv.getQty() - cart[i].getQtySold());
        invDB.writeRecord(slots[i], inv);
    }

    double subtotal = SoldBook::getTotal();
    double taxTotal = 0.0;
    for (int i = 0; i < booksListed; i++)
        taxTotal += cart[i].getTax();

    cout << endl;
    cout << right << setw(12) << "Subtotal: $" << (subtotal - taxTotal) << endl;
    cout << right << setw(12) << "Tax: $"      << taxTotal              << endl;
    cout << right << setw(12) << "Total: $"    << subtotal              << endl;
    cout << endl;
    cout << "Thank you for shopping at Serendipity!" << endl;

    delete[] slots;
    delete[] cart;

    return 0;
}
