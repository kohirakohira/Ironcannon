#include "CInputManager.h"
#include <cmath>

CInputManager::CInputManager(DWORD ID)
    : m_XInput(nullptr)
    , m_KeyInput(nullptr)
    , m_UseKeyInput(false)
{
    m_XInput = new CXInput(ID);

    if (ID == 0) // 0�Ԃ����L�[�{�[�h������ł���悤�ɂ���
    {
        m_UseKeyInput = true;
        m_KeyInput = std::make_unique<CKeyInput>();
    }
}

CInputManager::~CInputManager()
{
    SAFE_DELETE(m_XInput);
}

void CInputManager::Update()
{
    // �X�e�B�b�N�̓��͂ƕ������擾�������ɕێ�
    m_LeftStickDir = GetLeftStickDirection(m_LeftStickVec);     // ���X�e�B�b�N
    m_RightStickDir = GetRightStickDirection(m_RightStickVec);  // �E�X�e�B�b�N
    
    if (m_XInput != nullptr)
    {
        m_XInput->Update();
    }

    if (m_UseKeyInput)
    {
        m_KeyInput->Update();
    }
}

// ���X�e�B�b�N�̓��͌��m
CInputManager::Direction CInputManager::GetLeftStickDirection(Vector2& Vec)
{
    // �X�e�B�b�N�̎��f�[�^���擾
    SHORT LeftX = m_XInput->GetLThumbX();
    SHORT LeftY = m_XInput->GetLThumbY();

    // float�ɕϊ����āA-1.0f�`1.0�ɐ��K��
    float fx = static_cast<float>(LeftX) / MAX_THUMB_VALUE;
    float fy = static_cast<float>(LeftY) / MAX_THUMB_VALUE;

    // �f�b�h�]�[������
    // �X�e�B�b�N��臒l��菬�����Ƃ��͖����씻��
    if (std::fabs(fx) < THRESHOLD && std::fabs(fy) < THRESHOLD)
    {
        // �x�N�g����0�ɐݒ�(�ړ��Ȃ�)
        Vec = { 0.0f, 0.0f };

        // �����Ȃ���Ԃ�
        return Direction::None;
    }

    // �X�e�B�b�N�̓��͊i�[
    Vec = { fx, fy };

    // �x�N�g���̕����ɉ����������񋓂�Ԃ�
    return GetDirectionFromXY(fx, fy, THRESHOLD);
}

// �E�X�e�B�b�N�̓��͌��m
CInputManager::Direction CInputManager::GetRightStickDirection(Vector2& Vec)
{
    // �X�e�B�b�N�̎��f�[�^���擾
    SHORT LeftX = m_XInput->GetRThumbX();
    SHORT LeftY = m_XInput->GetRThumbY();

    // float�ɕϊ����āA-1.0f�`1.0�ɐ��K��
    float fx = static_cast<float>(LeftX) / MAX_THUMB_VALUE;
    float fy = static_cast<float>(LeftY) / MAX_THUMB_VALUE;

    // �f�b�h�]�[������
    // �X�e�B�b�N��臒l��菬�����Ƃ��͖����씻��
    if (std::fabs(fx) < THRESHOLD && std::fabs(fy) < THRESHOLD)
    {
        // �x�N�g����0�ɐݒ�(�ړ��Ȃ�)
        Vec = { 0.0f, 0.0f };

        // �����Ȃ���Ԃ�
        return Direction::None;
    }

    // �X�e�B�b�N�̓��͊i�[
    Vec = { fx, fy };

    // �x�N�g���̕����ɉ����������񋓂�Ԃ�
    return GetDirectionFromXY(fx, fy, THRESHOLD);
}

// ���g���K�[�̓��͌��m
CInputManager::Trigger CInputManager::GetLeftTrigger()
{
    BYTE PushTrigger = m_XInput->GetLTrigger();

    // �g���K�[�̉�������
    if (PushTrigger > TriggerTHRESHOLD)
    {
        return Trigger::LeftTrigger; // ���g���K�[��Ԃ�
    }

    return Trigger::None; // ���ݒ��Ԃ�
}

// �E�g���K�[�̓��͌��m
CInputManager::Trigger CInputManager::GetRightTrigger()
{
    BYTE PushTrigger = m_XInput->GetRTrigger();

    // �g���K�[�̉�������
    if (PushTrigger > TriggerTHRESHOLD)
    {
        return Trigger::RightTrigger; // �E�g���K�[��Ԃ�
    }

    return Trigger::None; // ���ݒ��Ԃ�
}

// WASD�L�[�̓��͌��m
CInputManager::Direction CInputManager::GetWASDKeyDirection()
{
    float x = 0.f;
    float y = 0.f;

    if (m_UseKeyInput)
    {
        if (m_KeyInput->IsRepeat('W')) y = 1.0f;
        if (m_KeyInput->IsRepeat('S')) y = -1.0f;
        if (m_KeyInput->IsRepeat('A')) x = -1.0f;
        if (m_KeyInput->IsRepeat('D')) x = 1.0f;
    }

    return GetDirectionFromXY(x, y, THRESHOLD);
}

// ���L�[�̓��͌��m
CInputManager::Direction CInputManager::GetArrowKeyDirection()
{
    float x = 0.f;
    float y = 0.f;

    if (m_UseKeyInput)
    {
        if (m_KeyInput->IsRepeat(VK_UP)) y = 1.0f;
        if (m_KeyInput->IsRepeat(VK_DOWN)) y = -1.0f;
        if (m_KeyInput->IsRepeat(VK_LEFT)) x = -1.0f;
        if (m_KeyInput->IsRepeat(VK_RIGHT)) x = 1.0f;
    }

    return GetDirectionFromXY(x, y, THRESHOLD);
}

// XY���W��������񋓌^�ɕϊ����鋤�ʊ֐�
CInputManager::Direction CInputManager::GetDirectionFromXY(float x, float y, float threshold)
{
    // �����(Y�����v���X)
    if (y > threshold) 
    {
        // ������(X�����}�C�i�X)
        if (x < -threshold)
        {
            // ���������Ԃ�
            return Direction::UpLeft;
        }

        // �E����(X�����v���X)
        if (x > threshold)
        {
            // �E�������Ԃ�
            return Direction::UpRight;
        }

        // ���E���͂��Ȃ��Ƃ��͏������Ԃ�
        return Direction::Up;
    }

    // ������(Y�����}�C�i�X)
    if (y < -threshold)
    {
        // ������(X�����}�C�i�X)
        if (x < -threshold)
        {
            // ����������Ԃ�
            return Direction::DownLeft;
        }

        // �E����(X�����v���X)
        if (x > threshold)
        {
            // �E��������Ԃ�
            return Direction::DownRight;
        }

        // ���E���͂��Ȃ��Ƃ��͉���Ԃ�
        return Direction::Down;
    }
    else // Y�����͂��Ȃ��Ƃ�
    {
        // �E����(X�����v���X)
        if (x > threshold)
        {
            // �E������Ԃ�
            return Direction::Right;
        }

        // ������(X�����}�C�i�X)
        if (x < -threshold)
        {
            // ��������Ԃ�
            return Direction::Left;
        }
    }

    // �����͂�Ԃ�
    return Direction::None;
}

// �L�[�{�[�h�p
// �L�[���������u��(�g���K�[)
bool CInputManager::IsKeyboardDown(int key)
{
    if (!m_UseKeyInput || !m_KeyInput)
        return false;
    return m_KeyInput->IsDown(key);
}

// �L�[�������ꑱ���Ă���
bool CInputManager::IsKeyboardRepeat(int key)
{
    if (!m_UseKeyInput || !m_KeyInput)
        return false;
    return m_KeyInput->IsRepeat(key);
}

// �L�[�������ꂽ(�����[�X)
bool CInputManager::IsKeyboardUp(int key)
{
    if (!m_UseKeyInput || !m_KeyInput)
        return false;
    return m_KeyInput->IsUp(key);
}

// �R���g���[���[�p
// �{�^�����������u��(�g���K�[)
bool CInputManager::IsControllerDown(CXInput::KEY key)
{
    if (!m_XInput)
        return false;
    return m_XInput->IsDown(key);
}

// �{�^���������ꑱ���Ă���
bool CInputManager::IsControllerRepeat(CXInput::KEY key)
{
    if (!m_XInput)
        return false;
    return m_XInput->IsDown(key);
}

// �{�^���������ꂽ(�����[�X)
bool CInputManager::IsControllerUp(CXInput::KEY key)
{
    if (!m_XInput)
        return false;
    return m_XInput->IsDown(key);
}
