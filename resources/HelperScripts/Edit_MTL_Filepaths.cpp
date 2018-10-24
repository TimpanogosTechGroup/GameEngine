#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;

void getDir(const char* d, vector<string> & f);


// current filepaths for files:
// Send From:
// ..\src\Model
// Send to:
// Model\

int main() {
	vector<string> files;
	vector<string> lineData;
	string fpath = "";
	string targetPath = "";
	string tmp = "";
	string desiredFileType = "mtl";

	string line = "";
	string lineTmp = "";
	ifstream file;

	ofstream newFile;

	cout << "Enter filepath containing all .mtl files to change: ";
	cin >> fpath;
	cout << endl;

	cout << "Enter the filepath (relative to project file) of the associated texture files: ";
	cin >> targetPath;
	cout << endl;

	getDir(fpath.c_str(), files);

	for (int i = 0; i < files.size(); i++) {
		files.at(i) = files.at(i).substr(0, files.at(i).length() - 1);
		tmp = files.at(i).substr(files.at(i).length() - 3);
		if (tmp == desiredFileType) {
			file.open(files.at(i));

			cout << files.at(i) << endl;

			while (getline(file, line)) {
				lineData.push_back(line + "\n");
			}
			file.close();

			newFile.open(files.at(i));

			for (int n = 0; n < lineData.size(); n++) {
				lineTmp = lineData.at(n).substr(0, 6);

				if (lineTmp == "map_Kd") {
					lineData.at(n) = lineData.at(n).substr(0, 7) + targetPath + lineData.at(n).substr(7);
				}

				newFile << lineData.at(n);
			}

			newFile.close();
		}
	}

	system("PAUSE");

	return 0;
}

void getDir(const char* d, vector<string> & f)
{
	FILE* pipe = NULL;
	string pCmd = "dir /B /S " + string(d);
	char buf[256];

	if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
	{
		cout << "Shit" << endl;
		return;
	}

	while (!feof(pipe))
	{
		if (fgets(buf, 256, pipe) != NULL)
		{
			f.push_back(string(buf));
		}

	}

	_pclose(pipe);


}