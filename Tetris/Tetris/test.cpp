// Tetris

/*
2024.02.15 
Start 화면 만들어 보겠음
*/

#include <stdio.h>
#include <iostream>

using namespace std;

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

void main()
{
	int startnum;
	start_logo();
	startnum = start_str();
	printf("startnum : %d\n", startnum);

	if (startnum == 2)
	{
		printf("Programe END");
		return;
	}
	
	cout << "테트리스 게임을 시작합니다.";
}