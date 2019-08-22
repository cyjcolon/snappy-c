#include <fstream>
#include <iostream>
#include "snappy-c.h"
#include <snappy.h>
using namespace std;
/*必须以二进制形式读取snappy文件，否则解压后数据后丢失*/
int main() 
{
	snappy_status status;
	ifstream infile("D:\\Documents\\Project\\snappy-c\\testdate\\02_1566302520750560048_94952974.snappy", ifstream::binary);
	infile.seekg(0, ios::end);
	size_t filelength = infile.tellg();//计算文件大小
	char* compressed=new char[filelength];
	infile.seekg(0);
	infile.read(compressed,filelength);
	//size_t length = snappy_max_compressed_length(filelength);
	size_t uncompressed_length;//解压后大小
	status = snappy_uncompressed_length(compressed,filelength,&uncompressed_length);//计算解压后的大小
	if (status != SNAPPY_OK)
	{
		printf_s("无效输入数据！");
		abort();
	}
	//string uncompressed;
	char* uncompressed_c = new char[uncompressed_length];
	
	status = snappy_uncompress(compressed, filelength, uncompressed_c, &uncompressed_length);//c方式解压
	if (status != SNAPPY_OK)
	{
		printf_s("解压失败！");
		abort();
	}
	//snappy::Uncompress(compressed, length, &uncompressed);//c++方式解压
	ofstream outfile("D:\\Documents\\Project\\snappy-c\\testdate\\02.log");
	//size_t unsizeof = sizeof(uncompressed);
	//size_t uncompressed_length = uncompressed->size();
	//char* ucchar=new char[uncompressed_length+1];
	//strcpy_s(ucchar,uncompressed_length+1,uncompressed->c_str());
	outfile.write(uncompressed_c,uncompressed_length);
	//cout << uncompressed << endl;
	delete[] compressed;
	delete[] uncompressed_c;
	infile.close();
	outfile.close();
}
