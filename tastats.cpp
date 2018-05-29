#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;


class HelpInstance {
private:
	static string currentDate;
	string date;
	string student;
	string helper;
	string enqueue;
	string dequeue;
	string wait;
	string type;
	string duration;

public:
	void addCurrentDate(string date) {
		this->currentDate = date;
	}
	void addDate(string date) {
		this->date = date;
	}
	void addStudent(string student) {
		this->student = student;
	}
	void addHelper(string helper) {
		this->helper = helper;
	}
	void addEnqueue(string enqueue) {
		this->enqueue = enqueue;
	}
	void addDequeue(string dequeue) {
		this->dequeue = dequeue;
	}
	void addWait(string wait) {
		this->wait = wait;
	}
	void addType(string type) {
		this->type = type;
	}
	void addDuration(string duration) {
		this->duration = duration;
	}
	string getCurrentDate() const {
		return currentDate;
	}
	string getStudent() const {
		return student;
	}
	string getHelper() const {
		return helper;
	}
	/*int getDuration() const {
		int minutes, seconds;
		istringstream
	}*/
	string toString() {
		ostringstream out;
		out << date << " ";
		out << student << " ";
		out << helper << " ";
		out << enqueue << " ";
		out << dequeue << " ";
		out << wait << " ";
		out << type << " ";
		out << duration << " ";
		return out.str();
	}
};

class TeachingAssistant {
private:
	string name;
	vector<HelpInstance> helpInstances;
	map<string, int> studentsHelped;
public:
	TeachingAssistant(string name) {
		this->name = name;
	}
	void addInstance(HelpInstance help) {
		helpInstances.push_back(help);
		studentsHelped[help.getStudent()]++;
	}
	string getName() const {
		return name;
	}
	int getHelpInstanceTotal() const {
		return helpInstances.size();
	}
	int getUniqueTotal() const {
		return studentsHelped.size();
	}
	string getMostFrequent() const {
		return max_element(studentsHelped.begin(), studentsHelped.end(), [] (pair<string, int> compare1, pair<string, int> compare2) {return compare1.second < compare2.second;})->first;
	}
	string toString() {
		ostringstream out;
		out << left;
		out << setw(20) << name;
		out << setw(10) << getHelpInstanceTotal();
		out << setw(10) << getUniqueTotal();
		out << setw(15) << getMostFrequent();
		/*for (HelpInstance help : helpInstances) {
			out << help.getDuration() << endl;
		}*/
		return out.str();
	}
};

const int NOT_FOUND = -1;

int index(const vector<TeachingAssistant> &teachingAssistants, string name) {
	for (int i = 0; i < teachingAssistants.size(); ++i) {
		if (teachingAssistants.at(i).getName() == name) {
			return i;
		}
	}
	return NOT_FOUND;
}

bool contains(const vector<TeachingAssistant> &teachingAssistants, string name) {
	return index(teachingAssistants, name) != NOT_FOUND;
}

string currentDate;

HelpInstance extract(string row) {
	HelpInstance help;
	string cell;

	istringstream line(row);

	getline(line, cell, ',');
	if (cell != "") currentDate = cell;
	help.addDate(currentDate);

	getline(line, cell, ',');
	help.addStudent(cell);

	getline(line, cell, ',');
	help.addHelper(cell);

	if (help.getHelper() == "") {
		cout << line.str() << endl;
	}

	getline(line, cell, ',');
	help.addEnqueue(cell);

	getline(line, cell, ',');
	help.addDequeue(cell);

	getline(line, cell, ',');
	help.addWait(cell);

	getline(line, cell, ',');
	help.addType(cell);

	getline(line, cell, ',');
	help.addDuration(cell);

	return help;
}

int main() {
	ifstream file("hhh.csv");
	string row;
	string currentDate;
	vector<HelpInstance> helpInstances;
	vector<TeachingAssistant> teachingAssistants;

	while (file.good()) {
		getline(file, row);
		if (row != ",,,,,,," && row != "") {
			helpInstances.push_back(extract(row));
		}
	}

	for (int i = 0; i < helpInstances.size(); ++i) {
		if (!contains(teachingAssistants, helpInstances.at(i).getHelper())) {
			if (helpInstances.at(i).getHelper() == "") {
				continue;
			}
			else {
				teachingAssistants.push_back(TeachingAssistant(helpInstances.at(i).getHelper()));
			}
		}
		unsigned int thisTA = index(teachingAssistants, helpInstances.at(i).getHelper());
		teachingAssistants.at(thisTA).addInstance(helpInstances.at(i));
	}

	cout << left << setw(20) << "Name";
	cout << setw(10) << "Helped";
	cout << setw(10) << "Unique";
	cout << setw(15) << "Most Helped";
	cout << endl;
	cout << setfill('-') << setw(80) << "-" << endl;
	for (int i = 0; i < teachingAssistants.size(); ++i) {
		cout << teachingAssistants.at(i).toString() << endl;
	}


}
