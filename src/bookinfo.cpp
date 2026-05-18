//
//  bookinfo.cpp
//  BooksellersSD — Part 16
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 16: Exceptions, Templates, and the STL
//

#include "serendipity.h"

void strUpper(char* str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (islower(str[i])) str[i] = toupper(str[i]);
}

// BookData mutators
void BookData::setTitle (const char* str){ strncpy(bookTitle,  str, 51); }
void BookData::setISBN  (const char* str){ strncpy(isbn,       str, 14); }
void BookData::setAuthor(const char* str){ strncpy(author,     str, 31); }
void BookData::setPub   (const char* str){ strncpy(publisher,  str, 31); }

// BookData accessors
const char* BookData::getTitle()  const { return bookTitle;  }
const char* BookData::getISBN()   const { return isbn;       }
const char* BookData::getAuthor() const { return author;     }
const char* BookData::getPub()    const { return publisher;  }

bool BookData::bookMatch(const char* searchStr) const {
    return strstr(bookTitle, searchStr) != nullptr;
}

// InventoryBook mutators
void InventoryBook::setDateAdded(const char* str){ strncpy(dateAdded, str, 11); }
void InventoryBook::setQty      (int qty)        { qtyOnHand = qty;             }
void InventoryBook::setWholesale(double val)     { wholesale = val;             }
void InventoryBook::setRetail   (double val)     { retail    = val;             }

// InventoryBook accessors
const char* InventoryBook::getDateAdded() const { return dateAdded;  }
int         InventoryBook::getQty()       const { return qtyOnHand;  }
double      InventoryBook::getWholesale() const { return wholesale;  }
double      InventoryBook::getRetail()    const { return retail;     }

int InventoryBook::isEmpty() const {
    return getTitle()[0] == '\0' ? 1 : 0;
}

void InventoryBook::removeBook() {
    memset(this, 0, sizeof(InventoryBook));
}

// SoldBook static member initialization
double SoldBook::taxRate = 0.06;
double SoldBook::total   = 0.0;

// SoldBook mutators
void SoldBook::setQtySold(int qty) { qtySold = qty; }

void SoldBook::calcTax() {
    tax = qtySold * getRetail() * taxRate;
}

void SoldBook::calcSubtotal() {
    subtotal = getRetail() * qtySold + tax;
    total += subtotal;
}

// SoldBook accessors
int    SoldBook::getQtySold()  const { return qtySold;  }
double SoldBook::getTax()      const { return tax;      }
double SoldBook::getSubtotal() const { return subtotal; }

// SoldBook static accessors / mutators
void   SoldBook::setTaxRate(double rate) { taxRate = rate; }
double SoldBook::getTaxRate()            { return taxRate;  }
double SoldBook::getTotal()              { return total;    }
void   SoldBook::resetTotal()            { total = 0.0;    }

// InventoryFile implementation
InventoryFile::InventoryFile(const char* fname) : filename(fname) {}

InventoryFile::~InventoryFile() {
    if (file.is_open()) file.close();
}

bool InventoryFile::open() {
    file.open(filename, ios::in | ios::out | ios::binary);
    if (!file) {
        file.open(filename, ios::out | ios::binary);
        if (!file) return false;
        InventoryBook empty = {};
        for (int i = 0; i < MAX_BOOKS; i++)
            file.write(reinterpret_cast<char*>(&empty), sizeof(InventoryBook));
        file.close();
        file.open(filename, ios::in | ios::out | ios::binary);
        if (!file) return false;
    }
    return true;
}

void InventoryFile::close() { file.close(); }

bool InventoryFile::isOpen() const { return file.is_open(); }

streampos InventoryFile::recordOffset(int slot) {
    return slot * sizeof(InventoryBook);
}

bool InventoryFile::readRecord(int slot, InventoryBook& b) {
    file.clear();
    file.seekg(recordOffset(slot));
    return static_cast<bool>(file.read(reinterpret_cast<char*>(&b), sizeof(InventoryBook)));
}

void InventoryFile::writeRecord(int slot, const InventoryBook& b) {
    file.clear();
    file.seekp(recordOffset(slot));
    file.write(reinterpret_cast<const char*>(&b), sizeof(InventoryBook));
    file.flush();
}

int InventoryFile::getBookCount() {
    int count = 0;
    InventoryBook b;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (readRecord(i, b) && !b.isEmpty())
            count++;
    }
    return count;
}

// InputValidator implementation
int InputValidator::getInt(const char* prompt, int min, int max) {
    int val = min - 1;
    cout << prompt;
    while (!(cin >> val) || val < min || val > max) {
        cout << "Please enter a number in the range "
             << min << "-" << max << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return val;
}

double InputValidator::getDouble(const char* prompt) {
    double val;
    cout << prompt;
    while (!(cin >> val)) {
        cout << "Invalid input. " << prompt;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return val;
}

void InputValidator::getString(const char* prompt, char* buf, int maxLen) {
    cout << prompt;
    cin.getline(buf, maxLen);
}

int bookinfo(const InventoryBook& b, BookInfoMode mode) {
    cout << fixed << setprecision(2);

    cout << setw(30) << "Serendipidty Booksellers\n";
    cout << setw(30) << "   Book Information\n";
    cout << endl;
    cout << left << setw(30) << "ISBN:"   << b.getISBN()   << endl;
    cout << left << setw(30) << "Title: " << b.getTitle()  << endl;

    if (mode == FULL) {
        cout << left << setw(30) << "Author: "     << b.getAuthor()    << endl;
        cout << left << setw(30) << "Publisher: "  << b.getPub()       << endl;
        cout << left << setw(30) << "Date Added: " << b.getDateAdded() << endl;
        cout << left << setw(30) << "Qty-On-Hand: "<< b.getQty()       << endl;
        cout << left << setw(30) << "Wholesale: $" << b.getWholesale() << endl;
        cout << left << setw(30) << "Retail: $"    << b.getRetail()    << endl;
    }
    else if (mode == WHOLESALE) {
        cout << left << setw(30) << "Qty-On-Hand: "<< b.getQty()       << endl;
        cout << left << setw(30) << "Wholesale: $" << b.getWholesale() << endl;
    }
    else if (mode == RETAIL) {
        cout << left << setw(30) << "Qty-On-Hand: "<< b.getQty()       << endl;
        cout << left << setw(30) << "Retail: $"    << b.getRetail()    << endl;
    }
    else if (mode == QTY_ONLY) {
        cout << left << setw(30) << "Qty-On-Hand: "<< b.getQty()       << endl;
    }
    else if (mode == AGE) {
        cout << left << setw(30) << "Date Added: " << b.getDateAdded() << endl;
        cout << left << setw(30) << "Qty-On-Hand: "<< b.getQty()       << endl;
    }

    cout << endl;
    return 0;
}
