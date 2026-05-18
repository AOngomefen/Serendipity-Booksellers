//
//  main.cpp
//  BooksellersSD — Part 13
//
//  Created by Andrea on 3/8/26.
//  Modified for Chapter 13: BookData class with private members
//

#include "serendipity.h"

fstream invFile;

int main() {
    invFile.open(INV_FILENAME, ios::in | ios::out | ios::binary);

    if (!invFile) {
        invFile.open(INV_FILENAME, ios::out | ios::binary);
        if (!invFile) {
            cerr << "ERROR: Could not create inventory file." << endl;
            return 1;
        }
        BookData empty = {};
        for (int i = 0; i < MAX_BOOKS; i++)
            invFile.write(reinterpret_cast<char*>(&empty), sizeof(BookData));
        invFile.close();

        invFile.open(INV_FILENAME, ios::in | ios::out | ios::binary);
        if (!invFile) {
            cerr << "ERROR: Could not open inventory file." << endl;
            return 1;
        }
    }

    mainmenu();

    invFile.close();
    return 0;
}

bool readRecord(int slot, BookData& b) {
    invFile.clear();
    invFile.seekg(recordOffset(slot));
    return static_cast<bool>(invFile.read(reinterpret_cast<char*>(&b), sizeof(BookData)));
}

void writeRecord(int slot, const BookData& b) {
    invFile.clear();
    invFile.seekp(recordOffset(slot));
    invFile.write(reinterpret_cast<const char*>(&b), sizeof(BookData));
    invFile.flush();
}

int getBookCount() {
    int count = 0;
    BookData b;
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (readRecord(i, b) && !b.isEmpty())
            count++;
    }
    return count;
}
