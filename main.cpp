
void main(int argc, char* argv[])
{

	std::string inputFile1,inputFile2,outputFileName;
        dataRecordSet file1,file2;
	vector<int> appCols;
	
	file1.readFile(inputFile1);
	file2.readFile(inputFile2);

	file1.setSyncField(syncField1);
	file2.setSyncField(syncField2);

        for (int i=0; i<appCols.size(); i++)
        { 
           file1.addColumn(file2,appCols(i));
	}
	
	file1.writeFile(outputFileName);
}

