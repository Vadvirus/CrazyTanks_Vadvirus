#pragma once

#include "BaseApp.h"

class Game : public BaseApp
{
	typedef BaseApp Parent;

private:
	string pos[5];
	int health = 3;
	int count=0;
	int X[5], Y[5];
	int r1, r2;
	int speed=20;
	int rightLimit,leftLimit,downLimit;
	char fig[5][3][3];
	vector <pair <int, int> > OldCord[5],clear;
	bool error = 0;
	bool restart = 0;
	struct MyStruct
	{
		int XX, YY;
		string kyda;
		bool my;
	};
	bool death[5];
	int kil = 0;
	vector < pair <int, int> > del;
	vector <MyStruct> bullet;
public:
	Game();
	bool Game::IsGood(int XX,int YY);
	void Game::DispBullets(int numb);
	void Game::Delete();
	void Fire(int Number_Tank, string kyda);
	void UpdateFig(int numb);
	bool Game::Good(string s, int Numb_of_tank);
	void SetFig(string pos, int XX, int YY, int numb);
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	void ChangeFig(string position, int numb) ;
	void Game::Go(int numb);
	void Game::DestroyTank(int x, int y, int kto);
	
};
