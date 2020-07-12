#include <iostream>
using namespace std;

struct AbstractServer
{
    virtual void requestService() = 0;
};

struct Server : public AbstractServer
{
    void requestService() {
        cout << endl << "Request Served!";
    }
};
struct Proxy : public AbstractServer
{
    Proxy(AbstractServer * server):server_(server){}
    bool checkCredential() {
        cout << endl << "Access Verified";
        return true;
    }
    void logAccess() {
        cout << endl << "Access detail logged";
    } 
    void requestService() {
        if(checkCredential()) {
            server_->requestService();
        }
        logAccess();
    } 
  private:
    AbstractServer * server_ = nullptr;  
    
};

void testServer(AbstractServer * server) 
{
    server->requestService();
}
int main()
{
    cout << endl << "Proxy Demo starts ..";
    
    cout << endl << "Server request without proxy ..";
    Server server;
    testServer(&server);  

    cout << endl << "Server request with proxy ..";
    Proxy proxy(&server);
    testServer(&proxy);

    cout << endl << "Proxy Demo ends ..";
    return 0;
}