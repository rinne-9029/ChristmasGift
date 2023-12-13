#pragma once
#include<list>

class TaskManager
{
private:
	//TaskManager�̃C���X�^���X
	static TaskManager* ms_instance;

	//Task�̃��X�g
	using TaskList = std::list<Task*>;
	//��������Ă���Task�̃��X�g
	static TaskList m_taskList;

public:
	~TaskManager();
	//TaskManager�̃C���X�^���X���擾
	static TaskManager* Instance();

	//TaskManager�̃C���X�^���X��j��
	static void ClearInstance();

	//���X�g�Ƀ^�X�N��ǉ�
	void AddTask(Task* task);

	//���X�g����^�X�N����菜��
	void RemoveTask(Task* task);

	//���X�g����S�Ẵ^�X�N����菜��
	static void KillALL();

	//�X�V����
	void Update();

	//3D�`�揈��
	void Render();

	//2D�`�揈��
	void Draw();

	static Task* FindObject(ETaskTag tag);

	static std::vector<Task*> FindObjects(const ETaskTag tag);

	static void Collision();

	
};