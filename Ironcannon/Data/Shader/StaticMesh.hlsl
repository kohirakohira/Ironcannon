/*********************************************************************
*	�X�^�e�B�b�N���b�V���N���X�p�V�F�[�_�t�@�C��.
**/
//�O���[�o���ϐ�.
//�e�N�X�`���� ���W�X�^ t(n).
Texture2D		g_Texture	: register( t0 );
//�T���v���� ���W�X�^ s(n).
SamplerState	g_SamLinear	: register( s0 );

//�R���X�^���g�o�b�t�@.
//���b�V���P��.
cbuffer per_mesh	: register( b0 )
{
	matrix	g_mW;			//���[���h�s��.
	matrix	g_mWVP;			//���[���h,�r���[,�v���W�F�N�V�����̍����s��.
};
//�}�e���A���P��.
cbuffer per_material: register( b1 )
{
	float4	g_Diffuse;		//�f�B�t���[�Y�F(�g�U���ːF).
	float4	g_Ambient;		//�A���r�G���g�F(���F).
	float4	g_Specular;		//�X�y�L�����F(���ʔ��ːF).
};
//�t���[���P��.
cbuffer per_frame	: register( b2 )
{
	float4	g_CameraPos;	//�J�����ʒu(���_�ʒu).
	float4	g_vLightDir;	//���C�g�̕����x�N�g��.
};

//���_�V�F�[�_�̏o�̓p�����[�^.
struct VS_OUTPUT
{
	float4	Pos			: SV_Position;
	float3	Normal		: TEXCOORD0;
	float2	UV			: TEXCOORD1;
	float3	Light		: TEXCOORD2;
	float3	EyeVector	: TEXCOORD3;
	float4	PosWorld	: TEXCOORD4;
	float4	Color		: COLOR;
};

//-------------------------------------------------
//	���_(�o�[�e�b�N�X)�V�F�[�_.
//-------------------------------------------------
VS_OUTPUT VS_Main(
	float4 Pos	: POSITION,
	float4 Norm	: NORMAL,
	float2 UV	: TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//�v���W�F�N�V�����ϊ�(���[���h,�r���[,�v���W�F�N�V����).
	output.Pos = mul( Pos, g_mWVP );

	//�@�������f���̎p���ɍ��킹��.
	// (���f������]����Ζ@������]������K�v�����邽��).
	output.Normal = mul( Norm, (float3x3)g_mW );
	output.Normal = normalize( output.Normal );

	//���C�g����:
	// �f�B���N�V���i�����C�g�́A�ǂ��ł���������.�ʒu�͖��֌W.
	output.Light = normalize( g_vLightDir );

	output.PosWorld = mul( Pos, g_mW );

	//�����x�N�g��:
	// ���[���h��ԏ�ł̒��_���璸�_�֌������x�N�g��.
	output.EyeVector = normalize( g_CameraPos - output.PosWorld );

	//�e�N�X�`�����W.
	output.UV = UV;

	return output;
}

//-------------------------------------------------
//	�s�N�Z���V�F�[�_.
//-------------------------------------------------
float4 PS_Main( VS_OUTPUT input ) : SV_Target
{
	//�e�N�X�`���J���[.
	float4 texColor = g_Texture.Sample( g_SamLinear, input.UV );

	//�����@���P.
	float4 ambient = texColor * g_Ambient;

	//�g�U���ˌ� ���Q.
	float NL = saturate( dot( input.Normal, input.Light ) );
	float4 diffuse = ( g_Diffuse / 2 + texColor / 2 )*NL;

	//���ʔ��ˌ� ���R.
	float3 reflect = normalize( 2 * NL * input.Normal - input.Light );
	float4 specular =
		pow( saturate( dot( reflect, input.EyeVector ) ), 4 )*g_Specular;

	//�ŏI�F�@���P�C�Q�C�R�̍��v.
	float4 Color = ambient + diffuse + specular;
	return Color;
}

//========= �e�N�X�`�������p ========================================
//-------------------------------------------------
//	���_(�o�[�e�b�N�X)�V�F�[�_.
//-------------------------------------------------
VS_OUTPUT VS_NoTex(
	float4 Pos : POSITION,
	float4 Norm: NORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//�v���W�F�N�V�����ϊ�(���[���h,�r���[,�v���W�F�N�V����).
	output.Pos = mul( Pos, g_mWVP );

	//�@�������f���̎p���ɍ��킹��.
	// (���f������]����Ζ@������]������K�v�����邽��).
	output.Normal = mul( Norm, ( float3x3 )g_mW );
	output.Normal = normalize( output.Normal );

	//���C�g����:
	// �f�B���N�V���i�����C�g�́A�ǂ��ł���������.�ʒu�͖��֌W.
	output.Light = normalize( g_vLightDir );

	output.PosWorld = mul( Pos, g_mW );

	//�����x�N�g��:
	// ���[���h��ԏ�ł̒��_���璸�_�֌������x�N�g��.
	output.EyeVector = normalize( g_CameraPos - output.PosWorld );


	return output;
}

//-------------------------------------------------
//	�s�N�Z���V�F�[�_.
//-------------------------------------------------
float4 PS_NoTex( VS_OUTPUT input ) : SV_Target
{
	//�e�N�X�`���J���[.
	//�����@���P.
	float4 ambient = g_Ambient;

	//�g�U���ˌ� ���Q.
	float NL = saturate( dot( input.Normal, input.Light ) );
	float4 diffuse = g_Diffuse * NL;

	//���ʔ��ˌ� ���R.
	float3 reflect = normalize( 2 * NL * input.Normal - input.Light );
	float4 specular =
		pow( saturate( dot( reflect, input.EyeVector ) ), 4 )*g_Specular;

	//�ŏI�F�@���P�C�Q�C�R�̍��v.
	float4 Color = ambient + diffuse + specular;
	return Color;
}
