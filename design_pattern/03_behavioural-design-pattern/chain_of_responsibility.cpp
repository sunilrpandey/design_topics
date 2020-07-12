#include <iostream>
#include <vector>

using namespace std;
struct Handler
{
    virtual std::string handle(const std::string& str) = 0;
    virtual Handler * setNext(Handler * handler) = 0;
};

struct ChainHandler : public Handler
{
    ChainHandler():next_(nullptr){}
    Handler * setNext(Handler * handler) override
    {
        next_ = handler;
        return handler;        
    }
    std::string handle(const std::string& str) override
    {
        if(next_) {
            next_->handle(str);
        }
        return {};
    }
    private:
    Handler * next_;    
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

void testChainofResponsibility(Handler * handler){
    std::vector<std::string> sequence = {"First", "Second","Last"};
    for(auto& s:sequence) {
        cout << "Start at " << s;
        const string& out = handler->handle(s);
        if(!out.empty()) {
            cout << "  " << out;            
        } else {
            std::cout << s << " was not handled" << endl;
        }
    } 
}


int main()
{
    FirstStepHandler * first_handler = new FirstStepHandler;
    SecondStepHandler * second_handler = new SecondStepHandler;
    LastStepHandler * last_handler = new LastStepHandler;
    first_handler->setNext(second_handler)->setNext(last_handler);

    testChainofResponsibility(first_handler);
    
    return 0;
}