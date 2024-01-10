#include "Book.h"
#include "Person.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>

// Constructors
Book::Book() : bookID(0), pageCount(0) {}

Book::Book(int id, const std::string& name, int count, const std::string& firstName, const std::string& lastName, const std::string& type)
    : bookID(id), bookName(name), pageCount(count), authorFirstName(firstName), authorLastName(lastName), bookType(type) {}

Book parseCSVLine(const std::string& csvLine);
void displayBookInfo(const Book& book);

std::string Book::getBookID() const {
    int requestedBookID;
    bool flag = true;
    bool book_exists = false;
    std::string foundBookDetails;  // Variable to store the details of the found book

    // Prompt the user for a book ID until a valid one is entered
    while (flag) {
        std::cout << "Enter the Book ID: ";
        std::cin >> requestedBookID;

        // Check if the book with the requested ID exists in the library_books.csv file
        std::ifstream inputFile("library_books.csv");
        if (!inputFile.is_open()) {
            std::cerr << "Unable to open the CSV file: library_books.csv" << std::endl;
            return ""; // Return an empty string to indicate an error
        }

        std::string csvLine;
        std::getline(inputFile, csvLine);  // Read and discard the header line if needed

        while (std::getline(inputFile, csvLine)) {
            // Find the position of the first comma in the line
            size_t pos = csvLine.find(',');

            // Extract the Book ID from the line (substring from the start to the first comma)
            std::string bookIDStr = csvLine.substr(0, pos);

            // Convert the extracted Book ID to an integer
            int bookID = std::stoi(bookIDStr);

            if (bookID == requestedBookID) {
                // Book found, display the entire line
                std::cout << "Book with ID " << requestedBookID << " found. Details:" << std::endl;
                std::cout << csvLine << std::endl;
                book_exists = true;

                // Ask the librarian if they are sure about this book
                char confirmation;
                std::cout << "Is this the correct book? (enter Y/y for yes): ";
                std::cin >> confirmation;

                if (confirmation == 'Y' || confirmation == 'y') {
                    // Save the details only if confirmation is 'Y' or 'y'
                    foundBookDetails = csvLine;
                    inputFile.close();
                    flag = false;
                    return foundBookDetails;
                } else {
                    std::cout << "Please choose again." << std::endl;
                    break;
                }
            }
        }

        // Book not found, inform the user and prompt for a new Book ID
        if (!book_exists) {
            std::cout << "Book with ID " << requestedBookID << " not found. Please enter a valid Book ID." << std::endl;
            inputFile.close();
        }
    }

    // Return an empty string to indicate that the function has finished without finding a book
    return "";
}

Book parseCSVLine(const std::string& csvLine) {
    std::istringstream iss(csvLine);
    std::string token;

    // Read Book ID
    std::getline(iss, token, ',');
    int bookID = std::stoi(token);

    // Read other fields
    std::string name, firstName, lastName, type;
    int count;

    // Read Book Name
    std::getline(iss, name, ',');

    // Read Page Count
    std::getline(iss, token, ',');
    count = std::stoi(token);

    // Read Author First Name
    std::getline(iss, firstName, ',');

    // Read Author Last Name
    std::getline(iss, lastName, ',');

    // Read Book Type
    std::getline(iss, type, ',');

    // Return a Book object with the extracted information
    return Book(bookID, name, count, firstName, lastName, type);
}


int Book::getPageCount() const {return pageCount;}
const std::string& Book::getBookName() const { return bookName; }
const std::string& Book::getAuthorFirstName() const { return authorFirstName; }
const std::string& Book::getAuthorLastName() const { return authorLastName; }
const std::string& Book::getBookType() const { return bookType; }


std::string Book::setDueDate() const {
   Date dueDate;
    
    // Format the due date as a string
    return dueDate.getFormattedDueDate();
    }

// Function to read books from a CSV line
Book Book::readBookFromCSV(const std::string& csvLine) {
    std::istringstream iss(csvLine);
    std::string token;

    // Read each field from the CSV line
    int id, count;
    std::string name, firstName, lastName, type;

    // Read Book ID
    std::getline(iss, token, ',');
    id = std::stoi(token);

    // Read Book Name
    std::getline(iss, name, ',');

    // Read Page Count
    std::getline(iss, token, ',');
    count = std::stoi(token);

    // Read Author First Name
    std::getline(iss, firstName, ',');

    // Read Author Last Name
    std::getline(iss, lastName, ',');

    // Read Book Type
    std::getline(iss, type, ',');

    // Return a Book object with the extracted information
    return Book(id, name, count, firstName, lastName, type);
}
