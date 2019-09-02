#include "minesweeper.h"
#include <random>
#include <ctime>

Sweeper::Sweeper() :
    mineIndex(-1),
    fieldHiddenChar('#'),
    fieldHiddenCount(1),
    mineAmount(10),
    pField(nullptr),
    pField_hidden(nullptr),
    sizeField(10),
    openMineChar('M') {
        srand( time( 0 ) );
}

Sweeper::~Sweeper() {
    ClearField();
    cout << "\x1b[0m";
}

void Sweeper::CreateFields(int lenght) {
    sizeField = lenght;
    pField = new char*[sizeField];
    for(int i =0; i < sizeField; i++) {
        pField[i] = new char[sizeField];
    }

    pField_hidden = new int*[sizeField];
    for(int i =0; i < sizeField; i++) {
        pField_hidden[i] = new int[sizeField];
    }

    for(int i = 0; i < sizeField; i++) {
        for(int j = 0; j < sizeField; j++) {
            pField[i][j] = fieldHiddenChar;
            pField_hidden[i][j] = 0;
            fieldHiddenCount++;
        }
    }


}

void Sweeper::ClearField() {
    for(int i = 0; i < sizeField; i++) {
        delete [] pField[i];
        pField = nullptr;
        delete [] pField_hidden[i];
        pField_hidden = nullptr;
    }
}

void Sweeper::SetMineCount(int count = 10) {
    if(count >= (sizeField*sizeField)) {
        count = (sizeField*sizeField)-sizeField;
    }
    mineAmount = count;
    for(int i =0; i < mineAmount;) {
        int x = rand()%sizeField;
        int y = rand()%sizeField;
        if(!pField_hidden[x][y]) {
            pField_hidden[x][y] = mineIndex;
            i++;
        }
    }
}

int Sweeper::GetMinesNearby(int x, int y) {
    if(pField_hidden[x][y] != mineIndex) {
        if(pField[x][y] == fieldHiddenChar) {
            int countMines = 0;
            if(y-1 >= 0 && pField_hidden[x][y-1] == mineIndex) {
                countMines++;
            }
            if(y+1 < sizeField && pField_hidden[x][y+1] == mineIndex) {
                countMines++;
            }
            if(y+1 < sizeField && x-1 >= 0 && pField_hidden[x-1][y+1] == mineIndex) {
                countMines++;
            }
            if(y-1 >= 0 && x-1 >= 0 && pField_hidden[x-1][y-1] == mineIndex) {
                countMines++;
            }
            if(x-1 >= 0 && pField_hidden[x-1][y] == mineIndex) {
                countMines++;
            }
            if(x+1 < sizeField && pField_hidden[x+1][y] == mineIndex) {
                countMines++;
            }
            if(x+1 < sizeField && y-1 >= 0 && pField_hidden[x+1][y-1] == mineIndex) {
                countMines++;
            }
            if(x+1 < sizeField && y+1 < sizeField && pField_hidden[x+1][y+1] == mineIndex) {
                countMines++;
            }
            fieldHiddenCount--;
            return countMines;
        } else {
            return (pField[x][y]-0x30);
        }
    }
    return mineIndex;
}

void Sweeper::OpenZeroField(int count, int x, int y) {
    if(count == 0) {
        if(x-1 >= 0 && pField[x-1][y] == fieldHiddenChar) {
            pField[x-1][y] = GetMinesNearby(x-1,y)+0x30;
            if(pField[x-1][y]-0x30 == 0) {
                OpenZeroField(0, x-1, y);
            }
        }
        if(x-1 >= 0 && y+1 < sizeField && pField[x-1][y+1] == fieldHiddenChar) {
            pField[x-1][y+1] = GetMinesNearby(x-1,y+1)+0x30;
            if(pField[x-1][y+1]-0x30 == 0) {
                OpenZeroField(0, x-1, y+1);
            }
        }
        if(x-1 >= 0 && y-1 >=0 && pField[x-1][y-1] == fieldHiddenChar) {
            pField[x-1][y-1] = GetMinesNearby(x-1,y-1)+0x30;
            if(pField[x-1][y-1]-0x30 == 0) {
                OpenZeroField(0, x-1, y-1);
            }
        }
        if(x+1 < sizeField && pField[x+1][y] == fieldHiddenChar) {
            pField[x+1][y] = GetMinesNearby(x+1,y)+0x30;
            if(pField[x+1][y]-0x30 == 0) {
                OpenZeroField(0, x+1, y);
            }
        }
        if(x+1 < sizeField && y+1 < sizeField && pField[x+1][y+1] == fieldHiddenChar) {
            pField[x+1][y+1] = GetMinesNearby(x+1,y+1)+0x30;
            if(pField[x+1][y+1]-0x30 == 0) {
                OpenZeroField(0, x+1, y+1);
            }
        }
        if(x+1 < sizeField && y-1 >= 0 && pField[x+1][y-1] == fieldHiddenChar) {
            pField[x+1][y-1] = GetMinesNearby(x+1,y-1)+0x30;
            if(pField[x+1][y-1]-0x30 == 0) {
                OpenZeroField(0, x+1, y-1);
            }
        }
        if(y+1 < sizeField && pField[x][y+1] == fieldHiddenChar) {
            pField[x][y+1] = GetMinesNearby(x,y+1)+0x30;
            if(pField[x][y+1]-0x30 == 0) {
                OpenZeroField(0, x, y+1);
            }
        }
        if(y-1 >= 0 && pField[x][y-1] == fieldHiddenChar) {
            pField[x][y-1] = GetMinesNearby(x,y-1)+0x30;
            if(pField[x][y-1]-0x30 == 0) {
                OpenZeroField(0, x, y-1);
            }
        }
    }
}

void Sweeper::ShowField() {
    cout << "\n\t  ";
    for(int i = 0; i < sizeField; i++) {
        cout << "\x1b[37m" << (char)(i+65) << ' ';
    }
    cout << "\n\t ";
    PrintSymbols('_', sizeField*2);
    cout << "\n\x1b[0m";
    for(int i = 0; i < sizeField; i++) {
        cout << "\x1b[37m" << i+1 << "\t| \x1b[0m";
        for(int j = 0; j < sizeField; j++) {
            SetColorText(pField[i][j]);
            cout << pField[i][j] << ' ' << "\x1b[0m";
        }
        cout << endl;
    }
}

void Sweeper::SetColorText(char control) {
    if(control == fieldHiddenChar) {
        cout << "\x1b[32m";
    } else if(control == openMineChar) {
        cout << "\x1b[31m";
    } else if (control == 48) {
        cout << "\x1b[37m";
    } else {
        cout << "\x1b[34m";
    }
}

int Sweeper::Shoot(int x, int y) {
    x--;
    int status = GetMinesNearby(x,y);
    OpenZeroField(status, x , y);
    return status;
}

bool Sweeper::CheckWin(int status) {
    if(fieldHiddenCount == mineAmount) {
        cout << "You Win!" << endl;
        return false;
    } else if (status == mineIndex) {
        OpenAllMines();
        cout << "You Lose :(" << endl;
        return false;
    }
    return true;
}

void Sweeper::OpenAllMines() {
    for(int i = 0; i < sizeField; i++) {
        for(int j = 0; j < sizeField; j++) {
            if(pField_hidden[i][j] == mineIndex) {
                pField[i][j] = openMineChar;
            }
        }
    }
    ShowField();
}

template <typename T>
void Sweeper::PrintSymbols(T symbol, int lenght) {
    while(lenght--) {
        cout << symbol;
    }
}

void Sweeper::ShowHelpCoordinates() {
    static short int help = 3;
    if(help) {
        cout << "Example coordinates: B2 , E4, I9" << endl;
        help--;
    }
}

void Sweeper::Start() {
    int x, y;
    char z;
    bool gameStatus = true;
    ShowField();
    while (gameStatus) {
        ShowHelpCoordinates();
        cout << "Please, enter coordinates: ";
        cin>>z>>x;
        y = z-65;
        if(x > 0 && x <= sizeField && y >= 0 && y <= sizeField) {
            int result = Shoot(x, y);
            if(result != mineIndex) {
                pField[x-1][y] = result+0x30;
            }
            ShowField();
            gameStatus = CheckWin(result);
        } else {
            continue;
        }
    }
}