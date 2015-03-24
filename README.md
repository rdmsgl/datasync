# datasync
Read two column separated data files, appending the first with selected columns from the second, aligned by a selected mutual data column.

The current version is controlled using command line arguments, and contains no error checking. The command line arguments are: file1 file2 outputfile syncCol1 syncCol2 appendCol1 ...
1: file1 : the base csv file, to which additional data will be appended.
2: file2 : the csv file providing additional data
3: outputfile : the new file with combined data
4: syncCol1 : the column index (an integer) for file 1 of the column that synchronizes the two files
5: syncCol2 : the column index (an integer) for file 2 of the column that synchronizes the two files
6: appendCol1 : column index (an integer) for data in file 2 that will be appended to data from file 1.
7: ... additional column data can also be appended. this has not been tested.
