#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Define a Book structure
struct Book {
    string title;
    string author;
    int bookID;
    bool available;

    // Constructor
    Book(string t, string a, int id, bool av) : title(t), author(a), bookID(id), available(av) {}
};

class Library {
private:
    vector<Book> books;

public:
    // Add a book to the library
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Remove a book from the library based on its ID
    void removeBook(int bookID) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->bookID == bookID) {
                books.erase(it);
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found." << endl;
    }

    // Display all books in the library
    void displayBooks() const {
        for (const auto& book : books) {
            cout << "Title: " << book.title << ", Author: " << book.author << ", Book ID: " << book.bookID << ", Available: " << (book.available ? "Yes" : "No") << endl;
        }
    }

    // Save library data to a file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& book : books) {
                file << book.title << "," << book.author << "," << book.bookID << "," << book.available << endl;
            }
            file.close();
            cout << "Library data saved to file: " << filename << endl;
        } else {
            cout << "Error: Unable to open file for writing: " << filename << endl;
        }
    }

    // Load library data from a file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            books.clear(); // Clear existing data
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string title, author, availableStr;
                int bookID;
                bool available;
                getline(ss, title, ',');
                getline(ss, author, ',');
                ss >> bookID;
                ss.ignore();
                ss >> boolalpha >> available;
                addBook(Book(title, author, bookID, available));
            }
            file.close();
            cout << "Library data loaded from file: " << filename << endl;
        } else {
            cout << "Error: Unable to open file for reading: " << filename << endl;
        }
    }
};

int main() {
    Library library;

    // Example usage
    library.addBook(Book("Harry Potter", "J.K. Rowling", 1, true));
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", 2, false));

    cout << "Books in library:" << endl;
    library.displayBooks();

    library.saveToFile("library_data.txt");

    Library newLibrary;
    newLibrary.loadFromFile("library_data.txt");

    cout << "\nBooks in newly loaded library:" << endl;
    newLibrary.displayBooks();

    return 0;
}
