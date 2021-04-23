
#include<iostream>
#include<fstream>
#include <vector>
#include "Salesman.h"

int Salesman::Salesman_input( char* argv) 
{
	/**
		\brief Function to read input data

		Function reads from the input file the data necessary fo the correct operation of the program.
		\param[in] char* argv - pointer to the source file.
		\return start - Initial vertex value.
		\throw runtime_error if the function cannot open file or there are negative values in the input file values.
	*/

	char* ptr = argv;
	ifstream fin;
	fin.open( ptr );
	if (!(fin.is_open())) 
	{
		throw std::runtime_error("Error, the file could not be open. Check the correctness of the file name");
		return EXIT_FAILURE;
	}
	int i = 0;
	int j = 0;
	fin >> Graph_size;
	fin >> Start;
	Finish = Start;
	Graph = new int*[Graph_size];
	for (int i = 0; i < Graph_size; i++)
	{
		Graph[i] = new int[Graph_size];
	}
	for (i = 0; i < Graph_size; i++)
	{
		for (j = 0; j < Graph_size; j++)
		{
			fin >> Graph[i][j];
			if (Graph[i][j] < 0)
			{
				throw std::runtime_error("Error, invalid input, please correct matrix and try again");
				return EXIT_FAILURE;
			}
		}
	
	}
	for (int i = 0; i < Graph_size; i++) 
	{
		Marked.push_back(0);
	}
	for (int i = 0; i <= Graph_size; i++)
	{
		Way.push_back(0);
	}
	for (int i = 0; i <= Graph_size; i++) 
	{
		Total_way.push_back(0);
	}
	fin.close();
	return(Start);
}
void Salesman::Brute_force( int Start ) 
{
	/**
	\brief Brute Force function

	Brute Force function for the traveling salesman problem.
	\param[in] int start - Value of the current vertex under concideration..
	\return None.
	*/
	if ((start == Finish) && (index == Graph_size)) //Если вернулись в исходную вершину и обошли весь граф
	{
		Way[Index ] = Start; //Добавляем стартовую вершину в конец пути
		Way_sum += Graph[Start][From];//Добавляем стоимость последнего ребра к общей сумме
		if (Way_sum < Total_price)//Если посчитанная стоимость меньше минимальной на данный момент 
		{
			Total_price = Way_sum;//Запоминаем эту стоимость как наименьшую
			for (int i = 0; i <= Graph_size; i++)
			{
				Total_way[i] = Way[i]; //Записываем маршрут как оптимальный
			}
		}
	
		Way_sum -= Graph[Start][From];
		return;
	}

	if (Marked[Start] == 1) //Если в этой вершине уже были, то в ней делать нечего
	{
		return;
	}

	if (Index > 0) 
	{
		Way_sum += Graph[Start][From];//Добавляем стоимость ребра в общую сумму
	}

	Marked[Start] = 1;//Помечаем, что в этой вершине мы уже были
	Way[Index] = Start;//Записываем эту вершину в путь
	Index++;
	for (int j = 0; j < Graph_size; j++)//Запускаем поиск пути из этой вершины
	{
		if (Graph[Start][j] != 0)
		{
			From = Start;
			Brute_force(j);
		}
	}
	Index--;
	Marked[Start] = 0;

	if (Start != finish) 
	{
		From = Way[Index - 1];
	}

	Way_sum -= Graph[Start][From];
	return;
}
void Salesman::Screen_output() 
{
	/**
	\brief Display gfunction.

	Function displays the result of the work on the screen.
	\return None.
	*/
	int i = 0;
	cout << "Total prise = " << Total_price << endl;
	cout << Total_way[0];
	for ( i = 1; i <= Graph_size; i++) 
	{
		cout << "->";
		cout << Total_way[i];
		
	}
}
void Salesman::File_output() 
{
	/**
	\brief File output  function.

	Function displays the result of the work to the genearted text file.
	\return None.
	*/
	int i = 0;
	ofstream fout("C:\\Users\\Эльдо\\Documents\\1SalesmanData\\Salesman_output.txt");
	fout << "Total price of way is " << Total_price << endl;
	fout << "The most optimal rout is ";
	fout << Total_way[0];
	for (i = 1; i <= Graph_size; i++)
	{
		fout << "->";
		fout << Total_way[i];

	}
	fout.close();
}
void Salesman::Graphviz_output() 
{
	/**
	\brief Graphviz output function.

	Function displays the result of the work to the generated file of a format .gv compatible with Graphviz.
	\return None.
	*/
	ofstream  fout("C:\\Users\\Эльдо\\Documents\\1SalesmanData\\Graphviz_output.gv");

	int i = 0;
	int j = 0;
	int c = 1;
	int k = 0;
	int count = 0;
	fout << "graph OutputGraph" << endl << "{" << endl;
	for (i = 0; i < Graph_size; i++)
	{
		fout << i << ";";
	}
	fout << endl;
	for (i = 0; i < Graph_size; i++) 
	{
		for (j = 0; j < Graph_size; j++)
		{
			if ((j != i) && (j > i))
			{
				for ( k = 0; k < Graph_size; k++)
				{
					if (((Total_way[k] == i) && (Total_way[c] == j)) || ((Total_way[k] == j) && (Total_way[c] == i)))
					{
						count++;
					}
					c++;
				}
				if (count == 0) 
				{
					fout << i << "--" << j << ";" << endl;
				}
			}
			c = 1;
			count = 0;
		}
	}
	j = 1;
	fout << "edge [color=red];" << endl;
	for (i = 0; i < Graph_size; i++) 
	{
		fout << Total_way[i] << "--"<< Total_way[j] << "["<<"label=" << i << "]" << endl;
		j++;

	}
	fout << "}" << endl;
	fout.close();
}
		

