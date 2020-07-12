#include <iostream>
using namespace std;

struct TargetPlug
{
    virtual void work() {
        cout << endl <<  "Working naturally ";
    } 
};

struct Adaptee
{
    virtual void primework() {
        cout << endl <<  "Only prime time working  ";
    }
};

//object adapter  
struct Adapter : public TargetPlug
{
    Adaptee * adpatee_;
    Adapter(Adaptee * a) : adpatee_(a){}
    void work() override {
        adpatee_->primework();
    }
};

//class adapter  
struct MultiAdapter : public TargetPlug, public Adaptee
{
    void work() override {
        Adaptee::primework();
    }
};


void testAdapter(TargetPlug * plg) {
    plg->work();
}

int main()
{
    cout << endl << "Msg : Test Target Plug";
    TargetPlug plg;
    testAdapter(&plg);
    
    cout << endl << "Msg : Test Target Plug with Adapter";
    Adaptee adptee;
    Adapter adapter(&adptee);
    testAdapter(&adapter);
    
    cout << endl << "Msg : Test Target Plug with Adapter using Multi Inheritance";
    MultiAdapter multiadapter;
    testAdapter(&multiadapter);

    cout << endl;
    
    return 0;
}