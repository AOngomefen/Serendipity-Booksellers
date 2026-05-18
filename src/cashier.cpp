//
//  cashier.cpp
//  BooksellersSD — Part 14
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 14: bookMatch, InventoryFile, InputValidator
//

#include "serendipity.h"

int cashier() {
    char date[20];
    int  purchasedSlot[20];   
    int  qtys[20];
    int  booksListed = 0;
    double total = 0.0;
    const double TAX = .06;

    cin.ignore();
    cout << "What is the Date: ";
    cin.getline(date, 20);

    char addingBook;
    do {
        char search[14];
        cout << "What book do you wish to purchase? Please insert ISBN: ";
        cin >> search;

        int  found = -1;
        BookData b;
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
        } else {
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

            purchasedSlot[booksListed] = found;
            qtys[booksListed]          = qty;
            booksListed++;
            cout << "--- Book added to cart! ---" << endl;
        }

        cin.ignore(1000, '\n');
        cout << "Are you finished adding books to your cart? (y/n): ";
        cin >> addingBook;

    } while (addingBook == 'n' || addingBook == 'N');

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
        BookData b;
        invDB.readRecord(purchasedSlot[i], b);

        int    qty = qtys[i];
        double sub = b.getRetail() * qty;
        total += sub;

        cout << setw(3)  << qty
             << left << setw(17) << b.getISBN()
             << left << setw(32) << b.getTitle()
             << left << setw(10) << format("${:.2f}", b.getRetail())
             << left << setw(10) << format("${:.2f}", sub)
             << endl;

        b.setQty(b.getQty() - qty);
        invDB.writeRecord(purchasedSlot[i], b);
    }

    cout << endl;
    cout << right << setw(12) << "Subtotal: $" << total            << endl;
    cout << right << setw(12) << "Tax: $"      << total * TAX      << endl;
    cout << right << setw(12) << "Total: $"    << total * (1 + TAX)<< endl;
    cout << endl;
    cout << "Thank you for shopping at Serendipity!" << endl;

    return 0;
}
