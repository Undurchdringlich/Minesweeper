#ifndef MINESWEEPER
#define MINESWEEPER
#include <iostream>

using namespace std;

class Sweeper {
    public:
        Sweeper(); //конструктор
        ~Sweeper(); //деструктор
        void CreateFields(int); //создаём поле и инициализируем все элементы
        void SetMineCount(int); //выставляем мины
        void Start(); //игровой цикл, разрешаем стрелять пока не попадём в мину или не выиграем
    private:
        void ClearField(); //очищаем память
        int GetMinesNearby(int, int); //высчитываем количество мин рядом с текущими координатами
        void OpenZeroField(int, int, int); //рекурсивно открываем пустые поля
        void ShowField(); //рисуем поле в консоли
        int Shoot(int, int); //делаем выстрел на основе введённых координат от пользователя
        bool CheckWin(int); //проверка на условие для победы/поражения
        template <typename T>
        void PrintSymbols(T, int); //выводим в консоль необходимое количество элементов
        void OpenAllMines(); //показываем расположение всех мин (при поражении)
        void SetColorText(char); //управление цветом текста
        void ShowHelpCoordinates(); //показываем подсказку с координатами
        char openMineChar; //символ показывающий открытую мину
        int sizeField; //размерность массива
        char **pField; //динамический двумерный массив с видимыми полями
        int **pField_hidden; //динамический двумерный массив со скрытыми полями с минами
        int mineIndex; //числовое обозначение мины
        char fieldHiddenChar; //символьное обозначение скрытых полей
        int fieldHiddenCount; //счётчик скрытых полей
        int mineAmount; //количество мин
};

#endif