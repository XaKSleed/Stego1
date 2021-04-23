#pragma once
#include <string>
using namespace std;
class Tail_space
{
	private:
	
		string message;
		int message_size;
		int num_insert_bits = 0;
		bool is_code = false;
		char delimeters[4];
		int num_delimeters = 0;
	public:

		Tail_space()
		{

		}
		
		~Tail_space() {}

		int Read_message(string message_file);
		int Create_steganogram(string conteiner_file, string res_file);
		int Get_steganogram(string stego_file, string res_file);
		int Bits_to_byte(bool bits[]);


};

