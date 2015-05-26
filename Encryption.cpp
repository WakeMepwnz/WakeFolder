// Crypt.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale( LC_ALL, "rus" );

	cout << "Введите путь к файлу: ";

	const int SIZE_PATH = 260;
	char path[ SIZE_PATH ] = { 0 };
	cin.getline( path, sizeof( path ) - 1 );

	fstream f( path, ios::binary | ios::in | ios::out );
	if( !f )
	{
		cout << "Ошибка открытия файла";
		cin.get();
		return 1;
	}

	f.seekg( 0, ios::end );

	size_t size_file = f.tellg();

	f.clear();

	f.seekg( 0, ios::beg );

	unsigned char *pbuf = new ( nothrow ) unsigned char[ size_file ];
	if( !pbuf )
	{
		cout << "Ошибка выделения памяти";
		f.close();
		cin.get();
		return 2;
	}

	f.read( ( char* )pbuf, size_file );

	//upd
	string key;
	int k;
	 cout << "Введите ключ на русском языке"<< endl;
	 getline(cin, key);
	 k = key.length();
	 for (int i=k; i<size_file; i++)
	 {
        key=key+key[i%k];
     }
	
	for( unsigned int i = 0; i < size_file; i++ )
		pbuf[ i ] ^= key[i%k];


	f.clear();

	f.seekg( 0, ios::beg );

	f.write( ( const char* )pbuf, size_file );

	f.close( );

	delete [ ] pbuf;

	return 0;
}