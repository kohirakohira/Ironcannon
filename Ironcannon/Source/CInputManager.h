#pragma once
#include "CXInput.h"     // �R���g���[���[�N���X
#include "CKeyInput.h"   // �L�[�{�[�h����
#include <memory>

//==========================================
// ���͓����}�l�[�W���[�N���X
// �S���F�M�� ����
//==========================================

class CInputManager
{
    //-----------------------
    // �萔�錾
    //-----------------------
public: // �ϐ�
    static constexpr float      MAX_THUMB_VALUE = 32767.0f;   // SHORT�^�̐��K���p�̒萔
    static constexpr float      THRESHOLD = 0.2f;             // �X����臒l(0f~1f)
    static constexpr BYTE       TriggerTHRESHOLD = 30;        // �g���K�[��臒l

public: // �\����&�񋓌^
    // �L�[�ɂ��ړ��x�N�g��.
    struct Vector2
    {
        float x;
        float z;
    };

    // �X�e�B�b�N�̓��͕���
    enum class Direction
    {
        Up,         // ��
        Down,       // ��
        Left,       // ��
        Right,      // �E

        UpLeft,     // ����
        UpRight,    // �E��
        DownLeft,   // ����
        DownRight,  // �E��

        None = -1   // ���ݒ�
    };

    // �g���K�[����
    enum class Trigger
    {
        LeftTrigger,    // ���g���K�[
        RightTrigger,   // �E�g���K�[
       
        None = -1       // ���ݒ�          
    };

public:
    CInputManager(DWORD ID);    // �R���X�g���N�^
    ~CInputManager();           // �f�X�g���N�^

    // ���͂𖈃t���[�����s
    void Update();

    // ���͏����̋��ʉ�
    Direction GetLeftStickDirection(Vector2& Vec);
    Direction GetRightStickDirection(Vector2& Vec);

    // �g���K�[����
    Trigger GetLeftTrigger();   // ���g���K�[�̓��͌��m
    Trigger GetRightTrigger();  // �E�g���K�[�̓��͌��m

    // �L�[�{�[�h���͕����擾�iWASD or ���L�[�j
    Direction GetWASDKeyDirection();
    Direction GetArrowKeyDirection();

    // �L�[�{�[�h�p
    bool IsKeyboardDown(int Key);	// �L�[���������u��(�g���K�[)
    bool IsKeyboardRepeat(int Key);	// �L�[�������ꑱ���Ă���
    bool IsKeyboardUp(int Key);		// �L�[�������ꂽ(�����[�X)

    // �R���g���[���[�p
    bool IsControllerDown(CXInput::KEY key);	// �{�^�����������u��(�g���K�[)
    bool IsControllerRepeat(CXInput::KEY key);	// �{�^���������ꑱ���Ă���
    bool IsControllerUp(CXInput::KEY key);		// �{�^���������ꂽ(�����[�X)

    // ���X�e�B�b�N�̃x�N�g����Ԃ�
    const Vector2& GetLeftStickVector() const { return m_LeftStickVec; }
    // ���X�e�B�b�N�̌��݂̕�����Ԃ�
    const Direction GetLeftStickDirection() const { return m_LeftStickDir; }

    // �E�X�e�B�b�N�̃x�N�g����Ԃ�
    const Vector2& GetRightStickVector() const { return m_RightStickVec; }
    // �E�X�e�B�b�N�̌��݂̕�����Ԃ�
    const Direction GetRightStickDirection() const { return m_RightStickDir; }

private:
    // XY���W����������肷�鋤�ʊ֐�
    Direction GetDirectionFromXY(float x, float y, float threshold);

private:
    CXInput*                    m_XInput;       // �R���g���[���[���̓N���X
    std::unique_ptr<CKeyInput>  m_KeyInput;     // �L�[���̓N���X

    bool                        m_UseKeyInput;  // �L�[�{�[�h���삷�邩

    // �X�e�B�b�N�̃x�N�g��
    Vector2 m_LeftStickVec = { 0.0f, 0.0f };
    Vector2 m_RightStickVec = { 0.0f, 0.0f };

    // ���͕������X�e�B�b�N�ɐݒ�
    Direction m_LeftStickDir = Direction::None;
    Direction m_RightStickDir = Direction::None;
};
