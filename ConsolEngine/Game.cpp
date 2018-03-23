#include "Game.h"
#include <conio.h>
#define F first
#define S second
void Game::ChangeFig(string position, int numb)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			fig_[numb][i][j] = ' ';
	pos_[numb] = position;
	if (position == "right")
	{
		fig_[numb][0][0] = '#';
		fig_[numb][0][1] = 'O';
		fig_[numb][0][2] = '#';
		fig_[numb][1][0] = '#';
		fig_[numb][1][1] = '-';
		fig_[numb][1][2] = '#';
	}
	else
		if (position == "down")
		{
			fig_[numb][0][0] = '#';
			fig_[numb][1][0] = 'O';
			fig_[numb][2][0] = '#';
			fig_[numb][0][1] = '#';
			fig_[numb][2][1] = '#';
			fig_[numb][1][1] = 'I';
		};
	if (position == "left")
	{
		fig_[numb][0][0] = '#';
		fig_[numb][0][1] = '-';
		fig_[numb][0][2] = '#';
		fig_[numb][1][0] = '#';
		fig_[numb][1][1] = 'O';
		fig_[numb][1][2] = '#';
	}
	else
		if (position == "up")
		{
			fig_[numb][0][0] = '#';
			fig_[numb][1][0] = 'I';
			fig_[numb][2][0] = '#';
			fig_[numb][0][1] = '#';
			fig_[numb][2][1] = '#';
			fig_[numb][1][1] = 'O';
		}
	if (numb == 0)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (fig_[0][i][j] == 'O') fig_[0][i][j] = char(health_ + 48);

}

void Game::Fire(int Number_Tank, string direction)
{
	MyStruct M;
	if (pos_[Number_Tank] == "up")
	{
		M.XX = X_[Number_Tank];
		M.YY = Y_[Number_Tank] - 2;
		M.direction = "up";
		M.my = Number_Tank;
	}
	if (pos_[Number_Tank] == "down")
	{
		M.XX = X_[Number_Tank];
		M.YY = Y_[Number_Tank] + 2;
		M.direction = "down";
		M.my = Number_Tank;
	}
	if (pos_[Number_Tank] == "left")
	{
		M.XX = X_[Number_Tank] - 2;
		M.YY = Y_[Number_Tank];
		M.direction = "left";
		M.my = Number_Tank;
	}
	if (pos_[Number_Tank] == "right")
	{
		M.XX = X_[Number_Tank] + 2;
		M.YY = Y_[Number_Tank];
		M.direction = "right";
		M.my = Number_Tank;
	}
	bullet_.push_back(M);
}
void Game::SetFig(string position, int XX, int YY, int numb)
{
	ChangeFig(position, numb);
	OldCord_[numb] = clear_;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (fig_[numb][i][j] != ' ')
			{
				SetChar(XX + i - 1, YY + j - 1, fig_[numb][i][j]);
				OldCord_[numb].push_back(make_pair(XX + i - 1, YY + j - 1));
			}
}
void Game::Delete()
{
	for (int i = 0; i < del_.size(); i++)
		SetChar(del_[i].first, del_[i].second, L' ');
	for (int i = 0; i <= 4; i++)
		if (!death_[i]) SetFig(pos_[i], X_[i], Y_[i], i);
}
void Game::DestroyTank(int x, int y, int enemy)
{

	if (enemy == 0) kil_++;
	for (int i = 0; i <= 4; i++)
		if (abs(X_[i] - x) < 2 && abs(Y_[i] - y) < 2)
		{
			if (enemy > 0 && i > 0) return;
			if (i == 0) health_--;
			if (health_ == 0 || i > 0)
				death_[i] = true;
			UpdateFig(i);
			return;
		}
}
void Game::DispBullets(int numb)
{
	Delete();

	for (int i = 0; i < bullet_.size(); i++)
	{

		int a = bullet_[i].XX;
		int b = bullet_[i].YY;



		if (GetChar(a, b) != ' ')
		{
			if (GetChar(a, b) == 'G') { health_ = 0, death_[0] = true; return; }
			if (GetChar(a, b) != '1')
				DestroyTank(a, b, bullet_[i].my);
			else if (a != 0 && a != 30 && b != 0 && b != 21) SetChar(a, b, L' ');
			bullet_.erase(bullet_.begin() + i);
		}
		else
		{
			SetChar(a, b, L'*');
			del_.push_back(make_pair(a, b));

			if (bullet_[i].direction == "up")
				bullet_[i].YY--;

			if (bullet_[i].direction == "down")
				bullet_[i].YY++;

			if (bullet_[i].direction == "right")
				bullet_[i].XX++;

			if (bullet_[i].direction == "left")
				bullet_[i].XX--;
		}

	}
}
bool Game::Good(string direction, int Numb_of_tank)
{
	if (direction == "left")
		for (int j = 0; j < 3; j++)
			if (fig_[Numb_of_tank][0][j] != ' ')
				if (GetChar(X_[Numb_of_tank] + 0 - 2, Y_[Numb_of_tank] + j - 1) != ' ') return false;

	if (direction == "right")
		for (int j = 0; j < 3; j++)
			if (fig_[Numb_of_tank][1][j] != ' ')
				if (GetChar(X_[Numb_of_tank] + 1 + 1, Y_[Numb_of_tank] + j - 1) != ' ') return false;

	if (direction == "up")
		for (int i = 0; i < 3; i++)
			if (fig_[Numb_of_tank][i][0] != ' ')
				if (GetChar(X_[Numb_of_tank] + i - 1, Y_[Numb_of_tank] + 0 - 2) != ' ') return false;

	if (direction == "down")
		for (int i = 0; i < 3; i++)
			if (fig_[Numb_of_tank][i][1] != ' ')
				if (GetChar(X_[Numb_of_tank] + i - 1, Y_[Numb_of_tank] + 1 + 1) != ' ') return false;

	return true;

}

void Game::UpdateFig(int numb)
{
	if (OldCord_[numb].size() > 0)
		for (int i = 0; i < OldCord_[numb].size(); i++) SetChar(OldCord_[numb][i].F, OldCord_[numb][i].S, L' ');

}
bool Game::IsGood(int XX, int YY)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (GetChar(XX + i - 1, YY + j - 1) != ' ') return false;
	return true;
}
Game::Game() : Parent(100, 80)
{

	// Draw the field
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
	for (int i = 1; i < 7; i++) SetChar(7, i, L'1');
	for (int i = 15; i < 21; i++) SetChar(7, i, L'1');
	for (int i = 8; i < 20; i++) SetChar(i, 15, L'1');
	for (int i = 8; i < 20; i++) SetChar(i, 6, L'1');
	for (int i = 16; i < 22; i++)
	{
		SetChar(i, 10, L'1');
		SetChar(i, 11, L'1');
	}
	for (int i = 9; i < 14; i++)
	{
		SetChar(25, i, L'1');
		SetChar(26, i, L'1');
	}
	SetChar(27, 10, L'1');
	SetChar(28, 10, L'1');
	SetChar(29, 10, L'1');
	SetChar(27, 9, L'1');
	SetChar(28, 9, L'1');
	SetChar(29, 9, L'1');
	SetChar(28, 11, L'G');
	SetChar(27, 12, L'1');
	SetChar(28, 12, L'1');
	SetChar(29, 12, L'1');
	SetChar(27, 13, L'1');
	SetChar(28, 13, L'1');
	SetChar(29, 13, L'1');
	for (int i = 0; i <= 4; i++)
	{
		X_[i] = rand() % 21;
		Y_[i] = rand() % 30;
	}
	for (int i = 0; i <= 4; i++)
	{
		death_[i] = false;
		while (!IsGood(X_[i], Y_[i]))
		{
			X_[i] = rand() % 30;
			Y_[i] = rand() % 21;
		}
		SetFig("right", X_[i], Y_[i], i);
	}


}
void Game::Go(int numb)
{
	r1_ = rand() % 100;
	r2_ = rand() % 100;
	if (r1_ > 50)
	{
		if (r2_ > 50)
		{
			if (Good("right", numb))
			{
				X_[numb]++;
				ChangeFig("right", numb);
			}
			else Go(numb);
		}
		else
		{
			if (Good("left", numb))
			{
				X_[numb]--;
				ChangeFig("left", numb);
			}
			else Go(numb);
		}
	}
	else
	{
		if (r2_ > 50)
		{
			if (Good("up", numb))
			{
				Y_[numb]--;
				ChangeFig("up", numb);
			}
			else Go(numb);
		}
		else
		{
			if (Good("down", numb))
			{
				Y_[numb]++;
				ChangeFig("down", numb);
			}
			else Go(numb);
		}
	}
}
void Game::KeyPressed(int btnCode)
{

	if (btnCode == 32) //space
		Fire(0, pos_[0]);
	else if (btnCode == 224)
	{

		int g = getch();
		if (g == 80) //arrow to down

		{
			ChangeFig("down", 0);
			if (Good("down", 0)) Y_[0] += 1;
		}
		else if (g == 75) //arrow to left

		{
			ChangeFig("left", 0);
			if (Good("left", 0)) X_[0] -= 1;
		}
		else if (g == 77)//arrow to right
			
		{
			ChangeFig("right",0);
		if (Good("right",0)) X_[0] += 1;
		}
		else if (g == 72)//arrow to up

		{
			ChangeFig("up", 0);
			if (Good("up", 0)) Y_[0] -= 1;
		}
	}

}

void Game::UpdateF(float deltaTime)
{
	if (!death_[0])
		count_++;

	if (count_ % 30 == 0)
	{
		if (count_ == 90) {

			for (int i = 1; i <= 4; i++)
				if (!death_[i])
					Fire(i, pos_[i]);
			count_ = 0;
		}
		for (int i = 1; i <= 4; i++)
		{
			if (!death_[i])
				Go(i);
		}
	}

	for (int i = 0; i <= 4; i++)
	{
		ChangeFig(pos_[i], i);
		if (!death_[i])
		{
			UpdateFig(i);
			SetFig(pos_[i], X_[i], Y_[i], i);
		}
	}
	DispBullets(0);



}



