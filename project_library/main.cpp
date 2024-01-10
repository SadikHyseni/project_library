#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include "Person.h"

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool doesMemberIDExist(const std::string& filename, const std::string& memberIDToCheck) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::string existingMemberID;
            std::istringstream iss(line);
            // MemberID is in the fourth column
            for (int i = 0; i < 4; ++i) {
                std::getline(iss, existingMemberID, ',');
            }
            if (existingMemberID == memberIDToCheck) {
                inputFile.close();
                return true; // MemberID found
            }
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open the CSV file for reading." << std::endl;
    }
    return false; // MemberID not found
}

// Function to check if a staff ID exists in the CSV file
bool checkStaffID(const std::string& filename, const std::string& login) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string line;
        std::getline(inputFile, line); // Read and discard the header line

        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string staffID;
            
            // the staff ID is in the fourth column 
            for (int i = 0; i < 4; ++i) {
                std::getline(iss, staffID, ',');
            }

            // Now staffID contains the value from the fourth column
            if (staffID == login) {
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

int main() {
    std::string start;

    std::cout << "Welcome to the library System" << std::endl;

    bool flag = true;
    while (flag) {
        std::cout << "Enter the Library System [e] or Register [r]: " << std::endl;
        std::cin >> start;
        if (start == "r" || start == "e") {
            flag = false;
        } else {
            std::cout << "Invalid input. Enter [e] for enter or [r] for staff register: " << std::endl;
        }
    }

    Librarian Librarian_options;
    Book Book_options;

    while (true) {
        if (start == "r") {
            std::cout << "Welcome to the new staff" << std::endl;

            const std::string filename = "staff_info.csv";

            if (!fileExists(filename)) {
                std::cerr << "Error: The CSV file does not exist or is empty." << std::endl;
                return 1;
            }

            Person newPerson;
            Librarian newLibrarian;

            newPerson.getName();
            newPerson.getAddress();
            newPerson.getEmail();
            newLibrarian.getStaffID();
            newLibrarian.getSalary();

            std::cout << "New Staff Info:" << std::endl;
            std::cout << "Name: " << newPerson.name << std::endl;
            std::cout << "Address: " << newPerson.address << std::endl;
            std::cout << "Email: " << newPerson.email << std::endl;
            std::cout << "Staff ID: " << newLibrarian.staffID << std::endl;
            std::cout << "Salary: " << newLibrarian.salary << std::endl;

            std::ofstream outputFile(filename, std::ios::app);
            if (outputFile.is_open()) {
                outputFile << newPerson.name << "," << newPerson.address << "," << newPerson.email << ","
                           << newLibrarian.staffID << "," << newLibrarian.salary << std::endl;

                outputFile.close();
                std::cout << "Thank you for your registration." << std::endl;
            } else {
                std::cerr << "Unable to open the file for writing." << std::endl;
                return 1;
            }
        }

        std::string login;
        std::string action_confirmation;
        std::string action_again;
	std::string inputMemberID;
        int option;

        std::cout << "Please enter your staff ID: " << std::endl;

        bool flag2 = true;
        bool flag3 = true;
        bool flag4 = true;
	bool exists = true;

        while (flag2) {
            std::cin >> login;
            if (checkStaffID("staff_info.csv", login)) {
                flag2 = false;
                std::cout << "Staff ID found. Logging in..." << std::endl;

                while (flag4) {
                    std::cout << "Select an option (by number):  " << std::endl
                              << "(1) Add a new Member" << std::endl
                              << "(2) Issue a book " << std::endl
                              << "(3) Return book " << std::endl
                               << "(4) Display borrowed books " << std::endl
                              << "(5) Exit terminate actions " << std::endl;

                    while (flag3) {
                        std::cin >> option;
                        if (option >= 1 && option <= 5) {
                            std::cout << "Are you sure you want to make this action? [y/n] " << std::endl;
                            while (flag3) {
                                std::cin >> action_confirmation;
                                if (action_confirmation == "y") {
                                    flag3 = false;
                                    switch (option) {
                                        case 1:
                                            Librarian_options.addMember();
                                            break;
                                        case 2:
					  while (exists) {
                                            std::cout << "Enter MemberID: ";
                                            std::cin >> inputMemberID;
                                            // Call the function to check if the MemberID exists
                                            if (doesMemberIDExist("Member_info.csv", inputMemberID)) {
                                            std::cout << "MemberID " << inputMemberID << " exists in the Member_info.csv file." << std::endl;
					    exists = false;
                                            // Additional processing for issuing a book can go here
                                            } else {
                                             std::cout << "MemberID " << inputMemberID << " does not exist in the Member_info.csv file." << std::endl;
                                            }
					    if (exists == false){
					        Date currentDate = Librarian_options.issueBook();	 
                                                std::string issuedate = currentDate.getFormattedDueDate();
					        std::string bookDetails = Book_options.getBookID();
					    if (!bookDetails.empty()) {
					       std::ofstream booksLoanedFile("booksLoaned.csv", std::ios::app); // Open the file in append mode
                                            if (booksLoanedFile.is_open()) {
                                              // Write the bookDetails to the file
					      std::cout << "Book details: " << bookDetails << std::endl;
                                              booksLoanedFile << inputMemberID << "," <<  issuedate << "," << bookDetails << std::endl;
                                              booksLoanedFile.close();
                                              std::cout << "Book successfully issued to MemberID " << inputMemberID << std::endl;
                                            } else {
                                              std::cerr << "Unable to open booksLoaned.csv for writing." << std::endl;
                                            }

                                                   } else {
                                                    std::cout << "No valid book selected. Please try again." << std::endl;
                                                }
					    }
					  }
                                            break;
                                        case 3:
					  // Librarian_options.returnBook();
                                            break;
                                        case 4:
                                            // Librarian_options.displayBorrowedBooks();
                                            break;
                                        case 5:
                                            std::cout << "You have selected to exit the Library System " << std::endl;
                                            flag4 = false;
                                            break;
                                        default:
                                            break;
                                    }
                                } else if (action_confirmation == "n") {
                                    flag3 = false;
                                    std::cout << "Action cancelled. " << std::endl;
                                } else {
                                    std::cout << "Invalid input. Give [y] for yes or [n] for no. " << std::endl;
                                    std::cin.clear();
                                }
                            }
			   
                        } else {
                            std::cout << "Invalid option. Please enter a number between 1 and 5." << std::endl;
                            // Clear the input buffer
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }

                    std::cout << "Would you like to make another action? [y/n] " << std::endl;
                    std::cin >> action_again;
                    if (action_again == "y") {
                        flag4 = true;
                        flag3 = true;
                    } else if (action_again == "n") {
                        flag4 = false;
			flag3 = false;
                        std::cout << "Thank you, see you soon!" << std::endl;
			exit(0); //terminate
                    }
                }
            } else {
                std::cout << "Invalid staff ID. Try again: " << std::endl;
            }
        }
    }

    return 0;
}

