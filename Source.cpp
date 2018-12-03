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

	for (int i = 1; i < argc; i++) if (strcmp(argv[i], "�������") == 0) help();

	if (argc <= 2)
	{
		cout << "������������ ����������, ��� ������� ��������� ��������� � ���������� \"�������\"." << endl;
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
		cout << "�� ���� ������� ���� " << s << ". �������� \"�������\" ��� �������." << endl;
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
	cout << "\n\n��������� ����������� ��� ����������� ���� �� ������ ��������.\n\n"
		 << "����������� ���������:\n"
		 << "��������� ��������� ��������� ���������� ���������� (�� ������ ����) ����\n"
		 << "\"����� �������� ������ (������������ ��������)\"\n"
		 << "\"������� (�� ������ 1) � ������� .txt,\n"
		 << "� ������� ������ ����� ����� ���������� � ����� ������,\n"
		 << "�������� \'������1.txt ������2.txt\' � ��� �����\".\n\n"
		 << "����� ������� ������ �������� �������� ���:\n"
		 << "program ���_����� ����1.txt ����2.txt\n\n"
		 << "��������� �������� �� ������ ����� �����, ������� �� �������,\n"
		 << "� ��������� ������� ���� ����� � ������.\n"
		 << "���� ����� � �������, �������� �, ����� �� ���������\n"
		 << "� ��������� ���������, ���� ����� ����� ���, ��������� � ���������� �����.\n\n"
		 << "�������� �� �������, ����� ������� ����� ���������� ��������.\n"
		 << "���������� ��������� ��������� ��� ������� �������,\n"
		 << "� ������ � ��������� ������� � ��������� out_.\n\n"
		 << "��� ���������� �� ������ ���������������, ���������, ������ � ������\n"
		 << "��������� ���� ����� � ������� ������� 4 �������.\n";
	exit(0);
}