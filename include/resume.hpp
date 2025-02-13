#pragma once

#include <string>
#include <vector>
#include <memory>

struct Education {
    std::string school;
    std::string degree;
    std::string field;
    std::string startDate;
    std::string endDate;
    float gpa;
};

struct Experience {
    std::string company;
    std::string position;
    std::string startDate;
    std::string endDate;
    std::vector<std::string> responsibilities;
};

struct Skill {
    std::string category;
    std::vector<std::string> items;
};

class Resume {
public:
    Resume() = default;
    ~Resume() = default;

    // Personal Information
    void setPersonalInfo(const std::string& name, 
                        const std::string& email,
                        const std::string& phone,
                        const std::string& location);

    // Education
    void addEducation(const Education& education);

    // Experience
    void addExperience(const Experience& experience);

    // Skills
    void addSkill(const Skill& skill);

    // Getters
    const std::string& getName() const { return name; }
    const std::string& getEmail() const { return email; }
    const std::string& getPhone() const { return phone; }
    const std::string& getLocation() const { return location; }
    const std::vector<Education>& getEducation() const { return education; }
    const std::vector<Experience>& getExperience() const { return experience; }
    const std::vector<Skill>& getSkills() const { return skills; }

private:
    // Personal Information
    std::string name;
    std::string email;
    std::string phone;
    std::string location;

    // Sections
    std::vector<Education> education;
    std::vector<Experience> experience;
    std::vector<Skill> skills;
}; 