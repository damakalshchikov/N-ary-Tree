#include <iostream>

#include "../Header Files/Node.h"
#include "../Header Files/FileReader.h"

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
        wcout << L"arity - арность дерева" << endl;
        return 1;
    }

    // progMode - режим работы программы
    // fileName - имя файла
    const int programMode = atoi(argv[1]);
    const string fileName = argv[2];
    const int arity = atoi(argv[3]);

    vector<Node*> tree;

    tree = FileReader::readFile(fileName, arity);
    FileReader::buildTreeConnections(tree, arity);

    return 0;
}