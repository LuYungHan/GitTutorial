#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "BachgroundMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBall: Ball class
	/////////////////////////////////////////////////////////////////////////////

	BachgroundMap::BachgroundMap()
	{
		is_alive = true;
		x = y = dx = dy = index = delay_counter = 0;
	}

	bool BachgroundMap::HitEraser(CEraser *eraser)
	{
		// 檢測擦子所構成的矩形是否碰到球
		return HitRectangle(eraser->GetX1(), eraser->GetY1(),
			eraser->GetX2(), eraser->GetY2());
	}

	bool BachgroundMap::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 球的左上角x座標
		int y1 = y + dy;				// 球的左上角y座標
		int x2 = x1 + bmp.Width();	// 球的右下角x座標
		int y2 = y1 + bmp.Height();	// 球的右下角y座標
									//
									// 檢測球的矩形與參數矩形是否有交集
									//
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool BachgroundMap::IsAlive()
	{
		return is_alive;
	}

	void BachgroundMap::LoadBitmap()
	{
		bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));			// 載入球的圖形
		bmp_map.LoadBitmap(IDB_BACKGROUND, RGB(0, 0, 0));	// 載入球圓心的圖形
	}

//	void BachgroundMap::OnMove()
//	{
//		if (!is_alive)
//			return;
//		delay_counter--;
//		if (delay_counter < 0) {
//			delay_counter = delay;
//			//
//			// 計算球向對於圓心的位移量dx, dy
//			//
//			const int STEPS = 18;
//			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
//			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
//			index++;
//			if (index >= STEPS)
//				index = 0;
//			dx = DIFFX[index];
//			dy = DIFFY[index];
//		}
//	}

//	void BachgroundMap::SetDelay(int d)
//	{
//		delay = d;
//	}

	void BachgroundMap::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void BachgroundMap::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void BachgroundMap::OnShow()
	{
		if (is_alive) {
			bmp.SetTopLeft(x + dx, y + dy);
			bmp.ShowBitmap();
			bmp_center.SetTopLeft(x, y);
			bmp_center.ShowBitmap();
		}
	}
}