#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Journal
{
	std::string  title;
	std::vector<std::string> entries;

	Journal(const string& value) :title(value) { }

	void add(const std::string& str) {
		entries.push_back(str);
	}

	// //should go to persistence manager
	// void save(const std::string& filename) {
	//     fstream filetosave(filename);
	//     for(auto& s : entries){
	//         filetosave << s << endl;
	//     }
	// }
};

struct PersistentManager
{
	PersistentManager(fstream& f):filetosave(f) {}
	void open(const string& f) {
		if (!filetosave.is_open()) {
			cout << "\n\n opening....";
			filetosave.open(f, ios::app);
		}
	}
	//should go to persistence manager
	void save(const Journal& j) {
		cout << "\n\n saving...";
		filetosave << endl << "\nTitle : " << j.title.c_str() << endl;
		for (auto& s : j.entries) {
			filetosave << s.c_str() << endl;
		}
	}
	void close() {
		if (filetosave.is_open()) {
			filetosave.close();
		}
	}
	void show() {
		cout << "\n\n showing...";

		std::string line;
		filetosave.open("C:\\srp1.txt", ios::app);
		while (getline(filetosave, line)) {
			cout << "\n\n getting line...";
			cout << line.c_str() << endl;
		}
	}

	fstream& filetosave;
};

int main()
{
	Journal j_per("personal");
	j_per.add("planned for trip");
	j_per.add("dinner at 10PM");

	Journal j_ofc("Office Work");
	j_ofc.add("Had Daily");
	j_ofc.add("Meeting with team");
	j_ofc.add("Delivery discussion");

	fstream f;
	f.open("srp_data.txt", ios::app|ios::out);
	f << "sunil" << "ssdfasdf" ;
	//f.close();

	PersistentManager persMgr(f);
	persMgr.save(j_per);
	persMgr.save(j_ofc);
	persMgr.show();
	persMgr.close();

	


	return 0;

}



