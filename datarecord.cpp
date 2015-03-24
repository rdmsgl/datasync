#include "datarecord.h"

void dataRecord::push_back(std::string value)
{
	fields.push_back(value);
	numFields=fields.size();
}

void dataRecordSet::readFile(std::string fname)
{
	std::ifstream input(fname);
	std::stringstream line;
	std::string str;
	// Read Column labels
	std::getline(input,str);
	line.str(str);
	while (line.good())
	{
		std::getline(line,str,',');
		columnLabels.push_back(str);
	}
	// Read data
	records.resize(30000);
	int idx=0;
	std::getline(input,str);
	line.str(str);
	line.clear();
	line.seekg(0);
	while (input.good())
	{
		if (idx==records.size())
			records.resize(records.size()*2);
		while (line.good())
		{
			std::getline(line,str,',');
			records[idx].push_back(str);
		}
		idx++;
		std::getline(input,str);
		line.str(str);
	}
	records.resize(idx);
	numRecords=idx;
	input.close();
}
void dataRecordSet::writeFile(std::string fname)
{
	std::ofstream output(fname);
	// Write Column labels
	output << columnLabels;
	// Read data
	auto current=records.begin();
	while (current<records.end())
	{
		output << *current++;
	}
	output.close();
}

void dataRecordSet::setSyncField(int iField)
{
	syncFieldIdx=iField;
	syncFields.resize(numRecords);
	auto current=records.begin();
	while (current < records.end())
		(current++)->setSyncField(iField);
}
void dataRecord::setSyncField(int iField)
{
	syncFieldIdx=iField;
	syncFieldVal=StringToNumber<int>(fields.at(iField));
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
		if (current1->syncFieldInt()==current2->syncFieldInt())
		{
			current1->push_back(current2->syncFieldStr());
			current1++;
			current2++;
		}
		else if (current1->syncFieldInt()<current2->syncFieldInt())
		{
			current1++;
		}
		else
		{
			current2++;
		}
	}
}

void dataRecordSet::sort()
{
	std::sort(records.begin(),records.end());
}

std::ostream& operator<<(std::ostream& os,dataRecord record)
{
	auto current=record.fields.begin();
	os<<*current++;
	while (current<record.fields.end())
		os<<record.recSeparator<<*current++;
	os<<std::endl;
	return os;
}