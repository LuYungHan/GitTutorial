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
		const int Y_POS = 340;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}


	void Pacman::LoadBitmap()
	{

			animation.AddBitmap(IDB_BALLLEFT1, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT3, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT4, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALLLEFT1, RGB(255, 255, 255));

/*			animation.AddBitmap(IDB_BALL1, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALL2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALL3, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALL4, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALL2, RGB(255, 255, 255));
			animation.AddBitmap(IDB_BALL1, RGB(255, 255, 255));*/
	}

	void Pacman::LoadBitmapLeft()
	{
		animation.AddBitmap(IDB_BALL1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BALL2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BALL3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BALL4, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BALL2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_BALL1, RGB(255, 255, 255));
	}

	void Pacman::OnMove()
	{
		const int STEP_SIZE = 2;
		animation.OnMove();

		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;
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
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}