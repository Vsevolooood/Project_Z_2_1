#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;
struct Profile
{
	int number;
	string fullName; 
	char sex;        
	int group;        
	int id;           
	int grades[8];    
	float sr;
};

void exportToFile(Profile student[], int* numbersOfStudents) {
	ofstream ofs;
	ofs.open("students.txt", ofstream::out | ofstream::trunc);
	ofs.close();
	ofstream database;
	database.open("students.txt", ios::app);
	if (!database.is_open())
		cout << '\n' << "Saving error!";
	else
	{
		for (int i = 0; i < *numbersOfStudents; i++)
		{
			if (i > 0)
				database << endl;
			database << student[i].number << ";";
			database << student[i].fullName << ";";
			database << student[i].group << ";" << student[i].id << ";" << student[i].sex << ";";
			for (int j = 0; j < 8; j++) {
				database << student[i].grades[j] << ";";
			}
			database << student[i].sr << ";";
		}

		database.close();
		cout << '\n' << "Profile is saved in the database.";
	}
}

void creatingRecord(Profile student[], int* sizeMAss) {
	char subjects[8][30]{ {"Mathematics\0"}, {"Programming\0"}, {"Physics\0"}, {"Philosophy\0"}, {"Mathematical Analysis\0"}, {"Computer Science\0"}, {"History\0"}, {"physical education\0"} };
	bool exitOfCreating = 0;
	for (int i = *sizeMAss; i < 100; i++) {
		float summ = 0;
		while (!exitOfCreating)
		{
			student[i].number = *sizeMAss + 1;
			cout << "Enter full name: ";
			cin >> student[i].fullName;
			cout << "Enter group: ";
			cin >> student[i].group;    
			cout << "Enter the order in the group: ";
			cin >> student[i].id;        
			cout << "Enter sex: ";
			cin >> student[i].sex;       
			cout << "Enter grades:  ";
			for (int j = 0; j < 8; j++)
			{
				cout << subjects[j] << ": ";
				cin >> student[i].grades[j];
				summ += student[i].grades[j];
				if (j == 8)
					cout << endl;
			}
			student[i].sr = summ / 8;
			summ = 0;
			++*sizeMAss;
			cout << endl << endl;
			int temp = 0;
			for (int j = 0; j < 8; j++) 
			{
				if (student[i].grades[j] == 2)
					temp++; 
			}
			if (temp == 0) 
			{
				exportToFile(student, sizeMAss);
			}
			else 
				cout << '\n' << "This student will be expelled. The profile will not be saved in the database." << endl;
			cout << "Enter 0 if you want coutine. Enter 1 if you want exit: ";
			cin >> exitOfCreating;
		}
	}
}

void showData(int* numbersOfStudents)
{
	int temp = 0;
	char massShow[14][25]{ {"Number"}, {"Full name: "}, {"Group:"}, {"Id:"}, {"Sex:"}, {"Mathematics:"}, {"Programming:"}, {"Physics:"}, {"Philosophy:"}, {"Mathematical Analysis:"}, {"Computer Science:"}, {"History:"}, {"physical education:"}, {"average value:"} };
	ifstream database("students.txt"); 
	if (!database.is_open()) 
		cout << "File opening error";
	else
	{
		string data;
		while (!database.eof())
		{
				for (int i = 0; i < 14; i++)
				{
					getline(database, data, ';');
					cout  << massShow[i] << " " << data << "; ";
				}
				cout << endl;
				temp++;
				if (temp == *numbersOfStudents)
					break;
		}
		database.close();
	}
	
}

void showGroup(Profile student[], int* numbersOfStudents)
{

	int n; 
	cout << "Enter the group number:" << endl;
	cin >> n;
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Error!";
	else
	{
		if (*numbersOfStudents == 0)
			cout << "The database is empty." << endl;
		else
		{
			int temp = 0;
			for (int i = 0; i < *numbersOfStudents; i++)
			{
				if (student[i].group == n)
				{
					cout << "Full name: " << student[i].fullName << "; ";
					cout << student[i].sex << " ";
					cout << "grades: ";
					for (int j = 0; j < 8; j++)
						cout << student[i].grades[j] << " ";
					cout << "\n\n";
					temp++;
				}
			}
			if (temp == 0)
				cout << "No records were found" << endl;
		}
	}
}

void showSex(Profile student[], int* numbersOfStudents) {
	char n;
	cout << "Enter the sex:" << endl;
	cin >> n;
		if (*numbersOfStudents == 0)
			cout << "The database is empty." << endl;
		else
		{
			int temp = 0;
			cout << "the number of students of the specified sex\n";
			for (int i = 0; i < *numbersOfStudents; i++)
			{
				if (student[i].sex == n)
				{
					temp++;
				}
			}
			if (temp == 0)
				cout << "No records were found" << endl;
			else
			{
				cout << temp << endl;
			}
		}
}

void sucsessTop(Profile student[], int* numbersOfStudents) {
	Profile dest[100];
	copy_n(student, 100, dest);
	for (int i = 0; i < *numbersOfStudents; i++) {
		for (int j = 0; j < *numbersOfStudents - 1; j++) {
			if (dest[j].sr > dest[j + 1].sr) {
				float b = dest[j].sr;
				string c = dest[j].fullName;
				dest[j].sr = dest[j + 1].sr;
				dest[j + 1].sr = b;
				dest[j].fullName = dest[j + 1].fullName;
				dest[j + 1].fullName = c;
			}
		}
	}
	cout << "average value\n";
	for (int i = *numbersOfStudents - 1; i >= 0; i--) {
		cout << dest[i].fullName << " :" << dest[i].sr << endl;
	}
}

void averageScore(Profile student[], int* numbersOfStudents) {
	for (int i = 0; i < *numbersOfStudents; i++)
	{
		int temp = 0;
		for (int j = 0; j < 8; j++)
		{
			if (student[i].grades[j] == 5) {
				temp += 2;
			}
			if (student[i].grades[j] == 4) {
				temp += 1;
			}
			if (student[i].grades[j] == 3) {
				temp = 0;
				break;
			}
		}
		if (temp == 16)
		{
			cout << "excellent student: \t";
			cout << student[i].fullName << endl;
		}
		if (temp < 16 && temp > 0)
		{
			cout << "good dtudent:     \t";
			cout << student[i].fullName << endl;
		}
		if (temp == 0)
		{
			cout << "without a degree: \t";
			cout << student[i].fullName << endl;
		}
	}
}

void id(Profile student[], int* numbersOfStudents) {
	int n;
	cout << "Enter the order in the group:" << endl;
	cin >> n;
	ifstream database("students.txt");
	if (!database.is_open())
		cout << "Error!";
	else
	{
		int temp = 0;
		if (*numbersOfStudents == 0)
			cout << "The database is empty." << endl;
		else
		{
			for (int i = 0; i < *numbersOfStudents; i++)
			{
				int temp = 0;
				if (student[i].id == n)
				{
					cout << student[i].fullName << " " << student[i].group << " ";
					cout << student[i].sex << " ";
					cout << "grades: ";
					for (int j = 0; j < 8; j++)
						cout << student[i].grades[j] << " ";
					cout << "\n\n";
					temp++;
				}
			}
			if (temp == 0)
				cout << "No records were found" << endl;
		}
	}

}

int edit(Profile mass[], int* numbersOfStudents)
{
	char subjects[8][30]{ {"Mathematics\0"}, {"Programming\0"}, {"Physics\0"}, {"Philosophy\0"}, {"Mathematical Analysis\0"}, {"Computer Science\0"}, {"History\0"}, {"physical education\0"} };
	int temp = 0;
	float summ = 0;
	int choice, examChoice, creditChoice, studIndex;
	char tempGender;
	cout << "Enter student Number (1 to " << *numbersOfStudents << "): ";
	cin >> studIndex;
	--studIndex; // Пользователи обычно считают с 1, а не с 0
	if (studIndex < 0 || studIndex >= *numbersOfStudents) {
		cout << "Incorrect student ID.\n";
	}
	cout << mass[studIndex].fullName << "; " << mass[studIndex].group << "; " << mass[studIndex].id << "; " << mass[studIndex].sex << "; ";
	for (int i = 0; i < 8; i++) {
		cout << subjects[i] << ": ";
		cout << mass[studIndex].grades[i] << ' ';
	}
	cout << endl;
	cout << "Pick an option to edit:\n";
	cout << "1. Full name\n";
	cout << "2. Gender\n";
	cout << "3. Group\n";
	cout << "4. The order in the group\n";
	cout << "5. Grades\n";
	cin >> choice;

	switch (choice) {
	case 1:
		cout << "Enter new full name: ";
		cin.ignore();
		getline(cin, mass[studIndex].fullName);
		break;
	case 2:
		cout << "Enter gender (M/F): ";
		cin >> tempGender;
		if (tempGender == 'm' || tempGender == 'w') {
			mass[studIndex].sex = tempGender;
		}
		else {
			cout << "Wrong gender entered.\n";
		}
		break;
	case 3:
		cout << "Enter new group ID: ";
		cin >> mass[studIndex].group;
		break;
	case 4:
		cout << "Enter new student ID: ";
		cin >> mass[studIndex].id;
		break;
	case 5:
		cout << "Grades editing.\n";
		cout << "Enter new grade\n ";
		for (int i = 0; i < 8; i++) {
			cout << subjects[i] << ": ";
			cin >> mass[studIndex].grades[i];
			summ += mass[studIndex].grades[i];
			if (mass[studIndex].grades[i] == 2)
				temp++;
		}
		mass[studIndex].sr = summ / 8;
		if (temp != 0)
		{
			cout << '\n' << "This student will be expelled. The profile will not be saved in the database." << endl;
			return 0;
		}
			
		break;
	default:
		cout << "Wrong choice.\n";
		break;
	}
	exportToFile(mass, numbersOfStudents);
}

int menue(int* sizeMAss, Profile students[100]) {

	bool statusMenue = true;
	int enterButton;
	do
	{
		system("cls");
		cout << "1: Creating record\n" << "2: Show data\n" << "3: Show group\n" << "4: Sow sex\n" << "5: Sucsess top\n" << "6: Average scoren\n" << "7: the order in the group\n" << "8: Edit\n" << "9: exit\n";
		cin >> enterButton;
		switch (enterButton)
		{
		case 1:
			system("cls");
			creatingRecord(students, sizeMAss);
			cin.clear();
			system("pause");
			break;
		case 2:
			system("cls");
			showData(sizeMAss);
			cin.clear();
			system("pause");
			break;
		case 3:
			system("cls");
			showGroup(students, sizeMAss);
			cin.clear();
			system("pause");
			break;
		case 4:
			system("cls");
			showSex(students, sizeMAss);
			cin.clear();
			system("pause");
			break;
		case 5:
			system("cls");
			sucsessTop(students, sizeMAss);
			cin.clear();
			system("pause");
			break;
		case 6:
			system("cls");
			averageScore(students, sizeMAss);
			cin.clear();
			system("pause");
			break;
		case 7:
			system("cls");
			id(students, sizeMAss);
			cin.clear();
			system("pause");
			break;
		case 8:
			system("cls");
			edit(students, sizeMAss);
			cin.clear();
			system("pause");
			break;
		case 9:
			return 0;
			break;
		default:
			cout << "Такой вариант отсутствует :) \n\n";
			cout << "Введите число: ";
			break;
		}
	} while (true);

}

void inportFromFile(Profile student[], int* numbersOfStudents) {

	string c;
	ifstream database;
	database.open("students.txt");
	if (!database)
	{
		cout << "File does not open " << '\n';
	}
	else
	{
		while (getline(database, c))
		{
			istringstream ss(c);
			Profile t;
			string p;
			getline(ss, p, ';');
			t.number = stoi(p);
			p = "";
			getline(ss, t.fullName, ';');
			getline(ss, p, ';');
			t.group = stoi(p);
			p = "";
			getline(ss, p, ';');
			t.id = stoi(p);
			p = "";
			ss >> t.sex;
			ss.ignore();
			p = "";
			for (int i = 0; i < 8; i++)
			{
				p = "";
				getline(ss, p, ';');
				t.grades[i] = stoi(p);
			}
			p = "";
			getline(ss, p, ';');
			t.sr = stof(p);
			p = "";
			student[*numbersOfStudents] = t;
			*numbersOfStudents += 1;
			p = "";
			c = "";
		}
	}
}

int main()
{
	Profile students[100];
	int sizeMAss = 0;
	inportFromFile(students, &sizeMAss);
	menue(&sizeMAss, students);
	return 0;
}

