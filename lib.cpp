#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Structure to represent a book
struct Book {
    string title;
    string author;
    bool available;
};

// Function to add a new book to the library
void addBook(vector<Book> &library) {
    Book newBook;
    cout << "Enter title: ";
    getline(cin, newBook.title);
    cout << "Enter author: ";
    getline(cin, newBook.author);
    newBook.available = true;
    library.push_back(newBook);
}

// Function to search for a book in the library
void searchBook(const vector<Book> &library, const string &title) {
    bool found = false;
    for (const auto &book : library) {
        if (book.title == title) {
            found = true;
            cout << "Book found!" << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Availability: " << (book.available ? "Available" : "Not Available") << endl;
            break;
        }
    }
    if (!found) {
        cout << "Book not found." << endl;
    }
}

// Function to save library data to a file
void saveLibrary(const vector<Book> &library, const string &filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto &book : library) {
            file << book.title << "," << book.author << "," << book.available << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

// Function to load library data from a file
void loadLibrary(vector<Book> &library, const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            Book book;
            size_t pos = line.find(',');
            book.title = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(',');
            book.author = line.substr(0, pos);
            line.erase(0, pos + 1);
            book.available = (line == "1" ? true : false);
            library.push_back(book);
        }
        file.close();
    } else {
        cout << "Unable to open file for reading." << endl;
    }
}

int main() {
    vector<Book> library;
    string filename = "library.txt";

    // Load library data from file
    loadLibrary(library, filename);

    int choice;
    do {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Search Book" << endl;
        cout << "3. Save Library" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character in input buffer

        switch (choice) {
            case 1:
                addBook(library);
                break;
            case 2: {
                string title;
                cout << "Enter title to search: ";
                getline(cin, title);
                searchBook(library, title);
                break;
            }
            case 3:
                saveLibrary(library, filename);
                cout << "Library data saved to " << filename << endl;
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
