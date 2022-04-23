#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	fstream file;
	file.open("clientc.c",ios::out);
	if(!file)
	{
		cout<<"client missing");
		file.close();
	}
	
	file.open("server.c",ios::out);
	if(!file)
	{
		cout<<"server missing");
		file.close();
	}

	//something something tactactoe file

	return 0;
}