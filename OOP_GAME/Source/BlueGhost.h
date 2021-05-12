#include "stdafx.h"
#include <ddraw.h>
#include "gamelib.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// �o��class���ѷ|�@���u�����y
// �����N�i�H��g���ۤv���{���F
/////////////////////////////////////////////////////////////////////////////

class BlueGhost
{
public:
	BlueGhost();

	bool HitEraser(Pacman *pacman);						// �O�_�I�����l
	bool IsAlive();											// �O�_����
	void LoadBitmap();		// ���J�ϧ�
	void OnMove();			// ����
	void SetIsAlive(bool alive);							// �]�w�O�_����
	void OnShow();			// �N�ϧζK��e��
	void Initialize();				// �]�w��l��

protected:
	CMovingBitmap bmp;			// ������
	int xx, yy;					// ��ߪ��y��
	int dxx, dyy;					// �y�Z����ߪ��첾�q
//	int index;					// �y���u���סv�A0-17���0-360��
//	int delay_counter;			// �վ����t�ת��p�ƾ�
//	int delay;					// ���઺�t��
	bool is_alive;				// �O�_����
	int x, y;				// �ϧήy��
	int floor;				// �a�O��Y�y��
	bool rising;			// true��W�ɡBfalse��U��
	int initial_velocity;	// ��l�t��
	int velocity;			// �ثe���t��(�I/��)
	CAnimation animation;	// �Q�ΰʵe�@�ϧ�

private:
	
	

	bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
};
