#pragma once

//�^�C�g���p�̐�Ǘ��N���X

class Snow : public Task {
private:
	CImage m_snow;			//��
	CVector2D m_snowPos;	//��̍��W
	float m_snowAng;		//��̉�]�l
public:
	//�R���X�g���N�^
	Snow();
	//�X�V����
	void Update();
	//2D�`�揈��
	void Draw();
};