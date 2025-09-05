/*********************************************************************
*	�f�o�b�O�e�L�X�g�N���X�p�V�F�[�_�t�@�C��.
**/
//�O���[�o���ϐ�.
//�e�N�X�`���� ���W�X�^ t(n).
Texture2D		g_Texture	: register( t0 );
//�T���v���� ���W�X�^ s(n).
SamplerState	g_samLinear	: register( s0 );

//�R���X�^���g�o�b�t�@.
//�A�v�����Ɠ����o�b�t�@�T�C�Y�ɂȂ��Ă���K�v������.
cbuffer per_mesh : register( b0 )	//���W�X�^�ԍ�.
{
	matrix	g_mWorld	: packoffset(c0);	//���[���h�s��.
	float4	g_Color		: packoffset(c4);	//�F�iRGBA:xyzw�j.
	float	g_ViewPortW	: packoffset(c5);	//�r���[�|�[�g��
	float	g_ViewPortH	: packoffset(c6);	//�r���[�|�[�g����
};

//���_�V�F�[�_�̏o�̓p�����[�^.
//���_�V�F�[�_�Ő��䂵�������̒l���s�N�Z���V�F�[�_���ɓn�����߂ɗp�ӂ��Ă���.
struct VS_OUTPUT
{
	float4	Pos		: SV_Position;	//���W�iSV_:System-Value Semantics�j.
	float2	UV		: TEXCOORD0;	//UV���W.
};

//���_�V�F�[�_.
//��Ƀ��f���̒��_�̕`��ʒu�����肷��.
VS_OUTPUT VS_Main(
	float4 Pos	: POSITION,
	float2 UV	: TEXCOORD )
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul( Pos, g_mWorld );
	
	//�X�N���[�����W�ɍ��킹��v�Z
    output.Pos.x = (output.Pos.x / g_ViewPortW) * 2.f - 1.f;
    output.Pos.y = 1.f - (output.Pos.y / g_ViewPortH) * 2.f;
	
	output.UV = UV;
	
	return output;
}

//�s�N�Z���V�F�[�_.
//��ʏ�ɕ]�����s�N�Z���i�h�b�g1���j�̐F�����肷��.
float4 PS_Main( VS_OUTPUT input ) : SV_Target
{
	float4 color = g_Texture.Sample( g_samLinear, input.UV );//�F��Ԃ�.

	//�v���O��������̐F(RGBA)���e�N�X�`���������Ă���F(RGBA)�ɂ������킹��.
	color *= g_Color;

	return color;
}