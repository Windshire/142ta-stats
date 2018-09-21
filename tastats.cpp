#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <iomanip>
#include <map>
#include <algorithm>

#include "HelpInstance.h"
#include "GradeInstance.h"
#include "TeachingAssistant.h"

const int NOT_FOUND = -1;
string currentDate;

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
	help.addTaName(cell);

	if (help.getTaName() == "") {
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
	out << left << setw(5) << "Num";
	out << setw(20) << "Name";
	out << setw(10) << "Helped";
	out << setw(10) << "Unique";
	out << setw(25) << "Most Helped";
	out << setw(15) << "Average Time";
	out << setw(15) << "Total Time";
	out << setw(15) << "Doubleclicks";
	out << endl;
	out << setfill('-') << setw(112) << "-" << endl;
	out << setfill(' ');
	int rank = 1;
	for (int i = 0; i < teachingAssistants.size(); ++i) {
		if (teachingAssistants.at(i).getName() != "Themselves") {
			string num = to_string(rank++) + '.';
			out << setw(5) << num << teachingAssistants.at(i).toString() << endl;
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

	sort(teachingAssistants.begin(), teachingAssistants.end());

	out << endl;
	out << "NUMBER OF ASSIGNMENTS GRADED" << endl;
	out << setfill('-') << setw(28) << "-" << endl;
	out << setfill(' ');

	for (int i = 0; i < teachingAssistants.size(); ++i) {
		if (teachingAssistants.at(i).getName() != "Not available") {
			out << left << "#";
			out << setw(5) << i+1;
			out << setw(25) << teachingAssistants.at(i).getName();
			out << setw(10) << teachingAssistants.at(i).getHelpInstanceTotal();
			out << setw(10) << teachingAssistants.at(i).getUniqueTotal() << endl;
		}
	}

	return out.str();
}

int main(int argc, char *argv[]) {

	string inLabFileLoc, gradingFileLoc;
	populateArgs(inLabFileLoc, gradingFileLoc, argc, argv);

	cout << PrintInLabResults(assignInstancesToTA(extractInLabFile(inLabFileLoc))) << endl;
	cout << PrintGradingResults(assignInstancesToTA(extractGradingFile(gradingFileLoc)));

}
