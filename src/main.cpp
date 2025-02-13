#include <iostream>
#include <string>
#include <limits>
#include "resume.hpp"
#include "pdf_generator.hpp"

// Helper function to get input with spaces
std::string getLineInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// Helper function to clear input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Resume resume;
    
    std::cout << "=== Personal Information ===" << std::endl;
    
    std::cout << "Full Name: ";
    std::string name = getLineInput();
    
    std::cout << "Email: ";
    std::string email = getLineInput();
    
    std::cout << "Phone: ";
    std::string phone = getLineInput();
    
    std::cout << "Location: ";
    std::string location = getLineInput();
    
    resume.setPersonalInfo(name, email, phone, location);

    // Education
    std::cout << "\n=== Education ===" << std::endl;
    std::cout << "How many education entries? ";
    int eduCount;
    std::cin >> eduCount;
    clearInputBuffer();

    for (int i = 0; i < eduCount; ++i) {
        Education edu;
        std::cout << "\nEducation #" << (i + 1) << std::endl;
        
        std::cout << "School: ";
        edu.school = getLineInput();
        
        std::cout << "Degree: ";
        edu.degree = getLineInput();
        
        std::cout << "Field of Study: ";
        edu.field = getLineInput();
        
        std::cout << "Start Date: ";
        edu.startDate = getLineInput();
        
        std::cout << "End Date: ";
        edu.endDate = getLineInput();
        
        std::cout << "GPA (0 if not applicable): ";
        std::cin >> std::fixed >> std::setprecision(2) >> edu.gpa;
        clearInputBuffer();

        resume.addEducation(edu);
    }

    // Experience
    std::cout << "\n=== Professional Experience ===" << std::endl;
    std::cout << "How many experience entries? ";
    int expCount;
    std::cin >> expCount;
    clearInputBuffer();

    for (int i = 0; i < expCount; ++i) {
        Experience exp;
        std::cout << "\nExperience #" << (i + 1) << std::endl;
        
        std::cout << "Company: ";
        exp.company = getLineInput();
        
        std::cout << "Position: ";
        exp.position = getLineInput();
        
        std::cout << "Start Date: ";
        exp.startDate = getLineInput();
        
        std::cout << "End Date: ";
        exp.endDate = getLineInput();
        
        std::cout << "Number of responsibilities: ";
        int respCount;
        std::cin >> respCount;
        clearInputBuffer();

        std::cout << "Enter responsibilities:" << std::endl;
        for (int j = 0; j < respCount; ++j) {
            std::cout << (j + 1) << ": ";
            std::string resp = getLineInput();
            exp.responsibilities.push_back(resp);
        }

        resume.addExperience(exp);
    }

    // Skills
    std::cout << "\n=== Skills ===" << std::endl;
    std::cout << "How many skill categories? ";
    int skillCatCount;
    std::cin >> skillCatCount;
    clearInputBuffer();

    for (int i = 0; i < skillCatCount; ++i) {
        Skill skill;
        std::cout << "\nSkill Category #" << (i + 1) << std::endl;
        
        std::cout << "Category Name: ";
        skill.category = getLineInput();
        
        std::cout << "Number of skills in this category: ";
        int skillCount;
        std::cin >> skillCount;
        clearInputBuffer();

        std::cout << "Enter skills:" << std::endl;
        for (int j = 0; j < skillCount; ++j) {
            std::cout << (j + 1) << ": ";
            std::string skillItem = getLineInput();
            skill.items.push_back(skillItem);
        }

        resume.addSkill(skill);
    }

    // Generate PDF
    try {
        PDFGenerator generator;
        std::string outputPath = "resume.pdf";
        
        std::cout << "\nGenerating PDF..." << std::endl;
        if (generator.generatePDF(resume, outputPath)) {
            std::cout << "Resume successfully generated as '" << outputPath << "'" << std::endl;
        } else {
            std::cerr << "Failed to generate PDF" << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
