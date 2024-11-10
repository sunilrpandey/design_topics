#include <iostream>
#include <stack>
#include <memory>

// Fan class - Receiver
class Fan {
private:
    int speed;

public:
    Fan() : speed(0) {}

    void setSpeed(int newSpeed) {
        if (newSpeed >= 0 && newSpeed <= 4) {
            speed = newSpeed;
            std::cout << "Fan speed set to " << speed << std::endl;
        } else {
            std::cout << "Invalid speed level. Speed should be between 0 and 4" << std::endl;
        }
    }

    int getSpeed() const {
        return speed;
    }
};

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Concrete command for setting fan speed
class SetSpeedCommand : public Command {
private:
    Fan* fan;
    int newSpeed;
    int previousSpeed;

public:
    SetSpeedCommand(Fan* f, int speed) : fan(f), newSpeed(speed) {
        previousSpeed = fan->getSpeed();
    }

    void execute() override {
        previousSpeed = fan->getSpeed();
        fan->setSpeed(newSpeed);
    }

    void undo() override {
        fan->setSpeed(previousSpeed);
    }
};

// Fan remote control - Invoker
class FanRemote {
private:
    Fan* fan;
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;

public:
    FanRemote(Fan* f) : fan(f) {}

    void setSpeed(int speed) {
        auto cmd = std::make_unique<SetSpeedCommand>(fan, speed);
        cmd->execute();
        undoStack.push(std::move(cmd));
        // Clear redo stack when a new command is executed
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undo() {
        if (undoStack.empty()) {
            std::cout << "Nothing to undo!" << std::endl;
            return;
        }

        std::unique_ptr<Command> cmd = std::move(undoStack.top());
        undoStack.pop();
        cmd->undo();
        redoStack.push(std::move(cmd));
    }

    void redo() {
        if (redoStack.empty()) {
            std::cout << "Nothing to redo!" << std::endl;
            return;
        }

        std::unique_ptr<Command> cmd = std::move(redoStack.top());
        redoStack.pop();
        cmd->execute();
        undoStack.push(std::move(cmd));
    }
};

// Main function to demonstrate the usage
int main() {
    // Create the fan and remote
    Fan fan;
    FanRemote remote(&fan);

    // Test sequence
    std::cout << "Initial state:" << std::endl;
    std::cout << "Current speed: " << fan.getSpeed() << std::endl;

    std::cout << "\nSetting speed to 3:" << std::endl;
    remote.setSpeed(3);

    std::cout << "\nSetting speed to 4:" << std::endl;
    remote.setSpeed(4);

    std::cout << "\nUndo last command:" << std::endl;
    remote.undo();
    std::cout << "Current speed: " << fan.getSpeed() << std::endl;

    std::cout << "\nUndo again:" << std::endl;
    remote.undo();
    std::cout << "Current speed: " << fan.getSpeed() << std::endl;

    std::cout << "\nRedo last command:" << std::endl;
    remote.redo();
    std::cout << "Current speed: " << fan.getSpeed() << std::endl;

    std::cout << "\nSet new speed to 2:" << std::endl;
    remote.setSpeed(2);

    std::cout << "\nTry to redo (should show nothing to redo):" << std::endl;
    remote.redo();

    std::cout << "\nFinal speed: " << fan.getSpeed() << std::endl;

    return 0;
}
