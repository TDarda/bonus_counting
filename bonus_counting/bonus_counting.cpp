#include<iostream>
#include<map>
#include<vector>
#include<iomanip>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <locale.h>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>

#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13


using namespace std;

map<string, int>szablon;
deque<string>wynik;
multimap<string, int>premia;

fstream plik;

vector<string>menu1 = {
		"wczytaj szablon","stwórz szablon","oblicz premie","wyjdź"
};
vector<string>menu2 = {
	"stwórz/wczytaj","zapisz","cofnij"
};

string path = "";

template<class T>
void print(T start, T stop)
{
	system("cls");
	T tmp = start;
	while (tmp != stop)
	{
		cout << tmp->first << " " << tmp->second << endl;
		tmp++;
	}
}

template<class T>
void printer(T start, T stop)
{
	system("cls");
	T tmp = start;
	while (tmp != stop)
	{
		cout << *tmp << endl;
		tmp++;
	}
}

void header()
{
	string h = "Liczenie Premii by td";
	string fill = "=";
	cout << endl << endl << endl;
	cout << setw(40 - fill.size()) << setfill('=') << fill << endl;
	cout << setfill(' ');
	cout << setw(40 - h.size() / 2) << h << setw(40 - h.size() / 2) << endl;
	cout << setw(40 - fill.size()) << setfill('=') << fill << endl;
	cout << setfill(' ');
}

int menu(int pos, vector<string>menu1)
{

	int tmp;

	static int returner = 0;
	char tr;
	switch (pos)
	{
	case 0:
		system("cls");
		tmp = 1;
		header();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout << menu1[0] << setw(40 - menu1[0].size()) << "[" << tmp << "]" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		for (vector<string>::iterator it = menu1.begin() + 1; it != menu1.end(); it++)
		{
			cout << *it << setw(40 - it->size()) << "[" << ++tmp << "]" << endl;
		}
		tr = _getch();
		if (tr == KEY_UP) { menu(0, menu1); break; };
		if ((tr == KEY_DOWN) || (tr == 's')) { menu(1, menu1); break; };
		if (tr == ENTER) { returner = 0; break; }
		else { menu(0, menu1); break; };
		break;
	case 1:
		tmp = 1;
		system("cls");
		header();
		cout << menu1[0] << setw(40 - menu1[0].size()) << "[" << tmp << "]" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout << menu1[1] << setw(40 - menu1[1].size()) << "[" << ++tmp << "]" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << menu1[2] << setw(40 - menu1[2].size()) << "[" << ++tmp << "]" << endl;
		cout << menu1[3] << setw(40 - menu1[3].size()) << "[" << ++tmp << "]" << endl;
		tr = _getch();
		if (tr == KEY_UP) { menu(0, menu1); break; };
		if (tr == KEY_DOWN) { menu(2, menu1); break; }
		if (tr == ENTER) { returner = 1; break; }
		else { menu(1, menu1); break; };
		break;
	case 2:
		tmp = 1;
		system("cls");
		header();
		cout << menu1[0] << setw(40 - menu1[0].size()) << "[" << tmp << "]" << endl;
		cout << menu1[1] << setw(40 - menu1[1].size()) << "[" << ++tmp << "]" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout << menu1[2] << setw(40 - menu1[2].size()) << "[" << ++tmp << "]" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << menu1[3] << setw(40 - menu1[3].size()) << "[" << ++tmp << "]" << endl;
		tr = _getch();
		if (tr == KEY_UP) { menu(1, menu1); break; }
		if (tr == KEY_DOWN) { menu(3, menu1); break; };
		if (tr == ENTER) { returner = 2; break; }
		else { menu(2, menu1); break; };
	case 3:
		tmp = 1;
		system("cls");
		header();
		cout << menu1[0] << setw(40 - menu1[0].size()) << "[" << tmp << "]" << endl;
		cout << menu1[1] << setw(40 - menu1[1].size()) << "[" << ++tmp << "]" << endl;
		cout << menu1[2] << setw(40 - menu1[2].size()) << "[" << ++tmp << "]" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout << menu1[3] << setw(40 - menu1[3].size()) << "[" << ++tmp << "]" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		tr = _getch();
		if (tr == KEY_UP) { menu(2, menu1); break; }
		if (tr == KEY_DOWN) { menu(3, menu1); break; };
		if (tr == ENTER) { returner = 3; break; }
		else { menu(3, menu1); break; };

		break;

	}
	return returner;
}

int stworz(map<string, int>& m)
{
	system("cls");
	header();
	vector<string>t;
	cout << "Podaj ścieżkę do pliku: " << endl;
	cin >> path;
	system("cls");
	header();
	fstream file(path, ios::in);
	if (file.good())
	{
		while (!file.eof())
		{
			string st;
			string st2;
			getline(file, st);
			stringstream ss(st);
			while (getline(ss, st2, ';'))
			{

				t.push_back(st2);
			}


		}

		for (int i = 2; i < t.size(); i++)
		{

			string st = t[i];

			int in = stoi(t[++i]);

			m.insert({ st, in });
		}
	}
	else
	{
		cout << endl << "Coś nie tak!, chcesz jeszcze raz?  t/n";
		char choos;
		cin >> choos;
		if (choos == 't')
		{
			stworz(m);
		}
		if (choos == 'n')
		{
			return 0;
		}

	}
	file.close();
	return 1;
}

void zapisz(map<string, int> m, fstream& plik)
{
	system("cls");
	header();
	cout << "Podaj ścieżkę do zapisu: ";
	cin >> path;
	plik.open(path.c_str(), ios::out);
	map<string, int>::iterator it = m.begin();
	for (; it != m.end(); it++)
	{
		plik << it->first << ";" << it->second << "\n";
	}
	plik.close();
}

int wczytaj(map<string, int>& m)
{
	system("cls");
	header();
	vector<string>t;
	cout << "Podaj ścieżkę do pliku: " << endl;
	cin >> path;
	system("cls");
	header();
	fstream file(path, ios::in);
	if (file.good())
	{
		while (!file.eof())
		{
			string st;
			string st2;
			getline(file, st);
			stringstream ss(st);
			while (getline(ss, st2, ';'))
			{

				t.push_back(st2);
			}


		}
		m.clear();
		for (int i = 0; i < t.size(); i++)
		{

			string st = t[i];

			int in = stoi(t[++i]);

			m.insert({ st, in });
		}
	}
	else
	{
		cout << endl << "Coś nie tak!, chcesz jeszcze raz?  t/n";
		char choos;
		cin >> choos;
		if (choos == 't')
		{
			wczytaj(m);
		}
		if (choos == 'n')
		{
			return 0;
		}

	}
	file.close();
	return 1;
}

int oblicz_premie(multimap<string, int> premia, map<string, int> szablon, deque<string>& wynik)
{
	system("cls");
	header();
	deque<string>d;

	float wszystkie_sztuki = 0;
	float jedna_pozycja_sztuki;
	float jedna_pozycja_kasa;
	float wszystka_kasa = 0;

	cout << "daj ścieżkę do premi: " << endl;
	cin >> path;
	plik.open(path, ios::in);
	if (!plik.good()) {
		cout << endl << "Coś nie tak!, chcesz jeszcze raz?  t/n";
		char choos;
		cin >> choos;
		if (choos == 't')
		{
			oblicz_premie(premia, szablon, wynik);
		}
		if (choos == 'n')
		{
			return 0;
		}
	}
	else
	{
		while (!plik.eof())
		{
			string st;
			string st2;
			getline(plik, st);
			stringstream ss(st);
			while (getline(ss, st2, ';'))
			{

				d.push_back(st2);
			}


		}
		plik.close();
		for (int i = 2; i < d.size(); i++)
		{

			string st = d[i];

			int in = stoi(d[++i]);

			premia.insert({ st, in });
		}

	}


	for (map<string, int>::iterator itmap = szablon.begin(); itmap != szablon.end(); itmap++)
	{
		stringstream ss;
		jedna_pozycja_sztuki = 0;
		jedna_pozycja_kasa = 0;
		for (multimap<string, int>::iterator itmulti = premia.begin(); itmulti != premia.end(); itmulti++)
		{
			if (itmap->first == itmulti->first)
			{
				jedna_pozycja_sztuki += itmulti->second;
				jedna_pozycja_kasa += (itmap->second * itmulti->second);
			}
		}
		wszystkie_sztuki += jedna_pozycja_sztuki;
		wszystka_kasa += jedna_pozycja_kasa;
		ss << itmap->first << " sprzedano " << jedna_pozycja_sztuki << " sztuk o wartości " << jedna_pozycja_kasa;
		wynik.push_back(ss.str());
	}
	printer(wynik.begin(), wynik.end());
	cout << endl << "Łącznie sprzedano " << wszystkie_sztuki << " sztuk, za wartość " << wszystka_kasa << " zł" << endl;
	return 1;
}

int main()
{

	setlocale(LC_CTYPE, "Polish");

	switch (menu(0, menu1))
	{
	case 0:
		switch (wczytaj(szablon))
		{
		case 0:
			system("cls");
			header();
			cout << "próba wczytania nie powiodła się" << endl; system("pause");
			main(); break;
		case 1:
			print(szablon.begin(), szablon.end()); cout << endl << "szablon wczytany" << endl; system("pause");
			main(); break;
		}
		break;
	case 1:
		switch (stworz(szablon))
		{
		case 0:
			main(); break;
		case 1:
			print(szablon.begin(), szablon.end()); cout << endl << "Zapisać? t/n";
			char czus; cin >> czus;
			if (czus == 't') { zapisz(szablon, plik); system("cls"); cout << "szablon zapisany" << endl; system("pause"); main(); break; }
			if (czus == 'n')main(); break;
		}
		break;
	case 2:
		system("cls");
		header();
		switch (oblicz_premie(premia, szablon, wynik))
		{
		case 0:
			main(); break;
		case 1:
			system("pause"); main(); break;
		}
		break;
	case 3:
		system("cls");
		header();
		cout << "czy napewno t/n" << endl;
		char w;
		cin >> w;
		if (w == 't')return 0;
		if (w == 'n')main(); break;
		break;

	}




	return 0;
}