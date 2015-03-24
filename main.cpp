
#include "datarecord.h"

void main(int argc, char* argv[])
{

	std::string inputFile1,inputFile2,outputFileName;
	dataRecordSet file1,file2;
	int syncField1,syncField2;
	std::vector<int> appCols;
	
	// TODO: read input arguments, argv, and define
	// input files, sync column, and columns to append

	// AND/OR: use Q&A format to define these details

	file1.readFile(inputFile1);
	file2.readFile(inputFile2);

	file1.setSyncField(syncField1);
	file2.setSyncField(syncField2);

        for (size_t i=0; i<appCols.size(); i++)
        { 
           file1.addColumn(file2,appCols[i]);
	}
	
	file1.writeFile(outputFileName);
}

