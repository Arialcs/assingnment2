#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define PRE_RELEASE  // comment to switch to standard code

struct STUDENT_DATA
{
    std::string firstName;
    std::string lastName;
    std::string email;  // Added for pre-release mode
};

int main()
{
    std::vector<STUDENT_DATA> students;
    std::ifstream file;

#ifdef PRE_RELEASE
   
    std::cout << "Running in Pre-Release mode." << std::endl;  // running in standard mode
    file.open("StudentData_Emails.txt");  // Open the pre-release data file
#else
   
    std::cout << "Running in Standard mode." << std::endl;   // running in standard mode
    file.open("StudentData.txt");  // Open the data file
#endif

    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        std::istringstream ss(line);
        STUDENT_DATA student;

#ifdef PRE_RELEASE
        // In pre-release mode, expect last name, first name, and email
        if (std::getline(ss, student.lastName, ',') &&
            std::getline(ss, student.firstName, ',') &&
            std::getline(ss, student.email)) 
        {
            students.push_back(student);
        }
        else
        {
            std::cerr << "Error reading line: " << line << std::endl;
        }
#else
        // In standard mode, expect last name and first name
        if (std::getline(ss, student.lastName, ',') &&
            std::getline(ss, student.firstName)) 
        {
            students.push_back(student);
        }
        else
        {
            std::cerr << "Error reading line: " << line << std::endl;
        }
#endif
    }

    file.close();  // Close the file

#ifdef _DEBUG
    // Debug output
    if (students.empty())
    {
        std::cout << "No students found." << std::endl;
    }
    else
    {
        for (const auto& student : students) 
        {
#ifdef PRE_RELEASE
            std::cout << "Name: " << student.lastName << ", "
                << student.firstName << ", Email: "
                << student.email << std::endl;
#else
            std::cout << "Name: " << student.lastName << ", "
                << student.firstName << std::endl;
#endif
        }
    }
#else
    // Release output
    if (students.empty()) 
    {
        std::cout << "No students found." << std::endl;
    }
    else {
        if (students.size() > 0)
        {
#ifdef PRE_RELEASE
            // In pre-release mode, print only emails
            for (const auto& student : students) 
            {
                std::cout << "Email: " << student.email << std::endl;
            }
#else
            // In standard release mode, just mention running status
            std::cout << "Just running in Standard mode." << std::endl;
#endif
        }
    }
#endif

    return 0;
}
