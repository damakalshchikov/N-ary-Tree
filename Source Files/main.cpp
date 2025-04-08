#include <iostream>

using namespace std;

int main(const int argc, char *argv[]) {
    // Локализация
    setlocale(LC_ALL, "Russian");

    // Вывод аргументов функции main
    if (argc < 2) {
        wcout << L"Аргументы, которые можно передать программе:" << endl;
        wcout << L"programMode - режим работы программы ";
        wcout << L"(1 - чтение существующего файла, 2 - генерация нового файла и его последующее чтение)" << endl;
        wcout << L"fileName - имя файла для чтения" << endl;
        return 0;
    }

    // progMode - режим работы программы
    // fileName - имя файла
    const int programMode = atoi(argv[1]);
    const string fileName = argv[2];

    // Проверяем режим работы программы
    switch (programMode) {
        case 1:
            cout << programMode << endl;
            cout << fileName << endl;
            break;
        case 2:
            cout << fileName << endl;
            break;
        default:
            wcout << L"Режим программы может быть 1 или 2!" << endl;
            return 0;
    }

    return 0;
}