#include "Person.h"
#include <iostream>
#include <vector>

//function to get the name of the person
void Person::getName() {
    std::cout << "Enter name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    while (!isValidString(name)) {
        std::cout << "Invalid name format. Please enter a valid name: ";
        std::getline(std::cin, name);
    }
}

//function to get the address of a person
void Person::getAddress() {
    std::cout << "Enter address: ";
    std::getline(std::cin >> std::ws, address);
    while (!isValidString(address)) {
        std::cout << "Invalid address format. Please enter a valid address: ";
        std::getline(std::cin >> std::ws, address);
    }
}

//function to get the email of the person
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

//validation for name ,email,address
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


//disaplyborroedbooks by memberid
void Librarian::displayBorrowedBooks(int memberID) {
    const std::string csvFilePath = "booksLoaned.csv";
    std::ifstream inputFile(csvFilePath);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << csvFilePath << std::endl;
        return;
    }

    std::cout << "Books borrowed by MemberID " << memberID << ":" << std::endl;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> row;

        // Split the line into tokens based on the comma (',') delimiter
        std::string token;
        while (std::getline(iss, token, ',')) {
            row.push_back(token);
        }

        // Check if the line contains the specified memberID
        if (row.size() >= 1) {
            int currentMemberID;
            try {
                currentMemberID = std::stoi(row[0]);
            }
            catch (const std::exception& e) {
                continue;  // Skip this line 
            }
            if (currentMemberID == memberID) {
                // Get Book ID and Book Name
                int bookID;
                try {
                    bookID = std::stoi(row[2]);  // Assuming Book ID is in the third column
                }
                catch (const std::exception& e) {
                    continue;  // Skip this line if Book ID is not a valid integer
                }

                std::string bookName = row[3];  // Assuming Book Name is in the fourth column

                std::string givendate = row[1];

                std::cout << bookName << " with book ID " << bookID << " was issued at " << givendate << std::endl;
            }
        }
    }

    inputFile.close();
}

//return book by memberid and bookid read and write to csv file
void Librarian::returnBook(int memberID, int bookID) {
    // Specify the path to your CSV file
    const std::string csvFilePath = "booksLoaned.csv";

    // Read the CSV file into a vector of vectors
    std::ifstream inputFile(csvFilePath);
    std::vector<std::vector<std::string>> csvData;

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << csvFilePath << std::endl;
        return;
    }

    try {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::vector<std::string> row;

            // Split the line into tokens based on the comma (',') delimiter
            std::string token;
            while (std::getline(iss, token, ',')) {
                row.push_back(token);
            }

            // Check if the line contains the specified memberID and bookID
            if (row.size() >= 3) {
                int currentMemberID, currentBookID;
                try {
                    currentMemberID = std::stoi(row[0]);
                    currentBookID = std::stoi(row[2]);
                } catch (const std::exception &e) {
                    std::cerr << "Exception during stoi: " << e.what() << std::endl;
                    continue;  // Skip this line if stoi fails
                }

                if (currentMemberID == memberID && currentBookID == bookID) {
                    // Book found, skip this line
                   std::cout << "Book has successfully returned." << std::endl;
                    continue;
                } else {
                    // Keep this line
                    csvData.push_back(row);
                }
            }
        }

        inputFile.close();

        // Write the modified content back to the file
        std::ofstream outputFile(csvFilePath);
        for (const auto &row : csvData) {
            for (const auto &item : row) {
                outputFile << item << ",";
            }
            outputFile << "\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return;
    }
}

//function to calculate time for overduebooks
void Librarian::calcFine(int memberID) {
    const std::string csvFilePath = "booksLoaned.csv";

    // Open the CSV file
    std::ifstream inputFile(csvFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << csvFilePath << std::endl;
        return;
    }

    // Get the current date
    auto now = std::chrono::system_clock::now();

    // Read each line from the CSV file
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> row;

        // Split the line into tokens based on the comma (',') delimiter
        std::string token;
        while (std::getline(iss, token, ',')) {
            row.push_back(token);
        }

        // Check if the line contains the specified memberID
        if (row.size() >= 2) { // Assuming issueDate is in the second column
            int currentMemberID;
            std::string issueDateString = row[1]; // Assuming issueDate is in the second column

            std::tm issueDate = {};
            std::istringstream(issueDateString) >> std::get_time(&issueDate, "%m-%d-%Y");

            if (std::istringstream(issueDateString).fail()) {
                std::cerr << "Error parsing date: " << issueDateString << std::endl;
                continue;
            }

            try {
                currentMemberID = std::stoi(row[0]);
            } catch (const std::exception& e) {
                continue;  // Skip this line if conversion to integer fails
            }

            if (currentMemberID == memberID) {
                // Calculate the duration between issueDate and currentDate
                auto issueTime = std::chrono::system_clock::from_time_t(std::mktime(&issueDate));
                auto duration = std::chrono::duration_cast<std::chrono::hours>(now - issueTime);

                // Check if it has passed 3 days from the issueDate
                if (duration.count() / 24 > 3) { // Convert hours to days
                    // Calculate the fine as a whole number of pounds
                    int fine = static_cast<int>(duration.count() / 24 - 3);
                    std::cout << "MemberID " << memberID << " owes " << fine << " pounds in fines." << std::endl;
                } else {
                    std::cout << "MemberID " << memberID << " has no fines within the initial 3 days." << std::endl;
                }
            }
        }
    }
}


//function to get staffid
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

//function to check staff id valid
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

//return date of issue book
Date Librarian::issueBook() {
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

//function to add new member and save to csv file
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

//function for current date
Date::Date() {
    auto now = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(now);
    tm* localTime = localtime(&t);

    day = localTime->tm_mday;
    month = localTime->tm_mon + 1;  // tm_mon is 0-based
    year = localTime->tm_year + 1900;  // tm_year is years since 1900
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

//validation for satff id
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




