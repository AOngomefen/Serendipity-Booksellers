//
//  serendipity.h
//  BooksellersSD — Part 16
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 16: Exceptions, Templates, and the STL
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
#include <stdexcept>
#include <new>

using namespace std;

// Base class — general data about a book
class BookData {
private:
    char bookTitle[51];
    char isbn[14];
    char author[31];
    char publisher[31];

public:
    // Mutators
    void setTitle (const char* str);
    void setISBN  (const char* str);
    void setAuthor(const char* str);
    void setPub   (const char* str);

    // Accessors
    const char* getTitle()  const;
    const char* getISBN()   const;
    const char* getAuthor() const;
    const char* getPub()    const;

    // Utility
    bool bookMatch(const char* searchStr) const;
};

// Derived class — inventory-specific data
class InventoryBook : public BookData {
private:
    char   dateAdded[11];
    int    qtyOnHand;
    double wholesale;
    double retail;

public:
    // Mutators
    void setDateAdded(const char* str);
    void setQty      (int qty);
    void setWholesale(double val);
    void setRetail   (double val);

    // Accessors
    const char* getDateAdded() const;
    int         getQty()       const;
    double      getWholesale() const;
    double      getRetail()    const;

    // Utility
    int  isEmpty()   const;
    void removeBook();
};

// Derived from InventoryBook — represents a sold book in a transaction
class SoldBook : public InventoryBook {
private:
    static double taxRate;
    static double total;
    int    qtySold;
    double tax;
    double subtotal;

public:
    // Mutators
    void setQtySold(int qty);
    void calcTax();
    void calcSubtotal();

    // Accessors
    int    getQtySold()  const;
    double getTax()      const;
    double getSubtotal() const;

    // Static accessors / mutators
    static void   setTaxRate(double rate);
    static double getTaxRate();
    static double getTotal();
    static void   resetTotal();
};

const  int     MAX_BOOKS      = 20;

void strUpper(char* str);

class InventoryFile {
private:
    fstream file;
    const char* filename;

public:
    InventoryFile(const char* fname);
    ~InventoryFile();

    bool open();
    void close();
    bool isOpen() const;

    bool readRecord (int slot, InventoryBook& b);
    void writeRecord(int slot, const InventoryBook& b);
    int  getBookCount();

    static streampos recordOffset(int slot);
};

extern InventoryFile invDB;

class InputValidator {
public:
    static int  getInt(const char* prompt, int min, int max);
    static double getDouble(const char* prompt);
    static void getString(const char* prompt, char* buf, int maxLen);
};

int mainmenu();
int invmenu();
int cashier();
int reports();

enum BookInfoMode { FULL, WHOLESALE, RETAIL, QTY_ONLY, AGE };
int bookinfo(const InventoryBook& b, BookInfoMode mode = FULL);

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
