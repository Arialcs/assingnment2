#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Define the STUDENT_DATA struct
struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() {
    std::vector<STUDENT_DATA> students; // Vector to store student data
    std::ifstream file("StudentData.txt"); // Open the input file

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        STUDENT_DATA student;

        // Parse the last name and first name
        if (std::getline(ss, student.lastName, ',') && std::getline(ss, student.firstName)) {
            // Create a student object and push it into the vector
            students.push_back(student);
        }
        else {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }

    file.close(); // Close the file

    // Print out the student information
    std::cout << "Students List:" << std::endl;
    for (const auto& student : students) {
        std::cout << "Name: " << student.lastName << ", " << student.firstName << std::endl;
    }

    return 0;
}
