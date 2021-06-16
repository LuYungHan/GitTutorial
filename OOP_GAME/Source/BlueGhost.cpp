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
	
}

bool BlueGhost::HitEraser(Pacman *pacman)
{
	// �˴����l�Һc�����x�άO�_�I��y
	return HitRectangle(pacman->GetX1(), pacman->GetY1(),
		pacman->GetX2(), pacman->GetY2());
}
bool BlueGhost::HitRectangle(int tx1, int ty1, int tx2, int ty2)
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

bool BlueGhost::IsAlive()
{
	return is_alive;
}
void BlueGhost::LoadBitmap()
{
	char *filename[7] = { ".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostUP01.bmp",".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostDown01.bmp",".\\RES\\blueghostUP01.bmp",".\\RES\\blueghostcenter01.bmp",".\\RES\\blueghostDown01.bmp", };
	for (int i = 0; i < 7; i++)	// ���J�ʵe(��4�i�ϧκc��)
		animation.AddBitmap(filename[i], RGB(0, 0, 0));
}

void BlueGhost::TrackPacman(Pacman *pacman,int num)
{	
	if (num < 25) {

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
		if ((pacman->GetX2() > x_right) && (pacman->GetY2() > y_bottom)) {		//�����b�k�W
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
