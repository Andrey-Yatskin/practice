#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <map>
#include <set>

using namespace std;

bool isalpha_rus(char c); //Проверят буква ли символ. Для русских символов
void sortAlpha(vector<string> words); //Сортировка по алфавиту
void sortAlphaIgnoreCase(vector<string> words); //Сортировка по алфавиту, игнорируя регистр
void sortByFrequency(vector<string> words); //Сортировка по частоте
void sortByFrequencyIgnoreCase(vector<string> words); //Сортировка по частоте, игнорируя регистр
vector<string> getWords(string path); //Взять слова из файла на пути path
bool compare(std::string a, std::string b); //Сравнить две строки
void printRules();
int getOkInt();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); //Установка ввода и вывоад русских символов
	printRules();
	std::map <std::string, int> wordMap; //Словарь слов
	vector<string> words;
	string path;
	cout << "Вводите путь к файлу\n";
	getline(cin, path);
	words = getWords(path);
	cout << "\n";
	while (true) {
		int choice;
		cout << "\tКОМАНДЫ\n";
		cout << "1: Сортировка по алфавиту\n";
		cout << "2: Сортировка по алфавиту, игнорировать регистр\n";
		cout << "3: Сортировка по частоте\n";
		cout << "4: Сортировка по частоте, игнорировать регистр\n";
		cout << "5: Выбрать файл\n";
		cout << "\n0: Выход\n";
		choice = getOkInt();
		switch (choice) {
		case 1:
			sortAlpha(words);
			break;
		case 2:
			sortAlphaIgnoreCase(words);
			break;
		case 3:
			sortByFrequency(words);
			break;
		case 4:
			sortByFrequencyIgnoreCase(words);
			break;
		case 5:
			cout << "Файл должен быть кодировки ASCII\n";
			cout << "Вводите путь к файлу\n";
			getline(cin, path);
			words = getWords(path);
			break;
		case 0:
			cout << "До свидания.";
			exit(0);
		default:
			cout << "Такой команды не существует\n";
		}
	}
}

void sortAlphaIgnoreCase(vector<string> words) {

	set<string> setWords;

	for (int i = 0; i < words.size(); i++) {
		setWords.insert(words.at(i));
	}
	ofstream file("sortAlphaIgnoreCase.txt");
	words.clear();

	for (auto it = setWords.begin(); it != setWords.end(); it++) {
		words.push_back(*it);
	}

	for (int i = 0; i < words.size(); i++) { //Все слова
		for (auto& c : words[i]) c = toupper(c); //Все буквы во всех словах перевести в верхний регистр
	}

	for (int i = 0; i < words.size(); i++) { //Пузырьковая сортировка по возрастанию
		for (int j = i; j < words.size(); j++) {
			if (words.at(i) > words.at(j)) {
				string temp = words.at(i);
				words[i] = words[j];
				words[j] = temp;
			}
		}
	}

	for (int i = 0; i < words.size(); i++) { //Вывод слов
		file << words.at(i) << "\n";
	}
	file.close();
}

void printRules() {
	cout << "\t\tПРАВИЛА\n";
	cout << "\t-Файл должен быть в кодировке ASCII\n";
}

void sortAlpha(vector<string> words) { //Тоже самое что сверху, но без смены регистра
	set<string> setWords;

	for (int i = 0; i < words.size(); i++) {
		setWords.insert(words.at(i));
	}
	words.clear();
	ofstream file("sortAlpha.txt");
	for (auto it = setWords.begin(); it != setWords.end(); it++) {
		words.push_back(*it);
	}
	for (int i = 0; i < words.size(); i++) {
		for (int j = i; j < words.size(); j++) {
			if (words.at(i) > words.at(j)) {
				string temp = words.at(i);
				words[i] = words[j];
				words[j] = temp;
			}
		}
	}

	for (int i = 0; i < words.size(); i++) {
		file << words.at(i) << "\n";
	}
	file.close();
}

vector<string> getWords(string path) {
	ifstream file(path);//Открываем файловый поток по пути path
	set<string> setWords;
	while (true)
	{
		if (file.is_open()) {
			cout << "Открыт файл: " << path << "\n";
			break;
		}
		cout << "Файл не удалось открыть, попробуйте снова.\n";
		cout << "Введите название файла:\n";
		getline(cin, path);
		file.open(path);
	}
	vector<string> words;
	string line, tempWord = "";
	while (getline(file, line)) { //Достаём оттуда строки 
		for (int i = 0; i < line.size(); i++) { //Проходим по всем буквам строки 
			if (isalpha_rus(line[i]) || std::isalpha(line[i])) { //Если строка русская буква или другая буква, то 
				tempWord += line[i]; //Добавляем её в слово
			}
			else { //Когда попали на пробел, знак пунктуации и тд, то записываем слово в вектор и обнуляем слово
				if (tempWord != "" && tempWord != " ") {
					words.push_back(tempWord);
					tempWord = "";
				}
			}
		}
		if (tempWord != "") { //После конца строки могло быть необработано слово, поэтому если оно не пустое, то добавим
			words.push_back(tempWord);
		}
	}
	file.close();
	return words;
}

bool isalpha_rus(char c) { //Проверка является ли символ русской буквой. Работает благодаря ASCII таблице
	return c >= 'а' && c <= 'я' || c >= 'А' && c <= 'Я'
		|| c == 'ё' || c == 'Ё'; // если надо включаем букву ё
}

void sortByFrequency(vector<string> words) {
	map <std::string, int> wordMap; //Заводим словарь слово-частота
	ofstream file("sortByFrequency.txt");
	for (int i = 0; i < words.size(); i++) {
		wordMap[words[i]]++; //Записываем слова в словарь увеличивая частоту
	}
	vector<string> vect;
	for (std::map<std::string, int>::iterator it = wordMap.begin(); it != wordMap.end(); ++it)
	{
		string word = (it->first); //Берём слово из словаря
		string count = std::to_string(it->second); //Берём частоту этого слова из словаря
		vect.push_back(count + ' ' + word); //Записываем его в вектор
	}
	sort(vect.begin(), vect.end(), compare); //Сортируем по 

	for (int i = 0; i < vect.size(); i++) { //Вывод на экран
		file << vect[i] << "\n";
	}
	file.close();
}
/*Ниже тоже самое, но вначале регистр меняется*/
void sortByFrequencyIgnoreCase(vector<string> words) {
	map <std::string, int> wordMap;
	for (int i = 0; i < words.size(); i++) {
		for (auto& c : words[i]) c = toupper(c);
	}
	ofstream file("sortByFrequencyIgnoreCase.txt");
	for (int i = 0; i < words.size(); i++) {
		wordMap[words[i]]++;
	}
	vector<string> vect;
	for (std::map<std::string, int>::iterator it = wordMap.begin(); it != wordMap.end(); ++it)
	{
		string word = (it->first);
		string count = std::to_string(it->second);
		vect.push_back(count + ' ' + word);
	}
	sort(vect.begin(), vect.end(), compare);

	for (int i = 0; i < vect.size(); i++) {
		file << vect[i] << "\n";
	}
	file.close();
}

bool compare(std::string a, std::string b)
{
	a.erase(remove_if(a.begin(), a.end(), isalpha_rus), a.end()); //Удаление всех русских букв и нерусских тоже
	b.erase(remove_if(b.begin(), b.end(), isalpha_rus), b.end()); //Потому что вектор будет с элементами вида "слово частота"
	a.erase(remove_if(a.begin(), a.end(), isalpha), a.end());
	b.erase(remove_if(b.begin(), b.end(), isalpha), b.end());
	int aInt = stoi(a);
	int bInt = stoi(b);
	return aInt > bInt;
}

int getOkInt()
{
	while (true)
	{
		int a;
		std::cin >> a;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Такой команды не существует.\n";
		}
		else
		{
			std::cin.ignore(32767, '\n');

			return a;
		}
	}
}