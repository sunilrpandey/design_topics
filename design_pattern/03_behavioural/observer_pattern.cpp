#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Forward declaration of Observer
class Observer;

// Subject Interface
class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0; // will update all the observers
};

// Observer Interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float temperature) = 0; // Update method to receive notifications
};
// Concrete Subject
class WeatherStation : public Subject {
private:
    std::vector<Observer*> observers; // List of observers
    float temperature;                 // Current temperature

public:
    void setTemperature(float temp) {
        temperature = temp;
        notify(); // Notify observers about the temperature change
    }

    float getTemperature() const {
        return temperature;
    }

    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(std::find(observers.begin(), observers.end(), observer));
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update(temperature); // Notify each observer
        }
    }
};
// Concrete Observer: Display
class CurrentConditionsDisplay : public Observer {
private:
    WeatherStation* weatherStation;

public:
    CurrentConditionsDisplay(WeatherStation* station) : weatherStation(station) {
        weatherStation->attach(this); // Register as an observer
    }

    void update(float temperature) override {
        std::cout << "Current temperature: " << temperature << "°C\n";
    }
};

// Concrete Observer: Statistics
class StatisticsDisplay : public Observer {
private:
    WeatherStation* weatherStation;

public:
    StatisticsDisplay(WeatherStation* station) : weatherStation(station) {
        weatherStation->attach(this); // Register as an observer
    }

    void update(float temperature) override {
        std::cout << "Statistics Display: New temperature recorded: " << temperature << "°C\n";
    }
};

int main() {
    WeatherStation weatherStation; // Create the subject

    CurrentConditionsDisplay currentDisplay(&weatherStation); // Create observers
    StatisticsDisplay statsDisplay(&weatherStation);

    // Change the temperature and notify observers
    weatherStation.setTemperature(25.0f); // Notify observers about the new temperature
    weatherStation.setTemperature(30.0f); // Notify observers about another change

/* ..works
    weatherStation.detach(&currentDisplay);
    weatherStation.setTemperature(300.0f); // Notify observers about another change
*/
    return 0;
}

