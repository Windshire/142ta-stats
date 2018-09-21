#include <string>

using namespace std;

class Instance {
protected:
	string taName;
	string student;
	int duration; //in seconds
	bool valid;

public:
	void addTaName(string taName) {
		this->taName = taName;
	}
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
