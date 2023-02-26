#include<iostream>
#include <time.h>
#include<string>
using namespace std;
namespace kak_u_Igorya {
	template<typename R>
	inline void revers(R& a, R& b) { auto pr = a; a = b; b = pr; }
	//vvvvDopolneniya
	bool prov(string ch) {
		for (int i = 0; i < ch.size(); i++) { if (!((i >= 48 && i <= 57) || (i == 46) || (i == 45))) { return 0; } }
		return 1;
	}
	int poisk(int* mas, int l, int r) {// 1 3 2 7 9 8 6 5 // 0 8
		int x = mas[r];
		int less = l;
		for (int i = l; i < r; ++i) {
			if (mas[i] <= x) {
				revers(mas[i], mas[less]);
				++less;
			}
		}
		revers(mas[less], mas[r]);
		return less;
	}
	void bis_sor(int* mas, int l, int r) {
		if (l < r) {
			int q = poisk(mas, l, r);
			bis_sor(mas, l, q - 1);
			bis_sor(mas, q + 1, r);
		}
	}
	void sli_sor(int* values, int* buffer, int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			sli_sor(values, buffer, l, m);
			sli_sor(values, buffer, m + 1, r);
			int k = l;
			for (int i = l, j = m + 1; i <= m || j <= r; ) {
				if (j > r || (i <= m && values[i] < values[j])) {
					buffer[k] = values[i];
					++i;
				}
				else {
					buffer[k] = values[j];
					++j;
				}
				++k;
			}
			for (int i = l; i <= r; ++i) {
				values[i] = buffer[i];
			}
		}
	}
	///\/\/\/\/\Dopolneniya
	//input
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
	//okrugleniye
	float round(float ch, int num = 0) {//Эта и последующие - округление как в питоне, указываем первый эл-т - число для округления, вторую - сколько знаков после запятой
		ch = ((int(ch * pow(10, num + 1)) % 10) >= 5) ? ((int(ch * pow(10, num)) + 1) / (pow(10, num))) : ((int(ch * pow(10, num))) / (pow(10, num)));
		return ch;
	}
	double round(double ch, int num = 0) {
		ch = ((int(ch * pow(10, num + 1)) % 10) >= 5) ? ((int(ch * pow(10, num)) + 1) / (pow(10, num))) : ((int(ch * pow(10, num))) / (pow(10, num)));
		return ch;
	}
	//preobrazovanie
	int toint(string ch, int els = 0) {//преобразует строку в инт
		int otv = 0, zn = 1, in = 0;
		if (ch[0] == '-') { in = 1; zn = -1; }
		for (int i = in; i < ch.size(); i++) {
			otv += (int(ch[i]) - 48) * pow(10, ch.size() - i - 1);
		}
		return ((to_string(otv * zn) == ch) ? (otv * zn) : (els));
	}
	float tofloat(string ch, float els = 0) {
		if (!prov(ch)) { return els; }
		int ot = 0, zn = 1, len = ch.size(), zap = len; float otv = 0; bool da = 0;
		if (ch[0] == '-') { zn = -1; ot = 1; }
		for (int i = ot; i < len; i++) {
			if (da) { otv += (int(ch[i]) - 48) / pow(10, i - zap); }
			if (ch[i] == '.' || ch[i] == ',') { zap = i; da = 1; }
		}
		for (int i = ot; i < zap; i++) { otv += (int(ch[i]) - 48) * pow(10, zap - i - 1); }
		return otv * zn;
	}
	double todouble(string ch, double els = 0) {
		if (!prov(ch)) { return els; }
		int ot = 0, zn = 1, len = ch.size(), zap = len; double otv = 0; bool da = 0;
		if (ch[0] == '-') { zn = -1; ot = 1; }
		for (int i = ot; i < len; i++) {
			if (da) { otv += (int(ch[i]) - 48) / pow(10, i - zap); }
			if (ch[i] == '.' || ch[i] == ',') { zap = i; da = 1; }
		}
		for (int i = ot; i < zap; i++) { otv += (int(ch[i]) - 48) * pow(10, zap - i - 1); }
		return otv * zn;
	}
	bool tobool(string ch, bool els = 1) {//преобразует строку в бул
		if (ch == "true" || ch == "True" || ch == "1" || ch == "да" || ch == "Да" || ch == "yes" || ch == "Yes") { return 1; }
		if (ch == "false" || ch == "False" || ch == "0" || ch == "нет" || ch == "Нет" || ch == "no" || ch == "No") { return 0; }
		else {
			return els;
		}
	}
	//bolshe minshe
	int maxof(int* mas, int len, int ot = 0) {//находит максимальный эл-т массива из интов
		int ma = mas[0];
		for (int i = ot; i < len; i++) {
			if (mas[i] > ma) ma = mas[i];
		}
		return ma;
	}
	float maxof(float* mas, int len, int ot = 0) {//находит максимальный эл-т массива из флот
		float ma = mas[0];
		for (int i = ot; i < len; i++) {
			if (mas[i] > ma) ma = mas[i];
		}
		return ma;
	}
	double maxof(double* mas, int len, int ot = 0) {//находит максимальный эл-т массива из дабл
		double ma = mas[0];
		for (int i = ot; i < len; i++) {
			if (mas[i] > ma) ma = mas[i];
		}
		return ma;
	}
	string maxof(string* mas, int len, int ot = 0) {//находит максимальный эл-т массива из стринг
		int ma = mas[0].size();
		for (int i = ot; i < len; i++) {
			if (ma < mas[0].size()) {
				ma = mas[0].size();
			}
		}
		return mas[ma];
	}
	int minof(int* mas, int len, int ot = 0) {//эта и последующая  - то же самое но для инт
		int ma = mas[0];
		for (int i = ot; i < len; i++) {
			if (mas[i] < ma) ma = mas[i];
		}
		return ma;
	}
	float minof(float* mas, int len, int ot = 0) {
		float ma = mas[0];
		for (int i = ot; i < len; i++) {
			if (mas[i] < ma) ma = mas[i];
		}
		return ma;
	}
	double minof(double* mas, int len, int ot = 0) {
		double ma = mas[0];
		for (int i = ot; i < len; i++) {
			if (mas[i] < ma) ma = mas[i];
		}
		return ma;
	}
	string minof(string* mas, int len, int ot = 0) {
		int ma = mas[0].size();
		for (int i = ot; i < len; i++) {
			if (ma > mas[0].size()) {
				ma = mas[0].size();
			}
		}
		return mas[ma];
	}
	//rabota s massivami
	template<typename T>
	void print_arr(T* mas, int len, string pr = ", ", string end = "\n") {//Выводит масив
		cout << mas[0];
		for (int i = 1; i < len; i++) {
			cout << pr << mas[i];
		}
		cout << end;
	}
	void rand_arr(char* mas, int len, int ot = 0, int doo = 100) {//Заполняет интовский массив, принимая значения от какого и до какого, дальнейшие заполняют  массивы других переменных
		srand(time(NULL));
		doo = doo - ot;
		for (int i = 0; i < len; i++) {
			mas[i] = char(rand() % doo + ot);
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
	template<typename S>
	int set(S* mas, int len, int els = 0) {
		S* newmas = new S[len];
		int in = 0;
		bool da = 1;
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < in; j++) {
				if (mas[i] == newmas[j]) {
					da = 0;
				}
			}
			if (da) {
				newmas[in] = mas[i];
				in++;
			}
			da = 1;
		}
		for (int i = 0; i < len; i++) {
			if (i < in) {
				mas[i] = newmas[i];
			}
			else {
				mas[i] = els;
			}
		}
		delete[] newmas;
		return in;
	}
	template<typename B>
	void revers_arr(B* mas, int len) {
		int len2 = ((len % 2 == 0) ? (len / 2) : ((len / 2) + 1));
		for (int i = 0; i < len2; i++) {
			revers(mas[i], mas[len - i - 1]);
		}
	}
	template<typename S>
	S sum(S* mas, int len = 0) {
		auto s = mas[0];
		for (int i = 1; i < len; i++) {
			s += mas[i];
		}
		return s;
	}
	template<typename U>
	U umn(U* mas, int len = 0) {
		auto s = mas[0];
		for (int i = 1; i < len; i++) {
			s *= mas[i];
		}
		return s;
	}
	template<typename S>
	S sr_arif(S* mas, int len = 0) {
		auto s = mas[0];
		for (int i = 1; i < len; i++) {
			s += mas[i];
		}
		return s/len;
	}
	template<typename S>
	int count_arr(S* mas, int len, S ind) {
		int count = 0;
		for (int i = 0; i < len; i++) {
			if (mas[i] == ind) { count++; }
		}
		return count;
	}
	template<typename T>
	int index_arr(T* mas, int len, T ch, int ot = 0) {
		for (int i = ot; i < len; i++) {
			if (mas[i] == ch) return i;
		}
	}
	//sortirovka massovov
	template<typename S>
	void sort_puz(S* mas, int len) {//sortirovka puzirkom
		int count = 0;
		for (int i = 0; i + 1 < len; ++i) {
			for (int j = 0; j + 1 < len - i; ++j) {
				if (mas[j + 1] < mas[j]) {
					revers(mas[j], mas[j + 1]);
					count++;
				}
			}
			if (count == 0) { break; }
			count = 0;
		}
	}
	template<typename S>
	void sort_she(S* mas, int len) {//sheikernaya sortirivka
		if (len == 0) {
			return;
		}
		int left = 0;
		int right = len - 1;
		while (left <= right) {
			for (int i = right; i > left; --i) {
				if (mas[i - 1] > mas[i]) {
					revers(mas[i - 1], mas[i]);
				}
			}
			++left;
			for (int i = left; i < right; ++i) {
				if (mas[i] > mas[i + 1]) {
					revers(mas[i], mas[i + 1]);
				}
			}
			--right;
		}
	}
	template<typename S>
	void sort_ras(S* mas, int len) {//sjrtirovka rashoskoi
		const double factor = 1.247;
		double step = len - 1;
		while (step >= 1) {
			for (int i = 0; i + step < len; ++i) {
				if (mas[i] > mas[i + int(step)]) {
					revers(mas[i], mas[i + int(step)]);
				}
			}
			step /= factor;
		}
		for (int i = 0; i + 1 < len; ++i) {
			for (int j = 0; j + 1 < len - i; ++j) {
				if (mas[j + 1] < mas[j]) {
					revers(mas[j], mas[j + 1]);
				}
			}
		}
	}
	template<typename S>
	void sort_vst(S* mas, int len) {//sortirovka vstavkami
		int x = 0, j = 0;
		for (int i = 1; i < len; ++i) {
			x = mas[i];
			j = i;
			while (j > 0 && mas[j - 1] > x) {
				mas[j] = mas[j - 1];
				--j;
			}
			mas[j] = x;
		}
	}
	template<typename S>
	void sort_vib(S* mas, int len) {//viborochnaya sortirovka
		auto mini = mas;
		for (int i = 0; i < len; i++) {
			for (int j = i; j < len; j++) {
				if (*(mas + j) < *mini) { mini = (mas + j); };
			}
			revers(*(mas + i), *mini);
			mini = mas + i + 1;
		}
	}
	template<typename S>
	void sort_bis(S* mas, int len) {//bistraya sortirovka
		if (!(len == 0 || len == 1)) {
			bis_sor(mas, 0, len - 1);
		}
	}
	template<typename S>
	void sort_sli(S* mas, int len) {//sortirovka sliyaniyem
		if (!(len == 0 || len == 1)) {
			int* buffer = new int[len];
			sli_sor(mas, buffer, 0, len - 1);
			delete[] buffer;
		}
	}
	//drugie poleznie funkcii
	bool prost(int ch) {
		if (ch < 0) { ch *= -1; }
		int count = 0;
		for (int i = 1; i < ch; i++) {
			if (ch % i == 0) { count++; }
		}
		return (count == 1) ? (1) : (0);
	}
	template<typename F>
	F fakt(F ch) {
		F otv = 1;
		for (int i = 1; i <= ch; i++) {
			otv *= i;
		}
		return otv;
	}
}