namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class Pacman
	{
	public:
		Pacman();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�


		void OnMove(int backgroundArray[479][636]);					// �������l

		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		bool HitBigball(int backgroundArray[479][636]);
		void SetTryingDown(bool flag);	// �]�w���թ��U����
		void SetTryingLeft(bool flag);	// �]�w���թ�������
		void SetTryingRight(bool flag);	// �]�w���թ��k����
		void SetTryingUp(bool flag);	// �]�w���թ��W����
	protected:
		CAnimation animation;		// ���l���ʵe����
		CAnimation animationRight;		// ���l���ʵe�k��
		CAnimation animationCenter;		// ���l���ʵe����
		CAnimation animationUp;		// ���l���ʵe�k��
		CAnimation animationDown;		// ���l���ʵe����
		int x, y;					// ���l���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����

		bool tryingDown;			//�O�_�i�H���U
		bool tryingLeft;			//�O�_�i�H����
		bool tryingRight;			//�O�_�i�H���k
		bool tryingUp;				//�O�_�i�H���W
		//int CGameStateInit::backgroundArray[479][636];
		//CGameStateInit backgroundArray;
		//int CGameStateInit::backgroundArray;
	};
}