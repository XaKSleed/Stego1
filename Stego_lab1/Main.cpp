#include<iostream>
#include<fstream>
#include <vector>
#include "Tail_space.h"
using namespace std;


void main(int argc, char* argv[])
{
	
	Tail_space ex1;
	
	ex1.Read_message("Message1.txt");
	ex1.Create_steganogram("Salesman.cpp", "newSalesman.cpp");
	ex1.Get_steganogram("newSalesman.cpp", "resMessageCPP.txt");
	cout << "END" << endl;
	getchar();
}