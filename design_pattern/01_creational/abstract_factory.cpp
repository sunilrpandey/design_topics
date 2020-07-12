/*
Factory Method is a creational design pattern that provides an interface for creating objects in
 a superclass, but allows subclasses to alter the type of objects that will be created
*/
#include <iostream>
using namespace std;

// abstract products
struct AbstractButton
{
    virtual void renderbutton() = 0;
};

struct AbstractCheckbox
{
    virtual void rendercheckbox() = 0;
};

struct WindowsButton : public AbstractButton
{
    void renderbutton() { cout << endl << "rendering button on windows platform !!";}
};


struct WindowsCheckbox : public AbstractCheckbox
{
    void rendercheckbox() { cout << endl << "rendering checkbox on windows platform !!";}
};

struct MacButton : public AbstractButton
{
    void renderbutton() { cout << endl << "rendering button on Mac platform !!";}
};

struct MacCheckbox : public AbstractCheckbox
{
    void rendercheckbox() { cout << endl << "rendering checkbox on Mac platform !!";}
};

struct AbstractControlFactory
{
    virtual AbstractButton * createButton() = 0;
    virtual AbstractCheckbox * createCheckbox() = 0;
};
struct WindowsFactory : public AbstractControlFactory
{
    virtual AbstractButton * createButton(){ return new WindowsButton;};
    virtual AbstractCheckbox * createCheckbox(){ return new WindowsCheckbox;};
};
struct MacFactory : public AbstractControlFactory
{
    virtual AbstractButton * createButton(){ return new MacButton;};
    virtual AbstractCheckbox * createCheckbox(){ return new MacCheckbox;};
};
enum class FacotoryType
{
    WINDOWS = 0, MAC = 1, INVALID = 2
};

struct GUIApp
{
    AbstractControlFactory * factory =  nullptr;
    AbstractButton * button =  nullptr;
    AbstractCheckbox * checkbox =  nullptr;
    
    GUIApp(AbstractControlFactory * f):factory(f){}
    
    void createControls() { 
        cout << endl << "Creating GUI Controls ..  " ;
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }
    void renderControls() {
        cout << endl << "rendering GUI Controls ..  " ;
        if(button) button->renderbutton();
        if(checkbox) checkbox->rendercheckbox();
    }
};

struct AbstractFactoryDemo
{
    static void execute() {

        cout << endl << "===== Abstract Factory demo ====="; 
        AbstractControlFactory * factory = nullptr;
        int input = -1;
        cout << endl << "Enter 0 for Windows  and 1 for Mac and 2 for exit !" << endl;
        FacotoryType factory_type;
        do {
            cout << endl << "Enter your choice !" << endl;
            cin >> input;
            factory_type = static_cast<FacotoryType>(input);
            if(factory_type == FacotoryType::WINDOWS) {
                factory = new WindowsFactory;
                factory->createButton()->renderbutton();
                factory->createCheckbox()->rendercheckbox();
            } else if (factory_type == FacotoryType::MAC) {
                factory = new MacFactory;
                factory->createButton()->renderbutton();
                factory->createCheckbox()->rendercheckbox();
            } else {
                cout << endl << "Exiting ...." << endl;
                return;
            }
            /*
            GUIApp gui(factory);
            gui.createControls();
            gui.renderControls();
            */

        } while (input != 2);
    }

};
int main() 
{
    AbstractFactoryDemo::execute();
    cout << endl;
    return 0;
}