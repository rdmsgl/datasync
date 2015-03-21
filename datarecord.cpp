class dataRecord
{
public :
	void addField(std::string value);
	friend bool isMatch(dataRecord rec1, dataRecord rec2);
private :
	int numFields;
	std::vector<std::string> fields;
	std::vector<int> id;
}


class dataRecordSet
{
public :
	void readFile(std::string fname);
	void writeFile(std::string fname);
        void addColumn(dataRecordSet recSet, int col);
private :
	int numRecords;
	std::vector<dataRecord> records;
}
