//
// Created by user on 02.09.2025.
//

#include "genre.h"
#include "iostream"
#include <string>
#include <utility>

genre::genre():name("Unknown genre"), description("No info yet.") {
    std::cout<<"Default constructor was called for "<<name<<std::endl;
};

genre::genre(std::string gn, std::string desc)
    :name(std::move(gn)), description(std::move(desc)) {
    std::cout<<"Parametrized constructor was called for "<<name<<std::endl;
};

genre::genre(const genre& other)
    :name(other.name), description(other.description) {
    std::cout<<"Copy constructor was called for "<<name<<std::endl;
};

genre& genre::operator=(const genre& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
    }
    return *this;
};

genre::genre(genre&& other) noexcept
    :name(std::move(other.name)),
    description(std::move(other.description)) {
    std::cout<<"Move constructor was called "<<std::endl;
}

genre::~genre() {
    std::cout<<"Destructor was called for "<<name<<std::endl;
}


std::string genre::getName() {
    return name;
}
std::string genre::getDescription() {
    return description;
}

void genre::setName(std::string newName) {
    this->name = std::move(newName);
}
void genre::setDescription(std::string newDescription) {
    this->description = std::move(newDescription);
}
