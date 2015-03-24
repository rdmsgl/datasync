
#include "datarecord.h"

void main(int argc, char* argv[])
{

	std::string inputFile1,inputFile2,outputFileName;
	dataRecordSet file1,file2;
	int syncField1,syncField2;
	std::vector<int> appCols;
	
	// TODO: read input arguments, argv, and define
	// input files, sync column, and columns to append
	if (argc>=7)
	{
		appCols.resize(argc-6);
		inputFile1.assign(argv[1]);
		inputFile2.assign(argv[2]);
		outputFileName.assign(argv[3]);
		syncField1=atoi(argv[4]);
		syncField2=atoi(argv[5]);
		int i=6;
		for (std::vector<int>::iterator itr=appCols.begin();itr<appCols.end();itr++)
		{
			*itr=atoi(argv[i++]);
		}
	}

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

