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
		tryingDown = tryingLeft = tryingRight = tryingUp = false;
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
			animationDown.AddBitmap(IDB_BALLDOWN1, RGB(255, 255, 255));		//Down
			animationDown.AddBitmap(IDB_BALLDOWN2, RGB(255, 255, 255));
			animationDown.AddBitmap(IDB_BALLDOWN3, RGB(255, 255, 255));
			animationDown.AddBitmap(IDB_BALLDOWN4, RGB(255, 255, 255));
			animationDown.AddBitmap(IDB_BALLDOWN2, RGB(255, 255, 255));
			animationDown.AddBitmap(IDB_BALLDOWN1, RGB(255, 255, 255));
			animationCenter.AddBitmap(IDB_BALL3, RGB(255, 255, 255));	//center
	}


	void Pacman::OnMove(int backgroundArray[479][636])

	{
		const int STEP_SIZE = 4;
		animation.OnMove();
		animationRight.OnMove();
		animationCenter.OnMove();
		animationUp.OnMove();
		animationDown.OnMove();
		int x_right = GetX2();
		int y_bottom = GetY2();
		if (tryingDown) {
			SetTryingLeft(false);
			SetTryingRight(false);
			SetTryingUp(false);
			if (backgroundArray[y_bottom + STEP_SIZE][x] == 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 1 ||
				backgroundArray[y_bottom + 2*STEP_SIZE][x] == 1 || backgroundArray[y_bottom + 2*STEP_SIZE][x_right] == 1 ||
				backgroundArray[y_bottom + 3 * STEP_SIZE][x] == 1 || backgroundArray[y_bottom + 3 * STEP_SIZE][x_right] == 1) {
				SetMovingDown(false);
			}
			else {
				SetMovingDown(true);
				SetTryingDown(false);
				SetMovingLeft(false);
				SetMovingRight(false);
				SetMovingUp(false);
			}
		}
		if (tryingRight) {
			SetTryingLeft(false);
			SetTryingDown(false);
			SetTryingUp(false);
			if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1 || 
				backgroundArray[y][x_right + 2*STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + 2*STEP_SIZE] == 1 ||
				backgroundArray[y][x_right + 3 * STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + 3 * STEP_SIZE] == 1) {
				SetMovingRight(false);
			}
			else {
				SetMovingRight(true);
				SetTryingRight(false);
				SetMovingLeft(false);
				SetMovingDown(false);
				SetMovingUp(false);
			}
		}
		if (tryingLeft) {
			SetTryingDown(false);
			SetTryingRight(false);
			SetTryingUp(false);
			if (backgroundArray[y][x - STEP_SIZE] == 1 || backgroundArray[y_bottom][x - STEP_SIZE] == 1 ||
				backgroundArray[y][x - 2*STEP_SIZE] == 1 || backgroundArray[y_bottom][x - 2*STEP_SIZE] == 1 ||
				backgroundArray[y][x - 3 * STEP_SIZE] == 1 || backgroundArray[y_bottom][x - 3 * STEP_SIZE] == 1) {
				SetMovingLeft(false);
			}
			else {
				SetMovingLeft(true);
				SetTryingLeft(false);
				SetMovingDown(false);
				SetMovingRight(false);
				SetMovingUp(false);
			}
		}
		if (tryingUp) {
			SetTryingLeft(false);
			SetTryingRight(false);
			SetTryingDown(false);
			if (backgroundArray[y - STEP_SIZE][x] == 1 || backgroundArray[y - STEP_SIZE][x_right] == 1 ||
				backgroundArray[y - 2*STEP_SIZE][x] == 1 || backgroundArray[y - 2*STEP_SIZE][x_right] == 1 ||
				backgroundArray[y - 3 * STEP_SIZE][x] == 1 || backgroundArray[y - 3 * STEP_SIZE][x_right] == 1) {
				SetMovingUp(false);
			}
			else {
				SetMovingUp(true);
				SetTryingUp(false);
				SetMovingLeft(false);
				SetMovingRight(false);
				SetMovingDown(false);
			}
		}

		if (isMovingLeft) {
			SetTryingLeft(false);
			if (backgroundArray[y][x - STEP_SIZE] == 1 || backgroundArray[y_bottom][x - STEP_SIZE] == 1) {
				x = x;
			}
			else {
				x -= STEP_SIZE;
			}
		}
		if (isMovingRight) {
			SetTryingRight(false);
			if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
				x = x;
			}
			else {
				x += STEP_SIZE;
			}
		}
		if (isMovingUp) {
			SetTryingUp(false);
			if (backgroundArray[y - STEP_SIZE][x] == 1 || backgroundArray[y - STEP_SIZE][x_right] == 1) {
				y = y;
			}
			else {
				y -= STEP_SIZE;
			}
		}
		if (isMovingDown) {
			SetTryingDown(false);
			if (backgroundArray[y_bottom + STEP_SIZE][x] == 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 1) {
				y = y;
			}
			else {
				y += STEP_SIZE;
			}
		}
	}

	void Pacman::SetTryingDown(bool flag) 
	{
		tryingDown = flag;
	}

	void Pacman::SetTryingLeft(bool flag)
	{
		tryingLeft = flag;
	}

	void Pacman::SetTryingRight(bool flag)
	{
		tryingRight = flag;
	}

	void Pacman::SetTryingUp(bool flag)
	{
		tryingUp = flag;
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
			SetTryingRight(false);
		}
		if (isMovingLeft) {
			animation.SetTopLeft(x, y);
			animation.OnShow();
			SetTryingLeft(false);
		}
		if (isMovingUp) {
			animationUp.SetTopLeft(x, y);
			animationUp.OnShow();
			SetTryingUp(false);
		}
		if (isMovingDown) {
			animationDown.SetTopLeft(x, y);
			animationDown.OnShow();
			SetTryingDown(false);
		}

	}
}