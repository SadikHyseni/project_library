#pragma once
#include <string>
#include <ctime>
#include <limits> 
#include <regex> 
#include <sstream>
#include <fstream>
#include "Book.h"

class Person {
public:
    std::string name;
    std::string address;
    std::string email;

    void getName();
    void getAddress();
    void getEmail();
    void setName(const std::string& newName);
    void setAddress(const std::string& newAddress);
    void setEmail(const std::string& newEmail);

    bool isValidString(const std::string& str);
    bool isValidEmail(const std::string& email);
};



class Member : public Person {
private:
    std::string memberID;
    std::vector<Book> booksLoaned;

public:
    Member(const std::string& memberID, const std::string& name, const std::string& address, const std::string& email);
  
    const std::string getMemberID() const;
  //  const std::vector<Book>& getBooksBorrowed() const;
    // Function to add a book to the list of books loaned by the member
  // void setBooksBorrowed(const Book& book);
};


class Date {
public:
    Date();
    Date(int day, int month, int year);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
  std::string getFormattedDueDate() const;

private:
    int day;
    int month;
    int year;
};

class Librarian : public Person {
public:
    int staffID;
    double salary;

    void getStaffID();
    void setStaffID(int newStaffID);
    void getSalary();
    void setSalary(double newSalary);
    void addMember();
    Date issueBook();
   
  
};

bool checkStaffID(const std::string& filename, int staffID);



