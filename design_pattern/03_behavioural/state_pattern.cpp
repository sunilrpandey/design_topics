#include <iostream>
#include <memory>

//TODO: Not working

// Forward declaration of State classes
class IdleState;
class HasMoneyState;
class DispensingState;

// State Interface
class State {
public:
    virtual ~State() = default;
    virtual void insertMoney(class VendingMachine* vendingMachine) = 0;
    virtual void selectProduct(VendingMachine* vendingMachine) = 0;
    virtual void dispense(VendingMachine* vendingMachine) = 0;
};

// Vending Machine Context
class VendingMachine {
private:
    State* currentState; // Current state of the vending machine

public:
    VendingMachine(State* initialState) : currentState(initialState) {}

    void setState(State * newState) {
        currentState = newState; // Change the current state
    }

    void insertMoney() {
        currentState->insertMoney(this); // Delegate to the current state's method
    }

    void selectProduct() {
        currentState->selectProduct(this); // Delegate to the current state's method
    }

    void dispense() {
        currentState->dispense(this); // Delegate to the current state's method
    }
};

// Idle State
class IdleState : public State {
public:
    void insertMoney(VendingMachine* vendingMachine) override {
        std::cout << "Money inserted. Ready to select a product.\n";
        vendingMachine->setState(new HasMoneyState());
    }

    void selectProduct(VendingMachine* vendingMachine) override {
        std::cout << "Please insert money first.\n";
    }

    void dispense(VendingMachine* vendingMachine) override {
        std::cout << "No product selected. Can't dispense.\n";
    }
};

// Has Money State
class HasMoneyState : public State {
public:
    void insertMoney(VendingMachine* vendingMachine) override {
        std::cout << "You already inserted money.\n";
    }

    void selectProduct(VendingMachine* vendingMachine) override {
        std::cout << "Product selected. Dispensing...\n";
        vendingMachine->setState(new DispensingState());
    }

    void dispense(VendingMachine* vendingMachine) override {
        std::cout << "You need to select a product first.\n";
    }
};

// Dispensing State
class DispensingState : public State {
public:
    void insertMoney(VendingMachine* vendingMachine) override {
        std::cout << "Please wait, dispensing product...\n";
    }

    void selectProduct(VendingMachine* vendingMachine) override {
        std::cout << "Dispensing in progress. Can't select another product.\n";
    }

    void dispense(VendingMachine* vendingMachine) override {
        std::cout << "Product dispensed. Thank you!\n";
        vendingMachine->setState(new IdleState());
    }
};

    }
int main() {
    // Create initial state as Idle
    //std::shared_ptr<State> idleState = std::make_shared<IdleState>();
    VendingMachine vendingMachine(new IdleState());

    // Interact with the vending machine
    vendingMachine.insertMoney();     // Transition to Has Money State
    vendingMachine.selectProduct();   // Transition to Dispensing State
    vendingMachine.dispense();        // Dispense the product

    // Try to insert money again
    vendingMachine.insertMoney();     // Should inform already has money

    return 0;
}
