#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"
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

		void LoadBitmap();		// ���J�ϧ�

		void OnMove(int backgroundArray[479][636],int num);			// ����
		void OnShow();			// �N�ϧζK��e��

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

	private:
		int x, y;				// �ϧήy��
		int floor;				// �a�O��Y�y��
		bool rising;			// true��W�ɡBfalse��U��
		int initial_velocity;	// ��l�t��
		int velocity;			// �ثe���t��(�I/��)
		CAnimation animation;	// �Q�ΰʵe�@�ϧ�
	};
}