#include "CComPlayer.h"
#include "CBody.h"
#include "CCannon.h"
#include <cmath>

#undef min

// ---- ���w���p ----
static inline float PI() { return D3DX_PI; }
static inline float TWO_PI() { return D3DX_PI * 2.0f; }

//�ÓI���W�X�g��.�������������Ɉ���
std::vector<CComPlayer*>& CComPlayer::Instances() {
    static std::vector<CComPlayer*> registry;
    return registry;
}

CComPlayer::CComPlayer()
    : MoveSpeed(0.10f)     // ���₷�������l
    , TurnStep(0.08f)
    , AimTurnStep(0.12f)
    , KeepDistance(9.0f)   // 0�Ȃ�x�^�l��
    , CannonHeight(0.3f)
    , m_Target(nullptr)
    , m_AvoidRadius ( 3.0f )
    , m_AvoidWeight ( 0.8f )
    , m_Registered ( false )
{
}

//����COM���g���폜���鏈��
CComPlayer::~CComPlayer()
{
    if (m_Registered) {
        auto& comList = Instances();
        //comList�̂Ȃ�����this��T����remove�Ō��ɉ񂷁A���������ꂽ�̂��܂Ƃ߂č폜
        comList.erase(std::remove(comList.begin(), comList.end(), this), comList.end());
        m_Registered = false;
    }
}

void CComPlayer::Initialize(int id)
{
    CPlayer::Initialize(id);
    SanitizeParams();

    //�������܂��o�^����Ă��Ȃ���΁A�S�̃��X�g�ɓo�^����
    if (!m_Registered) {
        Instances().push_back(this);
        m_Registered = true;
    }
}

void CComPlayer::SetTarget(std::shared_ptr<CPlayer> player)
{
    m_Target = player;
}
void CComPlayer::ClearTarget()
{
    m_Target = nullptr;
}

D3DXVECTOR3 CComPlayer::GetPosition() const
{
    if (m_pBody)return m_pBody->GetPosition();
    return CCharacter::GetPosition();
}

D3DXVECTOR3 CComPlayer::GetRotation() const
{
    if (m_pBody) return m_pBody->GetRotation();
    return CCharacter::GetRotation();
}

//�s���l��h��
void CComPlayer::SanitizeParams()
{
    if (MoveSpeed <= 0.0f)      MoveSpeed       = 0.06f;
    if (TurnStep <= 0.0f)       TurnStep        = 0.08f;
    if (AimTurnStep <= 0.0f)    AimTurnStep     = 0.12f;
    if (CannonHeight == 0.0f)   CannonHeight    = 0.3f;
    if (KeepDistance < 0.0f)    KeepDistance    = 0.0f;
    if (m_AvoidRadius < 0.0f)   m_AvoidRadius   = 0.0f;
    if (m_AvoidWeight < 0.0f)   m_AvoidWeight = 0.0f;
}

// [-��,��]�ɐ��K��
float CComPlayer::Wrap(float a)
{
    while (a > PI())     a -= TWO_PI();
    while (a < -PI())     a += TWO_PI();
    return a;
}

// �������step�����߂Â���i�ߕs���Ȃ��j
float CComPlayer::Approach(float cur, float goal, float step)
{
    const float d = goal - cur;
    if (d > step)  return cur + step;
    if (d < -step) return cur - step;
    return goal;
}

D3DXVECTOR3 CComPlayer::ForwardFromYaw(float yaw)
{
    return D3DXVECTOR3(std::sinf(yaw), 0.0f, std::cosf(yaw));
}

//COM���m�̕����x�N�g�����v�Z
void CComPlayer::ComputeSeparation(const D3DXVECTOR3& selfPos,
        D3DXVECTOR3& outSep, float& outNearest)const
{
    outSep = D3DXVECTOR3(0, 0, 0);
    outNearest = 1e9f;  //�傫���l.f�����Ă�̂�float�^�ɂ��邩��
       
    if (m_AvoidRadius <= 0.0f)return;   //��𔼌a��0�ȉ��Ȃ牽�����Ȃ�

    const float avoidRadius = m_AvoidRadius;
    const float avoidRadiusSq = avoidRadius * avoidRadius;

    for (CComPlayer* other : Instances()) {
        if (other == this) continue;
        std::shared_ptr<CBody> ob = other ? other->Body() : nullptr;
        if (!ob)continue;   //�ʒu�����Ȃ�����͖�������

        D3DXVECTOR3 offset = selfPos - ob->GetPosition();
        offset.y = 0.0f; //�����͖���

        const float distSq = offset.x * offset.x + offset.z * offset.z;
        if (distSq <= 1e-6f) {
            //�قړ���_�̂��ߏ�������
            outSep.x += 0.1f;
            continue;
        }
        //��ԋ߂�����܂ł̋������X�V
        outNearest = std::min(outNearest, std::sqrtf(distSq));

        if (distSq < avoidRadiusSq) {
            //�߂��قǋ�������
            const float invDistSq = 1.0f / distSq;
            outSep.x += offset.x * invDistSq;
            outSep.z += offset.z * invDistSq;
        }
    }
    //���K���͌Ăяo�����Ńu�����h���ɂ��
}

// �{�̂���Ƀ^�[�Q�b�g�։񓪁{�O�i
void CComPlayer::TickChaseTo(const D3DXVECTOR3& targetPos)
{
    std::shared_ptr<CBody> body = Body();
    if (!body) return;

    // ���ݎp��
    D3DXVECTOR3 pos = body->GetPosition();
    float yaw = body->GetRotation().y;

    // �����ʂ̍���
    D3DXVECTOR3 to = targetPos - pos; to.y = 0.0f;
    const float d2 = to.x * to.x + to.z * to.z;

    // �ڕW���ʂ֍ŒZ���ŉ�
    if (d2 > 1e-6f) {
        const float desiredYaw = std::atan2f(to.x, to.z);               // +Z�O ������W
        yaw = Approach(yaw, yaw + Wrap(desiredYaw - yaw), TurnStep);
    }

    D3DXVECTOR3 chaseDir(0, 0, 0);
    if (d2 > 1e-6f) {
        const float inv = 1.0f / std::sqrtf(d2);
        chaseDir.x = to.x * inv;    //���K��
        chaseDir.z = to.z * inv;
    }

    //�����x�N�g��
    D3DXVECTOR3 sep(0, 0, 0);
    float nearest = 1e9f;
    ComputeSeparation(pos, sep, nearest);

    //�u�����h
    D3DXVECTOR3 desire = chaseDir;  //�ڕW�D��
    if (m_AvoidWeight > 0.0f && (sep.x != 0.0f || sep.z != 0.0f)) {
        //sep�𐳋K�����ďd�ݕt��
        const float sepLen = std::sqrt(sep.x * sep.x + sep.z * sep.z);
        if (sepLen > 1e-6f) {
            sep.x /= sepLen; sep.z /= sepLen;
            desire.x += sep.x * m_AvoidWeight;
            desire.z += sep.z * m_AvoidWeight;
        }
    }

    //�����������L���Ȃ炻�̕��ʂɂ���
    float desiredYaw = yaw;
    const float desLen2 = desire.x * desire.x + desire.z * desire.z;
    if (desLen2 > 1e-8f) {
        desiredYaw = std::atan2f(desire.x, desire.z);
        yaw = Approach(yaw, yaw + Wrap(desiredYaw - yaw), TurnStep);
    }
 
    //�O�i�ʂ̌���
    float step = MoveSpeed;
    if (d2 > 0.0f) {
        const float dist = std::sqrtf(d2);
        if (KeepDistance > 0.0f) {
            const float remain = dist - KeepDistance;
            if (remain <= 0.0f) {
                step = 0.0f;    //����ȏ�͋l�߂Ȃ�
            }
            else if (step > remain) {
                step = remain;
            }
            else
            {
                if (step > dist)step = dist;
            }
        }
    }

    //COM���߂�����Ƃ��͌���.���S��~������
    if (nearest < 1e9f && m_AvoidRadius > 0.0f) {
        float scale = nearest / m_AvoidRadius;
        if (scale < 0.0f) scale = 0.0f;
        if (scale > 1.0f) scale = 1.0f;
        step *= scale;
    }

    // �O�i�i���[�ɉ����� +Z ��Łj
    if (step > 0.0f) {
        const D3DXVECTOR3 fwd = ForwardFromYaw(yaw);
        pos += fwd * step;
    }

    // ���f
    body->SetRotation(D3DXVECTOR3(0.0f, yaw, 0.0f));
    body->SetPosition(pos);
    body->CCharacter::Update();
}

// �C��������Ώ�Ƀ^�[�Q�b�g������
void CComPlayer::TickAimTo(const D3DXVECTOR3& targetPos)
{
    std::shared_ptr<CCannon> cannon = Cannon();
    const std::shared_ptr<CBody> body = Body();
    if (!cannon) return;

    // �C���̊�ʒu
    D3DXVECTOR3 base = body ? body->GetPosition() : cannon->GetPosition();
    base.y += CannonHeight;

    // �ڕW����
    const D3DXVECTOR3 to = targetPos - base;
    const float desiredYaw = std::atan2f(to.x, to.z);

    float cyaw = cannon->GetRotation().y;
    cyaw = Approach(cyaw, cyaw + Wrap(desiredYaw - cyaw), AimTurnStep);

    cannon->SetPosition(base);
    cannon->SetRotation(D3DXVECTOR3(0.0f, cyaw, 0.0f));
    cannon->CCharacter::Update();
}

void CComPlayer::Update()
{
    SanitizeParams();

    // �^�[�Q�b�g�s�݂ł������ڂ͍X�V
    std::shared_ptr<CBody> body = Body();
    if (!body) { if (auto c = Cannon()) c->CCharacter::Update(); return; }

    // �ǔ��Ώۂ��Ȃ���Ή񓪂��ړ��������A���̂܂܍X�V
    if (!m_Target) {
        body->CCharacter::Update();
        if (auto c = Cannon()) c->CCharacter::Update();
        return;
    }

    // ���ȃ^�[�Q�b�g�͖���
    if (m_Target.get() == this) {
        body->CCharacter::Update();
        if (auto c = Cannon()) c->CCharacter::Update();
        return;
    }


    const D3DXVECTOR3 tp = m_Target->GetPosition();
    TickChaseTo(tp);
    TickAimTo(tp);
}
