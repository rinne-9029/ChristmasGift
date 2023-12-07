#include"CharaBase.h"
#include"Field/Field.h"
#include"Navigation/NavNode.h"
#include"Navigation/NavManager.h"
#include"Debug/DebugPrint.h"
#include"Debug/DebugProfiler.h"

//�R���X�g���N�^
CharaBase::CharaBase(ETaskTag tag,bool remove)
	:ObjectBase(tag,remove)
	, m_isGround(false)
	, m_scale(0.0f, 0.0f, 0.0f)
{
	m_remove = true;
}

//�f�X�g���N�^
CharaBase::~CharaBase()
{
	NavManager::Instance()->RemoveNode(m_navNode);
}

//�Փ˔���
void CharaBase::Collision(Task* t)
{
	switch (t->GetTag())
	{
	case ETaskTag::eField:
		if (Field* f = dynamic_cast<Field*>(t))
		{
			//�����߂���
			CVector3D v(0, 0, 0);
			//�J�v�Z���ƃ��f���̏Փ�
			auto tri = f->GetColModel()->CollisionCupsel(m_lineS, m_lineE, m_rad);
			//�ڐG�����ʂ̐��J��Ԃ�
			for (auto& t : tri)
			{
				if (t.m_normal.y < -0.5f)
				{
					//�ʂ����������V��ɓ�������	
					//�㏸���x��0�ɖ߂�
					if (m_vec.y > 0)
						m_vec.y = 0;
				}
				else if (t.m_normal.y > 0.5f)
				{
					//�ʂ���������n�ʂɓ�������
					//�d�͗������x��0�ɖ߂�
					if (m_vec.y < 0) {
						m_vec.y = 0;
						m_isGround = true;
					}
					
				}
				float max_y = max(t.m_vertex[0].y, max(t.m_vertex[1].y, t.m_vertex[2].y));
				//�ڐG�����ʂ̕����ցA�߂荞�񂾕������߂�
				CVector3D nv = t.m_normal * (m_rad - t.m_dist);
				//�ł��傫�Ȉړ��ʂ����߂�
				v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
				v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
				v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
			}
			//�����߂�
			m_pos += v;
			m_lineS += v;
			m_lineE += v;
		}
		break;
	}
}

NavNode* CharaBase::GetNavNode() const
{
	return m_navNode;
}

void CharaBase::Update()
{

	if (m_navNode != nullptr)
	{
		m_navNode->SetPos(m_pos + CVector3D(0.0f, 1.0f, 0.0f));
	}

	m_vec.y -= GRAVITY;
	m_pos.y += m_vec.y;
}