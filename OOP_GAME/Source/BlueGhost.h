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
	int  GetX1();					// ghost左上角 x 座標
	int  GetY1();					// ghost左上角 y 座標
	int  GetX2();					// ghost右下角 x 座標
	int  GetY2();					// ghost右下角 y 座標
	bool HitEraser(Pacman *pacman);						// 是否碰到擦子
	bool IsAlive();											// 是否活著
	void LoadBitmap();		// 載入圖形
	void OnMove(int backgroundArray[479][636], Pacman *pacman,int num);	
	void OnMoveStar(int backgroundArray[479][636], Pacman *pacman, int num);// 移動
	void SetIsAlive(bool alive);							// 設定是否活著
	void OnShow(int backgroundArray[479][636],  Pacman *pacman);			// 將圖形貼到畫面
	void OnShowStar(int backgroundArray[479][636],  Pacman *pacman);
	void Initialize();				// 設定初始值
	void TrackPacman(Pacman *pacman, int num);
	void SetMovingDown(bool flag);	// 設定是否正在往下移動
	void SetMovingLeft(bool flag);	// 設定是否正在往左移動
	void SetMovingRight(bool flag); // 設定是否正在往右移動
	void SetMovingUp(bool flag);	// 設定是否正在往上移動
	void SetTryingDown(bool flag);	// 設定嘗試往下移動
	void SetTryingLeft(bool flag);	// 設定嘗試往左移動
	void SetTryingRight(bool flag);	// 設定嘗試往右移動
	void SetTryingUp(bool flag);	// 設定嘗試往上移動

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
	CAnimation animationStar;	// 利用動畫作圖形

	bool isMovingDown;			// 是否正在往下移動
	bool isMovingLeft;			// 是否正在往左移動
	bool isMovingRight;			// 是否正在往右移動
	bool isMovingUp;			// 是否正在往上移動

	bool tryingDown;			//是否可以往下
	bool tryingLeft;			//是否可以往左
	bool tryingRight;			//是否可以往右
	bool tryingUp;				//是否可以往上

private:
	
	
	int counter = 30 * 20;
	bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
};
