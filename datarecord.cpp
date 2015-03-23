#include "datarecord.h"

void dataRecord::addField(std::string value)
{
	fields.push_back(value);
        numFields=fields.size();
}

std::string dataRecordSet::readRecord(std::stringstream input)
{
	std::string rec;
	rec.resize(input.str.size());
	auto c=rec.begin();
        *c=input.get();
	while (*c!=recSeparator) *(c++)=input.get();
	rec.resize(c-rec.begin());
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
	auto current=records.begin();
	std::getline(input,str);
	line.str(str);
	while (input.good())
	{
		if (current>=records.end())
			records.resize(records.size()+100);
		while (line.good())
		{
			std::getline(line,str,',');
			current->addField(str);
		}
		current++;
		std::getline(input,str);
		line.str(str);
	}
	records.resize(current-records.begin());
}

void dataRecordSet::setSyncField(int iField)
{
	syncFieldNum=iField;
	syncFields.resize(0);
	syncFields.reserve(numRecords);
	auto current=records.begin();
	while (current < records.end())
		syncFields.push_back(StringToNumber<int>(current->field(iField)));
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

