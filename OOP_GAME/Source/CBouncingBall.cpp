#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Pacman.h"
#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBouncingBall: BouncingBall class
	/////////////////////////////////////////////////////////////////////////////

	CBouncingBall::CBouncingBall()
	{
		Initialize();
		/*
		const int INITIAL_VELOCITY = 15;	// ��l���k�t��
		const int FLOOR = 350;				// �a�O�y��
		floor = FLOOR;
		y = 180; x = FLOOR - 1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		*/
	}
	void CBouncingBall::Initialize() {

		const int INITIAL_VELOCITY = 15;	// ��l���k�t��
		const int FLOOR = 350;				// �a�O�y��
		floor = FLOOR;
		y = 180; x = FLOOR - 1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;

		is_alive = true;
		//xx = yy = dxx = dyy = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		tryingDown = tryingLeft = tryingRight = tryingUp = false;

	}
	int CBouncingBall::GetX1()
	{
		return x;
	}

	int CBouncingBall::GetY1()
	{
		return y;
	}

	int CBouncingBall::GetX2()
	{
		return x + animation.Width();
	}

	int CBouncingBall::GetY2()
	{
		return y + animation.Height();
	}

	bool CBouncingBall::HitEraser(Pacman *pacman)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(pacman->GetX1(), pacman->GetY1(),
			pacman->GetX2(), pacman->GetY2());
	}
	bool CBouncingBall::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x;		//�������W��x�y��
		int y1 = y;		//�������W��y�y��
		int x2 = x1 + animation.Width();	// �y���k�U��x�y��
		int y2 = y1 + animation.Height();	// �y���k�U��y�y��
									//
									// �˴��y���x�λP�ѼƯx�άO�_���涰
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}
	bool CBouncingBall::IsAlive()
	{
		return is_alive;
	}
	void CBouncingBall::LoadBitmap()
	{
		char *filename[4] = { ".\\RES\\redghost01.bmp",".\\RES\\redghost02.bmp",".\\RES\\redghost03.bmp",".\\RES\\redghost04.bmp" };
		for (int i = 0; i < 4; i++)	// ���J�ʵe(��4�i�ϧκc��)
			animation.AddBitmap(filename[i], RGB(0, 0, 0));
	}


	void CBouncingBall::TrackPacman(Pacman *pacman, int num)
	{
		if (num < 25) {

			if (rising) {			// ���k���A
				if (velocity > 0) {
					x -= velocity;	// ��t�� > 0�ɡAx�b���k(����velocity���I�Avelocity����쬰 �I/��)
					velocity--;		// �����O�v�T�A�U�������t�׭��C
				}
				else {
					rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�k��
					velocity = 1;	// �U������t(velocity)��1
				}
			}
			else {				// �U�����A
				if (x < floor - 1) {  // ��y�y���٨S�I��a�O
					x += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
					velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
				}
				else {
					x = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
					rising = true;	// �����ϼu�A�U���אּ�W��
					velocity = initial_velocity; // ���]�W�ɪ�l�t��
				}
			}
		}
	}

	void CBouncingBall::OnMove(int backgroundArray[479][636], Pacman *pacman, int num)
	{
		if (num >= 25) {

			const int STEP_SIZE = 4;
			animation.OnMove();

			int x_right = GetX2();
			int y_bottom = GetY2();
			int x_left = GetX1();
			int y_top = GetY1();
			/*if (pacman->GetX2() < x_right) {
				x_right -= STEP_SIZE;
			}else {
				x_right += STEP_SIZE;
			}
			if (pacman->GetY2() < y_bottom) {
				y_bottom -= STEP_SIZE;
			}else {
				y_bottom += STEP_SIZE;
			}*/
			//for (;(abs(pacman->GetX2() - x_right)) > 5;) {
			if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom) && (pacman->GetX1() > x_left) && (pacman->GetY2() > y_top)) {
				//SetTryingLeft(false);
				//SetTryingRight(false);
				//SetTryingUp(false);
				if (backgroundArray[y_bottom + STEP_SIZE][x] == 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 1) {
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
			if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom)&&(pacman->GetX1() > x_left)&&(pacman->GetY2() > y_top)) {
				//SetTryingLeft(false);
				//SetTryingDown(false);
				//SetTryingUp(false);
				if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
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
			if ((pacman->GetX2() < x_right) && (pacman->GetY2() < y_bottom) && (pacman->GetX1() < x_left) && (pacman->GetY2() < y_top)) {
				//SetTryingDown(false);
				//SetTryingRight(false);
				//SetTryingUp(false);
				if (backgroundArray[y][x - STEP_SIZE] == 1 || backgroundArray[y_bottom][x - STEP_SIZE] == 1) {
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
			if ((pacman->GetX2() < x_right) && (pacman->GetY2() < y_bottom) && (pacman->GetX1() < x_left) && (pacman->GetY2() < y_top)) {
				//SetTryingLeft(false);
				//SetTryingRight(false);
				//SetTryingDown(false);
				if (backgroundArray[y - STEP_SIZE][x] == 1 || backgroundArray[y - STEP_SIZE][x_right] == 1) {
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

			if ((pacman->GetX2() < x_right) && (pacman->GetY2() < y_bottom) && (pacman->GetX1() < x_left) && (pacman->GetY2() < y_top)) {
				SetTryingLeft(false);
				if (backgroundArray[y][x - STEP_SIZE] == 1 || backgroundArray[y_bottom][x - STEP_SIZE] == 1) {
					x = x;
				}
				else {
					x -= STEP_SIZE;
				}
			}
			if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom) && (pacman->GetX1() > x_left) && (pacman->GetY2() > y_top)) {
				SetTryingRight(false);
				if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
					x = x;
				}
				else {
					x += STEP_SIZE;
				}
			}
			if ((pacman->GetX2() < x_right) && (pacman->GetY2() < y_bottom) && (pacman->GetX1() < x_left) && (pacman->GetY2() < y_top)) {
				SetTryingUp(false);
				if (backgroundArray[y - STEP_SIZE][x] == 1 || backgroundArray[y - STEP_SIZE][x_right] == 1) {
					y = y;
				}
				else {
					y -= STEP_SIZE;
				}
			}
			if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom) && (pacman->GetX1() > x_left) && (pacman->GetY2() > y_top)) {
				SetTryingDown(false);
				if (backgroundArray[y_bottom + STEP_SIZE][x] == 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 1) {
					y = y;
				}
				else {
					y += STEP_SIZE;
				}
			}
			
		}
		//Sleep(3000);
	//}
	/*if (rising) {			// ���k���A
		if (velocity > 0) {
			y -= velocity/3;	// ��t�� > 0�ɡAx�b���k(����velocity���I�Avelocity����쬰 �I/��)
			velocity-=3;		// �����O�v�T�A�U�������t�׭��C
		}
		else {
			rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�k��
			velocity = 1;	// �U������t(velocity)��1
		}
	}
	else {				// �U�����A
		if (y < floor - 1) {  // ��y�y���٨S�I��a�O
			y += velocity/3;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
			velocity+=3;		// �����O�v�T�A�U�����U���t�׼W�[
		}
		else {
			y = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
			rising = true;	// �����ϼu�A�U���אּ�W��
			velocity = initial_velocity; // ���]�W�ɪ�l�t��
		}

	}*/
	//animation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
	}


	void CBouncingBall::SetTryingDown(bool flag)
	{
		tryingDown = flag;
	}

	void CBouncingBall::SetTryingLeft(bool flag)
	{
		tryingLeft = flag;
	}

	void CBouncingBall::SetTryingRight(bool flag)
	{
		tryingRight = flag;
	}

	void CBouncingBall::SetTryingUp(bool flag)
	{
		tryingUp = flag;
	}

	void CBouncingBall::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CBouncingBall::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CBouncingBall::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CBouncingBall::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	void CBouncingBall::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}
	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}


}