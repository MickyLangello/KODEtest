#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
// Структура для представления объекта
struct Object {
    string name;
    double x, y;
    string type;
    double creationTime;
};

// Функция для сравнения объектов по имени (используется при сортировке)
bool compareByName(const Object& obj1, const Object& obj2) {
    return obj1.name < obj2.name;
}

// Функция для сравнения объектов по времени создания (используется при сортировке)
bool compareByTime(const Object& obj1, const Object& obj2) {
    return obj1.creationTime < obj2.creationTime;
}

// Функция для группировки объектов по имени
map<char, vector<Object> > groupByName(const vector<Object>& objects) {
    map<char, vector<Object> > groupedObjects;

    for (const Object& obj : objects) {
        char firstChar = obj.name[0];

        // Помещаем объекты с именем, начинающимся с цифры, спецсимвола или
        // иностранных языков в отдельную группу с именем "#"
        if (!isalpha(firstChar)) {
            firstChar = '#';
        }

        groupedObjects[firstChar].push_back(obj);
    }

    return groupedObjects;
}

// Функция для группировки объектов по типу
map<string, vector<Object> > groupByType(const vector<Object>& objects, int minCount) {
    map<string, vector<Object> > groupedObjects;

    for (const Object& obj : objects) {
        groupedObjects[obj.type].push_back(obj);
    }

    // Помещаем объекты с количеством менее minCount в группу "Разное"
    for (auto& entry : groupedObjects) {
        if (entry.second.size() < minCount) {
            groupedObjects["Разное"].insert(groupedObjects["Разное"].end(), entry.second.begin(), entry.second.end());
            entry.second.clear();
        }
    }

    return groupedObjects;
}

int main() {
    vector<Object> objects;

    // Ожидание действий пользователя
    while (true) {
        cout << "Выберите действие:\n";
        cout << "1. Прочитать список объектов из файла\n";
        cout << "2. Добавить объект в список\n";
        cout << "3. Группировать и сортировать объекты\n";
        cout << "4. Сохранить результаты в файл\n";
        cout << "5. Выйти\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                // Чтение списка объектов из файла
                ifstream inputFile("file.txt");
                if (!inputFile.is_open()) {
                    cerr << "Ошибка открытия файла\n";
                    break;
                }

                Object obj;
                while (inputFile >> obj.name >> obj.x >> obj.y >> obj.type >> obj.creationTime) {
                    objects.push_back(obj);
                }

                inputFile.close();
                cout << "Список объектов успешно загружен из файла\n";
                break;
            }
            case 2: {
                // Добавление объекта в список
                Object obj;
                cout << "Введите имя объекта: ";
                cin >> obj.name;
                cout << "Введите координату X: ";
                cin >> obj.x;
                cout << "Введите координату Y: ";
                cin >> obj.y;
                cout << "Введите тип объекта: ";
                cin >> obj.type;
                cout << "Введите время создания: ";
                cin >> obj.creationTime;

                objects.push_back(obj);
                cout << "Объект успешно добавлен в список\n";
                break;
            }
            case 3: {
                // Группировка и сортировка объектов
                if (objects.empty()) {
                    cout << "Список объектов пуст. Пожалуйста, добавьте объекты или загрузите из файла.\n";
                    break;
                }

                // Группировка по имени
                map<char, vector<Object>> groupedByName = groupByName(objects);

                // Группировка по типу
                map<string, vector<Object>> groupedByType = groupByType(objects, 2);

                // Сортировка объектов внутри групп
                for (auto& entry : groupedByName) {
                    sort(entry.second.begin(), entry.second.end(), compareByName);
                }

                for (auto& entry : groupedByType) {
                    sort(entry.second.begin(), entry.second.end(), compareByName);
                }

                // Вывод результатов
                cout << "Группировка и сортировка выполнены:\n";

                // Вывод по группам по имени
                cout << "Группировка по имени:\n";
                for (const auto& entry : groupedByName) {
                    cout << "Группа '" << entry.first << "':\n";
                    for (const Object& obj : entry.second) {
                        cout << obj.name << " " << obj.x << " " << obj.y << " " << obj.type << " " << obj.creationTime << "\n";
                    }
                }

                // Вывод по группам по типу
                cout << "Группировка по типу:\n";
                for (const auto& entry : groupedByType) {
                    cout << "Группа '" << entry.first << "':\n";
                    for (const Object& obj : entry.second) {
                        cout << obj.name << " " << obj.x << " " << obj.y << " " << obj.type << " " << obj.creationTime << "\n";
                    }
                }

                break;
            }
            case 4: {
                // Сохранение результатов в файл
                ofstream outputFile("result.txt");
                if (!outputFile.is_open()) {
                    cerr << "Ошибка открытия файла\n";
                    break;
                }

                // Запись отсортированных объектов в файл
                for (const Object& obj : objects) {
                    outputFile << obj.name << " " << obj.x << " " << obj.y << " " << obj.type << " " << obj.creationTime << "\n";
                }

                outputFile.close();
                cout << "Результаты успешно сохранены в файл\n";
                break;
            }
            case 5: {
                // Выход из программы
                return 0;
            }
            default: {
                cout << "Неверный выбор. Пожалуйста, выберите действие из списка.\n";
                break;
            }
        }
    }

    return 0;
}


