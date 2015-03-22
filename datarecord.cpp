class dataRecord
{
public :
	void addField(std::string value);
	friend bool isMatch(dataRecord rec1, dataRecord rec2);
private :
	int numFields;
	std::vector<std::string> fields;
	std::vector<int> syncFieldNum;
}


class dataRecordSet
{
public :
	void readFile(std::string fname);
	void writeFile(std::string fname);
        void addColumn(dataRecordSet recSet, int col);
private :
        char recSeparator=",";
	int numRecords;
	std::vector<std::string> columnLabels;
	std::vector<dataRecord> records;
	std::string readRecord(std::stringstream input);
}


void dataRecord::addField(std::string value)
{
	fields.push_back(value);
        numFields=fields.size();
}

std::string dataRecordSet::readRecord(std::stringstream input)
{
	std::string rec;
	rec.resize(input.size());
	auto c=rec.begin();
        *c=input.getc();
	while (*c!=",") *(c++)=input.getc();
	rec.resize(c-rec.begin());
}

