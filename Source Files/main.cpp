#include <iostream>
#include <chrono>

#include "../Header Files/FinderLongestOddPath.h"
#include "../Header Files/FileGenerator.h"
#include "../Header Files/FileReader.h"
#include "../Header Files/PythonBridge.h"

using namespace std;

int main(const int argc, char *argv[]) {
    // Локализация
    setlocale(LC_ALL, "Russian");

    // Вывод аргументов функции main
    if (argc < 2) {
        wcout << L"Аргументы, которые можно передать программе:" << endl;
        wcout << L"programMode - режим работы программы ";
        wcout << L"(1 - чтение существующего файла, 2 - генерация нового файла и его чтение)" << endl;
        wcout << L"fileName - имя файла для чтения" << endl;
        wcout << L"arity - арность дерева (задаётся, если programMode равен 2)" << endl;
        wcout << L"nodeCount - количество узлов в n-арном дерева (задаётся, если programMode равен 2)" << endl;
        return 1;
    }

    const int programMode = atoi(argv[1]);
    const string fileName = argv[2];
    // Если режим программы - 2, то генерируем файл
    if (programMode == 2) {
        int arity = atoi(argv[3]);
        int nodeCount = atoi(argv[4]);
        FileGenerator::generateTreeFile(fileName, arity, nodeCount);
    }

    // Читаем дерево из файла и устанавливаем связи между узлами
    vector<Node*> tree = FileReader::readFile(argv[2]);
    FileReader::buildTreeConnections(tree, tree[0]->getArity());

    // Находим самый длинный путь от корня с нечётными значениями
    vector<int> currentPath;
    vector<vector<int>> longestPath;
    // Замеряем время поиска в мксек
    auto start = chrono::steady_clock::now();
    FinderLongestOddPath::findLongestOddPath(tree[0], currentPath, longestPath);
    auto end = chrono::steady_clock::now();

    // Результат замеров
    long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    // Выводим найденный путь
    if (longestPath.empty()) {
        wcout << L"Самый длинный путь от корня с нечётными вершинами не найден" << endl;
    } else {
        wcout << L"Самый длинный путь от корня, проходящий только по нечётным вершинам" << endl;
        for (int i = 0; i < longestPath.size(); i++) {
            wcout << L"Путь №" << i + 1 << ": ";
            for (int j = 0; j < longestPath[i].size(); j++) {
                cout << longestPath[i][j];
                if (j < longestPath[i].size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
        cout << endl;
        wcout << L"Длина пути: " << longestPath[0].size() - 1 << endl;
        wcout << L"Время поиска путей: " << duration << L" мксек" << endl;
    }

    // Создаём изображение n-арного дерева
    PythonBridge::initialize();

    // Создаём изображения найденных путей
    for (int i = 0; i < longestPath.size(); i++) {
        PythonBridge::drawTree(tree, longestPath[i], "./Images/tree" + to_string(i + 1) + ".png");
    }

    // Очищаем память и завершаем работу интерпретатора Python
    FileReader::cleanUpTree(tree);
    PythonBridge::finalize();

    return 0;
}