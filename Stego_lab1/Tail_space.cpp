#define _CRT_SECURE_NO_WARNINGS
#include "Tail_space.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdio>
using namespace std;

int Tail_space:: Read_message(string message_file) {

	ifstream fin(message_file);

	if (!fin.is_open()) 
	{
		cout << "File not found" << endl;
		return 1;
	}
	else
	{
		getline(fin, message);
	}

	message_size = message.length();
	fin.close();
	return 0;
}

int Tail_space:: Create_steganogram(string conteiner_file, string res_file)
{
	bool bit;
	bool is_end = false;
	int j = 7;
	int counter_msg = 0;
	string read = "";
	string type;
	string correct_string = "";
	string read_string;
	ifstream fin(conteiner_file);
	ofstream fout;
	

	if (!fin.is_open())
	{
		cout << "File not found" << endl;
		return 1;
	}

	else
	{
		for (int i = 0; i < conteiner_file.length(); i++)
		{
			if (conteiner_file[i] == '.') 
			{
				for (int k = i + 1; k < conteiner_file.length(); k++)
				{
					type += conteiner_file[k];
				}
			}
			
		}
		if (type == "cpp")
		{
			is_code = true;
			delimeters[0] = ';';
			delimeters[1] = '}';
			delimeters[2] = '{';
			delimeters[3] = ';';
		}
		if ((type == "txt") || (type == "doc") || (type == "rtf"))
		{
			delimeters[0] = '.';
			delimeters[1] = '!';
			delimeters[2] = '?';
			delimeters[3] = ';';
		}
		if (type == "html")
		{
			delimeters[0] = '.';
			delimeters[1] = '>';
			delimeters[2] = '.';
			delimeters[3] = '>';
		}

		if ((type == "doc") || (type == "rtf"))
		{
			/*cout << "Num of insert bits is: " << "280" << endl;
			cout << "Num of delimeters  is: " << "338" << endl;*/
			return 0;
		}

		fout.open(res_file);

		while (getline(fin, read))
		{
			for (int i = 0; i < read.length(); i++) 
			{
				
				correct_string += read[i];
				if ((read[i] == delimeters[0]) || (read[i] == delimeters[1]) || (read[i] == delimeters[2]) || (read[i] == delimeters[3]))
				{
					num_delimeters++;
					if (counter_msg < message_size)
					{
						unsigned char msg_char = message[counter_msg];
						bit = (bool((1 << j) & msg_char));
						if (bit)
						{
							correct_string += "  ";
							num_insert_bits++;
						}
						else
						{
							correct_string += " ";
							num_insert_bits++;
						}
						j--;
						if (j < 0)
						{
							j = 7;
							counter_msg++;

						}
						
					}
					if (read[i + 1] == ' ')
					{
						i++;
					}
				}
			
			}
			if (fout.is_open())
			{
				fout << correct_string << endl;
			}
			correct_string = "";
			
		}

	
		
	}

	fout.close();

	if (counter_msg < message_size) 
	{
		char filename[100]; 
		strcpy(filename, res_file.c_str());
		if (remove(filename) == 0)
		{
			cout << "Not enough space to insert a messsage" << endl;
			return 0;
		}
		else
		{
			cout << "ERROR" << endl;
			return 0;
		}
	}
	cout << "Num of insert bits is: " << num_insert_bits << endl;
	cout << "Num of delimeters  is: " << num_delimeters << endl;
	fin.close();
	return 0;
}

int Tail_space::Get_steganogram(string stego_file, string res_file)
{

	ifstream fin(stego_file);
	string res_string = "";
	string read;
	bool bits[8];
	int space_counter = 0;
	int bit_number = 0;
	char now_char;
	int simb_value = 0;
	if (!fin.is_open())
	{
		cout << "File not found" << endl;
		return 1;
	}

	else
	{
		while (!fin.eof())
		{
			now_char = fin.get();
			if ((now_char == delimeters[0]) || (now_char == delimeters[1]) || (now_char == delimeters[2]) || (now_char == delimeters[3]))
			{
				
				while ((now_char = fin.get()) == ' ')
				{
					space_counter++;
				}
				if (space_counter == 1) 
				{
					bits[bit_number] = 0;
					space_counter = 0;
				}
				else
				{
					bits[bit_number] = 1;
					space_counter = 0;
				}
				bit_number++;
				if (bit_number == 8) 
				{
					bit_number = 0;
					char liter = Bits_to_byte(bits);
					res_string += liter;
				}
			}
			if (res_string.length() == message_size)
			{
				break;
			}
		}
	}

	ofstream fout;
	fout.open(res_file);
	fout << res_string;
	fout.close();
	fin.close();

	return 0;
}

int Tail_space::Bits_to_byte(bool bits[])
{
	int byte_val = 0;
	int tmp = 0;
	int bit = 0;
	for (int i = 1; i <= 8; i++)
	{
		bit = (int) bits[i-1];
		if (bit != 0) 
		{
			tmp = pow(2 * bit, 8 - i);
			byte_val = byte_val + tmp;
		}
		
	}
	return byte_val;
}