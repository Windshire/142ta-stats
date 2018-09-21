
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
