#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Musician
{
protected:
    int id;
    string name;
    int age;
    string instrument;

public:
    Musician();
    Musician(int id, string name, int age, string instrument);
    virtual ~Musician();

    virtual void input();
    virtual void output(ostream& os) const;
    virtual void inputStream(istream& is);
    virtual void writeToFile(ostream& os) const;

    int getId() const;
    string getName() const;
    int getAge() const;
    string getInstrument() const;

    void setId(int id);
    void setName(string name);
    void setAge(int age);
    void setInstrument(string instrument);
};

ostream& operator<<(ostream& os, const Musician& musician);
istream& operator>>(istream& is, Musician& musician);

class StringMusician : public Musician
{
protected:
    int experience;

public:
    StringMusician();
    StringMusician(int id, string name, int age, string instrument, int experience);

    void input() override;
    void output(ostream& os) const override;
    void inputStream(istream& is) override;
    void writeToFile(ostream& os) const override;
};

class WindMusician : public Musician
{
protected:
    int experience;

public:
    WindMusician();
    WindMusician(int id, string name, int age, string instrument, int experience);

    void input() override;
    void output(ostream& os) const override;
    void inputStream(istream& is) override;
    void writeToFile(ostream& os) const override;
};

class Violinist : public StringMusician
{
public:
    Violinist();
    Violinist(int id, string name, int age, int experience);

    void input() override;
    void output(ostream& os) const override;
    void inputStream(istream& is) override;
    void writeToFile(ostream& os) const override;
};

class Orchestra
{
private:
    string filename;

public:
    Orchestra();
    Orchestra(string filename);

    void addMusician();
    void showMusicians();
    void deleteMusician(int id);
    void editMusician(int id);
    void searchMusician(string instrument);
};

class Concert
{
private:
    string name;
    string date;
    Orchestra orchestra;

public:
    Concert();
    Concert(string name, string date);
    void show();
};

void runLab2();
string normalize(string s);
int inputInt(string prompt);