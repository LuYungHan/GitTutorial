#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Pacman.h"
#include "CBouncingBall.h"
#include <random>
#include <iostream>
#include<time.h>
using namespace std;
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

		/* �H����l�ư��b�}�l�C���ɪ����V */
		int init_random = rand() % 4;

		if (init_random == 0) {
			SetTryingLeft(true);
		}

		else if (init_random == 1) {
			SetTryingRight(true);
		}

		else if (init_random == 2) {
			SetTryingUp(true);
		}

		else {
			SetTryingDown(true);
		}
	}

	void CBouncingBall::CBouncingBall_2()
	{
		Initialize_2();
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
	void CBouncingBall::Initialize_2() {

		const int INITIAL_VELOCITY = 30;	// ��l���k�t��
		const int FLOOR = 350;				// �a�O�y��
		floor = FLOOR;
		y = 261; x = FLOOR - 1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;

		is_alive = true;
		//xx = yy = dxx = dyy = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		tryingDown = tryingLeft = tryingRight = tryingUp = false;

		/* �H����l�ư��b�}�l�C���ɪ����V */
		int init_random = rand() % 4;

		if (init_random == 0) {
			SetTryingLeft(true);
		}

		else if (init_random == 1) {
			SetTryingRight(true);
		}

		else if (init_random == 2) {
			SetTryingUp(true);
		}

		else {
			SetTryingDown(true);
		}
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
		//animation.AddBitmap(IDB_STARGHOST, RGB(255, 255, 255));
		animationStar.AddBitmap(IDB_STARGHOST, RGB(0, 0, 0));
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
	/*	int CBouncingBall::Random_Time(int is_wall)
	{
		if (is_wall == 1) {
			srand((unsigned int)time(NULL));
			int random = rand() % 4;
			return random;
		}
	}*/
	void CBouncingBall::OnMove(int backgroundArray[479][636], Pacman *pacman, int num)
	{
		if (num >= 25) {

			const int STEP_SIZE = 1;
			animation.OnMove();
			std::cout << "hello world" << std::endl;
			int x_right = GetX2();
			int y_bottom = GetY2();
			int x_left = GetX1();
			int y_top = GetY1();

			/* ���H�����ʪ��޿�B�z (�ثe�ȼ���~�|��V) */
			TRACE("%d %d\n", isMovingLeft, tryingLeft);
			if (isMovingLeft || tryingLeft) {
				SetTryingLeft(false);
				if (backgroundArray[y_top][x_left - STEP_SIZE] == 1) {
					int random = rand() % 3;

					if (random == 0) {
						SetTryingRight(true);
					}

					else if (random == 1) {
						SetTryingUp(true);
					}

					else {
						SetTryingDown(true);
					}

					SetMovingLeft(false);
				}

				else {
					x -= STEP_SIZE;
					SetMovingLeft(true);
				}
			}

			else if (isMovingRight || tryingRight) {
				SetTryingRight(false);
				if (backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
					int random = rand() % 3;

					if (random == 0) {
						SetTryingLeft(true);
					}

					else if (random == 1) {
						SetTryingUp(true);
					}

					else {
						SetTryingDown(true);
					}

					SetMovingRight(false);
				}

				else {
					x += STEP_SIZE;
					SetMovingRight(true);
				}
			}

			else if (isMovingUp || tryingUp) {
				SetTryingUp(false);
				if (backgroundArray[y_top - STEP_SIZE][x_left] == 1) {
					int random = rand() % 3;

					if (random == 0) {
						SetTryingLeft(true);
					}

					else if (random == 1) {
						SetTryingRight(true);
					}

					else {
						SetTryingDown(true);
					}

					SetMovingUp(false);
				}

				else {
					y -= STEP_SIZE;
					SetMovingUp(true);
				}
			}

			else if (isMovingDown || tryingDown) {
				SetTryingDown(false);
				if (backgroundArray[y_bottom + STEP_SIZE][x_right] == 1) {
					int random = rand() % 3;

					if (random == 0) {
						SetTryingLeft(true);
					}

					else if (random == 1) {
						SetTryingRight(true);
					}

					else {
						SetTryingUp(true);
					}

					SetMovingDown(false);
				}

				else {
					y += STEP_SIZE;
					SetMovingDown(true);
				}
			}
		}
	}
	void CBouncingBall::OnMoveStar(int backgroundArray[479][636], Pacman * pacman)
	{

	}
	/*void CBouncingBall::Change_Dir(int backgroundArray[479][636],int change) {
		const int STEP_SIZE = 2;
		static int count = 0;
		int x_right = GetX2();
		int y_bottom = GetY2();
		int x = GetX1();
		int y = GetY1();
		int random;
		if (change == 0)	//right
		{
			if (backgroundArray[y][x_right + STEP_SIZE] != 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] != 1) {
				x += 1;
				Change_Dir(backgroundArray, 0);
			}
			else if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
				srand((unsigned int)time(NULL));
				random = rand() % 4;
				while (random == 0) {
					random = rand() % 4;
				}
				Change_Dir(backgroundArray, random);
			}
		}
		if (change == 1)	//left
		{
			if (backgroundArray[y][x - STEP_SIZE] != 1 || backgroundArray[y_bottom][x - STEP_SIZE] != 1) {
				x -= 1;
				Change_Dir(backgroundArray, 0);
			}
			else if (backgroundArray[y][x - STEP_SIZE] == 1 || backgroundArray[y_bottom][x - STEP_SIZE] == 1) {
				srand((unsigned int)time(NULL));
				random = rand() % 4;
				while(random == 1) {
					random = rand() % 4;
				}
				Change_Dir(backgroundArray, random);
			}
		}
		if (change == 2)	//up
		{
			if (backgroundArray[y - STEP_SIZE][x] != 1 || backgroundArray[y - STEP_SIZE][x_right] != 1) {
				y -= 1;
				Change_Dir(backgroundArray, 2);
			}
			else if (backgroundArray[y - STEP_SIZE][x] == 1 || backgroundArray[y - STEP_SIZE][x_right] == 1) {
				srand((unsigned int)time(NULL));
				random = rand() % 4;
				while (random == 2) {
					random = rand() % 4;
				}
				Change_Dir(backgroundArray, random);
			}
		}
		if (change == 3)	//down
		{
			if (backgroundArray[y_bottom + STEP_SIZE][x] != 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] != 1) {
				y += 1;
				Change_Dir(backgroundArray, 3);
			}
			else if (backgroundArray[y_bottom + STEP_SIZE][x] == 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 1) {
				srand((unsigned int)time(NULL));
				random = rand() % 4;
				while (random == 3) {
					random = rand() % 4;
				}
				Change_Dir(backgroundArray, random);
			}
		}
	}*/
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
	void CBouncingBall::OnShow(int backgroundArray[479][636], Pacman *pacman)
	{
		int x_right = pacman->GetX2();
		int y_bottom = pacman->GetY2();
		int x_left = pacman->GetX1();
		int y_top = pacman->GetY1();
		const int STEP_SIZE = 3;
		if (is_alive && (!(backgroundArray[y_top + STEP_SIZE][x] == 8 || backgroundArray[y_top + STEP_SIZE][x_left] == 8))) {
			animation.SetTopLeft(x, y);
			//animationStar.SetTopLeft(x, y);
			animation.OnShow();
			//animationStar.OnShow();
			//pacman eats ghost
			/*if (backgroundArray[y_top + STEP_SIZE][x] == 8 || backgroundArray[y_top+ STEP_SIZE][x_left] == 8) {
				animationStar.OnShow();
			}*/

		}
	}
	void CBouncingBall::OnShowStar(int backgroundArray[479][636], Pacman *pacman) {
		int x_right = GetX2();
		int y_bottom = GetY2();
		int x_left = pacman->GetX1();
		int y_top = pacman->GetY1();
		const int STEP_SIZE = 4;
		animationStar.SetTopLeft(x, y);
		if ((is_alive) && (backgroundArray[y_top + STEP_SIZE][x] == 8 || backgroundArray[y_top + STEP_SIZE][x_left] == 8)) {
			animationStar.OnShow();
			
		}
	}


}