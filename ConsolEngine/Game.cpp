#include "Game.h"
#include <conio.h>
#define F first
#define S second
void Game::ChangeFig(string position, int numb)
{	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			fig[numb][i][j] = ' ';
	pos[numb] = position;
	if (position == "right")
	{
		fig[numb][0][0] = '#';
		fig[numb][0][1] = 'O';
		fig[numb][0][2] = '#';
		fig[numb][1][0] = '#';
		fig[numb][1][1] = '-';
		fig[numb][1][2] = '#';
	} else
	if (position == "down")
	{
		fig[numb][0][0] = '#';
		fig[numb][1][0] = 'O';
		fig[numb][2][0] = '#';
		fig[numb][0][1] = '#';
		fig[numb][2][1] = '#';
		fig[numb][1][1] = 'I';
	};
	if (position == "left")
	{
		fig[numb][0][0] = '#';
		fig[numb][0][1] = '-';
		fig[numb][0][2] = '#';
		fig[numb][1][0] = '#';
		fig[numb][1][1] = 'O';
		fig[numb][1][2] = '#';
	}
	else
	if (position == "up")
	{
		fig[numb][0][0] = '#';
		fig[numb][1][0] = 'I';
		fig[numb][2][0] = '#';
		fig[numb][0][1] = '#';
		fig[numb][2][1] = '#';
		fig[numb][1][1] = 'O';
	}
	if (numb==0)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (fig[0][i][j] == 'O') fig[0][i][j] = char(health+48);

}

void Game::Fire(int Number_Tank, string kyda)
{	
	MyStruct M;
	if (pos[Number_Tank] == "up")
	{
		M.XX = X[Number_Tank];
		M.YY = Y[Number_Tank] - 2;
		M.kyda = "up";
		M.my = Number_Tank;
	}
	if (pos[Number_Tank] == "down")
	{
		M.XX = X[Number_Tank];
		M.YY = Y[Number_Tank] + 2;
		M.kyda = "down";
		M.my = Number_Tank;
	}
	if (pos[Number_Tank] == "left")
	{
		M.XX = X[Number_Tank] - 2;
		M.YY = Y[Number_Tank];
		M.kyda = "left";
		M.my = Number_Tank;
	}
	if (pos[Number_Tank] == "right")
	{
		M.XX = X[Number_Tank] + 2;
		M.YY = Y[Number_Tank];
		M.kyda = "right";
		M.my = Number_Tank;
	}
	bullet.push_back(M);
}
void Game::SetFig(string position, int XX, int YY, int numb)
{	
	ChangeFig(position, numb);
	OldCord[numb] = clear;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (fig[numb][i][j] != ' ') 
			{
				SetChar(XX + i - 1, YY + j - 1, fig[numb][i][j]);
				OldCord[numb].push_back(make_pair(XX + i - 1, YY + j - 1));
			}
}
void Game::Delete()
{
	for (int i = 0; i < del.size(); i++)
		SetChar(del[i].first, del[i].second, L' ');
	for (int i=0;i<=4;i++)
	if (!death[i]) SetFig(pos[i], X[i], Y[i], i);
}
void Game::DestroyTank(int x, int y, int kto)
{	
	
	if (kto == 0) kil++;
	for (int i = 0; i <= 4; i++)
		if (abs(X[i] - x) < 2 && abs(Y[i] - y) < 2)
		{	
			if (kto > 0 && i > 0) return;
			if (i == 0) health --;
			if (health==0 || i>0)
			death[i] = true;
			UpdateFig(i);
			return;
		}
}
void Game::DispBullets(int numb)
{	
	Delete();

	for (int i = 0; i < bullet.size(); i++)
	{
		
		int a = bullet[i].XX;
		int b = bullet[i].YY;
		
		
		
		if (GetChar(a, b) != ' ')
		{
			if (GetChar(a, b) != '1')
					DestroyTank(a, b, bullet[i].my);
			bullet.erase(bullet.begin() + i);
		}
		else
		{
			SetChar(a, b, L'*');
			del.push_back(make_pair(a, b));

			if (bullet[i].kyda == "up")
				bullet[i].YY--;

			if (bullet[i].kyda == "down")
				bullet[i].YY++;

			if (bullet[i].kyda == "right")
				bullet[i].XX++;

			if (bullet[i].kyda == "left")
				bullet[i].XX--;
		}
		
	}
}
bool Game::Good(string s, int Numb_of_tank)
{	
	if (s == "left")
			for (int j = 0; j < 3; j++)
				if (fig[Numb_of_tank][0][j] != ' ') 
					if (GetChar(X[Numb_of_tank] + 0 - 2, Y[Numb_of_tank] + j - 1) != ' ') return false;
					
	if (s == "right")
			for (int j = 0; j < 3; j++)
				if (fig[Numb_of_tank][1][j] != ' ')
					if (GetChar(X[Numb_of_tank] + 1 + 1, Y[Numb_of_tank] + j - 1) != ' ') return false;

	if (s == "up")
		for (int i = 0; i < 3; i++)
			if (fig[Numb_of_tank][i][0] != ' ')
				if (GetChar(X[Numb_of_tank] + i - 1, Y[Numb_of_tank] + 0 - 2) != ' ') return false;

	if (s == "down")
		for (int i = 0; i < 3; i++)
			if (fig[Numb_of_tank][i][1] != ' ')
				if (GetChar(X[Numb_of_tank] + i - 1, Y[Numb_of_tank] + 1 + 1) != ' ') return false;

	return true;

}

void Game::UpdateFig(int numb)
{
	if (OldCord[numb].size() > 0)
		for (int i = 0; i < OldCord[numb].size();i++) SetChar(OldCord[numb][i].F, OldCord[numb][i].S, L' ');
	
}
bool Game::IsGood(int XX,int YY)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (GetChar(XX + i - 1, YY + j - 1)!=' ') return false;
	return true;
}
Game::Game() : Parent(100, 80)
{
	
	//Рисуем поле
	for (int i = 0; i <= 21; i++)
	{
		SetChar(0, i, L'1');
		SetChar(30, i, L'1');
	}
	for (int i = 0; i <= 29; i++)
	{
		SetChar(i, 0, L'1');
		SetChar(i, 21, L'1');
	}
	for (int i = 1;i < 7;i++) SetChar(7, i, L'1');
	for (int i = 15; i < 21; i++) SetChar(7, i, L'1');
	for (int i = 8; i < 20; i++) SetChar(i, 15, L'1');
	for (int i = 8; i < 20; i++) SetChar(i, 6, L'1');
	for (int i = 16; i < 22; i++) 
	{
		SetChar(i, 10, L'1');
		SetChar(i, 11, L'1');
	}
	for (int i = 4; i < 18; i++) SetChar(25, i, L'1');
	for (int i = 0; i <= 4; i++) 
	{	
		X[i] = rand() % 21;
		Y[i] = rand() % 30;
	}
	for (int i = 0; i <= 4; i++)
	{	
		death[i] = false;
		while (!IsGood(X[i], Y[i]))
		{
			X[i] = rand() % 30;
			Y[i] = rand() % 21;
		}
		SetFig("right", X[i], Y[i], i);
	}
	
	
}
void Game::Go(int numb)
{
	r1 = rand() % 100;
	r2 = rand() % 100;
	if (r1 > 50)
	{
		if (r2 > 50)
		{
			if (Good("right", numb))
			{
				X[numb]++;
				ChangeFig("right", numb);
			}
			else Go(numb);
		}
		else
		{
			if (Good("left", numb)) 
			{
				X[numb]--;
				ChangeFig("left", numb);
			}
			else Go(numb);
		}
	}
	else
	{
		if (r2 > 50)
		{
			if (Good("up", numb)) 
			{
				Y[numb]--;
				ChangeFig("up", numb);
			}
			else Go(numb);
		}
		else
		{
			if (Good("down", numb))
			{
				Y[numb]++;
				ChangeFig("down", numb);
			}
			else Go(numb);
		}
	}
}
void Game::KeyPressed(int btnCode)
{

	if (btnCode == 32) //space
		Fire(0,pos[0]); 
	else if (btnCode == 224)
	{	
		
		int g = getch();
		if (g == 80) //стрелка вниз
		{
			ChangeFig("down",0);
			if (Good("down",0)) Y[0] += 1;
		}
		else if (g == 75) //стрелка влево
		{
			ChangeFig("left",0);
			if (Good("left",0)) X[0] -= 1;
		}
		else if (g == 77)//стрелка вправо
		{
			ChangeFig("right",0);
			if (Good("right",0)) X[0] += 1;
		}
		else if (g == 72)//стрелка вверх
		{
			ChangeFig("up",0);
			if (Good("up",0)) Y[0] -= 1;
		}
	}
	
}

void Game::UpdateF(float deltaTime)
{
	if (!death[0]) 
		count++;
		
	
	if (kil == 4) restart = true;
	if (count % 30==0)
	{
		if (count == 90) {
			
			for (int i = 1; i <= 4; i++)
				if (!death[i])
					Fire(i, pos[i]);
			count = 0;
		}	
		for (int i = 1; i <= 4; i++)
		{
			if (!death[i]) 
				Go(i);
		}
	}
	
	for (int i = 0; i <= 4; i++) 
	{
		ChangeFig(pos[i], i);
		if (!death[i])
		{
			UpdateFig(i);
			SetFig(pos[i], X[i], Y[i], i);
		}
	}
	DispBullets(0);
	
	
	
}


	 