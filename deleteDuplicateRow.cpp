#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <random>
using namespace std;
//ȥ������С�ļ��е��ظ���
void deleteDuplicateRow(string &originFile, string &resFile) {
	string curRow;
	unordered_set<string>se;
	ifstream fsOrigin(originFile);
	ofstream fsRes(resFile,ofstream::app);
	while (getline(fsOrigin,curRow))
	{
		if (se.find(curRow)==se.end())
		{
			se.insert(curRow);
			fsRes << curRow<<endl;
		}
	}
}
//�����ļ��ֳɶ��С�ļ�
vector<string> splitBigfile(string &originFile,int splitSize) {
	 vector<string>smallFiles(splitSize);
	string smallFileName;
	for (int i=0;i<splitSize;++i)
	{
		smallFileName = to_string(i) + "thSmallFile.txt";
		smallFiles[i] = smallFileName;
	}
	string curRow;
	ifstream fsOrigin(originFile);
	
	while (getline(fsOrigin,curRow))
	{
		auto hashcode=hash<string>()(curRow);
		fstream fsSmall(smallFiles[hashcode%splitSize], fstream::app);
		fsSmall<< curRow<<endl;
	}
	return smallFiles;
}
void handleSmallFiles(vector<string>& smallFiles, string &resFile) {
	vector<string> curRess(smallFiles.size());
	for (int i=0;i<smallFiles.size();++i)
	{
		string curResName = to_string(i) + "thCurResName.txt";
		curRess[i] = curResName;
		deleteDuplicateRow(smallFiles[i], curRess[i]);
	}
	ofstream fsRes(resFile,ofstream::app);
	
	for (auto &file:curRess)
	{
		fstream fs(file);
		string curRow;
		while (getline(fs,curRow))
		{
				fsRes << curRow << endl;
		}
	}
}
string strRand(int length) {			// length: �����ַ����ĳ���
	char tmp;							// tmp: �ݴ�һ�������
	string buffer;						// buffer: ���淵��ֵ

	// ���������бȽ���Ҫ:
	random_device rd;					// ����һ�� std::random_device ���� rd
	default_random_engine random(rd());	// �� rd ��ʼ��һ������������� random

	for (int i = 0; i < length; i++) {
		tmp = random() % 36;	// ���һ��С�� 36 ��������0-9��A-Z �� 36 ���ַ�
		if (tmp < 10) {			// ��������С�� 10���任��һ�����������ֵ� ASCII
			tmp += '0';
		}
		else {				// ���򣬱任��һ����д��ĸ�� ASCII
			tmp -= 10;
			tmp += 'A';
		}
		buffer += tmp;
	}
	return buffer;
}

int main() {
	
	string filename;
	cin >> filename;

	string resFilename;
	cin >> resFilename;
	/*ofstream fsOrigin(filename,ofstream::app);
	for (int i=0;i<1000000;++i)
	{
		string cur = strRand(100);
		fsOrigin << cur<<endl;
		fsOrigin << cur << endl;
	}*/
	//deleteDuplicateRow(filename, resFilename);
	int splitSize = 10;
	vector<string>smallFiles=splitBigfile(filename,splitSize);
	handleSmallFiles(smallFiles,resFilename);
	string s;
	ifstream fs(resFilename);
	while (getline(fs,s))
	{
		cout << s;
	}
	fs.close();
}