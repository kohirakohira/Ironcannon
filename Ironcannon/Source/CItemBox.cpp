#include "CItemBox.h"

CItemBox::CItemBox()
	: InitialSpeed			( 0.f )
	, GravitySpeed			( -9.8f )
	, m_ItemType			()
{
	//���0.016�ӂ�ɂȂ�.
	Framerate = 1.f / 60.f;
}

CItemBox::~CItemBox()
{

}

void CItemBox::Update()
{
	//�A�C�e���𗎉������邽�߂̊֐�.
	GravityMath();

	switch (m_ItemType)
	{
	case CItemType::Shield:
		//��񖳓G.
		ShieldEffect();
		break;
	case CItemType::SpeedUp:
		//���x�㏸.
		SpeedUpEffect();
		break;
	case CItemType::PowerUp:
		//�U���͏㏸.
		PowerUpEffect();
		break;
	case CItemType::BlastUp:
		//�����͈͑���.
		BlastUpEffect();
		break;
	case CItemType::Reflection:
		//����.
		ReflectionEffect();
		break;
	case CItemType::Reload:
		//�����[�h�Z�k.
		ReloadEffect();
		break;
	default:
		break;
	}
}

void CItemBox::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CStaticMeshObject::Draw(View, Proj, Light, Camera);
}

//�d�͂̌v�Z�p(���ɗ���).
void CItemBox::GravityMath()
{
	//�ʒu�ω�(Y���W += �������x * 1�t���[�� + 0.5f * �d�͉����x * 1�t���[�� * 1�t���[��)��0.5f��1/2�̂���.
	//�u0.5f * �d�͉����x * 1�t���[�� * 1�t���[���v�́u�����x�ɂ���ĕ��̂��ǂꂾ���ړ����邩�v��\����.
	//1�t���[�� * 1�t���[����1�t���[���ɂ����鎞��.
	//����:�������x�����^��.
	m_vPosition.y += InitialSpeed * Framerate + 0.5f * GravitySpeed * Framerate * Framerate;

	//���x�ω�(�������x += �d�͉����x / 2 * 1�t���[��)��/ 2 �͗������x�̒����p.
	InitialSpeed += GravitySpeed / 2 * Framerate;

	if (m_vPosition.y < 0)
	{
		m_vPosition.y = 20.f;
		InitialSpeed = 0.f;
	}
}

void CItemBox::SetItemInfo(CItemType item)
{
	m_ItemType = item;
}

void CItemBox::ShieldEffect()
{
	m_Item.m_ShieldFlag = true;
}

void CItemBox::SpeedUpEffect()
{
	//�萔�錾.
	static constexpr float PLUS_SPEED = 5.f;

	//�������鑬�x�ݒ�.
	m_Item.m_Speed = PLUS_SPEED;
}

void CItemBox::PowerUpEffect()
{
	//�萔�錾.
	static constexpr float PLUS_POWER = 3.f;

	//�U���͂�ݒ�.
	m_Item.m_Power = PLUS_POWER;
}

void CItemBox::BlastUpEffect()
{
	//�萔�錾.
	static constexpr float BLAST_RAD = 30.f;

	//���a��ݒ�.
	m_Item.m_Blast = BLAST_RAD;
}

void CItemBox::ReflectionEffect()
{
	//���˂���.
	m_Item.m_Reflection = true;
}

void CItemBox::ReloadEffect()
{
	//�萔�錾.
	static constexpr float RELOAD_INTERVAL = 0.5f;

	//�����[�h�Z�k.
	m_Item.m_Reload = RELOAD_INTERVAL;
}
