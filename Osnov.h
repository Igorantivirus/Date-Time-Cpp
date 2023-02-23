#include<iostream>
#include <time.h>
#include<string>
using namespace std;
namespace kak_u_Igorya {
	string input(string txt = "") {//Обычная функция инпут, как у питона!
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		cout << txt;
		string tx = "";
		getline(cin, tx);
		return tx;
	}
	int input_int(string txt = "") {//тот же интуп но только для инт
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		cout << txt;
		int ch = 0;
		cin >> ch;
		return ch;
	}
	bool input_bool(string txt = "") {//тот же интуп но только для логических переменных
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		cout << txt;
		bool ch = 0;
		cin >> ch;
		return ch;
	}
	float input_float(string txt = "") {//тот же интуп но только для чисел с плавающей запятой
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		cout << txt;
		float ch = 0;
		cin >> ch;
		return ch;
	}
	double input_double(string txt = "") {//тот же интуп но только для чисел с плавающей запятой
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		cout << txt;
		double ch = 0;
		cin >> ch;
		return ch;
	}

	float round(float ch, int num = 0) {//Эта и последующие - округление как в питоне, указываем первый эл-т - число для округления, вторую - сколько знаков после запятой
		ch = ((int(ch * pow(10, num + 1)) % 10) >= 5) ? ((int(ch * pow(10, num)) + 1) / (pow(10, num))) : ((int(ch * pow(10, num))) / (pow(10, num)));
		return ch;
	}
	double round(double ch, int num = 0) {
		ch = ((int(ch * pow(10, num + 1)) % 10) >= 5) ? ((int(ch * pow(10, num)) + 1) / (pow(10, num))) : ((int(ch * pow(10, num))) / (pow(10, num)));
		return ch;
	}

	int toint(string ch, int els = 0) {//преобразует строку в инт
		int otv = 0, zn = 1, in = 0;
		if (ch[0] == '-') { in = 1; zn = -1; }
		for (int i = in; i < ch.size(); i++) {
			otv += (int(ch[i]) - 48) * pow(10, ch.size() - i - 1);
		}
		return ((to_string(otv * zn) == ch) ? (otv * zn) : (els));
	}
	float tofloat(string ch, float els = 0) {//преобразует строку в флот
		int len = ch.size(), in = len, zn = 1, nach = 0;
		if (ch[0] == '-') { zn = -1, nach = 1; }
		for (int i = nach; i < len; i++) {
			if (ch[i] == '.' || ch[i] == ',') { in = i; break; }
		}
		float otv = 0;
		for (int i = nach; i < in; i++) {
			otv += (int(ch[i]) - 48) * pow(10, in - i - 1);
		}
		for (int i = in + 1; i < len; i++) {
			otv += float(int(ch[i] - 48) / pow(10, i - in));
		}
		int sum = 0;
		for (int i = in + 1; i < len; i++) { sum++; }
		while (sum < 6) {
			ch += "0";
			sum++;
		}
		//return ((to_string(otv * zn) == ch) ? (otv * zn) : (els));
		return otv * zn;
	}
	double todouble(string ch) {//преобразует строку в дабл
		int len = ch.size(), in = len, zn = 1, nach = 0;
		if (ch[0] == '-') { zn = -1, nach = 1; }
		for (int i = nach; i < len; i++) {
			if (ch[i] == '.') { in = i; break; }
		}
		double otv = 0;
		for (int i = nach; i < in; i++) {
			otv += (int(ch[i]) - 48) * pow(10, in - i - 1);
		}
		for (int i = in + 1; i < len; i++) {
			otv += double(int(ch[i] - 48) / pow(10, i - in));
		}
		return otv * zn;
	}
	bool tobool(string ch, bool els = 1) {//преобразует строку в бул
		if (ch == "true" || ch == "True" || ch == "1" || ch == "да" || ch == "Да" || ch == "yes" || ch == "Yes") { return 1; }
		if (ch == "false" || ch == "False" || ch == "0" || ch == "нет" || ch == "Нет" || ch == "no" || ch == "No") { return 0; }
		else {
			return els;
		}
	}

	int maxof(int* mas, int len) {//находит максимальный эл-т массива из интов
		int ma = mas[0];
		for (int i = 0; i < len; i++) {
			if (mas[i] > ma) ma = mas[i];
		}
		return ma;
	}
	float maxof(float* mas, int len) {//находит максимальный эл-т массива из флот
		float ma = mas[0];
		for (int i = 0; i < len; i++) {
			if (mas[i] > ma) ma = mas[i];
		}
		return ma;
	}
	double maxof(double* mas, int len) {//находит максимальный эл-т массива из дабл
		double ma = mas[0];
		for (int i = 0; i < len; i++) {
			if (mas[i] > ma) ma = mas[i];
		}
		return ma;
	}
	string maxof(string* mas, int len) {//находит максимальный эл-т массива из стринг
		int ma = mas[0].size();
		for (int i = 0; i < len; i++) {
			if (ma < mas[0].size()) {
				ma = mas[0].size();
			}
		}
		return mas[ma];
	}

	int minof(int* mas, int len) {//эта и последующая  - то же самое но для инт
		int ma = mas[0];
		for (int i = 0; i < len; i++) {
			if (mas[i] < ma) ma = mas[i];
		}
		return ma;
	}
	float minof(float* mas, int len) {
		float ma = mas[0];
		for (int i = 0; i < len; i++) {
			if (mas[i] < ma) ma = mas[i];
		}
		return ma;
	}
	double minof(double* mas, int len) {
		double ma = mas[0];
		for (int i = 0; i < len; i++) {
			if (mas[i] < ma) ma = mas[i];
		}
		return ma;
	}
	string minof(string* mas, int len) {
		int ma = mas[0].size();
		for (int i = 0; i < len; i++) {
			if (ma > mas[0].size()) {
				ma = mas[0].size();
			}
		}
		return mas[ma];
	}

	template<typename T>
	void print_arr(T* mas, int len, string pr = " ") {//Выводит масив
		cout << mas[0];
		for (int i = 1; i < len; i++) {
			cout << pr << mas[i];
		}
	}
	void rand_arr(int* mas, int len, int ot = 0, int doo = 100) {//Заполняет интовский массив, принимая значения от какого и до какого, дальнейшие заполняют  массивы других переменных
		srand(time(NULL));
		doo = doo - ot;
		for (int i = 0; i < len; i++) {
			mas[i] = rand() % doo + ot;
		}
	}
	void rand_arr(float* mas, int len, int ot = 0, int doo = 100, int col = 0) {//дополнительно принимает кол-во знаков после запятой
		srand(time(NULL));
		float v;
		for (int i = 0; i < len; i++) {
			v = rand() % (int)pow(10, col);
			mas[i] = ot + (v / pow(10, col)) * (doo - ot);
		}
	}
	void rand_arr(double* mas, int len, int ot = 0, int doo = 100, int col = 0) {//дополнительно принимает кол-во знаков после запятой
		srand(time(NULL));
		double v;
		for (int i = 0; i < len; i++) {
			v = rand() % (int)pow(10, col);
			mas[i] = ot + (v / pow(10, col)) * (doo - ot);
		}
	}
}