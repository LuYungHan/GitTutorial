#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBouncingBall: BouncingBall class
	/////////////////////////////////////////////////////////////////////////////

	CBouncingBall::CBouncingBall()
	{
		const int INITIAL_VELOCITY = 15;	// ��l���k�t��
		const int FLOOR = 350;				// �a�O�y��
		floor = FLOOR;
		y = 180; x = FLOOR - 1;				// y�y�Ф�a�O��1�I(���b�a�O�W)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
	}

	void CBouncingBall::LoadBitmap()
	{
		char *filename[4] = { ".\\RES\\redghost01.bmp",".\\RES\\redghost02.bmp",".\\RES\\redghost03.bmp",".\\RES\\redghost04.bmp" };
		for (int i = 0; i < 4; i++)	// ���J�ʵe(��4�i�ϧκc��)
			animation.AddBitmap(filename[i], RGB(0, 0, 0));
	}

	void CBouncingBall::OnMove()
	{
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
		animation.OnMove();		// ����@��animation.OnMove()�Aanimation�~�|����
	}

	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}