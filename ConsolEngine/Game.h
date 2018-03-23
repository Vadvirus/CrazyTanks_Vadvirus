#pragma once

#include "BaseApp.h"

class Game : public BaseApp
{
	typedef BaseApp Parent;

private:
	string pos[5];
	int health_ = 3;
	int count_ = 0;
	int X_[5], Y_[5];
	int r1_, r2_;
	char fig_[5][3][3];
	vector <pair <int, int> > OldCord_[5],clear_;
	bool error_ = 0;
	bool restart_ = 0;
	struct MyStruct
	{
		int XX, YY;
		string kyda;
		bool my;
	};
	bool death_[5];
	int kil_ = 0;
	vector < pair <int, int> > del_;
	vector <MyStruct> bullet_;
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
