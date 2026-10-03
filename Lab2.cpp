#include <sstream>
#include "Lab2.h"
#include <iomanip>
#include <windows.h>


int inputInt(string prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Ошибка ввода. Попробуйте снова." << endl;
            continue;
        }

        cin.ignore(1000, '\n');
        return value;
    }
}

string trim(string s)
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");

    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

string normalize(string s)
{
    s = trim(s);

    for (size_t i = 0; i < s.length(); i++)
    {
        unsigned char c = (unsigned char)s[i];
        if (c >= 'A' && c <= 'Z') s[i] = (char)(c + 32);
        else if (c >= 192 && c <= 223) s[i] = (char)(c + 32);
        else if (c == 168) s[i] = (char)184;
    }
    return s;
}

int getTypeByInstrument(string instrument)
{
    string inst = normalize(instrument);

    if (inst == "скрипка") return 3;

    if (inst == "саксафон" || inst == "труба" || inst == "флейта" ||
        inst == "кларнет" || inst == "тромбон" || inst == "гобой" ||
        inst == "фагот" || inst == "туба")
        return 2;

    return 1;
}

Musician::Musician()
{
    id = 0;
    name = "";
    age = 0;
    instrument = "";
}

Musician::Musician(int id, string name, int age, string instrument)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->instrument = instrument;
}

Musician::~Musician() {}

void Musician::input()
{
    id = inputInt("ID: ");

    cout << "ФИО: ";
    getline(cin, name);

    age = inputInt("Возраст: ");

    cout << "Инструмент: ";
    getline(cin, instrument);
}

void Musician::output(ostream& os) const
{
    os << left
        << setw(6) << id
        << setw(40) << name
        << setw(12) << age
        << setw(20) << instrument;
}

void Musician::inputStream(istream& is)
{
    string line;
    if (getline(is, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);

        id = stoi(trim(line.substr(0, p1)));
        name = trim(line.substr(p1 + 1, p2 - p1 - 1));
        age = stoi(trim(line.substr(p2 + 1, p3 - p2 - 1)));
        instrument = trim(line.substr(p3 + 1, p4 - p3 - 1));
    }
}

void Musician::writeToFile(ostream& os) const
{
    os << left
        << setw(6) << id << "|"
        << setw(30) << name << "|"
        << setw(10) << age << "|"
        << setw(20) << instrument;
}

int Musician::getId() const { return id; }
string Musician::getName() const { return name; }
int Musician::getAge() const { return age; }
string Musician::getInstrument() const { return instrument; }

void Musician::setId(int id) { this->id = id; }
void Musician::setName(string name) { this->name = name; }
void Musician::setAge(int age) { this->age = age; }
void Musician::setInstrument(string instrument) { this->instrument = instrument; }

ostream& operator<<(ostream& os, const Musician& musician)
{
    musician.writeToFile(os);
    return os;
}

istream& operator>>(istream& is, Musician& musician)
{
    musician.inputStream(is);
    return is;
}

StringMusician::StringMusician() : Musician()
{
    experience = 0;
}

StringMusician::StringMusician(int id, string name, int age, string instrument, int experience)
    : Musician(id, name, age, instrument)
{
    this->experience = experience;
}

void StringMusician::input()
{
    Musician::input();
    experience = inputInt("Стаж (лет): ");
}

void StringMusician::output(ostream& os) const
{
    Musician::output(os);
    os << setw(12) << experience;
}

void StringMusician::inputStream(istream& is)
{
    string line;
    if (getline(is, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        size_t p5 = line.find('|', p4 + 1);

        id = stoi(trim(line.substr(0, p1)));
        name = trim(line.substr(p1 + 1, p2 - p1 - 1));
        age = stoi(trim(line.substr(p2 + 1, p3 - p2 - 1)));
        instrument = trim(line.substr(p3 + 1, p4 - p3 - 1));
        experience = stoi(trim(line.substr(p4 + 1, p5 - p4 - 1)));
    }
}

void StringMusician::writeToFile(ostream& os) const
{
    os << left
        << setw(6) << id << "|"
        << setw(30) << name << "|"
        << setw(10) << age << "|"
        << setw(20) << instrument << "|"
        << setw(8) << experience;
}

WindMusician::WindMusician() : Musician()
{
    experience = 0;
}

WindMusician::WindMusician(int id, string name, int age, string instrument, int experience)
    : Musician(id, name, age, instrument)
{
    this->experience = experience;
}

void WindMusician::input()
{
    Musician::input();
    experience = inputInt("Стаж (лет): ");
}

void WindMusician::output(ostream& os) const
{
    Musician::output(os);
    os << setw(12) << experience;
}

void WindMusician::inputStream(istream& is)
{
    string line;
    if (getline(is, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        size_t p5 = line.find('|', p4 + 1);

        id = stoi(trim(line.substr(0, p1)));
        name = trim(line.substr(p1 + 1, p2 - p1 - 1));
        age = stoi(trim(line.substr(p2 + 1, p3 - p2 - 1)));
        instrument = trim(line.substr(p3 + 1, p4 - p3 - 1));
        experience = stoi(trim(line.substr(p4 + 1, p5 - p4 - 1)));
    }
}

void WindMusician::writeToFile(ostream& os) const
{
    os << left
        << setw(6) << id << "|"
        << setw(30) << name << "|"
        << setw(10) << age << "|"
        << setw(20) << instrument << "|"
        << setw(8) << experience;
}

Violinist::Violinist() : StringMusician()
{
    instrument = "Скрипка";
    experience = 0;
}

Violinist::Violinist(int id, string name, int age, int experience)
    : StringMusician(id, name, age, "Скрипка", experience)
{
}

void Violinist::input()
{
    id = inputInt("ID: ");

    cout << "ФИО: ";
    getline(cin, name);

    age = inputInt("Возраст: ");
    experience = inputInt("Стаж (лет): ");

    instrument = "Скрипка";
}

void Violinist::output(ostream& os) const
{
    Musician::output(os);
    os << setw(12) << experience;
}

void Violinist::inputStream(istream& is)
{
    string line;
    if (getline(is, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);
        size_t p4 = line.find('|', p3 + 1);
        size_t p5 = line.find('|', p4 + 1);

        id = stoi(trim(line.substr(0, p1)));
        name = trim(line.substr(p1 + 1, p2 - p1 - 1));
        age = stoi(trim(line.substr(p2 + 1, p3 - p2 - 1)));
        instrument = "Скрипка";
        experience = stoi(trim(line.substr(p4 + 1, p5 - p4 - 1)));
    }
}

void Violinist::writeToFile(ostream& os) const
{
    os << left
        << setw(6) << id << "|"
        << setw(30) << name << "|"
        << setw(10) << age << "|"
        << setw(20) << instrument << "|"
        << setw(8) << experience;
}

Orchestra::Orchestra()
{
    filename = "orchestra_lab2.txt";
}

Orchestra::Orchestra(string filename)
{
    this->filename = filename;
}

void Orchestra::addMusician()
{
    int type;

    cout << endl;
    cout << "ВЫБОР ТИПА МУЗЫКАНТА" << endl;
    cout << "1. Струнный музыкант" << endl;
    cout << "2. Духовой музыкант" << endl;
    cout << "3. Скрипач" << endl;

    type = inputInt("Выберите тип: ");

    Musician* musician = nullptr;

    if (type == 1) musician = new StringMusician();
    else if (type == 2) musician = new WindMusician();
    else if (type == 3) musician = new Violinist();
    else
    {
        cout << "Неверный тип музыканта." << endl;
        return;
    }

    cout << endl;
    cout << "ВВОД ДАННЫХ МУЗЫКАНТА" << endl;
    musician->input();

    fstream file;
    file.open(filename, ios::in | ios::out | ios::app);

    if (!file.is_open())
    {
        cout << "Не удалось открыть файл." << endl;
        delete musician;
        return;
    }

    file.seekg(0, ios::end);
    if (file.tellg() == 0)
    {
        file << left
            << setw(6) << "ID" << "|"
            << setw(30) << "ФИО" << "|"
            << setw(10) << "Возраст" << "|"
            << setw(20) << "Инструмент" << "|"
            << setw(8) << "Стаж" << endl;
        file << "--------------------------------------------------------------------------------" << endl;
    }

    file.seekp(0, ios::end);
    file << *musician << endl;

    file.close();

    delete musician;

    cout << endl;
    cout << "Музыкант добавлен в файл." << endl;
}

void Orchestra::showMusicians()
{
    ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        cout << endl << "Файл пока не создан." << endl;
        return;
    }

    cout << endl;
    cout << "ДАННЫЕ МУЗЫКАНТОВ ИЗ ФАЙЛА" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    cout.setf(ios::left);
    cout << setw(6) << "ID"
        << setw(40) << "ФИО"
        << setw(12) << "Возраст"
        << setw(20) << "Инструмент"
        << setw(12) << "Стаж (лет)" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    string line;
    bool firstLine = true;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        if (line[0] == '-') continue;

        stringstream record(line);
        string idText, name, ageText, currentInstrument, experienceText;

        if (getline(record, idText, '|') &&
            getline(record, name, '|') &&
            getline(record, ageText, '|') &&
            getline(record, currentInstrument, '|') &&
            getline(record, experienceText, '|'))
        {
            try
            {
                cout << left
                    << setw(6) << stoi(trim(idText))
                    << setw(40) << trim(name)
                    << setw(12) << stoi(trim(ageText))
                    << setw(20) << trim(currentInstrument)
                    << setw(12) << stoi(trim(experienceText))
                    << endl;
            }
            catch (...) { continue; }
        }
    }

    cout << "------------------------------------------------------------------------------------------" << endl;
    file.close();
}

void Orchestra::deleteMusician(int id)
{
    ifstream input;
    input.open(filename);

    if (!input.is_open())
    {
        cout << "Файл не найден" << endl;
        return;
    }

    ofstream temp;
    temp.open("orchestra_temp.txt");

    if (!temp.is_open())
    {
        cout << "Не удалось создать временный файл" << endl;
        input.close();
        return;
    }

    temp << left
        << setw(6) << "ID" << "|"
        << setw(30) << "ФИО" << "|"
        << setw(10) << "Возраст" << "|"
        << setw(20) << "Инструмент" << "|"
        << setw(8) << "Стаж" << endl;
    temp << "--------------------------------------------------------------------------------" << endl;

    string line;
    bool found = false;
    bool firstLine = true;

    while (getline(input, line))
    {
        if (line.empty()) continue;

        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        if (line[0] == '-') continue;

        stringstream record(line);
        string idText;

        if (getline(record, idText, '|'))
        {
            try
            {
                int currentId = stoi(trim(idText));
                if (currentId == id)
                {
                    found = true;
                    continue;
                }
            }
            catch (...) { continue; }
        }

        temp << line << endl;
    }

    input.close();
    temp.close();

    remove(filename.c_str());
    if (rename("orchestra_temp.txt", filename.c_str()) != 0)
    {
        cout << "Ошибка переименования файла." << endl;
    }

    if (found) cout << "Музыкант удалён из файла." << endl;
    else cout << "Музыкант с таким ID не найден." << endl;
}

void Orchestra::editMusician(int id)
{
    ifstream input;
    input.open(filename);

    if (!input.is_open())
    {
        cout << "Файл не найден." << endl;
        return;
    }

    ofstream temp;
    temp.open("orchestra_temp.txt");

    if (!temp.is_open())
    {
        cout << "Не удалось создать временный файл" << endl;
        input.close();
        return;
    }

    temp << left
        << setw(6) << "ID" << "|"
        << setw(30) << "ФИО" << "|"
        << setw(10) << "Возраст" << "|"
        << setw(20) << "Инструмент" << "|"
        << setw(8) << "Стаж" << endl;
    temp << "--------------------------------------------------------------------------------" << endl;

    string line;
    bool found = false;
    bool firstLine = true;

    while (getline(input, line))
    {
        if (line.empty()) continue;

        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        if (line[0] == '-') continue;

        stringstream record(line);
        string idText, name, ageText, instrumentText, experienceText;

        if (!(getline(record, idText, '|') &&
            getline(record, name, '|') &&
            getline(record, ageText, '|') &&
            getline(record, instrumentText, '|') &&
            getline(record, experienceText, '|')))
        {
            continue;
        }

        int currentId = 0;
        try { currentId = stoi(trim(idText)); }
        catch (...) { continue; }

        if (currentId == id)
        {
            found = true;

            int newId = currentId;
            string newName = trim(name);
            int newAge = stoi(trim(ageText));
            string newInstrument = trim(instrumentText);
            int newExperience = stoi(trim(experienceText));

            int fieldChoice;

            cout << endl;
            cout << "ЧТО ИЗМЕНИТЬ?" << endl;
            cout << "1. ID" << endl;
            cout << "2. ФИО" << endl;
            cout << "3. Возраст" << endl;
            cout << "4. Инструмент" << endl;
            cout << "5. Стаж" << endl;
            cout << "6. Изменить всё" << endl;

            fieldChoice = inputInt("Выберите поле: ");

            switch (fieldChoice)
            {
            case 1:
                newId = inputInt("Введите новый ID: ");
                break;

            case 2:
                cout << "Введите новое ФИО: ";
                getline(cin, newName);
                break;

            case 3:
                newAge = inputInt("Введите новый возраст: ");
                break;

            case 4:
            {
                string oldInstrument = normalize(newInstrument);

                if (oldInstrument == "скрипка")
                {
                    cout << "У скрипача инструмент фиксирован — Скрипка." << endl;
                }
                else
                {
                    cout << "Введите новый инструмент: ";
                    getline(cin, newInstrument);
                }
                break;
            }

            case 5:
                newExperience = inputInt("Введите новый стаж: ");
                break;

            case 6:
                cout << endl;
                cout << "ИЗМЕНЕНИЕ ВСЕХ ДАННЫХ" << endl;

                newId = inputInt("Введите новый ID: ");

                cout << "Введите новое ФИО: ";
                getline(cin, newName);

                newAge = inputInt("Введите новый возраст: ");

                if (normalize(newInstrument) == "скрипка")
                {
                    cout << "У скрипача инструмент фиксирован — Скрипка." << endl;
                    newInstrument = "Скрипка";
                }
                else
                {
                    cout << "Введите новый инструмент: ";
                    getline(cin, newInstrument);
                }

                newExperience = inputInt("Введите новый стаж: ");
                break;

            default:
                cout << "Неверный выбор." << endl;
                break;
            }

            if (normalize(newInstrument) == "скрипка") newInstrument = "Скрипка";

            temp << left
                << setw(6) << newId << "|"
                << setw(30) << newName << "|"
                << setw(10) << newAge << "|"
                << setw(20) << newInstrument << "|"
                << setw(8) << newExperience << endl;
        }
        else
        {
            temp << line << endl;
        }
    }

    input.close();
    temp.close();

    remove(filename.c_str());
    if (rename("orchestra_temp.txt", filename.c_str()) != 0)
    {
        cout << "Ошибка переименования файла" << endl;
    }

    if (found) cout << "Данные музыканта изменены" << endl;
    else cout << "Музыкант с таким ID не найден" << endl;
}

void Orchestra::searchMusician(string instrument)
{
    ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        cout << "Файл не найден" << endl;
        return;
    }

    string searchTarget = normalize(instrument);

    cout << endl;
    cout << "РЕЗУЛЬТАТ ПОИСКА" << endl;
    cout << "Инструмент: " << instrument << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    cout.setf(ios::left);
    cout << setw(6) << "ID"
        << setw(40) << "ФИО"
        << setw(12) << "Возраст"
        << setw(20) << "Инструмент"
        << setw(12) << "Стаж (лет)" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    string line;
    bool found = false;
    bool firstLine = true;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        if (line[0] == '-') continue;

        stringstream record(line);
        string idText, name, ageText, currentInstrument, experienceText;

        if (getline(record, idText, '|') &&
            getline(record, name, '|') &&
            getline(record, ageText, '|') &&
            getline(record, currentInstrument, '|') &&
            getline(record, experienceText, '|'))
        {
            try
            {
                string dbInstrument = normalize(currentInstrument);

                if (dbInstrument == searchTarget)
                {
                    cout << left
                        << setw(6) << stoi(trim(idText))
                        << setw(40) << trim(name)
                        << setw(12) << stoi(trim(ageText))
                        << setw(20) << trim(currentInstrument)
                        << setw(12) << stoi(trim(experienceText))
                        << endl;
                    found = true;
                }
            }
            catch (...) { continue; }
        }
    }

    if (!found)
    {
        cout << "Музыканты с таким инструментом не найдены" << endl;
    }

    cout << "------------------------------------------------------------------------------------------" << endl;
    file.close();
}

Concert::Concert()
{
    name = "";
    date = "";
}

Concert::Concert(string name, string date)
{
    this->name = name;
    this->date = date;
}

void Concert::show()
{
    cout << "Концерт: " << name << endl;
    cout << "Дата: " << date << endl;
    orchestra.showMusicians();
}

void runLab2()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Orchestra orchestra("orchestra_lab2.txt");

    int choice;

    do
    {
        cout << endl;
        cout << "       ЛАБОРАТОРНАЯ РАБОТА 2" << endl;
        cout << "       ВАРИАНТ 13 - ОРКЕСТР" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "1. Добавить музыканта в файл" << endl;
        cout << "2. Показать данные файла" << endl;
        cout << "3. Удалить музыканта из файла" << endl;
        cout << "4. Изменить данные в файле" << endl;
        cout << "5. Поиск по инструменту" << endl;
        cout << "0. Выход" << endl;
        cout << "---------------------------------------------" << endl;

        choice = inputInt("Выберите пункт: ");

        switch (choice)
        {
        case 1:
            orchestra.addMusician();
            break;

        case 2:
            orchestra.showMusicians();
            break;

        case 3:
        {
            int id = inputInt("Введите ID музыканта: ");
            orchestra.deleteMusician(id);
            break;
        }

        case 4:
        {
            int id = inputInt("Введите ID музыканта: ");
            orchestra.editMusician(id);
            break;
        }

        case 5:
        {
            string instrument;
            cout << endl << "Введите название инструмента: ";
            getline(cin, instrument);
            orchestra.searchMusician(instrument);
            break;
        }

        case 0:
            cout << endl << "Работа программы завершена" << endl;
            break;

        default:
            cout << endl << "Такого пункта меню нет" << endl;
        }

    } while (choice != 0);
}