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
	const int INITIAL_VELOCITY = 15;	// ��l���k�t��
	const int FLOOR = 225;				// �a�O�y��
	floor = FLOOR;
	x = 260; y = FLOOR - 1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
	rising = true;
	initial_velocity = INITIAL_VELOCITY;
	velocity = initial_velocity;

	is_alive = true;
	xx = yy = dxx = dyy = 0;
}
/*
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
}
*/
bool BlueGhost::HitEraser(Pacman *pacman)
{
	// �˴����l�Һc�����x�άO�_�I��y
	return HitRectangle(pacman->GetX1(), pacman->GetY1(),
		pacman->GetX2(), pacman->GetY2());
}
bool BlueGhost::HitRectangle(int tx1, int ty1, int tx2, int ty2)
{
	int x1 = xx + dxx;				// �y�����W��x�y��
	int y1 = yy + dyy;				// �y�����W��y�y��
	int x2 = x1 + animation.Width();	// �y���k�U��x�y��
	int y2 = y1 + bmp.Height();	// �y���k�U��y�y��
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

void BlueGhost::OnMove()
{
	if (rising) {			// ���k���A
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
	}
	animation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
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
