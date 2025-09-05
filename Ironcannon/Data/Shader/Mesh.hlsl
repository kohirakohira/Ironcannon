//��۰��ٕϐ�.
//ø����� ڼ޽� t(n).
Texture2D		g_Texture	: register(t0);
//����ׂ� ڼ޽� s(n).
SamplerState	g_SamLinear	: register(s0);

//�ݽ����ޯ̧.
//ү���P��.
cbuffer per_mesh	: register( b0 )
{
	matrix	g_mW;			//ܰ��ލs��.
	matrix	g_mWVP;			//ܰ���,�ޭ�,��ۼު���݂̍����s��.
};
//��رْP��.
cbuffer per_material: register( b1 )
{
	float4	g_Ambient;		//���޴�ĐF(���F).
	float4	g_Diffuse;		//�ި̭��ސF(�g�U���ːF).
	float4	g_Specular;		//��߷�אF(���ʔ��ːF).
};
//�ڰђP��.
cbuffer per_frame	: register( b2 )
{
	float4	g_CameraPos;	//��׈ʒu(���_�ʒu).
	float4	g_LightDir;		//ײĂ̕����޸��.
};

//���_����ނ̏o�����Ұ�.
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
//	���_(�ްï��)�����.
//-------------------------------------------------
VS_OUTPUT VS_Main(
	float4 Pos	: POSITION,
	float4 Norm	: NORMAL,
	float2 UV	: TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//��ۼު���ݕϊ�(ܰ��ށ��ޭ�����ۼު����).
	output.Pos = mul( Pos, g_mWVP );

	//�@�������ق̎p���ɍ��킹��.
	// (���ق���]����Ζ@������]������K�v�����邽��).
	output.Normal = mul( Norm, ( float3x3 )g_mW );
	output.Normal = normalize( output.Normal );

	//ײĕ���:
	// �ިڸ����ײẮA�ǂ��ł���������.�ʒu�͖��֌W.
	output.Light = normalize( g_LightDir );

	output.PosWorld = mul( Pos, g_mW );

	//�����޸��:
	// ܰ��ދ�ԏ�ł̒��_���璸�_�֌������޸��.
	output.EyeVector = normalize( g_CameraPos - output.PosWorld );

	//ø������W.
	output.UV = UV;

	return output;
}

//*************************************************
//	׽�ײ��(���ؑ��Őݒ肷�鍀�ځB�����ł͐G��Ȃ�).
//*************************************************

//-------------------------------------------------
//	�߸�ټ����.
//-------------------------------------------------
float4 PS_Main( VS_OUTPUT input ) : SV_Target
{
	//ø����װ.
	float4 texColor = g_Texture.Sample( g_SamLinear, input.UV );

	//�����@�@.
	float4 ambient = texColor * g_Ambient;

	//�g�U���ˌ� �A.
	float NL = saturate( dot( input.Normal, input.Light ) );
	float4 diffuse = ( g_Diffuse / 2 + texColor / 2 )*NL;

	//���ʔ��ˌ� �B.
	float3 reflect = normalize( 2 * NL * input.Normal - input.Light );
	float4 specular =
		pow( saturate( dot( reflect, input.EyeVector ) ), 4 )*g_Specular;

	//�ŏI�F�@�@�A�B�̍��v.
	float4 Color = ambient + diffuse + specular;
	return Color;
}

//========= ø��������p ========================================
//-------------------------------------------------
//	���_(�ްï��)�����.
//-------------------------------------------------
VS_OUTPUT VS_NoTex(
	float4 Pos : POSITION,
	float4 Norm: NORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//��ۼު���ݕϊ�(ܰ��ށ��ޭ�����ۼު����).
	output.Pos = mul( Pos, g_mWVP );

	//�@�������ق̎p���ɍ��킹��.
	// (���ق���]����Ζ@������]������K�v�����邽��).
	output.Normal = mul( Norm, ( float3x3 )g_mW );
	output.Normal = normalize( output.Normal );

	//ײĕ���:
	// �ިڸ����ײẮA�ǂ��ł���������.�ʒu�͖��֌W.
	output.Light = normalize( g_LightDir );

	output.PosWorld = mul( Pos, g_mW );

	//�����޸��:
	// ܰ��ދ�ԏ�ł̒��_���璸�_�֌������޸��.
	output.EyeVector = normalize( g_CameraPos - output.PosWorld );


	return output;
}

//-------------------------------------------------
//	�߸�ټ����.
//-------------------------------------------------
float4 PS_NoTex( VS_OUTPUT input ) : SV_Target
{
	//ø����װ.
	//�����@�@.
	float4 ambient = g_Ambient;

	//�g�U���ˌ� �A.
	float NL = saturate( dot( input.Normal, input.Light ) );
	float4 diffuse = g_Diffuse * NL;

	//���ʔ��ˌ� �B.
	float3 reflect = normalize( 2 * NL * input.Normal - input.Light );
	float4 specular =
		pow( saturate( dot( reflect, input.EyeVector ) ), 4 )*g_Specular;

	//�ŏI�F�@�@�A�B�̍��v.
	float4 Color = ambient + diffuse + specular;
	return Color;
}
