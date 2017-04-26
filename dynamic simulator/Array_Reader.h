#ifndef ARRAY_READER_H
#define ARRAY_READER_H
#include <fstream>
using namespace std;
class Array_Reader
{
private:
	std::ifstream fin;
public:
//	template<class T>
//	T* read(const string &file_name, const int array_size);
	float* read(const string &file_name, const int array_size);
	//void read(const string &file_name, const int array_size);
};



template<class T>
void copy_array(T* des, T* src,int n) {
	for (int i = 0; i < n; i++) {
		des[i] = src[i];
	}

}

template<class T>
T* read(const string &file_name, int& size) {
	ifstream fin(file_name);
	vector<T> ret_v;
	size = 0;
	while (!fin.eof()) {
		ret_v.push_back(0);
		fin >> ret_v[size];
		size++;
	}
	T* ret = new T[size];
	copy_array(ret, ret_v.data(), size);
	fin.close();
	return ret;
}


template<class T>
void read_obj(const string& file_name, int& vN, T* &verts, int& tN, int* &tri) {
	ifstream fin(file_name);
	vN = 0;
	string line;
	int vert_arr_size = 0;
	while (getline(fin,line)){
		if (line == "#vertex") {
			int row_size;
			fin >> vN >> row_size;
			verts = new T[vN*row_size];
			for (int i = 0; i < vN; i++) {
				for (int j = 0; j < row_size; j++) {
					fin >> verts[i*row_size+j];
				}
			}
		}
		else if (line == "#triangle") {
			fin >> tN ;
			tri = new int[tN*3];
			for (int i = 0; i < tN; i++) {
				for (int j = 0; j < 3; j++) {
					fin >> tri[i*3+j];
				}
			}

		}
	}

}


//float* read(const string &file_name, const int col_size,const int row_size=1) {
//	ifstream fin(file_name);
//	float* ret = new float[col_size*row_size];
//	int col = 0;
//	string line;
//	while (!fin.eof()) {
//		for (int i = 0; i < row_size; i++) {
//			fin >> ret[col*row_size + i];
//		}
//		col++;
//	}
//	fin.close();
//	return ret;
//}
//
//template<class T>
//inline T * Array_Reader::read(const string & file_name, const int array_size)
//{
////	fin.open(file_name);
////	ret = new T[array_size];
////	for (int i = 0; i < array_size; i++) {
////		fin >> ret[i];
////	}
////	fin.close();
////	return ret;
//	return nullptr;
//}


#endif
