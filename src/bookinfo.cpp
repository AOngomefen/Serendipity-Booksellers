//
//  bookinfo.cpp
//  BooksellersSD — Part 12
//
//  Created by Andrea 👾 on 3/8/26.
//  Modified for Chapter 12: File-based inventory
//

#include "serendipity.h"

void strUpper(char* str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (islower(str[i])) str[i] = toupper(str[i]);
}

void setTitle    (char* str,  BookData& b){ strncpy(b.bookTitle, str, 51); }
void setISBN     (char* str,  BookData& b){ strncpy(b.isbn,      str, 14); }
void setAuthor   (char* str,  BookData& b){ strncpy(b.author,    str, 31); }
void setPub      (char* str,  BookData& b){ strncpy(b.publisher, str, 31); }
void setDateAdded(char* str,  BookData& b){ strncpy(b.dateAdded, str, 11); }
void setQty      (int qty,    BookData& b){ b.qtyOnHand = qty;              }
void setWholesale(double val, BookData& b){ b.wholesale = val;              }
void setRetail   (double val, BookData& b){ b.retail    = val;              }

int isEmpty(const BookData& b) {
    return b.bookTitle[0] == '\0' ? 1 : 0;
}


void removeBook(BookData& b) {
    memset(&b, 0, sizeof(BookData));
}

int bookinfo(const BookData& b, BookInfoMode mode) {
    cout << fixed << setprecision(2);

    cout << setw(30) << "Serendipidty Booksellers\n";
    cout << setw(30) << "   Book Information\n";
    cout << endl;
    cout << left << setw(30) << "ISBN:"   << b.isbn      << endl;
    cout << left << setw(30) << "Title: " << b.bookTitle << endl;

    if (mode == FULL) {
        cout << left << setw(30) << "Author: "     << b.author    << endl;
        cout << left << setw(30) << "Publisher: "  << b.publisher << endl;
        cout << left << setw(30) << "Date Added: " << b.dateAdded << endl;
        cout << left << setw(30) << "Qty-On-Hand: "<< b.qtyOnHand << endl;
        cout << left << setw(30) << "Wholesale: $" << b.wholesale << endl;
        cout << left << setw(30) << "Retail: $"    << b.retail    << endl;
    }
    else if (mode == WHOLESALE) {
        cout << left << setw(30) << "Qty-On-Hand: "<< b.qtyOnHand << endl;
        cout << left << setw(30) << "Wholesale: $" << b.wholesale << endl;
    }
    else if (mode == RETAIL) {
        cout << left << setw(30) << "Qty-On-Hand: "<< b.qtyOnHand << endl;
        cout << left << setw(30) << "Retail: $"    << b.retail    << endl;
    }
    else if (mode == QTY_ONLY) {
        cout << left << setw(30) << "Qty-On-Hand: "<< b.qtyOnHand << endl;
    }
    else if (mode == AGE) {
        cout << left << setw(30) << "Date Added: " << b.dateAdded << endl;
        cout << left << setw(30) << "Qty-On-Hand: "<< b.qtyOnHand << endl;
    }

    cout << endl;
    return 0;
}
