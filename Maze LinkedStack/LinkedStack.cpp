#include "LinkedStack.h"
#include <cstdlib>
#include <Windows.h>
using namespace std;

class Maze {
public:
    Maze() { init(0, 0); }
    ~Maze() { reset(); }
private:
    int column;             //미로의 너비
    int row;                //미로의 높이
    int** map;              //미로 맵
    LinkedStack locStack;   //스택
    Location2D exitLoc;     //미로의 출구
public:
    void init(int col, int row) { //map 이차원 배열을 동적으로 할당
        map = new int* [row];
        for (int i = 0; i < row; i++)
            map[i] = new int[col];
    }
    void reset() { //미로 맵 maze를 동적으로 해제
        for (int i = 0; i < row; i++)
            delete[]map[i];
        delete[]map;
    }
    //void WidthNHeight(FILE* file, int* width, int* height){}

    void Load(const char* fname) { //파일에서 미로 파일을 읽어옴
        char load;
        FILE* Maze;
        fopen_s(&Maze, fname, "rb");
        if (Maze == NULL) {
            printf("FILE OPEN ERROR\n");
        }
        else {
		    fscanf_s(Maze, "%d %d", &column, &row);
            init(column, row);

            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    while (1) {
                        load = getc(Maze);
                        if ((load >= '0' && load <= '9')) {
                            ungetc(load, Maze);
                            fscanf_s(Maze, "%d", &map[i][j]);
                            break;
                        }
                        else if (load == 'e') { // 입구 위치 저장
                            map[i][j] = load;
                            Node* entry = new Node(i, j);
                            locStack.push(entry);
                            break;
                        }
                        else if (load == 'x') { // 출구 위치 저장
                            map[i][j] = load;
                            exitLoc.setRow(i);
                            exitLoc.setCol(j);
                            break;
                        }
                    }
                    // 미로 체크용
                    //if (map[i][j] == 'e' || map[i][j] == 'x') { printf("%2c ", map[i][j]); }
                    //else { printf("%2d ", map[i][j]); }
                }
                //printf("\n");
            }
            fclose(Maze);
        }
    }

    bool isValidLoc(int r, int c) {
        if (r < 0 || c < 0 || r >= row || c >= column) //범위를 벗어나면 갈 수 없다
            return false;
        else //비어있는 통로나 도착지점일 때만 true
            return (map[r][c] == 0 || map[r][c] == 'x');
    }

    void print() {  //현재 Maze를 화면에 출력
        printf("전체 미로의 크기 = %d * %d\n", row, column);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (map[i][j] == 0) {
                    printf("  ");   // 길
                }
                else if (map[i][j] == 1) {
                    printf("■");    // 벽
                }
                else if (map[i][j] == 7) {
                    printf("□");    // 지나온 경로
                }
                else if (map[i][j] == 'e') {
                    printf("○");    // 입구
                }
                else if (map[i][j] == 'x') {
                    printf("◎");    // 출구
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    void searchExit() { //실제 미로를 탐색하는 함수
        print();
        Sleep(1000);
        while (locStack.isEmpty() == false) {  //스택이 비어있지 않는 동안
            Location2D* here = locStack.pop()->getLocation(); //스택에 상단 객체 복사
            int r = here->getRow();
            int c = here->getCol();

            map[r][c] = 7; //시작점은 최적 경로
            if (exitLoc.getCol() == c && exitLoc.getRow() == r) {
                return;
            }
            else {
                map[r][c] = 7; //지나온 곳으로 표기
                system("cls");
                print();
                //갈 수 있는 곳 다 가본다
                if (isValidLoc(r - 1, c)) { locStack.push(new Node(r - 1, c)); }
                if (isValidLoc(r + 1, c)) { locStack.push(new Node(r + 1, c)); }
                if (isValidLoc(r, c - 1)) { locStack.push(new Node(r, c - 1)); }
                if (isValidLoc(r, c + 1)) { locStack.push(new Node(r, c + 1)); }
                Sleep(1000);
            }
        }
    }
};

int main() {
    Maze maze;
    maze.Load("미로 test.txt");
    maze.searchExit();
}