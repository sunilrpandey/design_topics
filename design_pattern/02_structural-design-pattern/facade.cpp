#include <iostream>
using namespace std;

//Facade is a structural design pattern that provides a simplified interface to a library, a framework, or any other complex set of classes.

struct Subsystem1
{
    void init10() {
        cout << endl << "System1 : init 0";
    }
    void init1N() {
        cout << endl << "System1 : init N";
    }
    void clean10() {
        cout << endl << "System1 : clean 0";
    }
    void clean1N() {
        cout << endl << "System1 : clean N";
    }
};

struct Subsystem2
{
    void init20() {
        cout << endl << "System2 : init 0";
    }
    void init2N() {
        cout << endl << "System2 : init N";
    }
    void clean20() {
        cout << endl << "System2 : clean 0";
    }
    void clean2N() {
        cout << endl << "System2 : clean N";
    }
};

struct Facade {
    Subsystem1 * subsystem1;
    Subsystem2 * subsystem2;
    Facade(){
        subsystem1 = subsystem1 ? : new Subsystem1;
        subsystem2 = subsystem2 ? : new Subsystem2; 
    }
    void init() {
        subsystem1->init10();
        subsystem1->init1N();

        subsystem2->init20();
        subsystem2->init2N();
    }
    void clean() {
        subsystem1->clean10();
        subsystem1->clean1N();

        subsystem2->clean20();
        subsystem2->clean2N();
    }
};

void testFacade(Facade * facade)
{
    cout << endl << "Demo Facade starts.." << endl;
    facade->init();
    facade->clean();
    cout << endl << "Demo Facade ends.." << endl;    
}

int main()
{
    Facade facade;
    testFacade(&facade);
    return 0;
}