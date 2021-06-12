#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
//#include "Pacman.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供會一直彈跳的球
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CBouncingBall
	{
	public:
		CBouncingBall();

		void LoadBitmap();		// 載入圖形

		void OnMove(int backgroundArray[479][636],int num);			// 移動
		void OnShow();			// 將圖形貼到畫面

		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetTryingDown(bool flag);	// 設定嘗試往下移動
		void SetTryingLeft(bool flag);	// 設定嘗試往左移動
		void SetTryingRight(bool flag);	// 設定嘗試往右移動
		void SetTryingUp(bool flag);	// 設定嘗試往上移動
	

	protected:
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動

		bool tryingDown;			//是否可以往下
		bool tryingLeft;			//是否可以往左
		bool tryingRight;			//是否可以往右
		bool tryingUp;				//是否可以往上

	private:
		int x, y;				// 圖形座標
		int floor;				// 地板的Y座標
		bool rising;			// true表上升、false表下降
		int initial_velocity;	// 初始速度
		int velocity;			// 目前的速度(點/次)
		CAnimation animation;	// 利用動畫作圖形
	};
}