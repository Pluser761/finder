#include <iostream>
#include <fstream>
#include <thread>
#include <string>

using namespace std;

string s0;
int work = 0;

void doWork(string);
void help();

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");	

	for (int i = 1; i < argc; i++) if (strcmp(argv[i], "справка") == 0) help();

	if (argc <= 2)
	{
		cout << "Недостаточно аргументов, для справки запустите программу с параметром \"справка\"." << endl;
		return 1;
	}
	s0 = argv[1];
	for (int i = 2; i < argc; i++)
	{
		thread t(doWork, (string)argv[i]);
		t.detach();
	}
	while (work != 0)
	{
		continue;
	}
	return 0;
}

void doWork(string s)
{
	work++;
	ifstream fin(s);
	if (!fin)
	{
		cout << "Не могу открыть файл " << s << ". Параметр \"справка\" для справки." << endl;
		fin.close();
		work--;
		return;
	}
	ofstream fout(string("out_") + s);
	while (fin)
	{
		string st, b, set = s0;
		int pos = string::npos;
		getline(fin, st);
		b = st;
		for (int i = 0; i < (int)(st.length() - 1); i++)
		{
			pos = set.find(st[i]);
			if (pos == string::npos) break;
			else set[pos] = '0';
		}
		if (pos != string::npos && b.length() > 3) fout << b << endl;
	}
	fout.close();
	fin.close();
	work--;
}

void help()
{
	cout << "\n\nПрограмма разработана для составления слов из набора символов.\n\n"
		 << "Особенности программы:\n"
		 << "Программа принимает некоторое количество аргументов (не меньше двух) вида\n"
		 << "\"набор символов слитно (обязательный параметр)\"\n"
		 << "\"словари (не меньше 1) в формате .txt,\n"
		 << "в которых каждое новое слово начинается с новой строки,\n"
		 << "например \'пример1.txt пример2.txt\' и так далее\".\n\n"
		 << "Таким образом запуск выглядит примерно так:\n"
		 << "program это_набор файл1.txt файл2.txt\n\n"
		 << "Программа проходит по каждой букве слова, взятого из словаря,\n"
		 << "и проверяет наличие этой буквы в наборе.\n"
		 << "Если буква в наличии, отмечает её, чтобы не учитывать\n"
		 << "в следующем сравнении, если такой буквы нет, переходит к следующему слову.\n\n"
		 << "Работает на потоках, число которых равно количеству словарей.\n"
		 << "Результаты сохраняет раздельно для каждого словаря,\n"
		 << "в файлах с названием словаря и префиксом out_.\n\n"
		 << "Для исключения из поиска звукоподражаний, предлогов, союзов и других\n"
		 << "программа ищет слова с длинной минимум 4 символа.\n";
	exit(0);
}