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
