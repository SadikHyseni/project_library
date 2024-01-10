#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    int bookID;
    std::string bookName;
    int pageCount;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    std::string dueDate;

public:
    Book();
     Book(int id, const std::string& name, int count, const std::string& firstName, const std::string& lastName, const std::string& type);
    // Getter functions
  

    std::string getBookID() const; 
    const std::string& getBookName() const;
    int getPageCount() const;
    const std::string& getAuthorFirstName() const;
    const std::string& getAuthorLastName() const;
    const std::string& getBookType() const;;
    // Function to read books from a CSV line
    static Book readBookFromCSV(const std::string& csvLine);
    std::string setDueDate() const;
};

#endif // BOOK_H
