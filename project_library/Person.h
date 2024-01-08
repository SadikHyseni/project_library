#pragma once
#include <string>

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
    void displayMemberInfo();

    bool isValidString(const std::string& str);
    bool isValidEmail(const std::string& email);
};

class Member : public Person {
  private:
    std::string memberID; // Declare memberID as a private member variable

public:
    std::string getMemberID() const;
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
};

bool checkStaffID(const std::string& filename, int staffID);

