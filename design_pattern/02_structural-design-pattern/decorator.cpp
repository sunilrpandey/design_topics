#include <iostream>
#include <string>
using namespace std;
struct Notifier
{
    virtual void showMessage() = 0;
};
struct SMSNotifier : public Notifier
{
    void showMessage() override{
        cout << "Communication Medium :  " << "SMS"; 
    }
};

struct NotificationBaseDecorator : public Notifier
{
    NotificationBaseDecorator(Notifier * n):notifier(n){}
    void showMessage() override{
        notifier->showMessage();
    }
  private:
    Notifier * notifier;
};
struct FacebookNotificationDecorator : public Notifier
{
    FacebookNotificationDecorator(Notifier * n):notifier(n){}
    void showMessage() override{
        notifier->showMessage();
        cout << ", Facebook ";
    }
  private:
    Notifier * notifier;
};

struct TwitterNotificationDecorator : public Notifier
{
    TwitterNotificationDecorator(Notifier * n):notifier(n){}
    void showMessage() override{
        notifier->showMessage();
        cout << ", Twitter "; 
    }
  private:
    Notifier * notifier;
};

void showNotification(Notifier * notifier) {
    cout << endl;
    notifier->showMessage();
}

int main()
{
    cout << endl << "Here goes Demo for Decorator pattern" << endl;
    Notifier * notifier = new SMSNotifier;
    showNotification(notifier);

    cout << "\n\nAdd Facebook to SMS";
    notifier  = new FacebookNotificationDecorator(notifier);
    showNotification(notifier);

    cout << endl << "Add Twitter to Facebook and SMS";
    notifier  = new TwitterNotificationDecorator(notifier);
    showNotification(notifier);

    cout << endl << "..and Demo ends for Decorator pattern";
    return 0;
}