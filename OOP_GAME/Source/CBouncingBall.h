#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
//#include "Pacman.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѷ|�@���u�����y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CBouncingBall
	{
	public:
		CBouncingBall();
		void CBouncingBall_2();
		int  GetX1();					// ghost���W�� x �y��
		int  GetY1();					// ghost���W�� y �y��
		int  GetX2();					// ghost�k�U�� x �y��
		int  GetY2();					// ghost�k�U�� y �y��
		int random_time;
		void LoadBitmap();		// ���J�ϧ�
		void Initialize();				// �]�w��l��
		void Initialize_2();
		void TrackPacman(Pacman *pacman, int num);
		//int Random_num(int backgroundArray[479][636], int num);
		//void Change_Dir(int backgroundArray[479][636], int change);
		void OnMove(int backgroundArray[479][636], Pacman *pacman,int num);			// ����
		void OnMoveStar(int backgroundArray[479][636], Pacman *pacman);
		void OnShow(int backgroundArray[479][636], Pacman *pacman);			// �N�ϧζK��e��
		void OnShowStar(int backgroundArray[479][636], Pacman *pacman);
		bool is_alive;				// �O�_����
		bool IsAlive();											// �O�_����
		void SetIsAlive(bool alive);							// �]�w�O�_����
		bool HitEraser(Pacman* pacman);						// �O�_�I�����l
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetTryingDown(bool flag);	// �]�w���թ��U����
		void SetTryingLeft(bool flag);	// �]�w���թ�������
		void SetTryingRight(bool flag);	// �]�w���թ��k����
		void SetTryingUp(bool flag);	// �]�w���թ��W����
	

	protected:
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����

		bool tryingDown;			//�O�_�i�H���U
		bool tryingLeft;			//�O�_�i�H����
		bool tryingRight;			//�O�_�i�H���k
		bool tryingUp;				//�O�_�i�H���W
		CAnimation animationStar;	// �Q�ΰʵe�@�ϧ�

	private:
		int x, y;				// �ϧήy��
		int floor;				// �a�O��Y�y��
		bool rising;			// true��W�ɡBfalse��U��
		int initial_velocity;	// ��l�t��
		int velocity;			// �ثe���t��(�I/��)
		CAnimation animation;	// �Q�ΰʵe�@�ϧ�

		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}