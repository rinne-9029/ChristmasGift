#include"Debug/DebugPrint.h"
#include"Debug/DebugProfiler.h"

TaskManager* TaskManager::ms_instance = nullptr;
std::list<Task*> TaskManager::m_taskList;

TaskManager::~TaskManager()
{
	//Task�̍폜����
	TaskList::iterator it = m_taskList.begin();
	while (it != m_taskList.end()) {
		//Task�̏�Ԃ��擾
		Task* deleteTask = *it;

		//���̃^�X�N�֐i�s���Ă���
		it++;

		//�폜�t���O�������Ă�����A�^�X�N���폜
		//�i���X�g�����Remove������Task�̃f�X�g���N�^�ŌĂ΂��j
		delete deleteTask;
	}
	m_taskList.clear();
}

// TaskManager�̃C���X�^���X���擾
TaskManager* TaskManager::Instance()
{
	if (ms_instance == nullptr)
	{
		ms_instance = new TaskManager();
	}
	return ms_instance;
}

// TaskManager�̃C���X�^���X��j��
void TaskManager::ClearInstance()
{
	if (ms_instance != nullptr)
	{
		delete ms_instance;
		ms_instance = nullptr;
	}
}

// ���X�g�Ƀ^�X�N��ǉ�
void TaskManager::AddTask(Task* task)
{
	TaskList::iterator it = m_taskList.begin();
	while (it != m_taskList.end())
	{
		//�ǉ�����^�X�N���������̃^�X�N���
		//������������Ȃ�΁A���̈ʒu�ɒǉ�
		if (task->GetTag() < (*it)->GetTag())
		{
			m_taskList.insert(it, task);
			return;
		}

		//������������Ȃ�΁A���̃^�X�N������
		it++;
	}

	//�ǉ�����^�X�N���
	//������������̃^�X�N��������Ȃ��ꍇ��
	//���X�g�̍Ō���ɒǉ�
	m_taskList.push_back(task);
}

// ���X�g����^�X�N����菜��
void TaskManager::RemoveTask(Task* task)
{
	m_taskList.remove(task);
}

//�S�Ẵ^�X�N���폜����
void TaskManager::KillALL() {
	//�S�Ă̍폜�t���O��ON�ɂ���
	for (auto& t : m_taskList) {
		if (!t->m_remove) return;
		t->Kill();
	}
}

//�X�V����
void TaskManager::Update()
{
	//Task�̍폜����
	TaskList::iterator it = m_taskList.begin();
	while (it != m_taskList.end())
	{
		//Task�̏�Ԃ��擾
		Task* deleteTask = *it;
		bool isDelete = deleteTask->IsKill();

		//���̃^�X�N�֐i�s���Ă���
		it++;

		//�폜�t���O�������Ă�����A�^�X�N���폜
		//�i���X�g�����Remove������Task�̃f�X�g���N�^�ŌĂ΂��j
		if (isDelete)
		{
			delete deleteTask;
		}
	}

	//�STask��Update�֐����Ăяo��
	for (Task* task : m_taskList)
	{
		task->Update();
	}
}

//3D�`�揈��
void TaskManager::Render()
{
	//�STask��Render�֐����Ăяo��
	for (Task* task : m_taskList)
	{
		task->Render();
	}
}

//2D�`�揈��
void TaskManager::Draw()
{
	//�STask��Draw�֐����Ăяo��
	for (Task* task : m_taskList)
	{
		task->Draw();
	}
}

Task* TaskManager::FindObject(ETaskTag tag) {

	for (auto& b : m_taskList) {
		if (b->GetTag() == tag && !b->m_isKill) return b;
	}
	return nullptr;
}

std::vector<Task*> TaskManager::FindObjects(const ETaskTag tag)
{
	auto& list = m_taskList;
	std::vector<Task*> ret;
	for (auto& b : list) {
		if (b->GetTag() == tag)ret.push_back(b);
	}
	return ret;
}

//�^�X�N�̃R���W��������
void TaskManager::Collision() {
	auto itr = m_taskList.begin();
	//�����܂ŌJ��Ԃ�
	while (itr != m_taskList.end()) {
		if (!(*itr)->m_isKill) {
			auto ct = itr;
			ct++;
			while (ct != m_taskList.end()) {
				if (!(*ct)->m_isKill) {
					(*itr)->Collision(*ct);
					(*ct)->Collision(*itr);
				}
				//���̃I�u�W�F�N�g
				ct++;
			}
		}
		//���̃I�u�W�F�N�g
		itr++;
	}
}

