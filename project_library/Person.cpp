#include "Person.h"
#include <iostream>

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

Date  Librarian::issueBook() {
        std::cout << "Librarian issuing a book..." << std::endl;
        // Create a Date object, which will set the current date in the constructor
        Date currentDate;
        std::cout << "Current Date: " << currentDate.getDay() << '-' << currentDate.getMonth() << '-' << currentDate.getYear() << std::endl;
        // Return the current date
        return currentDate;
    }


void Librarian::setSalary(double newSalary) {
    if (newSalary >= 0) {
        salary = newSalary;
    } else {
        std::cout << "Invalid input. Salary must be a non-negative number." << std::endl;
    }
}

void Librarian::addMember() {
    std::cout << "New Library member: " << std::endl;
    getName();
    getAddress();
    getEmail();

    // Generate random 4-digit number and convert it to a string
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int random4DigitNumber = std::rand() % 9000 + 1000;
    std::string memberId = std::to_string(random4DigitNumber);

    std::ofstream outputFile("Member_info.csv", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << name << "," << address << "," << email << "," << memberId << "\n";
        outputFile.close();
        std::cout << "Information saved to Member_info.csv" << std::endl;

        // Display member information after saving
        std::ifstream inputFile("Member_info.csv");
        if (inputFile.is_open()) {
            std::string line;
            std::string lastLine;
            while (std::getline(inputFile, line)) {
                lastLine = line;
            }
            if (!lastLine.empty()) {
                std::istringstream iss(lastLine);
                std::string value;
                std::cout << "New Member Information:\n";
                std::cout << "Name: ";
                std::getline(std::getline(iss, value, ','), name);
                std::cout << "Address: ";
                std::getline(iss, value, ',');
                std::cout << value << std::endl;
                std::cout << "Email: ";
                std::getline(iss, value, ',');
                std::cout << value << std::endl;
                std::cout << "MemberID: ";
                std::getline(iss, memberId, ',');
                std::cout << memberId << std::endl;
            } else {
                std::cerr << "No member information found." << std::endl;
            }
            inputFile.close();
        } else {
            std::cerr << "Unable to open the CSV file for reading." << std::endl;
        }
    } else {
        std::cerr << "Unable to open the CSV file for writing." << std::endl;
    }
}


//std::string Member::getMemberID() const {}



Date::Date() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    day = now->tm_mday;
    month = now->tm_mon + 1;  // tm_mon is 0-based
    year = now->tm_year + 1900;  // tm_year is years since 1900
}

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

std::string Date::getFormattedDueDate() const {
    // Format the date as a string (e.g., "DD-MM-YYYY")
    return std::to_string(day) + '-' + std::to_string(month) + '-' + std::to_string(year);
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
