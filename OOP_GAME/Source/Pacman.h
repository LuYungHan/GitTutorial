namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class Pacman
	{
	public:
		Pacman();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形


		void OnMove(int backgroundArray[479][636]);					// 移動擦子

		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		bool HitBigball(int backgroundArray[479][636]);
		void SetTryingDown(bool flag);	// 設定嘗試往下移動
		void SetTryingLeft(bool flag);	// 設定嘗試往左移動
		void SetTryingRight(bool flag);	// 設定嘗試往右移動
		void SetTryingUp(bool flag);	// 設定嘗試往上移動
	protected:
		CAnimation animation;		// 擦子的動畫左邊
		CAnimation animationRight;		// 擦子的動畫右邊
		CAnimation animationCenter;		// 擦子的動畫中間
		CAnimation animationUp;		// 擦子的動畫右邊
		CAnimation animationDown;		// 擦子的動畫中間
		int x, y;					// 擦子左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動

		bool tryingDown;			//是否可以往下
		bool tryingLeft;			//是否可以往左
		bool tryingRight;			//是否可以往右
		bool tryingUp;				//是否可以往上
		//int CGameStateInit::backgroundArray[479][636];
		//CGameStateInit backgroundArray;
		//int CGameStateInit::backgroundArray;
	};
}