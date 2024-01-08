#include "Person.h"
#include <iostream>
#include <limits> 
#include <regex> 
#include <sstream>
#include <fstream>


void Person::getName() {
    std::cout << "Enter name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    while (!isValidString(name)) {
        std::cout << "Invalid name format. Please enter a valid name: ";
        std::getline(std::cin, name);
    }
}

void Person::getAddress() {
    std::cout << "Enter address: ";
    std::getline(std::cin >> std::ws, address);
    while (!isValidString(address)) {
        std::cout << "Invalid address format. Please enter a valid address: ";
        std::getline(std::cin >> std::ws, address);
    }
}

void Person::getEmail() {
    std::cout << "Enter email: ";
    while (true) {
        std::cin >> email;
        if (isValidEmail(email)) {
             break;
        } else {
            std::cout << "Invalid email format. Please enter a valid gmail email: ";
        }
    }
}

bool Person::isValidString(const std::string& str) {
    // Basic check for only alphanumeric characters and spaces
    return std::all_of(str.begin(), str.end(), [](char c) {
        return std::isalnum(c) ;
    });
}

bool Person::isValidEmail(const std::string& email) {
    const std::regex gmailPattern(R"([a-zA-Z0-9._%+-]+@gmail\.com)");
    return std::regex_match(email, gmailPattern);
    return true;
}


void Librarian::getStaffID() {
    while (true) {
        std::cout << "Enter staff ID: ";
        std::cin >> staffID;

        if (std::cin.fail() || staffID <= 0) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a positive integer for staff ID." << std::endl;
        } else if (checkStaffID("staff_info.csv", staffID)) {
            std::cout << "Staff ID already exists. Please enter a different staff ID." << std::endl;
        } else {
            break; // Valid and unique staff ID
        }
    }
}

void Librarian::setStaffID(int newStaffID) {
    if (newStaffID > 0) {
        staffID = newStaffID;
    } else {
        std::cout << "Invalid input. Staff ID must be a positive integer." << std::endl;
    }
}

void Librarian::getSalary() {
    while (true) {
        std::cout << "Enter salary: ";
        std::cin >> salary;

        if (std::cin.fail() || salary < 0) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a non-negative number for salary." << std::endl;
        } else {
            break; // Valid salary
        }
    }
}

//void Librarian::issueBook(int memberID, int bookID){}

void Librarian::setSalary(double newSalary) {
    if (newSalary >= 0) {
        salary = newSalary;
    } else {
        std::cout << "Invalid input. Salary must be a non-negative number." << std::endl;
    }
}

void Person::displayMemberInfo() {
    std::ifstream inputFile("Member_info.csv");
    if (inputFile.is_open()) {
        std::string line;
        std::string lastLine;
        while (std::getline(inputFile, line)) {
            lastLine = line;
        }
        if (!lastLine.empty()) {
            std::istringstream iss(lastLine);
            std::string name, address, email, memberID;

            // Assuming the format is: name,address,email,memberID
            std::getline(iss, name, ',');
            std::getline(iss, address, ',');
            std::getline(iss, email, ',');
            std::getline(iss, memberID, ',');

            std::cout << "New Member Information:\n"
                      << "Name: " << name << "\n"
                      << "Address: " << address << "\n"
                      << "Email: " << email << "\n"
                      << "MemberID: " << memberID << std::endl;
        } else {
            std::cerr << "No member information found." << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open the CSV file for reading." << std::endl;
    }
}



void Librarian::addMember() {
    std::cout << "New Library member: " << std::endl;
    getName();
    getAddress();
    getEmail();

    Member member; // Create an instance of Member
    std::string memberId = member.getMemberID();

    std::ofstream outputFile("Member_info.csv", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << name << "," << address << "," << email << "," << memberId << "\n";
        outputFile.close();
        std::cout << "Information saved to Member_info.csv" << std::endl;

        // Display member information after saving
        displayMemberInfo();
    } else {
        std::cerr << "Unable to open the CSV file for writing." << std::endl;
    }
}



std::string Member::getMemberID() const {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // Generate a random 4-digit number
    int random4DigitNumber = std::rand() % 9000 + 1000;
    // Convert the random number to a string and return it as the member ID
    return std::to_string(random4DigitNumber);
}



bool checkStaffID(const std::string& filename, int staffID) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            int existingStaffID;
            std::istringstream iss(line);
            iss >> existingStaffID;
            if (existingStaffID == staffID) {
                inputFile.close();
                return true; // Staff ID found
            }
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open the CSV file for reading." << std::endl;
    }
    return false; // Staff ID not found
}



