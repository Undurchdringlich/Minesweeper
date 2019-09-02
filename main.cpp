#include "minesweeper.cpp"

int SelectLevel();

int main() {
    Sweeper *minesweeper = new Sweeper();
    switch(SelectLevel()) {
        case 1:
            minesweeper->CreateFields(9);
            minesweeper->SetMineCount(10);
            break;
        case 2:
            minesweeper->CreateFields(15);
            minesweeper->SetMineCount(30);
            break;
        case 3:
            minesweeper->CreateFields(20);
            minesweeper->SetMineCount(50);
            break;
    }
    minesweeper->Start();
}

int SelectLevel() {
    cout << "\n1. Low\n2. Medium\n3. Hard" << endl;
    cout << "Please select a difficulty level: ";
    int result;
    scanf("%d", &result);
    return result;
}