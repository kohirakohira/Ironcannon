#include "CPlayer.h"
#include <d3dx9math.h>

class CComPlayer 
	: public CPlayer
{
public:
	CComPlayer();
	~CComPlayer() override;

	void Initialize(int id)override;
	void Update() override;

	//�ǔ��Ώۂ̐ݒ�
	void SetTarget(std::shared_ptr<CPlayer> player);
	void ClearTarget();

	//�`���[�j���O�l,m_��t���Y�ꂽ�̂ł��ƂŏC������
	float MoveSpeed;		// 1�t���[���̑O�i��
	float TurnStep;			// 1�t���[���̉񓪗�
	float AimTurnStep;		// �C���񓪂�1�t���[����
	float KeepDistance;		// ���̋�����ۂ�
	float CannonHeight;		// �C���̍����I�t�Z�b
	float m_AvoidRadius;		// �ق�COM���痣��锼�a
	float m_AvoidWeight;		// �����x�N�g���̏d��(0�Ŗ���.1����)

	D3DXVECTOR3 GetPosition() const override;
	D3DXVECTOR3 GetRotation() const override;

private:
	std::shared_ptr<CPlayer> m_Target;	//�ǔ��Ώ�
	bool m_Registered;	//�C���X�^���X�o�^�Ǘ�

	//��������
	void SanitizeParams();
	void TickChaseTo(const D3DXVECTOR3& targetPos);
	void TickAimTo(const D3DXVECTOR3& targetPos);

	// �w���p
	static float Wrap(float rad);                         // [-��,��]�ɐ��K��
	static float Approach(float cur, float goal, float step);
	static D3DXVECTOR3 ForwardFromYaw(float yaw);         // (sin(yaw),0,cos(yaw))

	//����COM���d�Ȃ����肷��̂�h���v�Z
	void ComputeSeparation(const D3DXVECTOR3& selfPos,
		D3DXVECTOR3& outSep, float& outNearest) const;

	//COM�C���X�^���X�̐ÓI���W�X�g��
	static std::vector<CComPlayer*>& Instances();

};