/**************************************************
*	���C�i�����j�`��N���X�p�V�F�[�_�t�@�C��
**/
//�O���[�o���ϐ�
//�R���X�^���g�o�b�t�@
//�A�v�����Ɠ����o�b�t�@�T�C�Y�ɂȂ��Ă���K�v������
cbuffer per_mesh : register(b0) //���W�X�^�ԍ�
{
    matrix g_mWVP;  //���[���h,�r���[,�v���W�F�N�V�����̕ϊ������s��
    float4 g_Color; //�F(RGBA:xyzw)
};

//���_�V�F�[�_
//��Ƀ��f���̒��_�̕`��ʒu�����肷��
float4 VS_Main( float4 Pos : POSITION ) : SV_POSITION
{
	return Pos;
}

//�s�N�Z���V�F�[�_
//��ʏ�ɕ]�����s�N�Z���i�h�b�g�P���j�̐F�����肷��
float4 PS_Main(float4 Pos : SV_POSITION) : SV_Target
{
    return g_Color;
}