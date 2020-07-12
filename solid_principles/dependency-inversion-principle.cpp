#include <iostream>
#include <vector>
using namespace std;
struct Employee
{
    virtual void work() = 0;
};
struct Developer : public Employee 
{
    void work() override;
};
struct Designer :public Employee
{
    void work() override;

};

struct ResourceManager 
{
    std::vector<Employee> resources; // here Resouerce manager depends on employee not on developer or something, another kind of Employee will not make any change here
};
int main()
{

    return;
}