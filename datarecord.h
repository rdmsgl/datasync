#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

template <typename T>
T StringToNumber ( const std::string &Text ) //Text not by const reference so that the function can be used with a character array as argument
{                               
	std::stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

class dataRecord
{
public :
	dataRecord() { recSeparator = ',';};
	void push_back(std::string value);
	friend bool isMatch(dataRecord rec1, dataRecord rec2);
	inline std::string field(int iField) { return fields.at(iField); };
	inline void syncField(int val) { syncFieldVal=val; };
	inline int syncFieldInt() { return syncFieldVal; };
	inline std::string syncFieldStr() { return field(syncFieldIdx); };
	inline bool operator<(const dataRecord &b) {return this->syncFieldVal<b.syncFieldVal;};
	friend std::ostream& operator<<(std::ostream& os, dataRecord);
	void setSyncField(int iField);
private :
	char recSeparator;
	int numFields;
	int syncFieldVal;
	int syncFieldIdx;
	std::vector<std::string> fields;
};


class dataRecordSet
{
public :
	dataRecordSet() { recSeparator = ','; isSortBool=false;};
	void readFile(std::string fname);
	void writeFile(std::string fname);
	void addColumn(dataRecordSet recSet, int col);
	void setSyncField(int iField);
	inline bool isSorted() { return isSortBool; };
private :
	char recSeparator;
	int numRecords, syncFieldIdx;
	bool isSortBool;
	dataRecord columnLabels;
	std::vector<dataRecord> records;
	std::vector<int> syncFields;
	void sort();
};
