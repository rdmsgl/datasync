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
	while (*c!=recSeparator) *(c++)=input.getc();
	rec.resize(c-rec.begin());
}

void dataRecordSet::readFile(std::string fname)
{
	std::istream input(fname);
	std::stringstream line;
	// Read Column labels
	line=input.getline();
	while (line.good())
	{
		columnLabels.addField(readRecord(line));
	}
	// Read data
	auto current=records.begin();
	line=input.getline();
	while (input.good())
	{
		if (current>=records.end())
			records.resize(records.size()+100);
		while (line.good())
		{
			current->addField(readRecord(line));
		}
		current++;
		line=input.getline();
	}
	records.resize(current-records.begin());
}

void dataRecordSet::setSyncField(int iField)
{
	syncFieldNum=iField;
	syncFields.resize(0);
	syncFields.reserve(numRecords);
	auto current=records.begin()
	while (current < records.end())
		syncFields.push_back(StringToNumber(current->fields.at(iField)));
}

void dataRecordSet::addColumn(dataRecordSet file2, int iField)
{
	if (!this->isSorted())
		this->sort();
	if (!file2.isSorted())
		file2.sort();
	auto current1= this->records.begin();
	auto current2= file2.records.begin();
	while (current1 < this->records.end())
	{
		if (current1->syncField==current2->syncField)
		{
			current1->addField(current2->syncField);
			current1++;
			current2++;
		}
		else if (current->syncField<current2->syncField)
		{
			current1++;
		}
		else
		{
			current2++;
		}
	}
}

