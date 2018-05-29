#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


class HelpInstance {
private:
	string date;
	string student;
	string helper;
	string enqueue;
	string dequeue;
	string wait;
	string type;
	string duration;

public:
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
	string getHelper() {
		return helper;
	}
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
public:
	TeachingAssistant(string name) {
		this->name = name;
	}
	void addInstance(HelpInstance help) {
		helpInstances.push_back(help);
	}
	string getName() const {
		return name;
	}
	string toString() {
		ostringstream out;
		out << name;
		out << " helped students ";
		out << helpInstances.size();
		out << " times!";
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

int main() {
	ifstream file("il1.csv");
	string row;
	string currentDate;
	vector<HelpInstance> helpInstances;
	vector<TeachingAssistant> teachingAssistants;

	while (file.good()) {
		getline(file, row);
		if (row != ",,,,,,," && row != "") {
			HelpInstance help;
			istringstream line(row);
			string cell;

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

			helpInstances.push_back(help);
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

	for (int i = 0; i < teachingAssistants.size(); ++i) {
		cout << teachingAssistants.at(i).toString() << endl;
	}
}
