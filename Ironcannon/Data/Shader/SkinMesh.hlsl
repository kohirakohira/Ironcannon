/***************************************************************************************************
*	SkinMeshCode Version 2.50
*	LastUpdate	: 2025/06/23.
**/
//------------------------------------------------.
//	�萔.
//------------------------------------------------.
static const int MAX_BONE_MATRICES = 255;

//------------------------------------------------.
//	�O���[�o���ϐ�.
//------------------------------------------------.
Texture2D		g_Texture	: register( t0 );	//�e�N�X�`���[�́A���W�X�^�[t(n).
SamplerState	g_Sampler	: register( s0 );	//�T���v���[�́A���W�X�^�[s(n).

//------------------------------------------------.
//	�R���X�^���g�o�b�t�@.
//------------------------------------------------.
//���b�V��.
cbuffer per_mesh		: register( b0 )
{
	float4x4 g_mW;		//���[���h�s��.
	float4x4 g_mWVP;	//���[���h,�r���[,�v���W�F�N�V�����̍����s��.
};
//�}�e���A��.
cbuffer per_material	: register( b1 )
{
	float4 g_Ambient;	//�A���r�G���g�F(���F).
	float4 g_Diffuse;	//�f�B�t���[�Y�F(�g�U���ːF).
	float4 g_Specular;	//�X�y�L�����F(���ʔ��ːF).
};
//�t���[��.
cbuffer per_frame		: register( b2 )
{
    float4 g_CameraPos; //�J�����ʒu(�n�_�ʒu).
    float4 g_vLightDir;  //���C�g�̕����x�N�g��.
};
//�{�[���̃|�[�Y�s�񂪓���.
cbuffer per_bones		: register( b3 )
{
	float4x4 g_mConstBoneWorld[MAX_BONE_MATRICES];
};

//�X�L�j���O��̒��_�E�@��������.
struct Skin
{
	float4 Pos;
	float4 Norm;
};
//�o�[�e�b�N�X�o�b�t�@�[�̓���.
struct VSSkinIn
{
	float3 Pos		: POSITION;		//�ʒu.  
	float3 Norm		: NORMAL;		//���_�@��.
	float2 UV		: TEXCOORD;		//UV���W�i�e�N�X�`���[���W�j.
	uint4  Bones	: BONE_INDEX;	//�{�[���̃C���f�b�N�X.
	float4 Weights	: BONE_WEIGHT;	//�{�[���̏d��.
};

//�s�N�Z���V�F�[�_�[�̓��́i�o�[�e�b�N�X�o�b�t�@�[�̏o�́j�@
struct PSSkinIn
{
	float4 Pos		: SV_Position;	//�ʒu.
	float3 Norm		: TEXCOORD0;	//���_�@��.
	float2 UV		: TEXCOORD1;	//UV���W�i�e�N�X�`���[���W�j.
	float3 Light	: TEXCOORD2;	//���C�g.
	float3 EyeVector: TEXCOORD3;	//�����x�N�g��.
	float4 PosWorld : TEXCOORD4;	//���[���h���W.
	float4 Color	: COLOR;		//�ŏI�J���[�i���_�V�F�[�_�[�ɂ����Ắj.
};


//�w�肵���ԍ��̃{�[���̃|�[�Y�s���Ԃ�.
//	�T�u�֐��i�o�[�e�b�N�X�V�F�[�_�[�Ŏg�p�j.
matrix FetchBoneMatrix( uint Bone )
{
	return g_mConstBoneWorld[Bone];
}


//���_���X�L�j���O�i�{�[���ɂ��ړ��j����.
//	�T�u�֐��i�o�[�e�b�N�X�V�F�[�_�[�Ŏg�p�j.
Skin SkinVert( VSSkinIn Input )
{
	Skin Output = (Skin)0;

	float4 Pos	= float4( Input.Pos, 1.f );		//���W��w�� 1.
	float4 Norm = float4( Input.Norm, 0.f );	//�x�N�g����w�� 0.
	//�{�[��0.
	uint Bone	= Input.Bones.x;
	float Weight= Input.Weights.x;
	float4x4 m	= FetchBoneMatrix( Bone );
	Output.Pos	+= Weight * mul( Pos, m );
	Output.Norm += Weight * mul( Norm, m );
	
	//�{�[��1.
	Bone		= Input.Bones.y;
	Weight		= Input.Weights.y;
	m			= FetchBoneMatrix( Bone );
	Output.Pos	+= Weight * mul( Pos, m );
	Output.Norm += Weight * mul( Norm, m );
	
	//�{�[��2.
	Bone		= Input.Bones.z;
	Weight		= Input.Weights.z;
	m			= FetchBoneMatrix( Bone );
	Output.Pos	+= Weight * mul( Pos, m );
	Output.Norm += Weight * mul( Norm,m );
	
	//�{�[��3.
	Bone		= Input.Bones.w;
	Weight		= Input.Weights.w;
	m			= FetchBoneMatrix( Bone );
	Output.Pos	+= Weight * mul( Pos, m );
	Output.Norm += Weight * mul( Norm, m );

	return Output;
}

// �o�[�e�b�N�X�V�F�[�_.
PSSkinIn VS_Main( VSSkinIn input )
{
	PSSkinIn output = (PSSkinIn)0;
	
	Skin vSkinned = SkinVert( input );

	//�v���W�F�N�V�����ϊ��i���[���h�A�r���[�A�v���W�F�N�V�����j.
	output.Pos	= mul( vSkinned.Pos, g_mWVP );
	
	//�@�������f���̎p���ɍ��킹��.
	// (���f������]����Ζ@������]������K�v�����邽��).
	output.Norm = normalize( (float3)mul( vSkinned.Norm, g_mW ) );
	
	//���C�g����:
	// �f�B���N�V���i�����C�g�́A�ǂ��ł���������.�ʒu�͖��֌W.
	output.Light = normalize( g_vLightDir.xyz );
	
	//���[���h���W.
	output.PosWorld = mul( float4( input.Pos, 1.f ), g_mW );
	
	//�����x�N�g��:
	// ���[���h��ԏ�ł̒��_���璸�_�֌������x�N�g��.
	output.EyeVector = normalize( g_CameraPos.xyz - output.PosWorld.xyz );	//w�ȊO�Ōv�Z.

	//UV���W�i�e�N�X�`�����W�j.	
	output.UV	= input.UV;

	return output;
}

// �s�N�Z���V�F�[�_.
float4 PS_Main( PSSkinIn input ) : SV_Target
{
	//�e�N�X�`������s�N�Z���F�����o��.
	float4 texColor = g_Texture.Sample( g_Sampler, input.UV );

	//���� ���P.
	float4 ambient = texColor * g_Ambient;

	//�g�U���ˌ� ���Q.
	float NL = saturate( dot( input.Norm.xyz, input.Light.xyz ) );
	float4 diffuse = ( g_Diffuse * 0.5f + texColor * 0.5f ) * NL;

	//���ʔ��ˌ� ���R.
	float3 reflect = normalize( 2.f * NL * input.Norm.xyz - input.Light.xyz );
	float4 specular =
		pow( saturate( dot( reflect, input.EyeVector.xyz ) ), 4.f ) * g_Specular;

	//�ŏI�F�@���P�C�Q�C�R�̍��v.
	float4 Color = ambient + diffuse + specular;
	
	// �e�N�X�`���̃��l�����̂܂܎g�p.
	Color.a = texColor.a;
	
	return Color;
}
