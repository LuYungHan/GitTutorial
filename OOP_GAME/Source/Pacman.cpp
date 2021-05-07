#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Pacman.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Pacman: Pacman class
	/////////////////////////////////////////////////////////////////////////////
	

	Pacman::Pacman()
	{
		Initialize();
	}

	int Pacman::GetX1()
	{
		return x;
	}

	int Pacman::GetY1()
	{
		return y;
	}

	int Pacman::GetX2()
	{
		return x + animation.Width();
	}

	int Pacman::GetY2()
	{
		return y + animation.Height();
	}

	void Pacman::Initialize()
	{
		const int X_POS = 305;
		const int Y_POS = 342;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}


	void Pacman::LoadBitmap()
	{
		
			animationRight.AddBitmap(IDB_BALL1, RGB(255, 255, 255));		//right
			animationRight.AddBitmap(IDB_BALL2, RGB(255, 255, 255));
			animationRight.AddBitmap(IDB_BALL3, RGB(255, 255, 255));
			animationRight.AddBitmap(IDB_BALL4, RGB(255, 255, 255));
			animationRight.AddBitmap(IDB_BALL2, RGB(255, 255, 255));
			animationRight.AddBitmap(IDB_BALL1, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT1, RGB(255, 255, 255));		//left
			animation.AddBitmap(IDB_BALLLEFT2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT3, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT4, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT1, RGB(255, 255, 255));	
			animationUp.AddBitmap(IDB_BALLUP1, RGB(255, 255, 255));	//Up
			animationUp.AddBitmap(IDB_BALLUP2, RGB(255, 255, 255));
			animationUp.AddBitmap(IDB_BALLUP3, RGB(255, 255, 255));
			animationUp.AddBitmap(IDB_BALLUP4, RGB(255, 255, 255));
			animationUp.AddBitmap(IDB_BALLUP2, RGB(255, 255, 255));
			animationUp.AddBitmap(IDB_BALLUP1, RGB(255, 255, 255));
//			animationDown.AddBitmap(IDB_BALLLEFT1, RGB(255, 255, 255));		//Down
			animationCenter.AddBitmap(IDB_BALL3, RGB(255, 255, 255));	//center
	}


	void Pacman::OnMove(int backgroundArray[479][636])

	{
		const int STEP_SIZE = 4;
		animation.OnMove();
		animationRight.OnMove();
		animationCenter.OnMove();
		animationUp.OnMove();
		int x_right = GetX2();
		int y_bottom = GetY2();
		if (isMovingLeft) {
			if (backgroundArray[y][x - STEP_SIZE] == 1||backgroundArray[y_bottom][x-STEP_SIZE]==1) {
				x = x+1;
				SetMovingLeft(false);
			}
			else {
				x -= STEP_SIZE;
			}
		}
		if (isMovingRight) {
			if (backgroundArray[y][x_right + STEP_SIZE] == 1||backgroundArray[y_bottom][x_right+STEP_SIZE]==1) {
				x = x-1;
				SetMovingRight(false);
			}
			else {
				x += STEP_SIZE;
			}
		}
		if (isMovingUp) {
			if (backgroundArray[y-STEP_SIZE][x] == 1||backgroundArray[y-STEP_SIZE][x_right]==1) {
				y = y+1;
				SetMovingUp(false);
			}
			else {
				y -= STEP_SIZE;
			}
		}
		if (isMovingDown) {
			if (backgroundArray[y_bottom + STEP_SIZE][x] == 1||backgroundArray[y_bottom+STEP_SIZE][x_right]==1) {
				y = y-1;
				SetMovingDown(false);
			}
			else {
				y += STEP_SIZE;
			}
		}
	}

	void Pacman::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Pacman::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Pacman::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Pacman::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Pacman::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Pacman::OnShow()
	{
		animationCenter.SetTopLeft(x, y);
		animationCenter.OnShow();
		if (isMovingRight) {
			animationRight.SetTopLeft(x, y);
			animationRight.OnShow();
		}
		if (isMovingLeft) {
			animation.SetTopLeft(x, y);
			animation.OnShow();
			
		}
		if (isMovingUp) {
			animationUp.SetTopLeft(x, y);
			animationUp.OnShow();

		}
/*		if (isMovingDown) {
			animationDown.SetTopLeft(x, y);
			animationDown.OnShow();

		}*/

	}
/*	void Pacman::OnShowLeft()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}*/
}