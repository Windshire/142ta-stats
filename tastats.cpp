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

class Instance {
protected:
	string taName;
	string student;
public:
	void addStudent(string student) {
		this->student = student;
	}
	string getTaName() {
		return taName;
	}
	string getStudent() const {
		return student;
	}
};

class HelpInstance : public Instance {
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
	void addHelper(string helper) {
		this->helper = helper;
		this->taName = helper;
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

class GradeInstance : public Instance {
private:
	string date;
	string student;
	string grader;
	string assignment;
	string before;
	string after;
	string current;
public:
	void addDate(string date) {
		this->date = date;
	}
	void addGrader(string grader) {
		this->grader = grader;
		this->taName = grader;
	}
	void addAssignment(string assignment) {
		this->assignment = assignment;
	}
	void addBefore(string before) {
		this->before = before;
	}
	void addAfter(string after) {
		this->after = after;
	}
	void addCurrent(string current) {
		this->current = current;
	}
};

class TeachingAssistant {
private:
	string name;
	vector<Instance> helpInstances;
	map<string, int> studentsHelped;
public:
	TeachingAssistant(string name) {
		this->name = name;
	}
	void addInstance(Instance help) {
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
	string toString() const {
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

HelpInstance parseHelpInstance(string row) {
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

GradeInstance parseGradingInstance(string row) {
	GradeInstance grade;
	string cell;

	istringstream line(row);

	getline(line, cell, ',');
	grade.addDate(cell);

	getline(line, cell, ',');
	grade.addStudent(cell);

	getline(line, cell, ',');
	grade.addGrader(cell);

	getline(line, cell, ',');
	grade.addAssignment(cell);

	getline(line, cell, ',');
	grade.addBefore(cell);

	getline(line, cell, ',');
	grade.addAfter(cell);

	getline(line, cell, ',');
	grade.addCurrent(cell);

	return grade;
}

string PrintInLabResults(const vector<TeachingAssistant> &teachingAssistants) {
	ostringstream out;
	out << left << setw(20) << "Name";
	out << setw(10) << "Helped";
	out << setw(10) << "Unique";
	out << setw(15) << "Most Helped";
	out << endl;
	out << setfill('-') << setw(80) << "-" << endl;
	for (int i = 0; i < teachingAssistants.size(); ++i) {
		out << teachingAssistants.at(i).toString() << endl;
	}
	return out.str();
}

vector<Instance> extractInLabFile(string fileloc) {
	vector<Instance> inLab;
	ifstream inLabFile;
	string row;

	inLabFile.open(fileloc);

	while (inLabFile.good()) {
		getline(inLabFile, row);
		if (row != ",,,,,,," && row != "") {
			inLab.push_back(parseHelpInstance(row));
		}
	}

	inLabFile.close();

	return inLab;
}

vector<GradeInstance> extractGradingFile(string fileloc) {
	vector<GradeInstance> grading;
	ifstream gradingFile;
	string row;

	gradingFile.open(fileloc);

	while (gradingFile.good()) {
		getline(gradingFile, row);
		if (row != ",,,,,,," && row != "") {
			grading.push_back(parseGradingInstance(row));
		}
	}

	gradingFile.close();

	return grading;
}

vector<TeachingAssistant> assignInstancesToTA(vector<Instance> instances) {
	vector<TeachingAssistant> teachingAssistants;

	for (int i = 0; i < instances.size(); ++i) {
		if (!contains(teachingAssistants, instances.at(i).getTaName())) {
			if (instances.at(i).getTaName() == "") {
				continue;
			}
			else {
				teachingAssistants.push_back(TeachingAssistant(instances.at(i).getTaName()));
			}
		}
		unsigned int thisTA = index(teachingAssistants, instances.at(i).getTaName());
		teachingAssistants.at(thisTA).addInstance(instances.at(i));
	}

	return teachingAssistants;
}

void populateArgs(string &inLabFile, string &gradingFile, int argc, char *argv[]) {
	if(argc == 1) {
		inLabFile = "inlab.csv";
		gradingFile = "grading.csv";
	}
	else if (argc == 3) {

	}
}

int main(int argc, char *argv[]) {

	string inLabFileLoc, gradingFileLoc;
	populateArgs(inLabFileLoc, gradingFileLoc, argc, argv);

	cout << PrintInLabResults(assignInstancesToTA(extractInLabFile(inLabFileLoc)));

	vector<GradeInstance> grades = extractGradingFile(gradingFileLoc);

	cout << grades.size() << endl;

/*
	ifstream gradingFile(gradingFileLoc);
	while(gradingFile.good()) {
		string line;
		getline(gradingFile, line);
		cout << line << endl;
	}
	*/

}
