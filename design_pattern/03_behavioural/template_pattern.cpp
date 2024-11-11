//The Template Method Pattern is a behavioral design pattern that defines the skeleton of an algorithm in a base class, allowing subclasses to redefine certain steps of the algorithm without changing its structure. This pattern helps to promote code reuse and enforce a specific order of operations in derived classes.

#include <iostream>

// Abstract Class
class CaffeineBeverage {
public:
    // Template Method
    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

protected:
    // Steps that are common and implemented in the base class
    void boilWater() {
        std::cout << "Boiling water...\n";
    }

    void pourInCup() {
        std::cout << "Pouring into cup...\n";
    }

    // Abstract methods to be implemented by subclasses
    virtual void brew() = 0; // Must be implemented in derived classes
    virtual void addCondiments() = 0; // Must be implemented in derived classes
};

// Concrete Class: Tea
class Tea : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Steeping the tea...\n";
    }

    void addCondiments() override {
        std::cout << "Adding lemon...\n";
    }
};

// Concrete Class: Coffee
class Coffee : public CaffeineBeverage {
protected:
    void brew() override {
        std::cout << "Dripping coffee through filter...\n";
    }

    void addCondiments() override {
        std::cout << "Adding sugar and milk...\n";
    }
};

int main() {
    CaffeineBeverage* tea = new Tea();
    tea->prepareRecipe(); // Prepare tea

    std::cout << "\n";

    CaffeineBeverage* coffee = new Coffee();
    coffee->prepareRecipe(); // Prepare coffee

    // Clean up
    delete tea;
    delete coffee;

    return 0;
}

