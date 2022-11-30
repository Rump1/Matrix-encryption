#include <iostream>
#include <vector>
using namespace std;

// Алфавит с 'a' по '{' ('{' идет после 'z' в таблице ASCII), где { - пробел, монщность алфавита - 27 символов

int invert(int a, int mod) // Алгоритм поиска обратного по модулю
{
	if (a == 1)
		return 1;
	return (1 - 1 * invert(mod % a, a) * mod) / a + mod;
}

string encryption(vector<vector<int>> Matrix, string original) // Функция шифрования
{
	string encrypted = ""; // Контейнер для зашифрованной строки
	for (int i = 0; i < original.length() - 1; i += 2) // Цикл, перебирающий по два символа строки
	{
		encrypted+= (Matrix[0][0] * (original[i] - 97) + Matrix[0][1] * (original[i + 1] - 97)) % 27 + 97; // Матричное шифрование
		encrypted+= (Matrix[1][0] * (original[i] - 97) + Matrix[1][1] * (original[i + 1] - 97)) % 27 + 97;
	}
	return encrypted;
}

string decryption(vector<vector<int>> Matrix, string encrypted, int det) // Функция дешифрования
{
	string decrypted = ""; // Контейнер для расшифрованной строки
	int inv_det = invert(det, 27); // Нахождение det^-1(mod27)
	vector<vector<int>> inv_Matrix(2, vector <int>(2)); // Инициализация двумерного массива A^-1

	for (int i = 0; i < 2; i++) // Нахождение обратной матрицы
		for (int j = 0; j < 2; j++)
		{
			int n = pow(-1, i + j);
			inv_Matrix[i][j] = inv_det * Matrix[(i + 1) % 2][(j + 1) % 2] * n % 27;
			if (inv_Matrix[i][j] % 27 < 0)
				inv_Matrix[i][j] += 27;
		}
	swap(inv_Matrix[0][1], inv_Matrix[1][0]); // Транспонирование матрицы 2x2
	for (int i = 0; i < encrypted.length() - 1; i += 2) // Дешифрование 
	{
		decrypted += (inv_Matrix[0][0] * (encrypted[i] - 97) + inv_Matrix[0][1] * (encrypted[i + 1] - 97)) % 27 + 97;
		decrypted += (inv_Matrix[1][0] * (encrypted[i] - 97) + inv_Matrix[1][1] * (encrypted[i + 1] - 97)) % 27 + 97;
	}
	return decrypted;
}

int main()
{
	setlocale(LC_ALL, "ru");
	vector<vector<int>> Matrix = { {3,4},{2,7} }; // Инициализация двумерного массива
	int det = Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0]; // Вычисление определителя матрицы
	string original;
	cout << "Введите текст, который необходимо зашифровать: ";
	cin >> original; // Ввод исходной строки
	if (original.length() % 2 == 1)
		original += "{"; // Если длина текста нечетная, добавляем пробел
	string encrypted = encryption(Matrix, original); // Вызов функции шифрования
	cout << "Зашифрованная строка: " + encrypted << endl;

	cout << "Дешифрованная строка: " + decryption(Matrix, encrypted, det) << endl; // Вызов функции дешифровния
}