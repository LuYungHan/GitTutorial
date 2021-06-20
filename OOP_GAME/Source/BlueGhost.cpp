#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Pacman.h"
#include "BlueGhost.h"
#include <iostream>
#include <time.h>
#include <random>

using namespace game_framework;


/////////////////////////////////////////////////////////////////////////////
// BlueGhost: BlueGhost class
/////////////////////////////////////////////////////////////////////////////

BlueGhost::BlueGhost()
{
	Initialize();
	/*
	const int INITIAL_VELOCITY = 15;	// 初始左右速度
	const int FLOOR = 225;				// 地板座標
	floor = FLOOR;
	x = 260; y = FLOOR - 1;				// y座標比地板高1點(站在地板上)
	rising = true;
	initial_velocity = INITIAL_VELOCITY;
	velocity = initial_velocity;

	is_alive = true;
	xx = yy = dxx = dyy = 0;
	*/
}
int BlueGhost::GetX1()
{
	return x;
}

int BlueGhost::GetY1()
{
	return y;
}

int BlueGhost::GetX2()
{
	return x + animation.Width();
}

int BlueGhost::GetY2()
{
	return y + animation.Height();
}

void BlueGhost::Initialize() {
	
	const int INITIAL_VELOCITY = 15;	// 初始左右速度
	const int FLOOR = 225;				// 地板座標
	floor = FLOOR;
	x = 260; y = FLOOR - 1;				// y座標比地板高1點(站在地板上)
	rising = true;
	initial_velocity = INITIAL_VELOCITY;
	velocity = initial_velocity;

	is_alive = true;
	xx = yy = dxx = dyy = 0;
	isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	tryingDown = tryingLeft = tryingRight = tryingUp = false;
	/* 隨機初始化鬼在開始遊戲時的走向 */
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

bool BlueGhost::HitEraser(Pacman *pacman)
{
	// 檢測擦子所構成的矩形是否碰到球
	return HitRectangle(pacman->GetX1(), pacman->GetY1(),
		pacman->GetX2(), pacman->GetY2());
}
bool BlueGhost::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
	int x1 = x;		//鬼的左上角x座標
	int y1 = y;		//鬼的左上角y座標
	int x2 = x1 + animation.Width();	// 球的右下角x座標
	int y2 = y1 + animation.Height();	// 球的右下角y座標
								//
								// 檢測球的矩形與參數矩形是否有交集
								//
	return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
}

bool BlueGhost::IsAlive()
{
	return is_alive;
}
void BlueGhost::LoadBitmap()
{
	animationStar.AddBitmap(IDB_STARGHOST, RGB(0, 0, 0));
	char *filename[7] = { ".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostUP01.bmp",".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostDown01.bmp",".\\RES\\blueghostUP01.bmp",".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostDown01.bmp", };
	for (int i = 0; i < 7; i++)	// 載入動畫(由4張圖形構成)
		animation.AddBitmap(filename[i], RGB(0, 0, 0));
	animationStar.AddBitmap(IDB_STARGHOST, RGB(0, 0, 0));
}

void BlueGhost::TrackPacman(Pacman *pacman,int num)
{	
	if (num < 25) {

		if (rising) {			// 左右狀態
			if (velocity > 0) {
				y -= velocity / 3;	// 當速度 > 0時，x軸左右(移動velocity個點，velocity的單位為 點/次)
				velocity -= 3;		// 受重力影響，下次的左速度降低
			}
			else {
				rising = false; // 當速度 <= 0，上升終止，下次改為右移
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else {				// 下降狀態
			if (y < floor - 1) {  // 當y座標還沒碰到地板
				y += velocity / 3;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity += 3;		// 受重力影響，下次的下降速度增加
			}
			else {
				y = floor - 1;  // 當y座標低於地板，更正為地板上
				rising = true;	// 探底反彈，下次改為上升
				velocity = initial_velocity; // 重設上升初始速度
			}
		}
	}
}

void BlueGhost::OnMove(int backgroundArray[479][636], Pacman *pacman,int num)
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
			/* 鬼隨機移動的邏輯處理 (目前僅撞牆才會改向) */
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
void BlueGhost::OnMoveStar(int backgroundArray[479][636], Pacman *pacman, int num) {
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


void BlueGhost::SetTryingDown(bool flag)
{
	tryingDown = flag;
}

void BlueGhost::SetTryingLeft(bool flag)
{
	tryingLeft = flag;
}

void BlueGhost::SetTryingRight(bool flag)
{
	tryingRight = flag;
}

void BlueGhost::SetTryingUp(bool flag)
{
	tryingUp = flag;
}

void BlueGhost::SetMovingDown(bool flag)
{
	isMovingDown = flag;
}

void BlueGhost::SetMovingLeft(bool flag)
{
	isMovingLeft = flag;
}

void BlueGhost::SetMovingRight(bool flag)
{
	isMovingRight = flag;
}

void BlueGhost::SetMovingUp(bool flag)
{
	isMovingUp = flag;
}
void BlueGhost::SetIsAlive(bool alive)
{
	is_alive = alive;
}

void BlueGhost::OnShow(int backgroundArray[479][636], Pacman *pacman)
{	
	int x_right = pacman->GetX2();
	int y_bottom = pacman->GetY2();
	int x_left =pacman-> GetX1();
	int y_top = pacman->GetY1();
	const int STEP_SIZE = 3;
	if (is_alive &&(!(backgroundArray[y_top + STEP_SIZE][x] == 8 || backgroundArray[y_top + STEP_SIZE][x_left] == 8))) {
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


void BlueGhost::OnShowStar(int backgroundArray[479][636],Pacman *pacman) {
	int x_right = GetX2();
	int y_bottom = GetY2();
	int x_left =pacman-> GetX1();
	int y_top =pacman-> GetY1();
	const int STEP_SIZE = 4;
	animationStar.SetTopLeft(x, y);
	if ((is_alive)&&(backgroundArray[y_top + STEP_SIZE][x] == 8 || backgroundArray[y_top + STEP_SIZE][x_left] == 8)) {
		animationStar.OnShow();
		if (counter == 0) {
			animation.OnShow();
		}
			
	}
}

