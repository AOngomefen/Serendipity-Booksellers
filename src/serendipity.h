//
//  serendipity.h
//  BooksellersSD — Part 13
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 13: BookData class with private members
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

class BookData {
private:
    char   bookTitle[51];
    char   isbn[14];
    char   author[31];
    char   publisher[31];
    char   dateAdded[11];
    int    qtyOnHand;
    double wholesale;
    double retail;

public:
    // Mutators
    void setTitle    (const char* str);
    void setISBN     (const char* str);
    void setAuthor   (const char* str);
    void setPub      (const char* str);
    void setDateAdded(const char* str);
    void setQty      (int qty);
    void setWholesale(double val);
    void setRetail   (double val);

    // Accessors
    const char* getTitle()     const;
    const char* getISBN()      const;
    const char* getAuthor()    const;
    const char* getPub()       const;
    const char* getDateAdded() const;
    int         getQty()       const;
    double      getWholesale() const;
    double      getRetail()    const;

    // Utility
    int  isEmpty()   const;
    void removeBook();
};

extern fstream invFile;
const  char    INV_FILENAME[] = "inventory.dat";
const  int     MAX_BOOKS      = 20;

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
