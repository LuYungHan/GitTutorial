#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Pacman.h"
#include "BlueGhost.h"

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
	char *filename[7] = { ".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostUP01.bmp",".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostDown01.bmp",".\\RES\\blueghostUP01.bmp",".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostDown01.bmp", };
	for (int i = 0; i < 7; i++)	// 載入動畫(由4張圖形構成)
		animation.AddBitmap(filename[i], RGB(0, 0, 0));
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

<<<<<<< HEAD
	int x_right = GetX2();
	int y_bottom = GetY2();
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
		if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom)) {		//偵測在右上
=======
		const int STEP_SIZE = 4;
		animation.OnMove();

		int x_right = GetX2();
		int y_bottom = GetY2();
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
		if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom)) {
>>>>>>> 10ea9f8bc057ca4e8614a6c63acc6c199c579c16
			SetTryingLeft(false);
			SetTryingRight(false);
			SetTryingUp(false);
			if (backgroundArray[y_bottom + STEP_SIZE][x] == 1 || backgroundArray[y_bottom + STEP_SIZE][x_right] == 1) {
				SetTryingDown(false);
			}
			else {
				SetTryingDown(true);
				SetMovingDown(false);
				SetMovingLeft(false);
				SetMovingRight(false);
				SetMovingUp(false);
			}
		}
		if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom)) {
			SetTryingLeft(false);
			SetTryingDown(false);
			SetTryingUp(false);
			if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
				SetTryingRight(false);
			}
			else {
				SetTryingRight(true);
				SetMovingRight(false);
				SetMovingLeft(false);
				SetMovingDown(false);
				SetMovingUp(false);
			}
		}
		if ((pacman->GetX2() < x_right) && (pacman->GetY2() < y_bottom)) {
			SetTryingDown(false);
			SetTryingRight(false);
			SetTryingUp(false);
			if (backgroundArray[y][x - STEP_SIZE] == 1 || backgroundArray[y_bottom][x - STEP_SIZE] == 1) {
				SetTryingLeft(false);
			}
			else {
				SetTryingLeft(true);
				SetMovingLeft(false);
				SetMovingDown(false);
				SetMovingRight(false);
				SetMovingUp(false);
			}
		}
		if ((pacman->GetX2() < x_right) && (pacman->GetY2() < y_bottom)) {
			SetTryingLeft(false);
			SetTryingRight(false);
			SetTryingDown(false);
			if (backgroundArray[y - STEP_SIZE][x] == 1 || backgroundArray[y - STEP_SIZE][x_right] == 1) {
				SetTryingUp(false);
			}
			else {
				SetTryingUp(true);
				SetMovingUp(false);
				SetMovingLeft(false);
				SetMovingRight(false);
				SetMovingDown(false);
			}
		}

		if ((pacman->GetX2() < x_right) && (pacman->GetY2() < y_bottom)) {
			//SetMovingLeft(false);
			if (backgroundArray[y][x - STEP_SIZE] == 1 || backgroundArray[y_bottom][x - STEP_SIZE] == 1) {
				x = x;
			}
			else {
				x -= STEP_SIZE;
			}
		}
		if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom)) {
			//SetMovingRight(false);
			if (backgroundArray[y][x_right + STEP_SIZE] == 1 || backgroundArray[y_bottom][x_right + STEP_SIZE] == 1) {
				x = x;
			}
			else {
				x += STEP_SIZE;
			}
		}
		if ((pacman->GetX2() < x_right) && (pacman->GetY2() < y_bottom)) {
			//SetMovingUp(false);
			if (backgroundArray[y - STEP_SIZE][x] == 1 || backgroundArray[y - STEP_SIZE][x_right] == 1) {
				y = y;
			}
			else {
				y -= STEP_SIZE;
			}
		}
		if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom)) {
			//SetMovingDown(false);
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
	/*if (rising) {			// 左右狀態
		if (velocity > 0) {
			y -= velocity/3;	// 當速度 > 0時，x軸左右(移動velocity個點，velocity的單位為 點/次)
			velocity-=3;		// 受重力影響，下次的左速度降低
		}
		else {
			rising = false; // 當速度 <= 0，上升終止，下次改為右移
			velocity = 1;	// 下降的初速(velocity)為1
		}
	}
	else {				// 下降狀態
		if (y < floor - 1) {  // 當y座標還沒碰到地板
			y += velocity/3;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
			velocity+=3;		// 受重力影響，下次的下降速度增加
		}
		else {
			y = floor - 1;  // 當y座標低於地板，更正為地板上
			rising = true;	// 探底反彈，下次改為上升
			velocity = initial_velocity; // 重設上升初始速度
		}
		
	}*/
	//animation.OnMove();		// 執行一次animation.OnMove()，animation才會換圖
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

void BlueGhost::OnShow()
{	
	if (is_alive) {
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
	

}
