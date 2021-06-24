#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Pacman.h"
#include "Orange.h"
#include <iostream>
#include <time.h>
#include <random>

using namespace game_framework;


	/////////////////////////////////////////////////////////////////////////////
	// Orange: Orange class
	/////////////////////////////////////////////////////////////////////////////

	Orange::Orange()
	{
		Initialize();
		/*
		const int INITIAL_VELOCITY = 15;	// ��l���k�t��
		const int FLOOR = 225;				// �a�O�y��
		floor = FLOOR;
		x = 260; y = FLOOR - 1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;

		is_alive = true;
		xx = yy = dxx = dyy = 0;
		*/
	}

	int Orange::GetX1()
	{
		return x;
	}

	int Orange::GetY1()
	{
		return y;
	}

	int Orange::GetX2()
	{
		return x + animation.Width();
	}

	int Orange::GetY2()
	{
		return y + animation.Height();
	}

	void Orange::Initialize() {

		const int INITIAL_VELOCITY = 15;	// ��l���k�t��
		const int FLOOR = 225;				// �a�O�y��
		floor = FLOOR;
		x = 260; y = FLOOR - 1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;

		is_alive = true;
		xx = yy = dxx = dyy = 0;
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

	bool Orange::HitEraser(Pacman *pacman)
	{
		// �˴����l�Һc�����x�άO�_�I��y
		return HitRectangle(pacman->GetX1(), pacman->GetY1(),
			pacman->GetX2(), pacman->GetY2());
	}
	bool Orange::HitRectangle(int tx1, int ty1, int tx2, int ty2)
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

	bool Orange::IsAlive()
	{
		return is_alive;
	}
	void Orange::LoadBitmap()
	{
		//animationStar.AddBitmap(IDB_STARGHOST, RGB(0, 0, 0));
		char *filename[7] = { ".\\bitmaps\\orange1.bmp",".\\bitmaps\\orange2.bmp",".\\bitmaps\\orange3.bmp",".\\bitmaps\\orange4.bmp",".\\bitmaps\\orange3.bmp",".\\bitmaps\\orange2.bmp",".\\bitmaps\\orange1.bmp", };
		for (int i = 0; i < 7; i++)	// ���J�ʵe(��4�i�ϧκc��)
			animation.AddBitmap(filename[i], RGB(0, 0, 0));
		animationStar.AddBitmap(IDB_STARGHOST, RGB(0, 0, 0));
	}

	void Orange::TrackPacman(Pacman *pacman, int num)
	{
		if (num < 50) {

			if (rising) {			// ���k���A
				if (velocity > 0) {
					y -= velocity / 3;	// ��t�� > 0�ɡAx�b���k(����velocity���I�Avelocity����쬰 �I/��)
					velocity -= 3;		// �����O�v�T�A�U�������t�׭��C
				}
				else {
					rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�k��
					velocity = 1;	// �U������t(velocity)��1
				}
			}
			else {				// �U�����A
				if (y < floor - 1) {  // ��y�y���٨S�I��a�O
					y += velocity / 3;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
					velocity += 3;		// �����O�v�T�A�U�����U���t�׼W�[
				}
				else {
					y = floor - 1;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
					rising = true;	// �����ϼu�A�U���אּ�W��
					velocity = initial_velocity; // ���]�W�ɪ�l�t��
				}
			}
		}
	}

	void Orange::OnMove(int backgroundArray[479][636], Pacman *pacman, int num)
	{
		if (num >= 25) {

			const int STEP_SIZE = 3;
			animation.OnMove();
			static int count = 0;
			int x_right = GetX2();
			int y_bottom = GetY2();
			int x_left = GetX1();
			int y_top = GetY1();
			srand((unsigned int)time(NULL));

			int random = rand() % 4;
			std::cout << random << " HERE" << std::endl;
			if (count % 2 != 0) {
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
			else if (count % 2 == 0) {
				if ((pacman->GetX2() < x_right) || (pacman->GetX1() < x_left)) {
					SetTryingLeft(false);
					if (backgroundArray[y][x_left - STEP_SIZE] == 1 || backgroundArray[y_top][x_left - STEP_SIZE] == 1) {
						x = x;
						/*if (backgroundArray[y_top - STEP_SIZE][x] != 1 || backgroundArray[y_top - STEP_SIZE][x_right] != 1) {
							y -= STEP_SIZE;
						}
						if (backgroundArray[y_bottom + STEP_SIZE][x] != 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] != 1) {
							y += STEP_SIZE;
						}*/
					}
					else {
						x -= STEP_SIZE;

					}
				}
				if ((pacman->GetX2() > x_right) || (pacman->GetX1() > x_left)) {
					SetTryingRight(false);
					if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
						x = x;
						/*if (backgroundArray[y_top - STEP_SIZE][x] != 1 || backgroundArray[y_top - STEP_SIZE][x_right] != 1) {
							y -= STEP_SIZE;
						}
						if (backgroundArray[y_bottom + STEP_SIZE][x] != 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] != 1) {
							y += STEP_SIZE;
						}*/

					}
					else {
						x += STEP_SIZE;

					}
				}
				if ((pacman->GetY2() < y_bottom) || (pacman->GetY2() < y_top)) {
					SetTryingUp(false);
					if (backgroundArray[y_top - STEP_SIZE][x] == 1 || backgroundArray[y_top - STEP_SIZE][x_right] == 1) {
						y = y;
						/*if (backgroundArray[y][x_right + STEP_SIZE] != 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] != 1 || backgroundArray[y_top - STEP_SIZE][x] == 5 || backgroundArray[y_top - STEP_SIZE][x_right] == 5) {
							x += STEP_SIZE;
						}
						if (backgroundArray[y][x_left - STEP_SIZE] != 1 || backgroundArray[y_top][x_left - STEP_SIZE] != 1) {
							x -= STEP_SIZE;
						}*/
					}
					else {
						y -= STEP_SIZE;


					}
				}
				if ((pacman->GetY2() > y_bottom) || (pacman->GetY2() > y_top)) {
					SetTryingDown(false);
					if (backgroundArray[y_bottom + STEP_SIZE][x] == 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 1 || backgroundArray[y_bottom + STEP_SIZE][x] == 5 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 5) {
						y = y;
						/*if (backgroundArray[y][x_right + STEP_SIZE] != 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] != 1) {
							x += STEP_SIZE;
						}
						if (backgroundArray[y][x_left - STEP_SIZE] != 1 || backgroundArray[y_top][x_left - STEP_SIZE] != 1) {
							x -= STEP_SIZE;
						}*/
					}
					else {
						y += STEP_SIZE;

					}
				}
			}
			count = count + 1;
		}
	}
	void Orange::OnMoveStar(int backgroundArray[479][636], Pacman *pacman, int num) {
		const int STEP_SIZE = 3;
		//animation.OnMove();
		//animationStar.OnMove();
		int x_right = GetX2();
		int y_bottom = GetY2();
		int x_left = pacman->GetX1();
		int y_top = pacman->GetY1();
		srand((unsigned int)time(NULL));
		int random = rand() % 4;
		if ((num >= 25) && (backgroundArray[y_top][x_left] == 8)) {
			if (random == 1) { //down
					//std::cout << random << std::endl;
				if (backgroundArray[y_bottom + STEP_SIZE][x] == 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 1) {
					//Random_Time(1);
					SetMovingDown(false);
					y = y;
					if (backgroundArray[y][x_right + STEP_SIZE] != 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] != 1 || backgroundArray[y_top - STEP_SIZE][x] == 5 || backgroundArray[y_top - STEP_SIZE][x_right] == 5) {
						x += STEP_SIZE;
					}
					if (backgroundArray[y][x_left - STEP_SIZE] != 1 || backgroundArray[y_top][x_left - STEP_SIZE] != 1) {
						x -= STEP_SIZE;
					}
				}
				else {
					y += STEP_SIZE;
					SetMovingDown(true);
					SetTryingDown(false);
					SetMovingLeft(false);
					SetMovingRight(false);
					SetMovingUp(false);
				}
				//x_right -= STEP_SIZE;

			}
			else if (random == 2) { //right
				//std::cout << random << std::endl;
				if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
					//Random_Time(1);
					SetMovingRight(false);
					x = x;
					if (backgroundArray[y_top - STEP_SIZE][x] != 1 || backgroundArray[y_top - STEP_SIZE][x_right] != 1) {
						y -= STEP_SIZE;
					}
					if (backgroundArray[y_bottom + STEP_SIZE][x] != 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] != 1) {
						y += STEP_SIZE;
					}

				}
				else {
					x += STEP_SIZE;
					SetMovingRight(true);
					SetTryingRight(false);
					SetMovingLeft(false);
					SetMovingDown(false);
					SetMovingUp(false);
				}
				//x_right += STEP_SIZE;
			}
			else if (random == 3) { //left
				//std::cout << random << std::endl;
				if (backgroundArray[y][x_left - STEP_SIZE] == 1 || backgroundArray[y_top][x_left - STEP_SIZE] == 1) {
					//Random_Time(1);
					SetMovingLeft(false);
					x = x;
					if (backgroundArray[y_top - STEP_SIZE][x] != 1 || backgroundArray[y_top - STEP_SIZE][x_right] != 1) {
						y -= STEP_SIZE;
					}
					if (backgroundArray[y_bottom + STEP_SIZE][x] != 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] != 1) {
						y += STEP_SIZE;
					}
				}
				else {
					x -= STEP_SIZE;
					SetMovingLeft(true);
					SetTryingLeft(false);
					SetMovingDown(false);
					SetMovingRight(false);
					SetMovingUp(false);
				}
				//y_bottom -= STEP_SIZE;
			}
			else if (random == 0) { //up
				//std::cout << random << std::endl;
				if (backgroundArray[y_top - STEP_SIZE][x] == 1 || backgroundArray[y_top - STEP_SIZE][x_right] == 1) {
					//Random_Time(1);
					SetMovingUp(false);
					y = y;
					if (backgroundArray[y][x_right + STEP_SIZE] != 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] != 1 || backgroundArray[y_top - STEP_SIZE][x] == 5 || backgroundArray[y_top - STEP_SIZE][x_right] == 5) {
						x += STEP_SIZE;
					}
					if (backgroundArray[y][x_left - STEP_SIZE] != 1 || backgroundArray[y_top][x_left - STEP_SIZE] != 1) {
						x -= STEP_SIZE;
					}

				}
				else {
					y -= STEP_SIZE;
					SetMovingUp(true);
					SetTryingUp(false);
					SetMovingLeft(false);
					SetMovingRight(false);
					SetMovingDown(false);
				}
				//y_bottom += STEP_SIZE;
			}
			animationStar.OnMove();

		}
	}


	void Orange::SetTryingDown(bool flag)
	{
		tryingDown = flag;
	}

	void Orange::SetTryingLeft(bool flag)
	{
		tryingLeft = flag;
	}

	void Orange::SetTryingRight(bool flag)
	{
		tryingRight = flag;
	}

	void Orange::SetTryingUp(bool flag)
	{
		tryingUp = flag;
	}

	void Orange::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Orange::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Orange::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Orange::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	void Orange::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void Orange::OnShow(int backgroundArray[479][636], Pacman *pacman)
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


	void Orange::OnShowStar(int backgroundArray[479][636], Pacman *pacman) {
		int x_right = GetX2();
		int y_bottom = GetY2();
		int x_left = pacman->GetX1();
		int y_top = pacman->GetY1();
		const int STEP_SIZE = 4;
		animationStar.SetTopLeft(x, y);
		if ((is_alive) && (backgroundArray[y_top + STEP_SIZE][x] == 8 || backgroundArray[y_top + STEP_SIZE][x_left] == 8)) {
			animationStar.OnShow();
			if (counter == 0) {
				animation.OnShow();
			}

		}
	}
