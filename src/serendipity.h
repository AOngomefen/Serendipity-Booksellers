//
//  serendipity.h
//  BooksellersSD — Part 12
//
//  Created by Andrea 👾 on 3/8/26.
//  Modified for Chapter 12: File-based inventory
//

#ifndef serendipity_h
#define serendipity_h

#include <iostream>
#include <iomanip>
#include <string>
#include <format>
#include <limits>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

struct BookData {
    char   bookTitle[51];
    char   isbn[14];
    char   author[31];
    char   publisher[31];
    char   dateAdded[11];
    int    qtyOnHand;
    double wholesale;
    double retail;
};

extern fstream invFile;
const  char    INV_FILENAME[] = "inventory.dat";
const  int     MAX_BOOKS      = 20;

void setTitle    (char* str,  BookData& b);
void setISBN     (char* str,  BookData& b);
void setAuthor   (char* str,  BookData& b);
void setPub      (char* str,  BookData& b);
void setDateAdded(char* str,  BookData& b);
void setQty      (int qty,    BookData& b);
void setWholesale(double val, BookData& b);
void setRetail   (double val, BookData& b);
int  isEmpty     (const BookData& b);   // 1 = empty slot
void removeBook  (BookData& b);         // zeroes the struct

void strUpper(char* str);


inline streampos recordOffset(int slot){ return slot * sizeof(BookData); }

bool readRecord (int slot, BookData& b);

// Write b to the file at the given slot.
void writeRecord(int slot, const BookData& b);

int  getBookCount();

int mainmenu();
int invmenu();
int cashier();
int reports();

enum BookInfoMode { FULL, WHOLESALE, RETAIL, QTY_ONLY, AGE };
int bookinfo(const BookData& b, BookInfoMode mode = FULL);

void lookUpBook();
void addBook();
void editBook();
void deleteBook();

void repListing();
void repWholesale();
void repRetail();
void repQty();
void repCost();
void repAge();

#endif /* serendipity_h */
