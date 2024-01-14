#ifndef BOOK_H
#define BOOK_H

#include <string>

//book class
class Book {
private:
  //private data for books details
    int bookID;
    std::string bookName;
    int pageCount;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    std::string dueDate;

public:
  //constructors 
    Book();
     Book(int id, const std::string& name, int count, const std::string& firstName, const std::string& lastName, const std::string& type);
    // Getter functions
  

  //functions to retrieve for book details
    std::string getBookID() const; 
    const std::string& getBookName() const;
    int getPageCount() const;
    const std::string& getAuthorFirstName() const;
    const std::string& getAuthorLastName() const;
    const std::string& getBookType() const;
    // Function to read books from a CSV line
    static Book readBookFromCSV(const std::string& csvLine);
    std::string setDueDate() const;
};

#endif // BOOK_H
