#include <iostream>
#include <list>
using namespace std;
//classes concept wise
struct Component
{
    virtual void execute() = 0;
    
    virtual void setParent(Component * p) {parent = p;}
    virtual Component * getParent(){return parent;}
    virtual bool isComposite() { return false;}
    
    virtual void add(Component * c) {}
    virtual void remove(Component * c) {}

  private:
    Component * parent = nullptr;

};
struct Leaf : public Component
{
    void execute() override {
        cout << "leaf" << endl;
    } 
};
struct Composite : public Component
{
  protected:
    std::list<Component*> children;
    void add(Component * c) {
        c->setParent(this);
        children.push_back(c);
    }
    void remove(Component * c) {
        c->setParent(nullptr);
        children.remove(c);
    }
    void execute() override {
        cout << "Branch : ";
        for(auto c : children) {
            c->execute();
        }
    } 
};

void testCompositeCode(Component * c){
    c->execute();
}

int main()
{
    cout << endl << "Corner case: just one leaf";
    Component * root = new Leaf;
    testCompositeCode(root);
    delete root;
    Component * root_0 = new Composite;
    Component * root_10 = new Composite;
    Component * root_11 = new Composite;
    Component * leaf_1 = new Leaf;
    Component * leaf_101 = new Leaf;
    Component * leaf_111 = new Leaf;
    root_0->add(root_10);
    root_0->add(root_11);
    root_0->add(leaf_1);
    root_10->add(leaf_101);
    root_11->add(leaf_111);
    
    testCompositeCode(root_0);

    cout << endl << "Yet to delete pointers"; 

    return 0;
}
