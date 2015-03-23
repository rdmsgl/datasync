#include <sstream>
#include <fstream>
#include <vector>

template <typename T>
T StringToNumber ( const string &Text )//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

class dataRecord
{
public :
	void addField(std::string value);
	friend bool isMatch(dataRecord rec1, dataRecord rec2);
	std::string field(int iField) { return fields.at(iField); };
private :
	int numFields;
	std::vector<std::string> fields;
}


class dataRecordSet
{
public :
	void readFile(std::string fname);
	void writeFile(std::string fname);
        void addColumn(dataRecordSet recSet, int col);
	void setSyncField(int iField);
private :
        char recSeparator=",";
	int numRecords, syncFieldNum;
	std::vector<std::string> columnLabels;
	std::vector<dataRecord> records;
	std::vector<int> syncFields;
	std::string readRecord(std::stringstream input);
}
