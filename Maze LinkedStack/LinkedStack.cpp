#include "LinkedStack.h"
#include <cstdlib>
using namespace std;

class Maze {
public:
    Maze() { init(0, 0); }
    ~Maze() { reset(); }
private:
    int column;             //�̷��� �ʺ�
    int row;                //�̷��� ����
    int** map;              //�̷� ��
    LinkedStack locStack;   //����
    Location2D exitLoc;     //�̷��� �ⱸ
public:
    void init(int col, int row) { //map ������ �迭�� �������� �Ҵ�
        map = new int* [row];
        for (int i = 0; i < row; i++)
            map[i] = new int[col];
    }
    void reset() { //�̷� �� maze�� �������� ����
        for (int i = 0; i < row; i++)
            delete[]map[i];
        delete[]map;
    }
    //void WidthNHeight(FILE* file, int* width, int* height){}

    void Load(const char* fname) { //���Ͽ��� �̷� ������ �о��
        char load;
        FILE* Maze;
        fopen_s(&Maze, fname, "rb");
        if (Maze == NULL) {
            printf("FILE OPEN ERROR\n");
        }

		fscanf_s(Maze, "%d %d", &row, &column);
        init(column, row);

        for (int r = 0; r < row; ++r) {
            for (int c = 0; c < column; ++c) {
                while (1) {
                    load = getc(Maze);
                    if ((load >= '0' && load <= '9')) {
                        ungetc(load, Maze);
                        fscanf_s(Maze, "%d", &map[r][c]);
                        break;
                    }
                    else if (load == 'e') { // �Ա� ��ġ ����
                        map[r][c] = load;
                        Node* entry = new Node(r, c);
                        locStack.push(entry);
                        break;
                    }
                    else if (load == 'x') { // �ⱸ ��ġ ����
                        map[r][c] = load;
                        exitLoc.setRow(r);
                        exitLoc.setCol(c);
                        break;
                    }
                }
                // �̷� üũ��
                //if (map[i][j] == 'e' || map[i][j] == 'x') { printf("%2c ", map[i][j]); }
                //else { printf("%2d ", map[i][j]); }
            }
            //printf("\n");
        }
        fclose(Maze);
    }

    bool isValidLoc(int r, int c) {
        if (r < 0 || c < 0 || r >= row || c >= column) //������ ����� �� �� ����
            return false;
        else //����ִ� ��γ� ���������� ���� true
            return (map[r][c] == '0' || map[r][c] == 'x');
    }

    void print() {  //���� Maze�� ȭ�鿡 ���
        printf("��ü �̷��� ũ�� = %d * %d\n", row, column);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (map[i][j] == 0) {
                    printf("  ");   // ��
                }
                else if (map[i][j] == 1) {
                    printf("��");    // ��
                }
                else if (map[i][j] == 7) {
                    printf("��");    // ������ ���
                }
                else if (map[i][j] == 'e') {
                    printf("��");    // �Ա�
                }
                else if (map[i][j] == 'x') {
                    printf("��");    // �ⱸ
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    void searchExit() { //���� �̷θ� Ž���ϴ� �Լ�
        print();

        while (locStack.isEmpty() == false) {  //������ ������� �ʴ� ����
            Location2D* here = locStack.pop()->getLocation(); //���ÿ� ��� ��ü ����
            int r = here->getRow();
            int c = here->getCol();

            map[r][c] = 7; //�������� ���� ���
            if (exitLoc.getCol() == c && exitLoc.getRow() == r) {
                return;
            }
            else {
                map[r][c] = 7; //������ ������ ǥ��
                print();

                //�� �� �ִ� �� �� ������
                if (isValidLoc(r - 1, c)) { locStack.push(new Node(r - 1, c)); }
                if (isValidLoc(r + 1, c)) { locStack.push(new Node(r + 1, c)); }
                if (isValidLoc(r, c - 1)) { locStack.push(new Node(r, c - 1)); }
                if (isValidLoc(r, c + 1)) { locStack.push(new Node(r, c + 1)); }
            }
        }
    }
};

int main() {
    /*
    LinkedStack stack;
    stack.dispaly();

    Node* node = stack.pop();
    printf("[Pop�׸�]\n");
    node->display();
    printf("\n");
    delete node;
    stack.dispaly();
    */
    /*
    LinkedStack locStack;
    Node* entry = new Node(1, 0);
    locStack.push(entry);

    while (locStack.isEmpty() == false) {

    }
    */

    Maze maze;
    maze.Load("�̷� test.txt");
    maze.searchExit();
}