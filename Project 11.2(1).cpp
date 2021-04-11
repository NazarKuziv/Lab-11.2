// Lab_11_2.cpp
// < Кузів Назар >
// Лабораторна робота № 11.2
// Послідовний пошук у бінарному файлі
// Варіант 6

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <fstream>
#include <iomanip>

using namespace std;


enum Specialty { KN, IT, ME, PI, TN };;
string SpecialtyStr[] = { "Комп’ютерні науки", "Інформатика", "Математика та економіка","Фізика та інформатика","Трудове навчання" };

struct Student
{
	char prizv[25];
	int kurs;
	Specialty specialty;
	int Phisic;
	int Math;
	union {
		int Prog;
		int Num_Methods;
		int Pedagogy;
	};
};


void Create(char* fname);
void Print(char* fname);
void Percentage_of_Excellent_Students(char* fname);
void Print_Students_Who_Have_5_or_4_In_Physics(char* fname);

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char fname[100];
	int menuItem;

	do {
		cout << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - ввести дані у файл" << endl;
		cout << " [2] - вивести дані на екран" << endl;
		cout << " [3] - процент студентів, які вчаться без трійок" << endl;
		cout << " [4] - dивести прізвища студентів, які отримали з фізики оцінки «5» або «4»" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:

			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << "Введіть ім'я файла: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case 2:
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файла: "; cin.getline(fname, sizeof(fname));
			Print(fname);
			break;
		case 3:
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файла: "; cin.getline(fname, sizeof(fname));
			Percentage_of_Excellent_Students(fname);
			break;
		case 4:
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файла: "; cin.getline(fname, sizeof(fname));
			Print_Students_Who_Have_5_or_4_In_Physics(fname);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	return 0;


}
void Create(char* fname)
{
	FILE* f;
	if ((f = fopen(fname, "wb")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}

	int specialty;
	Student student;
	char ch;

	do
	{
		cout << endl;
		cout << " Прізвище: ";  cin.sync(); cin >> student.prizv;
		cout << " Курс: "; cin >> student.kurs;
		cout << " Спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
		cin >> specialty;
		student.specialty = (Specialty)specialty;
		cout << " Оцінка з Фізики: "; cin >> student.Phisic;
		cout << " Оцінка з Математики: "; cin >> student.Math;
		switch (student.specialty)
		{
		case KN:
			cout << " Оцінка з Програмування: "; cin >> student.Prog;
			break;
		case IT:
			cout << " Оцінка з Чисельних методів: "; cin >> student.Num_Methods;
			break;
		case ME:
		case PI:
		case TN:
			cout << " Оцінка з Педагогіки: "; cin >> student.Pedagogy;
			break;
		}
		if (fwrite(&student, sizeof(Student), 1, f) != 1)
		{
			cerr << "Error writing file." << endl;
			return;
		}

		cout << "продовжити? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');

	fclose(f);
}
void Print(char* fname) // виведення файлу на екран
{
	FILE* f;
	if ((f = fopen(fname, "rb")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	Student student;

	while (!feof(f))
	{

		if (fread(&student, sizeof(Student), 1, f) != 1)
			if (feof(f))
			{
				return;
			}

		cout << endl;
		cout << " Прізвище : " << student.prizv << endl;
		cout << " Курс: " << student.kurs << endl;
		cout << " Спеціальність: " << SpecialtyStr[student.specialty] << endl;
		cout << " Оцінка з Фізики:" << student.Phisic << endl;
		cout << " Оцінка з Математики:" << student.Math << endl;
		switch (student.specialty)
		{
		case KN:
			cout << " Оцінка з Програмування: :" << student.Prog << endl;
			break;
		case IT:
			cout << " Оцінка з Чисельних методів:" << student.Num_Methods << endl;
			break;
		case ME:
		case PI:
		case TN:
			cout << "Оцінка з Педагогіки:" << student.Pedagogy << endl;
			break;
		}
	}


	fclose(f);
}
void Percentage_of_Excellent_Students(char* fname)
{
	ifstream f(fname, ios::binary);
	Student student;

	if (!f)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}

	double P_of_S = 0;
	int kilk = 0;

	while (f.read((char*)&student, sizeof(Student)))
	{
		if (student.Phisic > 3 && student.Math > 3 && (student.Prog > 3 || student.Num_Methods > 3 || student.Pedagogy > 3))
			P_of_S += 1;

		kilk++;
	}
	P_of_S = (P_of_S / kilk) * 100;

	cout << "Процент студентів, які вчаться без трійокна (“відмінно” і “добре”). = " << setprecision(3) << P_of_S <<"%"<< endl;

}
void Print_Students_Who_Have_5_or_4_In_Physics(char* fname)
{
	ifstream f(fname, ios::binary);
	Student student;

	if (!f)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	int № = 0;
	cout << "Прізвища студентів, які отримали з фізики оцінки “5” або “4”: " << endl;
	while (f.read((char*)&student, sizeof(Student)))
	{
		
			if (student.Phisic == 4 || student.Phisic == 5)
				cout << ++№ << "." << student.prizv << endl;

	}

}