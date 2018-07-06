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
	int duration; //in seconds
	bool valid;

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
	int getDuration() const {
		return duration;
	}
	bool isValid() const {
		return valid;
	}
	void setValid(bool valid) {
		this->valid = valid;
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
		if (duration != "None") {
			const int MIN_LENGTH = 60;
			string min = duration.substr(0,2);
			string sec = duration.substr(3,2);
			this->duration = (stoi(min)*MIN_LENGTH) + stoi(sec);
		}
		else {
			this->duration = 0;
		}
	}
	string getCurrentDate() const {
		return currentDate;
	}
	string getHelper() const {
		return helper;
	}
	int getDuration() const {
		return duration;
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
	string anonymous;
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
	void addAnonymous(string anonymous) {
		this->anonymous = anonymous;
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
		if (help.isValid()) {
			helpInstances.push_back(help);
			studentsHelped[help.getStudent()]++;
		}
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
	int getTotalTime() const {
		double totalTime;
		for (int i = 0; i < helpInstances.size(); i++) {
			totalTime += helpInstances.at(i).getDuration();
		}
		return totalTime;
	}
	string doubleClicks() const {
		int doubleClicks;
		const int DOUBLE_CLICK_THRESHOLD = 10;
		for (int i = 0; i < helpInstances.size(); i++) {
			if (helpInstances.at(i).getDuration() < DOUBLE_CLICK_THRESHOLD) {
				doubleClicks++;
			}
		}
		return to_string(doubleClicks);
	}
	string getAverageTime() const {
		ostringstream out;
		out << fixed << setprecision(2) << setw(6) << (getTotalTime()/helpInstances.size()/60.0) << " mins";
		return out.str();
	}
	string getTotalHours() const {
		ostringstream out;
		out << fixed << setprecision(2) << setw(4) << (getTotalTime() / 60.0 / 60.0) << " hrs";
		return out.str();
	}
	string toString() const {
		ostringstream out;
		out << left;
		out << setw(20) << name;
		out << setw(10) << getHelpInstanceTotal();
		out << setw(10) << getUniqueTotal();
		out << setw(25) << getMostFrequent();
		out << setw(15) << getAverageTime();
		out << setw(15) << getTotalHours();
		out << setw(15) << doubleClicks();
		/*for (HelpInstance help : helpInstances) {
			out << help.getDuration() << endl;
		}*/
		return out.str();
	}
	bool operator < (const TeachingAssistant &comp) {
		return (this->getHelpInstanceTotal() > comp.getHelpInstanceTotal());
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

	help.setValid(true);

	return help;
}

GradeInstance parseGradingInstance(string row) {
	GradeInstance grade;
	string cell;

	istringstream line(row);

	//cout << "LINE: " << line.str() << endl;

	string date;
	getline(line, cell, ',');
	date += cell;
	getline(line, cell, ',');
	date += cell;
	grade.addDate(date);
	//cout << "date: " << date << endl;

	getline(line, cell, ',');
	grade.addAnonymous(cell);
	//cout << "anonymous: " << cell << endl;

	getline(line, cell, ',');
	grade.addStudent(cell);
	//cout << "student: " << cell << endl;

	getline(line, cell, ',');
	grade.addGrader(cell);
	//cout << "GRADER NAME: " << cell << endl;

	getline(line, cell, ',');
	grade.addAssignment(cell);
	//cout << "assignment: " << cell << endl;

	getline(line, cell, ',');
	grade.addBefore(cell);
	//cout << "previous grade: " << cell << endl;
	if(cell == "0/100") {
		//cout << "`````````````AYYY~~~~~~~~~~~~~~~~~~" << endl;
		grade.setValid(true);
	}
	else {
		grade.setValid(false);
	}

	getline(line, cell, ',');
	grade.addAfter(cell);
	//cout << "new grade: " << cell << endl;

	getline(line, cell, ',');
	grade.addCurrent(cell);
	//cout << "most recent grade: " << cell << endl;

	return grade;
}

string PrintInLabResults(vector<TeachingAssistant> teachingAssistants) {

	std::sort(teachingAssistants.begin(), teachingAssistants.end());

	ostringstream out;
	out << left << setw(20) << "Name";
	out << setw(10) << "Helped";
	out << setw(10) << "Unique";
	out << setw(25) << "Most Helped";
	out << setw(15) << "Average Time";
	out << setw(15) << "Total Time";
	out << setw(15) << "Doubleclicks";
	out << endl;
	out << setfill('-') << setw(110) << "-" << endl;
	for (int i = 0; i < teachingAssistants.size(); ++i) {
		if (teachingAssistants.at(i).getName() != "Themselves") {
			out << teachingAssistants.at(i).toString() << endl;
		}
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

vector<Instance> extractGradingFile(string fileloc) {
	vector<Instance> grading;
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

string PrintGradingResults(vector<TeachingAssistant> teachingAssistants) {
	ostringstream out;

	//vector<TeachingAssistant> temp = teachingAssistants;

	std::sort(teachingAssistants.begin(), teachingAssistants.end());

	out << endl;
	out << "NUMBER OF ASSIGNMENTS GRADED" << endl;
	out << setfill('-') << setw(110) << "-" << endl;
	out << setfill(' ');

	for (int i = 0; i < teachingAssistants.size(); ++i) {
		if (teachingAssistants.at(i).getName() != "Not available") {
			out << left << setw(20) << teachingAssistants.at(i).getName() << setw(10) << teachingAssistants.at(i).getHelpInstanceTotal() << endl;
		}
	}

	return out.str();
}

int main(int argc, char *argv[]) {

	string inLabFileLoc, gradingFileLoc;
	populateArgs(inLabFileLoc, gradingFileLoc, argc, argv);

	cout << PrintInLabResults(assignInstancesToTA(extractInLabFile(inLabFileLoc))) << endl;
	cout << PrintGradingResults(assignInstancesToTA(extractGradingFile(gradingFileLoc)));


/*
	ifstream gradingFile(gradingFileLoc);
	while(gradingFile.good()) {
		string line;
		getline(gradingFile, line);
		cout << line << endl;
	}
	*/

}
