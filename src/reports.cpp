//
//  reports.cpp
//  BooksellersSD — Part 13
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 13: BookData class with private members
//

#include "serendipity.h"

int reports() {
    int choice = 0;

    do {
        cout << setw(30) << "Serendipidty Booksellers\n";
        cout << setw(30) << "         Reports\n";
        cout << endl;
        cout << "1. Inventory Listing\n";
        cout << "2. Inventory Wholesale Value\n";
        cout << "3. Inventory Retail Value\n";
        cout << "4. Listing by Quantity\n";
        cout << "5. Listing by Cost\n";
        cout << "6. Listing by Age\n";
        cout << "7. Return to Main Menu\n";
        cout << endl;

        cout << "Enter Your Choice: ";
        cin >> choice;
        while (choice < 1 || choice > 7) {
            cout << "Please enter a number in the range 1-7: ";
            cin >> choice;
        }

        switch (choice) {
            case 1: cout << "--------------------------------------------------" << endl; repListing();   break;
            case 2: cout << "--------------------------------------------------" << endl; repWholesale(); break;
            case 3: cout << "--------------------------------------------------" << endl; repRetail();    break;
            case 4: cout << "--------------------------------------------------" << endl; repQty();       break;
            case 5: cout << "--------------------------------------------------" << endl; repCost();      break;
            case 6: cout << "--------------------------------------------------" << endl; repAge();       break;
            case 7:
                cout << "Returning to main..." << endl;
                cout << "--------------------------------------------------" << endl;
                break;
        }
    } while (choice != 7);

    return 0;
}

static void getDate(char* date) {
    cin.ignore(1000, '\n');
    cout << "Please Enter the Date: ";
    cin.getline(date, 20);
    cout << endl;
}

// Returns the count of records loaded.
static int loadAllRecords(BookData arr[], int maxSize) {
    int count = 0;
    BookData b;
    for (int i = 0; i < maxSize && count < maxSize; i++) {
        if (!readRecord(i, b)) break;
        if (!b.isEmpty())
            arr[count++] = b;
    }
    return count;
}

/*__________________________________________________________________*/

void repListing() {
    char date[20];
    getDate(date);
    cout << "[ Date: " << date << " ]" << endl;

    BookData b;
    bool anyFound = false;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (!readRecord(i, b)) break;
        if (!b.isEmpty()) {
            bookinfo(b, FULL);
            cout << "--------------------------------------------------" << endl;
            anyFound = true;
        }
    }
    if (!anyFound) cout << "No books in inventory." << endl;
    cout << "List Complete!! Returning to Reports..." << endl;
    cout << "--------------------------------------------------" << endl;
}

/*__________________________________________________________________*/

void repWholesale() {
    char date[20];
    getDate(date);
    cout << "[ Date: " << date << " ]" << endl;

    double total = 0.0;
    BookData b;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (!readRecord(i, b)) break;
        if (!b.isEmpty()) {
            bookinfo(b, WHOLESALE);
            cout << "--------------------------------------------------" << endl;
            total += b.getWholesale() * b.getQty();
        }
    }
    cout << "[ Total Wholesale Value: $" << fixed << setprecision(2) << total << " ]" << endl;
    cout << "List Complete!! Returning to Reports..." << endl;
    cout << "--------------------------------------------------" << endl;
}

/*__________________________________________________________________*/

void repRetail() {
    char date[20];
    getDate(date);
    cout << "[ Date: " << date << " ]" << endl;

    double total = 0.0;
    BookData b;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (!readRecord(i, b)) break;
        if (!b.isEmpty()) {
            bookinfo(b, RETAIL);
            cout << "--------------------------------------------------" << endl;
            total += b.getRetail() * b.getQty();
        }
    }
    cout << "[ Total Retail Value: $" << fixed << setprecision(2) << total << " ]" << endl;
    cout << "List Complete!! Returning to Reports..." << endl;
    cout << "--------------------------------------------------" << endl;
}

/*__________________________________________________________________*/

void repQty() {
    char date[20];
    getDate(date);
    cout << "[ Date: " << date << " ]" << endl;

    BookData arr[MAX_BOOKS];
    int size = loadAllRecords(arr, MAX_BOOKS);

    // Selection sort descending by qtyOnHand
    for (int i = 0; i < size - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j].getQty() > arr[maxIdx].getQty()) maxIdx = j;
        swap(arr[i], arr[maxIdx]);
    }

    for (int i = 0; i < size; i++) {
        bookinfo(arr[i], QTY_ONLY);
        cout << "--------------------------------------------------" << endl;
    }
    cout << "List Complete!! Returning to Reports..." << endl;
    cout << "--------------------------------------------------" << endl;
}

/*__________________________________________________________________*/

void repCost() {
    char date[20];
    getDate(date);
    cout << "[ Date: " << date << " ]" << endl;

    BookData arr[MAX_BOOKS];
    int size = loadAllRecords(arr, MAX_BOOKS);

    // Selection sort descending by retail price
    for (int i = 0; i < size - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j].getRetail() > arr[maxIdx].getRetail()) maxIdx = j;
        swap(arr[i], arr[maxIdx]);
    }

    for (int i = 0; i < size; i++) {
        bookinfo(arr[i], WHOLESALE);
        cout << "--------------------------------------------------" << endl;
    }
    cout << "List Complete!! Returning to Reports..." << endl;
    cout << "--------------------------------------------------" << endl;
}

/*__________________________________________________________________*/

void repAge() {
    char date[20];
    getDate(date);
    cout << "[ Date: " << date << " ]" << endl;

    BookData arr[MAX_BOOKS];
    int size = loadAllRecords(arr, MAX_BOOKS);

    // Selection sort ascending by dateAdded string
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++)
            if (strcmp(arr[j].getDateAdded(), arr[minIdx].getDateAdded()) < 0) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }

    for (int i = 0; i < size; i++) {
        bookinfo(arr[i], AGE);
        cout << "--------------------------------------------------" << endl;
    }
    cout << "List Complete!! Returning to Reports..." << endl;
    cout << "--------------------------------------------------" << endl;
}
