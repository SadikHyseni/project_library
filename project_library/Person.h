#pragma once
#include <string>
// ctime and chrono are used for time
#include <ctime>
#include <chrono>
//cmath used for math expressions
#include <cmath>
//iomanip is used for fromating inputs and outputs
#include <iomanip>
#include <limits> 
#include <regex> 
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Book.h"


//the person represents a generic person class with name,address, and email
class Person {
public:
    std::string name;
    std::string address;
    std::string email;

  //functions to ger and set name , address and email
    void getName();
    void getAddress();
    void getEmail();
    void setName(const std::string& newName);
    void setAddress(const std::string& newAddress);
    void setEmail(const std::string& newEmail);

  //validation functions for checking if a string is valid or if an email is valid 
    bool isValidString(const std::string& str);
    bool isValidEmail(const std::string& email);
};



//the Member class repsents a library member inheriting from the Person class
class Member : public Person {
private:
    std::string memberID;
    std::vector<Book> booksLoaned;

public:
  //Constuctor for initializzing a member with a member ID ,name,address and email
    Member(const std::string& memberID, const std::string& name, const std::string& address, const std::string& email);

  //function to retieve member id
    const std::string getMemberID() const;
};

//the date class represents a date with day,month, and year components
class Date {
public:
  //constuctors for creating Date objects eith difault values or specfied values
    Date();
    Date(int day, int month, int year);
  //functions to retrieve day,month,year and formatted due date string
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    std::string getFormattedDueDate() const;

private:
    int day;
    int month;
    int year;
};


//the librarian class represents a Librarian ,inheriting from the Person class
class Librarian : public Person {
public:
  //properties fro the librarian
    int staffID;
    double salary;

  //fucntions related to library operations 
    void returnBook(int memberID, int bookID);
    void getStaffID();
    void setStaffID(int newStaffID);
    void getSalary();
    void setSalary(double newSalary);
    void addMember();
    void displayBorrowedBooks(int memberID);
    void calcFine(int memberID);
    Date issueBook();  
};

bool checkStaffID(const std::string& filename, int staffID);
