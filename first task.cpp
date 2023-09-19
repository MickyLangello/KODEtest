#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
// ��������� ��� ������������� �������
struct Object {
    string name;
    double x, y;
    string type;
    double creationTime;
};

// ������� ��� ��������� �������� �� ����� (������������ ��� ����������)
bool compareByName(const Object& obj1, const Object& obj2) {
    return obj1.name < obj2.name;
}

// ������� ��� ��������� �������� �� ������� �������� (������������ ��� ����������)
bool compareByTime(const Object& obj1, const Object& obj2) {
    return obj1.creationTime < obj2.creationTime;
}

// ������� ��� ����������� �������� �� �����
map<char, vector<Object> > groupByName(const vector<Object>& objects) {
    map<char, vector<Object> > groupedObjects;

    for (const Object& obj : objects) {
        char firstChar = obj.name[0];

        // �������� ������� � ������, ������������ � �����, ����������� ���
        // ����������� ������ � ��������� ������ � ������ "#"
        if (!isalpha(firstChar)) {
            firstChar = '#';
        }

        groupedObjects[firstChar].push_back(obj);
    }

    return groupedObjects;
}

// ������� ��� ����������� �������� �� ����
map<string, vector<Object> > groupByType(const vector<Object>& objects, int minCount) {
    map<string, vector<Object> > groupedObjects;

    for (const Object& obj : objects) {
        groupedObjects[obj.type].push_back(obj);
    }

    // �������� ������� � ����������� ����� minCount � ������ "������"
    for (auto& entry : groupedObjects) {
        if (entry.second.size() < minCount) {
            groupedObjects["������"].insert(groupedObjects["������"].end(), entry.second.begin(), entry.second.end());
            entry.second.clear();
        }
    }

    return groupedObjects;
}

int main() {
    vector<Object> objects;

    // �������� �������� ������������
    while (true) {
        cout << "�������� ��������:\n";
        cout << "1. ��������� ������ �������� �� �����\n";
        cout << "2. �������� ������ � ������\n";
        cout << "3. ������������ � ����������� �������\n";
        cout << "4. ��������� ���������� � ����\n";
        cout << "5. �����\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                // ������ ������ �������� �� �����
                ifstream inputFile("file.txt");
                if (!inputFile.is_open()) {
                    cerr << "������ �������� �����\n";
                    break;
                }

                Object obj;
                while (inputFile >> obj.name >> obj.x >> obj.y >> obj.type >> obj.creationTime) {
                    objects.push_back(obj);
                }

                inputFile.close();
                cout << "������ �������� ������� �������� �� �����\n";
                break;
            }
            case 2: {
                // ���������� ������� � ������
                Object obj;
                cout << "������� ��� �������: ";
                cin >> obj.name;
                cout << "������� ���������� X: ";
                cin >> obj.x;
                cout << "������� ���������� Y: ";
                cin >> obj.y;
                cout << "������� ��� �������: ";
                cin >> obj.type;
                cout << "������� ����� ��������: ";
                cin >> obj.creationTime;

                objects.push_back(obj);
                cout << "������ ������� �������� � ������\n";
                break;
            }
            case 3: {
                // ����������� � ���������� ��������
                if (objects.empty()) {
                    cout << "������ �������� ����. ����������, �������� ������� ��� ��������� �� �����.\n";
                    break;
                }

                // ����������� �� �����
                map<char, vector<Object>> groupedByName = groupByName(objects);

                // ����������� �� ����
                map<string, vector<Object>> groupedByType = groupByType(objects, 2);

                // ���������� �������� ������ �����
                for (auto& entry : groupedByName) {
                    sort(entry.second.begin(), entry.second.end(), compareByName);
                }

                for (auto& entry : groupedByType) {
                    sort(entry.second.begin(), entry.second.end(), compareByName);
                }

                // ����� �����������
                cout << "����������� � ���������� ���������:\n";

                // ����� �� ������� �� �����
                cout << "����������� �� �����:\n";
                for (const auto& entry : groupedByName) {
                    cout << "������ '" << entry.first << "':\n";
                    for (const Object& obj : entry.second) {
                        cout << obj.name << " " << obj.x << " " << obj.y << " " << obj.type << " " << obj.creationTime << "\n";
                    }
                }

                // ����� �� ������� �� ����
                cout << "����������� �� ����:\n";
                for (const auto& entry : groupedByType) {
                    cout << "������ '" << entry.first << "':\n";
                    for (const Object& obj : entry.second) {
                        cout << obj.name << " " << obj.x << " " << obj.y << " " << obj.type << " " << obj.creationTime << "\n";
                    }
                }

                break;
            }
            case 4: {
                // ���������� ����������� � ����
                ofstream outputFile("result.txt");
                if (!outputFile.is_open()) {
                    cerr << "������ �������� �����\n";
                    break;
                }

                // ������ ��������������� �������� � ����
                for (const Object& obj : objects) {
                    outputFile << obj.name << " " << obj.x << " " << obj.y << " " << obj.type << " " << obj.creationTime << "\n";
                }

                outputFile.close();
                cout << "���������� ������� ��������� � ����\n";
                break;
            }
            case 5: {
                // ����� �� ���������
                return 0;
            }
            default: {
                cout << "�������� �����. ����������, �������� �������� �� ������.\n";
                break;
            }
        }
    }

    return 0;
}


