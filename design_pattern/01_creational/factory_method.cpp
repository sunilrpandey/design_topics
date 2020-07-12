/*
Factory Method is a creational design pattern that provides an interface for creating objects in
 a superclass, but allows subclasses to alter the type of objects that will be created
*/
#include <iostream>
using namespace std;

// abstract products
struct AbstractButton
{
    virtual void render() = 0;
    virtual void onClick() = 0;
};

struct WindowsButton : public AbstractButton
{
    void render() { cout << endl << "rendering on windows platform !!";}
    void onClick() {};
};

struct HTMLButton : public AbstractButton
{
    void render() { cout << endl << "rendering on Web platform !!";}
    void onClick() {};
};

struct Dialog
{
    virtual AbstractButton * createButton() = 0;
};
struct WindowsDialog : public Dialog
{
    virtual AbstractButton * createButton(){ return new WindowsButton;};
};
struct WebDialog : public Dialog
{
    virtual AbstractButton * createButton(){ return new HTMLButton;};
};
enum class DialogType
{
    WINDOWS = 0, WEB = 1, INVALID = 2
};

struct FactoryMethodDemo
{
    static void execute() {

        cout << endl << "===== Factory pattern demo ====="; 
        Dialog * dlg = nullptr;
        int input = -1;
        cout << endl << "Enter 0 for Windows button and 1 for HTML button and 2 for exit !" << endl;
        DialogType dlg_type;
        do {
            cout << endl << "Enter your choice !" << endl;
            cin >> input;
            dlg_type = static_cast<DialogType>(input);
            if(dlg_type == DialogType::WINDOWS) {
                dlg = new WindowsDialog;
                dlg->createButton()->render();
            } else if (dlg_type == DialogType::WEB) {
                dlg = new WebDialog;
                dlg->createButton()->render();
            } else {
                cout << endl << "Exiting ...." << endl;
                return;
            }
        } while (input != 2);
    }

};
int main() 
{
    FactoryMethodDemo::execute();
    cout << endl;
    return 0;
}