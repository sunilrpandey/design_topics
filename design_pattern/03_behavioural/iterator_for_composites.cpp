#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <string>

// TODO: BFS/DFS iterator still to be fixed
// Component interface (common for both leaf and composite)
class Component {
public:
    virtual ~Component() = default;
    virtual void operation() const = 0;   // Do something (like print or process)
    virtual bool isComposite() const { return false; }  // Indicates if it is a composite object
    virtual void add(std::shared_ptr<Component>) {}      // Add a child (only for composites)
    virtual std::vector<std::shared_ptr<Component>> getChildren() const { return {}; }  // Get children
};

// Leaf class (end node in the composite structure)
class Leaf : public Component {
private:
    std::string name;

public:
    Leaf(const std::string& name) : name(name) {}
    void operation() const override {
        std::cout << "Leaf: " << name << "\n";
    }
};

// Composite class (node with children)
class Composite : public Component {
private:
    std::string name;
    std::vector<std::shared_ptr<Component>> children;  // Stores children components

public:
    Composite(const std::string& name) : name(name) {}
    void operation() const override {
        std::cout << name << " Composite contains:\n";
        for (const auto& child : children) {
            child->operation();  // Delegates operation to children
        }
    }

    bool isComposite() const override { return true; }

    void add(std::shared_ptr<Component> component) override {
        children.push_back(component);
    }

    std::vector<std::shared_ptr<Component>> getChildren() const override {
        return children;
    }
};

// Iterator Interface
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual std::shared_ptr<Component> next() = 0;
};

// Depth-First Iterator (DFS)
class DepthFirstIterator : public Iterator {
private:
    std::stack<std::shared_ptr<Component>> stack;

public:
    DepthFirstIterator(std::shared_ptr<Component> root) {
        stack.push(root);
    }

    bool hasNext() override {
        return !stack.empty();
    }

    std::shared_ptr<Component> next() override {
        if (!hasNext()) {
            throw std::out_of_range("No more elements");
        }

        std::shared_ptr<Component> current = stack.top();
        stack.pop();

        // If the current component is a composite, push its children onto the stack (in reverse order)
        if (current->isComposite()) {
            auto children = current->getChildren();
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                stack.push(*it);
            }
        }

        return current;
    }
};

// Breadth-First Iterator (BFS)
class BreadthFirstIterator : public Iterator {
private:
    std::queue<std::shared_ptr<Component>> queue;

public:
    BreadthFirstIterator(std::shared_ptr<Component> root) {
        queue.push(root);
    }

    bool hasNext() override {
        return !queue.empty();
    }

    std::shared_ptr<Component> next() override {
        if (!hasNext()) {
            throw std::out_of_range("No more elements");
        }

        std::shared_ptr<Component> current = queue.front();
        queue.pop();

        // If the current component is a composite, enqueue its children
        if (current->isComposite()) {
            auto children = current->getChildren();
            for (const auto& child : children) {
                queue.push(child);
            }
        }

        return current;
    }
};

// Client code to demonstrate the iterator with composite objects
int main() {
    // Create leaf nodes
    std::shared_ptr<Component> leaf1 = std::make_shared<Leaf>("Leaf 1");
    std::shared_ptr<Component> leaf2 = std::make_shared<Leaf>("Leaf 2");
    std::shared_ptr<Component> leaf3 = std::make_shared<Leaf>("Leaf 3");

    // Create composite nodes
    std::shared_ptr<Composite> composite1 = std::make_shared<Composite>("Node 1-2");
    std::shared_ptr<Composite> composite2 = std::make_shared<Composite>("Node 1-2-3");

    // Build the composite structure (a tree)
    composite1->add(leaf1);
    composite1->add(leaf2);
    composite2->add(composite1);
    composite2->add(leaf3);

    // Depth-first traversal
    std::cout << "Depth-First Traversal:\n";
    DepthFirstIterator dfsIterator(composite2);
    while (dfsIterator.hasNext()) {
        std::shared_ptr<Component> component = dfsIterator.next();
        component->operation();
    }

    // Breadth-first traversal
    std::cout << "\nBreadth-First Traversal:\n";
    BreadthFirstIterator bfsIterator(composite2);
    while (bfsIterator.hasNext()) {
        std::shared_ptr<Component> component = bfsIterator.next();
        component->operation();
    }

    return 0;
}
