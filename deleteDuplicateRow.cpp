#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <random>
using namespace std;
//去除单个小文件中的重复行
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
//将大文件分成多个小文件
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
string strRand(int length) {			// length: 产生字符串的长度
	char tmp;							// tmp: 暂存一个随机数
	string buffer;						// buffer: 保存返回值

	// 下面这两行比较重要:
	random_device rd;					// 产生一个 std::random_device 对象 rd
	default_random_engine random(rd());	// 用 rd 初始化一个随机数发生器 random

	for (int i = 0; i < length; i++) {
		tmp = random() % 36;	// 随机一个小于 36 的整数，0-9、A-Z 共 36 种字符
		if (tmp < 10) {			// 如果随机数小于 10，变换成一个阿拉伯数字的 ASCII
			tmp += '0';
		}
		else {				// 否则，变换成一个大写字母的 ASCII
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