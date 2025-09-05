/*********************************************************************
*	�X�v���C�g3D�N���X�p�V�F�[�_�t�@�C��.
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
	matrix	g_mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̕ϊ������s��.
	float4	g_Color;	//�F�iRGBA:xyzw�j.
	float4	g_UV;		//UV���W�ixy�����g��Ȃ��j.
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
	output.Pos = mul( Pos, g_mWVP );
	output.UV = UV;
	
	//UV�X�N���[��(UV���W�𑀍삷��)
    output.UV.x += g_UV.x;
    output.UV.y += g_UV.y;

	return output;
}

//�s�N�Z���V�F�[�_.
//��ʏ�ɕ]�����s�N�Z���i�h�b�g1���j�̐F�����肷��.
float4 PS_Main( VS_OUTPUT input ) : SV_Target
{
	float4 color = g_Texture.Sample( g_samLinear, input.UV );//�F��Ԃ�.

	//�v���O��������̃��l���e�N�X�`���������Ă��郿�l�ɂ������킹��.
	color.a *= g_Color.a;

	return color;
}