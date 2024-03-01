// Tetris

/*
2024.02.15 
Start 화면 만들어 보겠음
*/

/*
2024.02.22 
테트리스 벽을 만들어 보겠음
-> 고민
Tetris 화면을 구성할 때 어떻게 구현을 할지 고민이 생김
Tetris 조각들이 판에 나오게 되는 것을 어떻게 표현할지, 지뢰 찾기처럼 좌표를 찍어야 하나?
*/

/*
2024.02.24
- 도형 제작
- 실시간으로 내려오게 함
*/

/*
2024.02.24
- 새로운 도형이 내려오게 함
*/

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>

using namespace std;

//테트리스 모양
const int height = 15;
const int width = 20;

//초기화된 테트리스 판
int last_board[height][width] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int next_board[height][width] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

const int num_shapes = 4; // 도형의 개수

// 각 도형의 2D 배열 정의
int box_1[2][2] = {
    {1, 1},
    {1, 1}
};

int box_2[1][4] = {
    {1, 1, 1, 1}
};

int box_3[2][2] = {
    {1, 0},
    {1, 1}
};

int box_4[2][3] = {
    {0, 1, 0},
    {1, 1, 1}
};

// 모든 도형을 담는 배열
int boxes[num_shapes][2][4] = {
    {
        {1, 1},
        {1, 1}
    },
    {
        {1, 1, 1, 1}
    },
    {
        {1, 0},
        {1, 1}
    },
    {
        {0, 1, 0},
        {1, 1, 1}
    }
};

// 나머지 코드...


// update 되는 행의 처음 값
int currow = 1;

void start_logo()
{
	printf("====================================================\n"
		"                                                    \n"
		"   ████████╗███████╗████████╗██████╗ ██╗███████╗    \n"
		"   ╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝    \n"
		"      ██║   █████╗     ██║   ██████╔╝██║███████╗    \n"
		"      ██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║    \n"
		"      ██║   ███████╗   ██║   ██║  ██║██║███████║    \n"
		"      ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝    \n"
		"                                                    \n"
		"====================================================\n");
	 

}

int start_str()
{  
	int startnum;
	printf("\n                                      >> start (1) <<\n");
	cout << "                                      >>  end (2)  <<\n";
	cin >> startnum;
	return startnum;
}


void TetrisWall()
{
    // system("clear"); // 화면을 지우고 새로 생성

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (next_board[i][j] == 1)
            {
                cout << '#';  // 블록이 있는 곳은 #
            }
            else
            {
                cout << ' ';  // 블록이 없는 곳은 공백
            }
        }
        cout << '\n';
    }
}

void ingbox(int num)
{
    switch (num)
    {
    case 1:
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                if (boxes[num - 1][i][j] == 1)
                {
                    next_board[currow + i][width / 2 - 1 + j] = 1;
                }
            }
        }
        break;

    case 2:
        for (int i = 0; i < 1; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (boxes[num - 1][i][j] == 1)
                {
                    next_board[currow + i + 1][width / 2 - 1 + j - 1] = 1;
                }
            }
        }
        break;

    case 3:
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                if (boxes[num - 1][i][j] == 1)
                {
                    next_board[currow + i][width / 2 - 1 + j] = 1;
                }
            }
        }
        break;

    case 4:
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (boxes[num - 1][i][j] == 1)
                {
                    next_board[currow + i][width / 2 - 1 + j] = 1;
                }
            }
        }
        break;
	}
	
}

bool isBlockOnBottom(int num)
{
    // 현재 도형이 바닥에 닿았는지 확인
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (boxes[num - 1][i][j] == 1 &&
                (last_board[currow + i + 1][width / 2 - 1 + j - 1] == 1 ||
                 next_board[currow + i + 1][width / 2 - 1 + j - 1] == 1))
            {
                return true;
            }
        }
    }

    return false;
}

void updateBoard(int num)
{
    // 현재 도형이 바닥에 도달하면
    if (isBlockOnBottom(num))
    {
        // 보드에 현재 도형 고정
        ingbox(num);

        // 이전 도형을 바닥에 고정시킨 상태를 보드에 반영
        for (int i = 1; i + 2 < height; ++i)
        {
            for (int j = 1; j < width - 1; ++j)
            {
                if (last_board[i][j] == 1)
                {
                    next_board[i][j] = 1;
                }
            }
        }

        // 행 위치 초기화
        currow = 1;

        // 랜덤으로 도형 내려오기
        num = rand() % 4 + 1;
        cout << "box_num : " << num;
    }
    else
    {
        // 아직 도형이 바닥에 도달하지 않았으면 행 위치 증가
        ++currow;
    }

    cout << "\n\n\n\n update \n\n\n\n";
    TetrisWall();
}



int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}



int main()
{
	int startnum;

	// 도형 번호 
	int box_num;

	// srand를 사용하여 난수 발생 초기화 (프로그램 시작시 한 번만 호출)
    srand(time(0));

	start_logo();
	startnum = start_str();
	printf("startnum : %d\n", startnum);

	if (startnum == 2)
	{
		printf("Programe END");
		return 0;
	}
	
	cout << "\n\n테트리스 게임을 시작합니다.\n\n";

	// 테트리스 보드 표시
	TetrisWall();
	// 랜덤으로 도형 내려오기
	box_num = rand() % 4 + 1;
	cout << "box_num : " << box_num;

	while (true)
	{
		// 일정 주기로 내려오는 행
		updateBoard(box_num);
			// delay 
		this_thread::sleep_for(chrono::seconds(1));
		// 현재 도형이 바닥에 도달하면
        if (currow + 2 >= height)
        {
            // 보드에 현재 도형 고정
            ingbox(box_num);

			// 이전 도형을 바닥에 고정시킨 상태를 보드에 반영
			for (int i = 1; i + 2 < height; ++i)
			{
				for (int j = 1; j < width - 1; ++j)
				{
					if (last_board[i][j] == 1)
					{
						next_board[i][j] = 1;
					}
				}
			}

			for (int i = 0; i < height; ++i) {
				for (int j = 0; j < width; ++j) {
					last_board[i][j] = next_board[i][j];
				}
			}

            // 행 위치 초기화
            currow = 1;

            // 랜덤으로 도형 내려오기
            box_num = rand() % 4 + 1;
            cout << "box_num : " << box_num;
        }
	}

	// 내려온 도형이 끝나면 다른 도형이 내려오게 하기
	

	return 0;
}