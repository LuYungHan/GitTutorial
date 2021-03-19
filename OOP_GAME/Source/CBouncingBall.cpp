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
		const int INITIAL_VELOCITY = 15;	// 初始左右速度
		const int FLOOR = 350;				// 地板座標
		floor = FLOOR;
		y = 180; x = FLOOR - 1;				// y座標比地板高1點(站在地板上)
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
	}

	void CBouncingBall::LoadBitmap()
	{
		char *filename[4] = { ".\\RES\\redghost01.bmp",".\\RES\\redghost02.bmp",".\\RES\\redghost03.bmp",".\\RES\\redghost04.bmp" };
		for (int i = 0; i < 4; i++)	// 載入動畫(由4張圖形構成)
			animation.AddBitmap(filename[i], RGB(0, 0, 0));
	}

	void CBouncingBall::OnMove()
	{
		if (rising) {			// 左右狀態
			if (velocity > 0) {
				x -= velocity;	// 當速度 > 0時，x軸左右(移動velocity個點，velocity的單位為 點/次)
				velocity--;		// 受重力影響，下次的左速度降低
			}
			else {
				rising = false; // 當速度 <= 0，上升終止，下次改為右移
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else {				// 下降狀態
			if (x < floor - 1) {  // 當y座標還沒碰到地板
				x += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity++;		// 受重力影響，下次的下降速度增加
			}
			else {
				x = floor - 1;  // 當y座標低於地板，更正為地板上
				rising = true;	// 探底反彈，下次改為上升
				velocity = initial_velocity; // 重設上升初始速度
			}
		}
		animation.OnMove();		// 執行一次animation.OnMove()，animation才會換圖
	}

	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}