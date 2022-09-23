#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define N 3

using namespace std;

struct student {
    char student_name[30];
    int student_course;
    int student_group;
    char student_adress[50];
    int student_phone;
};

struct results {
    char results_name[30];
    int results_course;
    int results_group;
    float results_session[4];
    string results_discipline;
};

void write(student* data, const string& filename);
void read(const string& filename);

void write(results* base, const string& filename);
void read(results* base, const string& filename);
void newgroups(results* base, string filename, string selected);

int main() {
    student data[N];
    results base[N];

    cout << "Input data in the next format for DAT: name, course, group, adress, phone number (print 0 if student doesn't have phone number)" "\n";
    for (auto& i : data) {
        cin >> i.student_name >> i.student_course >> i.student_group >> i.student_adress >> i.student_phone;
        cout << "----------------------------\n";
    }

    write(data, "data.dat");
    read("data.dat");

    for (auto& i : base) {
        cout << "\nInput data in the next format for TXT: name, course, group" << endl;
        cin >> i.results_name >> i.results_course >> i.results_group;
        cout << "\nSelected elective discipline (Programming, Robotics, Web-design)" << endl;
        cin.ignore();
        getline(cin, i.results_discipline);
        cout << "\nInput results of 4 subjects:" << endl;
        for (int j = 0; j < 4; j++)
        {
            cin >> i.results_session[j];
        }
        cout << "----------------------------\n";
    }

    write(base, "data.txt");
    read(base, "data.txt");
    newgroups(base, "group1.txt", "Programming");
    newgroups(base, "group2.txt", "Robotics");
    newgroups(base, "group3.txt", "Web-design");

    return 0;
}

void write(student* data, const string& filename) {
    ofstream file(filename);
    file.seekp(0, ios::beg);
    if (file.is_open()) {
        file.write((char*)data, sizeof(student) * N);
    }
    file.close();
}
void read(const string& filename) {
    student data[N];
    ifstream file(filename);
    if (file.is_open()) {
        // read structure from dat file and print to console
        file.read((char*)data, sizeof(student) * N);
        for (auto& i : data) {
            if (i.student_phone == 0)
            {
                cout << i.student_name << " " << i.student_adress;
            }
        }
    }
    file.close();
}

void write(results* base, const string& filename) {
    cout << "Write to txt file" << endl;

    ofstream file(filename);
    file.seekp(0, ios::beg);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            file << base[i].results_name << " " << base[i].results_course << " " << base[i].results_group << base[i].results_discipline << " " << endl;
            for (int j = 0; j < 4; j++) {
                file << base[i].results_session[j] << " ";
            }
        }
    }
    file.close();
}

void sorting(results* base, int kurs, string filename) {
    ifstream file(filename);
    cout << "\n" << kurs << " course: \n" << endl;
    for (int i = 0; i < N; i++) {
        if (base[i].results_course == kurs) {
            cout << base[i].results_name << " " << base[i].results_course << " " << base[i].results_group << " " << base[i].results_discipline << " " << endl;
            for (int j = 0; j < 4; j++) {
                cout << base[i].results_session[j] << " ";
            }
            cout << endl;
        }
    }
    file.close();
}

void read(results* base, const string& filename) {
    sorting(base, 1, filename);
    sorting(base, 2, filename);
    sorting(base, 3, filename);
    sorting(base, 4, filename);
}

void newgroups(results* base, string filename, string selected)
{
    ofstream fileNewGroup(filename);
    for (int i = 0; i < N; i++) {
        if (base[i].results_discipline == selected) {
            fileNewGroup << "\nNew group " << i + 1 << "\n" << endl;
            fileNewGroup << base[i].results_name << " " << base[i].results_course << " " << base[i].results_discipline << " " << endl;
            for (int j = 0; j < 4; j++) {
                fileNewGroup << base[i].results_session[j] << " ";
            }
            fileNewGroup << endl;
        }
    }
    fileNewGroup.close();
}
