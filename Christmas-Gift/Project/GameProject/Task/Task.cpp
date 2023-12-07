
//�R���X�g���N�^
Task::Task(ETaskTag tag,bool Remove)
	: m_tag(tag)
	, m_isKill(false)
	, m_remove(Remove)
{
	TaskManager::Instance()->AddTask(this);
}

//�f�X�g���N�^
Task::~Task()
{
	TaskManager::Instance()->RemoveTask(this);
}

//�^�X�N�̎�ނ��擾
ETaskTag Task::GetTag() const
{
	return m_tag;
}

void Task::Collision(Task* t)
{
}

//�폜�t���O�擾
bool Task::IsKill() const
{
	return m_isKill;
}

//�^�X�N���폜
void Task::Kill()
{
	m_isKill = true;
}

//�X�V����
void Task::Update()
{

}

//���f���`�揈��
void Task::Render()
{

}

