// no client should be forced to depend on something it does not use
// so break up your interfaces into lot of little interfaces and use which one is needed only
#include<iostream>
using namespace std;

class Document;
/*
struct IMachine
{
	virtual void print(Document *) = 0;
	virtual void scan(Document *) = 0;
	virtual void fax(Document *) = 0;
};
struct Machine : public IMachine
{
	virtual void print(Document *) override {}
	virtual void scan(Document *) override {}
	virtual void fax(Document *) override {}
};
Not acceptable as client will have to implment scan and fax even if it does not use it
*/

// instead use below
struct IPrinter
{
	virtual void print(Document *) = 0;
};
struct IScanner
{
	virtual void scan(Document *) = 0;
};
struct IFax
{
	virtual void fax(Document *) = 0;
};

struct Printer : public IPrinter
{
	void print(Document* doc) override {}
};
struct Scanner : public IScanner
{
	void scan(Document * doc) override {}
};
struct Faxer : public IFax
{
	void fax(Document * doc) override {}
};

// one can use multiple inheritance to use more than one interface or use decorator pattern
struct IScanPrintMachine : public IPrinter, public IScanner
{

};
//Deorator pattern
struct ScanPrintMachine : public IScanPrintMachine
{
	IPrinter * printer;
	IScanner * scanner;
	ScanPrintMachine(IPrinter * p, IScanner * s) : printer(p), scanner(s) {}
	void print(Document * doc) { printer->print(doc); }
	void scan(Document * doc) { scanner->scan(doc); }
};