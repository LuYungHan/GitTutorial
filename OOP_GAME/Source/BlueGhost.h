#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class提供會一直彈跳的球
// 看懂就可以改寫成自己的程式了
/////////////////////////////////////////////////////////////////////////////

class BlueGhost
{
public:
	BlueGhost();

	bool HitEraser(Pacman *pacman);						// 是否碰到擦子
	bool IsAlive();											// 是否活著
	void LoadBitmap();		// 載入圖形
	void OnMove();			// 移動
	void SetIsAlive(bool alive);							// 設定是否活著
	void OnShow();			// 將圖形貼到畫面
	void Initialize();				// 設定初始值

protected:
	CMovingBitmap bmp;			// 鬼的圖
	int xx, yy;					// 圓心的座標
	int dxx, dyy;					// 球距離圓心的位移量
//	int index;					// 球的「角度」，0-17表示0-360度
//	int delay_counter;			// 調整旋轉速度的計數器
//	int delay;					// 旋轉的速度
	bool is_alive;				// 是否活著
	int x, y;				// 圖形座標
	int floor;				// 地板的Y座標
	bool rising;			// true表上升、false表下降
	int initial_velocity;	// 初始速度
	int velocity;			// 目前的速度(點/次)
	CAnimation animation;	// 利用動畫作圖形

private:
	
	

	bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
};
