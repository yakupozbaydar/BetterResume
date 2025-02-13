#include "resume.hpp"

void Resume::setPersonalInfo(const std::string& name, 
                           const std::string& email,
                           const std::string& phone,
                           const std::string& location) {
    this->name = name;
    this->email = email;
    this->phone = phone;
    this->location = location;
}

void Resume::addEducation(const Education& education) {
    this->education.push_back(education);
}

void Resume::addExperience(const Experience& experience) {
    this->experience.push_back(experience);
}

void Resume::addSkill(const Skill& skill) {
    this->skills.push_back(skill);
} 