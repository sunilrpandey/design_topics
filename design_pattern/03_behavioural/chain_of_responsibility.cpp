#include <iostream>
#include <vector>
#include <memory>

using namespace std;
struct Handler
{
    virtual std::string handle(const std::string& str) = 0;
    virtual void setNextHandler(std::shared_ptr<Handler> handler) = 0;
};

struct ChainHandler : public Handler
{
    ChainHandler():next_(nullptr){}
    void setNextHandler(std::shared_ptr<Handler> handler) override
    {
        next_ = handler;
        return;
    }
    std::string handle(const std::string& str) override
    {
        if(next_) {
            next_->handle(str);
        }
        return {};
    }
    private:
    std::shared_ptr<Handler> next_;
};

struct FirstStepHandler : ChainHandler
{
    std::string handle(const std::string& str) override
    {
        if(str == "First") {
            return str + " Step done, move to Next!!";
        } else {
            return ChainHandler::handle(str);
        }
        return {};
    }
};
struct SecondStepHandler : ChainHandler
{
    std::string handle(const std::string& str) override
    {
        if(str == "Second") {
            return str + " Step done, move to Next!!";
        } else {
            return ChainHandler::handle(str);
        }
        return {};
    }
};

struct LastStepHandler : ChainHandler
{
    std::string handle(const std::string& str) override
    {
        if(str == "Last") {
            return str + " Step done, Here it ends!!";
        } else {
            return ChainHandler::handle(str);
        }
        return {};
    }
};

void DemoTestChainofResponsibility() {

    auto first_handler = std::shared_ptr<FirstStepHandler>(new FirstStepHandler);
    auto second_handler = std::shared_ptr<SecondStepHandler>(new SecondStepHandler);
    auto last_handler = std::shared_ptr<LastStepHandler>(new LastStepHandler);

    first_handler->setNextHandler(second_handler);
    second_handler->setNextHandler(last_handler);

    std::cout << "\nDemoing Chain of responsibility Pattern" << std::endl;

    std::cout << "\nhandling request 'first'...";
    first_handler->handle("First");

    std::cout << "\nhandling request 'second'...";
    first_handler->handle("Second");

    std::cout << "\nhandling request 'third'...";
    first_handler->handle("Third");

    std::cout << std::endl;

}


int main()
{

    DemoTestChainofResponsibility();

    return 0;
}
