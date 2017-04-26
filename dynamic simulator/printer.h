#ifndef PRINTER_H
#define  PRINTER_H
#include <fstream>





template<class T>
void print_2d_array(ofstream& fout,T* arr, int col, int row)
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			fout << arr[i*row + j] << "	";
		}
		fout << endl;
	}
	fout << endl;
}

void print_header(ofstream& fout, const string& file, const string& type, int col, int row)
{
	fout << file << "	" << type << "	" << col << "	" << row << "	"<< endl;
}

template<class T>
void print_2d_array_2_file(const string& file, const string& type, T*arr,int col, int row) {
	ofstream fout(file);
	print_header(fout,file, type,col, row);
	print_2d_array(arr, col, row);
}

template<class T>
void print_1d_array_series_2_file(const string& file, const string& type, T*arr, int col,int row) {
	static ofstream fout(file);
	static int count = 0;
	if (count == 0) {
		print_header(fout, file, type, col, row);
	}
	print_2d_array(fout,arr, col, row);
	count++;

}

#endif
