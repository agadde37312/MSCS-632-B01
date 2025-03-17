#include <iostream>
#include <string>

class Car {
public:
    std::string brand;
    int year;

    Car(std::string b, int y) : brand(b), year(y) {}
    void display() { std::cout << "Car: " << brand << " - " << year << std::endl; }
};

int main() {
    Car* myCar = new Car("Ford", 2020); // Dynamic allocation
    myCar->display();

    delete myCar; // Manual memory deallocation to prevent leaks
    myCar = nullptr; // Avoid dangling pointer

    return 0;
}