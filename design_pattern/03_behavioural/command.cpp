#include <iostream>
using namespace std;

struct Command
{
    virtual void execute() = 0;
};
struct Light
{
    bool light_on_ = true;
    void switchOn() { light_on_ = true;}
    void switchOff() { light_on_ = false;}
};
struct LightOnCommand
{
    Light * light_;
    LightOnCommand(Light* light):light_(light){}
    void execute(){
        light_->switchOn();
    }
};
struct LightOffCommand
{
    Light * light_;
    LightOffCommand(Light* light):light_(light){}
    void execute(){
        light_->switchOff();
    }
};

int main()
{
    return 0;
}