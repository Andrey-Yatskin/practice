#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <map>
#include <set>

using namespace std;

bool isalpha_rus(char c); //�������� ����� �� ������. ��� ������� ��������
void sortAlpha(vector<string> words); //���������� �� ��������
void sortAlphaIgnoreCase(vector<string> words); //���������� �� ��������, ��������� �������
void sortByFrequency(vector<string> words); //���������� �� �������
void sortByFrequencyIgnoreCase(vector<string> words); //���������� �� �������, ��������� �������
vector<string> getWords(string path); //����� ����� �� ����� �� ���� path
bool compare(std::string a, std::string b); //�������� ��� ������
void printRules();
int getOkInt();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); //��������� ����� � ������ ������� ��������
	printRules();
	std::map <std::string, int> wordMap; //������� ����
	vector<string> words;
	string path;
	cout << "������� ���� � �����\n";
	getline(cin, path);
	words = getWords(path);
	cout << "\n";
	while (true) {
		int choice;
		cout << "\t�������\n";
		cout << "1: ���������� �� ��������\n";
		cout << "2: ���������� �� ��������, ������������ �������\n";
		cout << "3: ���������� �� �������\n";
		cout << "4: ���������� �� �������, ������������ �������\n";
		cout << "5: ������� ����\n";
		cout << "\n0: �����\n";
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
			cout << "���� ������ ���� ��������� ASCII\n";
			cout << "������� ���� � �����\n";
			getline(cin, path);
			words = getWords(path);
			break;
		case 0:
			cout << "�� ��������.";
			exit(0);
		default:
			cout << "����� ������� �� ����������\n";
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

	for (int i = 0; i < words.size(); i++) { //��� �����
		for (auto& c : words[i]) c = toupper(c); //��� ����� �� ���� ������ ��������� � ������� �������
	}

	for (int i = 0; i < words.size(); i++) { //����������� ���������� �� �����������
		for (int j = i; j < words.size(); j++) {
			if (words.at(i) > words.at(j)) {
				string temp = words.at(i);
				words[i] = words[j];
				words[j] = temp;
			}
		}
	}

	for (int i = 0; i < words.size(); i++) { //����� ����
		file << words.at(i) << "\n";
	}
	file.close();
}

void printRules() {
	cout << "\t\t�������\n";
	cout << "\t-���� ������ ���� � ��������� ASCII\n";
}

void sortAlpha(vector<string> words) { //���� ����� ��� ������, �� ��� ����� ��������
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
	ifstream file(path);//��������� �������� ����� �� ���� path
	set<string> setWords;
	while (true)
	{
		if (file.is_open()) {
			cout << "������ ����: " << path << "\n";
			break;
		}
		cout << "���� �� ������� �������, ���������� �����.\n";
		cout << "������� �������� �����:\n";
		getline(cin, path);
		file.open(path);
	}
	vector<string> words;
	string line, tempWord = "";
	while (getline(file, line)) { //������ ������ ������ 
		for (int i = 0; i < line.size(); i++) { //�������� �� ���� ������ ������ 
			if (isalpha_rus(line[i]) || std::isalpha(line[i])) { //���� ������ ������� ����� ��� ������ �����, �� 
				tempWord += line[i]; //��������� � � �����
			}
			else { //����� ������ �� ������, ���� ���������� � ��, �� ���������� ����� � ������ � �������� �����
				if (tempWord != "" && tempWord != " ") {
					words.push_back(tempWord);
					tempWord = "";
				}
			}
		}
		if (tempWord != "") { //����� ����� ������ ����� ���� ������������ �����, ������� ���� ��� �� ������, �� �������
			words.push_back(tempWord);
		}
	}
	file.close();
	return words;
}

bool isalpha_rus(char c) { //�������� �������� �� ������ ������� ������. �������� ��������� ASCII �������
	return c >= '�' && c <= '�' || c >= '�' && c <= '�'
		|| c == '�' || c == '�'; // ���� ���� �������� ����� �
}

void sortByFrequency(vector<string> words) {
	map <std::string, int> wordMap; //������� ������� �����-�������
	ofstream file("sortByFrequency.txt");
	for (int i = 0; i < words.size(); i++) {
		wordMap[words[i]]++; //���������� ����� � ������� ���������� �������
	}
	vector<string> vect;
	for (std::map<std::string, int>::iterator it = wordMap.begin(); it != wordMap.end(); ++it)
	{
		string word = (it->first); //���� ����� �� �������
		string count = std::to_string(it->second); //���� ������� ����� ����� �� �������
		vect.push_back(count + ' ' + word); //���������� ��� � ������
	}
	sort(vect.begin(), vect.end(), compare); //��������� �� 

	for (int i = 0; i < vect.size(); i++) { //����� �� �����
		file << vect[i] << "\n";
	}
	file.close();
}
/*���� ���� �����, �� ������� ������� ��������*/
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
	a.erase(remove_if(a.begin(), a.end(), isalpha_rus), a.end()); //�������� ���� ������� ���� � ��������� ����
	b.erase(remove_if(b.begin(), b.end(), isalpha_rus), b.end()); //������ ��� ������ ����� � ���������� ���� "����� �������"
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
			std::cout << "����� ������� �� ����������.\n";
		}
		else
		{
			std::cin.ignore(32767, '\n');

			return a;
		}
	}
}