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

#include <stdio.h>
#include <iostream>

using namespace std;

//테트리스 모양
const int height = 15;
const int width = 10;

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


void TetrisWall(int board[height][width])
{
	for (int i=0; i<height; ++i)
	{
		for(int j=0; j<width; ++j)
		{
			if (board[i][j] == 1) {
                cout << '#';  // 블록이 있는 곳은 #
            } else {
                cout << ' ';  // 블록이 없는 곳은 공백
            }
		}
		cout << '\n'; 
	}
}


int main()
{
	int startnum;
	// 테트리스 벽 만들기
	int tetrisH = 20;
	int tetrisW = 35;

	start_logo();
	startnum = start_str();
	printf("startnum : %d\n", startnum);

	if (startnum == 2)
	{
		printf("Programe END");
		return 0;
	}
	
	cout << "\n\n테트리스 게임을 시작합니다.\n\n";

	//초기화된 테트리스 판
	int board[height][width] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
	TetrisWall(board);
	return 0;
}