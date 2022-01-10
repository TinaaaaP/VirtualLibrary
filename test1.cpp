#include "libraryDef.cpp"
#include "materialDef.cpp"
#include <iostream>

int main() {
    std::string name = "name";
    student *STU = new student(name, 1);
    staff *STA = new staff(name, 2);
}
