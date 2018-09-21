#include "Instance.h"

class HelpInstance : public Instance {
private:
	static string currentDate;
	string date;
	string student;
	//string helper;
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
	/*void addHelper(string helper) {
		this->helper = helper;
		this->taName = helper;
	}*/
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
	/*string getHelper() const {
		return helper;
	}*/
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
		out << taName << " ";
		out << enqueue << " ";
		out << dequeue << " ";
		out << wait << " ";
		out << type << " ";
		out << duration << " ";
		return out.str();
	}
};
