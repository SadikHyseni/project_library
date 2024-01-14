#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include "Person.h"

bool fileExists(const std::string &filename)
{
    std::ifstream file(filename);
    return file.good();
}

// verifiacation for member id
bool doesMemberIDExist(const std::string &filename, const std::string &memberIDToCheck)
{
    std::ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        std::string line;
        while (std::getline(inputFile, line))
        {
            std::string existingMemberID;
            std::istringstream iss(line);
            // MemberID is in the fourth column
            for (int i = 0; i < 4; ++i)
            {
                std::getline(iss, existingMemberID, ',');
            }
            if (existingMemberID == memberIDToCheck)
            {
                inputFile.close();
                return true; // MemberID found
            }
        }
        inputFile.close();
    }
    else
    {
        std::cerr << "Unable to open the CSV file for reading." << std::endl;
    }
    return false; // MemberID not found
}

// verification for book id
bool isBookIdExists(int bookid)
{
    std::ifstream file("booksLoaned.csv");
    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;

        // Tokenize the line using commas as delimiters
        std::getline(iss, token, ','); // MemberID
        std::getline(iss, token, ','); // issueDate
        std::getline(iss, token, ','); // Book ID

        // Convert the Book ID token to an integer
        int currentBookId;
        std::istringstream(token) >> currentBookId;

        // Check if the current Book ID matches the input bookid
        if (currentBookId == bookid)
        {
            // std::cout << "book id found " << std::endl;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// verification in staff id
bool checkStaffID(const std::string &filename, const std::string &login)
{
    std::ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        std::string line;
        std::getline(inputFile, line); // Read and discard the header line

        while (std::getline(inputFile, line))
        {
            std::istringstream iss(line);
            std::string staffID;

            // the staff ID is in the fourth column
            for (int i = 0; i < 4; ++i)
            {
                std::getline(iss, staffID, ',');
            }

            // staffID contains the value from the fourth column
            if (staffID == login)
            {
                inputFile.close();
                return true; // Staff ID found
            }
        }
        inputFile.close();
    }
    else
    {
        std::cerr << "Unable to open the CSV file for reading." << std::endl;
    }
    return false; // Staff ID not found
}

int main()
{
    std::string start;

    std::cout << "Welcome to the library System" << std::endl;

    bool flag = true;
    while (flag)
    {

        // Register a new staff or enter the system
        std::cout << "Enter the Library System [e] or Register [r]: " << std::endl;
        std::cin >> start;
        if (start == "r" || start == "e")
        {
            flag = false;
        }
        else
        {
            std::cout << "Invalid input. Enter [e] for enter or [r] for staff register: " << std::endl;
        }
    }

    // objects for Libararian and for book
    Librarian Librarian_options;
    Book Book_options;

    while (true)
    {
        if (start == "r")   //user selects Librarian registration
        {
            std::cout << "Welcome to the new staff" << std::endl;
            // save the staff in a csv file
            const std::string filename = "staff_info.csv";

            if (!fileExists(filename))
            {
                std::cerr << "Error: The CSV file does not exist or is empty." << std::endl;
                return 1;
            }

            // object for Person and Librarian
            Person newPerson;
            Librarian newLibrarian;

            // take new staff information
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

            // save info in the staff file
            std::ofstream outputFile(filename, std::ios::app);
            if (outputFile.is_open())
            {
                outputFile << newPerson.name << "," << newPerson.address << "," << newPerson.email << ","
                            << newLibrarian.staffID << "," << newLibrarian.salary << std::endl;

                outputFile.close();
                std::cout << "Thank you for your registration." << std::endl;
            }
            else
            {
                std::cerr << "Unable to open the file for writing." << std::endl;
                return 1;
            }
        }

        // declare variables
        std::string login;
        std::string action_confirmation;
        std::string action_again;
        std::string inputMemberID;
        int option;

        //after registration or not system asks for staff id
        std::cout << "Please enter your staff ID: " << std::endl;

        bool flag2 = true;
        bool flag4 = true;
        int inputbookID;
        int memberID;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (flag2)
        {
            std::cin >> login;

            // check valid tsaff id
            if (checkStaffID("staff_info.csv", login))
            {
                std::cout << "Staff ID found. Logging in..." << std::endl;
                flag2 = false;

                while (flag4)
                {

                    bool flag3 = true;
                    bool flag5 = true;
                    bool exists = true;
                    bool memberexist = false;
                    bool bookborrowed = true;

                    // Librarian action options
                    std::cout << "Select an option (by number):  " << std::endl
                              << "(1) Add a new Member" << std::endl
                              << "(2) Issue a book " << std::endl
                              << "(3) Return book " << std::endl
                              << "(4) Display borrowed books " << std::endl
                              << "(5) Exit terminate actions " << std::endl;

                    while (flag3)
                    {
                        std::cin >> option;
                        //option numbered from 1 to 5
                        if (option >= 1 && option <= 5)
                        {
                            // ask for action confirmation
                            std::cout << "Are you sure you want to make this action? [y/n] " << std::endl;
                            while (flag5)
                            {
                                std::cin >> action_confirmation;
                                if (action_confirmation == "y")
                                {
                                    flag3 = false;
                                    flag5 = false;

                                    // Lirarian activities
                                    switch (option)
                                    {
                                    case 1: // create a new member
                                        Librarian_options.addMember();
                                        break;
                                    case 2: // issue a book to a member
                                        while (exists)
                                        {
                                            std::cout << "Enter MemberID: ";
                                            std::cin >> inputMemberID;
                                            // Call the function to check if the MemberID exists
                                            if (doesMemberIDExist("Member_info.csv", inputMemberID))
                                            {
                                                std::cout << "MemberID " << inputMemberID << " exists in the database." << std::endl;
                                                exists = false;

                                                Date currentDate = Librarian_options.issueBook();
                                                std::string issueDate = currentDate.getFormattedDueDate();
                                                std::string bookDetails = Book_options.getBookID();
                                                if (!bookDetails.empty())
                                                {
                                                    std::ofstream booksLoanedFile("booksLoaned.csv", std::ios::app);
                                                    if (booksLoanedFile.is_open())
                                                    {
                                                        // Write the bookDetails to the file
                                                        std::cout << "Book details: " << bookDetails << std::endl;
                                                        booksLoanedFile << inputMemberID << "," << issueDate << "," << bookDetails << std::endl;
                                                        booksLoanedFile.close();
                                                        std::cout << "Book successfully issued to MemberID " << inputMemberID << std::endl;
                                                    }
                                                    else
                                                    {
                                                        std::cerr << "Unable to open data for writing." << std::endl;
                                                    }
                                                }
                                                else
                                                {
                                                    std::cout << "No valid book selected or has already been selected. Please try again." << std::endl;
                                                }
                                            }
                                            else
                                            {
                                                std::cout << "MemberID " << inputMemberID << " does not exist in the database." << std::endl;
                                            }
                                        }
                                        break;
                                    case 3: // return a book
                                        while (!memberexist)
                                        {
                                            std::cout << "Enter MemberID: " << std::endl;
                                            std::cin >> memberID;

                                            // Call the function to check if the MemberID exists
                                            if (doesMemberIDExist("Member_info.csv", std::to_string(memberID)))
                                            {
                                                memberexist = true;
                                                std::cout << "MemberID " << memberID << " exists in the database." << std::endl;

                                                while (bookborrowed)
                                                {
                                                    std::cout << "Enter the Book ID you would like to return: " << std::endl;
                                                    std::cin >> inputbookID;

                                                    if (isBookIdExists(inputbookID) == true)
                                                    {
                                                        Librarian_options.calcFine(memberID);
                                                        Librarian_options.returnBook(memberID, inputbookID);
                                                        bookborrowed = false;
                                                    }
                                                    else
                                                    {
                                                        std::cout << "Book has not been borrowed. Try again." << std::endl;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                std::cout << "MemberID " << inputMemberID << " does not exist in the database." << std::endl;
                                            }
                                        }
                                        bookborrowed = true;
                                        break;
                                    case 4: // Display borrowed books by member
                                        while (!memberexist)
                                        {
                                            std::cout << "Enter MemberID: " << std::endl;
                                            std::cin >> memberID;

                                            // Call the function to check if the MemberID exists
                                            if (doesMemberIDExist("Member_info.csv", std::to_string(memberID)))
                                            {
                                                memberexist = true;
                                                std::cout << "MemberID " << memberID << " exists in the database." << std::endl;
                                                Librarian_options.displayBorrowedBooks(memberID);
                                            }
                                        }
                                        break;
                                    case 5: // exit the Librarian activities
                                        std::cout << "You have selected to exit the Library System " << std::endl;
                                        flag4 = false;
                                        break;
                                    }
                                }
                                else if (action_confirmation == "n")
                                {
                                    // i need to clear the options if yes
                                    flag3 = false;
                                    flag5 = false;
                                    std::cout << "Action cancelled. " << std::endl;
                                }
                                else
                                {
                                    std::cout << "Invalid input. Give [y] for yes or [n] for no. " << std::endl;
                                    std::cin.clear();
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Invalid option. Please enter a number between 1 and 5." << std::endl;
                            // Clear the input buffer
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }

                    // verification for another action
                    std::cout << "Would you like to make another action? [y/n] " << std::endl;
                    std::cin >> action_again;

                    if (action_again == "y")
                    {
                        flag4 = true;
                    }
                    else if (action_again == "n")
                    {
                        std::cout << "Thank you, see you soon!" << std::endl;
                        exit(0); // terminate
                    }
                }
            }
            else
            {
                std::cout << "Invalid staff ID. Try again: " << std::endl;
            }
        }
    }

    return 0;
}
