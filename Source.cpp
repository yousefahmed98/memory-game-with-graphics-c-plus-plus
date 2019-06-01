#include <iostream>
#include<Windows.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <sstream>
#include <MMSystem.h>
#include <mciapi.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
#include "CMUgraphicsLib\CMUgraphics.h"
window WIND(1372, 200);
void CreateStatusBar();
void squares(string []);
void PrintMessage(string msg);
void stop();
int main()
{
	

	CreateStatusBar();
	vector <string> alpha;
	vector <string> alpha2;
	string arr[20],darr[20];
	string s,s1,s2;
	stringstream convert;
	int r1, r2,i=0,q=0,j=10,score1=0,score2=0,n=0,x,y,click1,click2;
	//load all images to the game
	alpha.push_back("images\\A.jpg");
	alpha.push_back("images\\B.jpg");
	alpha.push_back("images\\C.jpg");
	alpha.push_back("images\\D.jpg");
	alpha.push_back("images\\E.jpg");
	alpha.push_back("images\\F.jpg");
	alpha.push_back("images\\G.jpg");
	alpha.push_back("images\\H.jpg");
	alpha.push_back("images\\I.jpg");
	alpha.push_back("images\\J.jpg");
	alpha2.push_back("images\\A.jpg");
	alpha2.push_back("images\\B.jpg");
	alpha2.push_back("images\\C.jpg");
	alpha2.push_back("images\\D.jpg");
	alpha2.push_back("images\\E.jpg");
	alpha2.push_back("images\\F.jpg");
	alpha2.push_back("images\\G.jpg");
	alpha2.push_back("images\\H.jpg");
	alpha2.push_back("images\\I.jpg");
	alpha2.push_back("images\\J.jpg");
	//load all ? images
	for (int i = 0; i < 10; i++)
		darr[i] = "images\\square.jpg";
	for (int i = 10; i < 20;i++)
		darr[i] = "images\\square2.jpg";
	// to change the order of alpha images
	while (alpha.size() || alpha2.size())
	{
		srand(time(NULL));
		r1 = rand() % (alpha.size());
		r2 = rand() % (alpha2.size());
		arr[i] = alpha[r1];
		alpha.erase(alpha.begin() + r1);
		i++;
		arr[j] = alpha2[r2];
		alpha2.erase(alpha2.begin()+r2);
		j++;
	}
	
	while (score1 + score2 < 10)
	{ 
		for (int i = 0; i<10; i++)
			WIND.DrawImage(arr[i], i * 65, 0, 65, 100);
		for (int i = 10; i<20; i++)
			WIND.DrawImage(arr[i], i * 65, 0, 65, 100);
		stop();
		stop();
		squares(darr);
		
		if (n % 2 == 0)
		{
			convert << score1;
			s = convert.str();
			PrintMessage("Player 1's Turn                                  Score= "+s);
			convert.str("");
		}
		else
		{
			convert << score2;
			s = convert.str();
			PrintMessage("Player 2's Turn                                  Score= " + s);
			convert.str("");
		}
		stop();
		do 
		{	 
			PrintMessage("Please Click the first click");
			// to get the positon of click mouse
			WIND.WaitMouseClick(x, y);
			// sound for click
			mciSendString("play sound\\click.mp3 wait", NULL, 0, NULL);
			click1 = x / 65;
			if (click1 > 19&&y<100)
				return 0;
		} while (y > 100 || x > 10 * 65);
		WIND.DrawImage(arr[click1], click1 * 65, 0, 65, 100);
		do
		{
			PrintMessage("Please Click the second click");
			WIND.WaitMouseClick(x, y);
			mciSendString("play sound\\click.mp3 wait", NULL, 0, NULL);
			click2 = x / 65;
			// end game if click on exist image position
			if (click2 > 19 && y<100)
				return 0;
		} while (y > 100 || x<10*65);
		//after you get the posiston draw the selected image
		WIND.DrawImage(arr[click2], click2 * 65, 0, 65, 100);
		stop();
		if (arr[click1] == arr[click2])
		{
			darr[click1] = darr[click2] = arr[click1];
			mciSendString("play sound\\Correct.mp3 wait", NULL, 0, NULL);

			if (n % 2 == 0)
				score1++;
			else
				score2++;
		}

		n++;
		}
	
	if (score1 > score2)
	{
		PrintMessage("Player 1 is the winner");
		mciSendString("play sound\\Congratulations.mp3 wait", NULL, 0, NULL);
	}
	else if (score1 < score2)
	{
		PrintMessage("Player 2 is the winner");
		mciSendString("play sound\\Congratulations.mp3 wait", NULL, 0, NULL);
	}
	
	else
	{
		PrintMessage("Draw");
		mciSendString("play sound\\wlaw3mloha.mp3 wait", NULL, 0, NULL);
	}
	return 0;
	}

void CreateStatusBar()
{
	WIND.SetPen(NAVYBLUE, 2);
	WIND.SetBrush(HONEYDEW);
	WIND.DrawRectangle(0, 120, 1372, 200);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintMessage(string msg)	//Prints a message on status bar
{
	CreateStatusBar();	//First clear the status bar

	WIND.SetPen(BLACK, 50);
	WIND.SetFont(40, BOLD, BY_NAME, "Arial");
	WIND.DrawString(10, 200 - (int)( 80/ 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void squares(string *arr)
{
	for (int i = 0; i<10; i++)
		WIND.DrawImage(arr[i], i * 65, 0, 65, 100);
	for (int i = 10; i<20; i++)
		WIND.DrawImage(arr[i], i * 65, 0, 65, 100);
	WIND.DrawImage("images\\exit.jpg", 20 * 65, 0, 65, 100);
}
void stop()
{
	for (int i = 0; i < 300000000; i++)
	{ }
}
