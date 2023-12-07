#include"Title/Title.h"			//�^�C�g��
#include"Camera/Camera.h"		//�J����
#include"Chara/Player/Player.h"	//�v���C���[
#include"Chara/Enemy/Enemy.h"	//�G
#include"Field/Field.h"			//�X�e�[�W
#include"Field/Closet.h"		//�N���[�[�b�g
#include"Item/Item.h"			//�A�C�e��
#include"Filta/Filta.h"			//�t�B���^�[
#include"Chara/Enemy/EnemyManager.h"
#include"Task/TaskManager.h"	

#include"Debug/DebugPrint.h"
#include"Debug/DebugProfiler.h"
#include"Navigation/NavManager.h"

//--------------------------------------------
//�O���[�o���ϐ��̈�
//-------------------------------------------

//�i�r�m�[�h�`�揈���t���O:�f�o�b�O�p
bool g_isRenderDebug = false;
int count = 0;
int i = 0;
CImage g_Loading;
CImage g_LoadingText;

void MainLoop(void) {
	//--------------------------------------------------------------
	//�Q�[�����̓����͂����ɏ���
	//�Q�[�����͂��̊֐�_��1�b�Ԃ�60��Ăяo���Ă���
	//--------------------------------------------------------------

	//�i�r�m�[�h�`��؂�ւ�:�f�o�b�O�p
	if (PUSH(CInput::eButton11))		//Q�{�^��
	{
		g_isRenderDebug = !g_isRenderDebug;
	}

	//�S�^�X�N�̍X�V
	DebugProfiler::StartTimer("Update");	//�^�X�N�X�V�����v���X�^�[�g
	TaskManager::Instance()->Update();
	DebugProfiler::EndTimer("Update");		//�^�X�N�X�V�����v���I��

	//�S�^�X�N�̕`��
	DebugProfiler::StartTimer("Render");	//�^�X�N�`�揈���v���X�^�[�g
	TaskManager::Instance()->Render();	
	DebugProfiler::EndTimer("Render");		//�^�X�N�`�揈���v���I��

	//�S�^�X�N�̔��菈��
	DebugProfiler::StartTimer("Collision");	//�^�X�N���菈���v���X�^�[�g
	TaskManager::Instance()->Collision();
	DebugProfiler::EndTimer("Collision");	//�^�X�N���菈���v���I��

	//���[�h�I���`�F�b�N
	if (CLoadThread::GetInstance()->CheckEnd())
	{
		//���[�h�O�͉������Ȃ�
	}
	//���[�h���̏���
	else
	{
		count++;
		if (count >= 5)
		{
			i++;
			count = 0;
			if (i >= 8) i = 0;
		}
		g_Loading.SetSize(128, 128);
		g_Loading.SetPos(1700, 900);
		g_Loading.SetRect(128 * i, 0, 128 * i + 128, 128);
		g_Loading.Draw();
		
		//���[�f�B���O�����\��
		g_LoadingText.SetPos(850, 900);
		g_LoadingText.Draw();

		//���[�h��
		//NowLoading�̕������A�j���[�V����
		/*static int t = 0;
		t++;
		char buf[128] = "Now Loading";
		int tt = (t / 30) % 4;
		for (int i = 0; i < tt; i++)
			strcat_s(buf, 128, ".");

		FONT_T()->Draw(960, 540, 1, 0, 0, buf);*/
	}

	float lineWidth = 1.0f;
	//���E�̎���\��
	/*Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(100, 0, 0), CVector4D(1, 0, 0, 1), lineWidth);
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 100, 0), CVector4D(0, 1, 0, 1), lineWidth);
	Utility::DrawLine(CVector3D(0, 0, 0), CVector3D(0, 0, 100), CVector4D(0, 0, 1, 1), lineWidth);

	for (int i = -5; i <= 5; i++) {
		Utility::DrawLine(CVector3D(-5, 0, i * 1.0f), CVector3D(5, 0, i * 1.0f), CVector4D(0.2, 0.2, 0.2, 1), lineWidth);
		Utility::DrawLine(CVector3D(i * 1.0f, 0, -5), CVector3D(i * 1.0f, 0, 5), CVector4D(0.2, 0.2, 0.2, 1), lineWidth);
	}*/

	//�v�����ʂ̕`��
	//DebugProfiler::Print();

}
void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//�u�����h�̗L����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//�Œ�V�F�[�_�[�p
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	CFPS::SetFPS(60);
	//�t���[�����䏉����
	CFPS::Init();
	//�{�^���̐ݒ�
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'X');
	CInput::SetButton(0, CInput::eButton3, 'C');
	CInput::SetButton(0, CInput::eButton4, 'V');
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton6, VK_SHIFT);
	CInput::SetButton(0, CInput::eButton7, VK_CONTROL);
	CInput::SetButton(0, CInput::eButton8, 'F');
	CInput::SetButton(0, CInput::eButton9, 'E');
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eButton11, 'Q');
	CInput::SetButton(0, CInput::eButton12, 'K');	//�m�[�h�z�u�m�F�F�f�o�b�O�p
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);

	//�}�E�X��\��
	//CInput::ShowCursor(false);
	//CInput::SetMouseInside(true);
	CInput::Update();
	CInput::Update();


	//���C�g�ݒ�
	CLight::SetType(0, CLight::eLight_Direction);
	CLight::SetPos(0, CVector3D(0, 200, 200));
	CLight::SetDir(0, CVector3D(-1, -2, 1).GetNormalize());
	CLight::SetColor(0, CVector3D(0.2f, 0.2f, 0.2f), CVector3D(0.8f, 0.8f, 0.8f));

	CLight::SetFogParam(CVector4D(1, 1, 1, 1), 700, 800);

	//�J����������
	CCamera::GetCamera()->LookAt(CVector3D(0, 5, 0),
		CVector3D(0, 0, 0),
		CVector3D(0.0, 1.0, 0.0));

	SetCurrentDirectory("data");


	CShader::GetInstance("StaticMesh");
	CShader::GetInstance("SkinMesh");
	CSound::GetInstance();

	SetCurrentDirectory("data");


	//-----------------------------------------------------
	//�������̖��߂�����
	//�Q�[���N�����Ɉ�x�����Ă΂��
	//-----------------------------------------------------
	
	ADD_RESOURCE("NowLoading", CImage::CreateImage("UI/NowLoading.png"));
	ADD_RESOURCE("NowLoading_Text", CImage::CreateImage("UI/NowLoading_Text.png"));
	g_Loading = COPY_RESOURCE("NowLoading", CImage);
	g_LoadingText = COPY_RESOURCE("NowLoading_Text", CImage);

	CLoadThread::GetInstance()->LoadStart([]()
		{
			//�v���C���[���f���̓ǂݍ���
			ADD_RESOURCE("Player", CModel::CreateModel("Charactor/Santa/Santa.a3m"));

			//�G���f���i�Ƒ��j�̓ǂݍ���
			ADD_RESOURCE("Father", CModel::CreateModel("Charactor/Enemy/father.a3m"));

			//�^���X���f���ǂݍ���
			ADD_RESOURCE("Item", CModel::CreateModel("object/tansu2.obj"));
			ADD_RESOURCE("Telephone", CModel::CreateModel("object/telephone.obj"));
			
			//�^�C�g���摜�ǂݍ���
			ADD_RESOURCE("StartText", CImage::CreateImage("Title/StartText.png"));
			ADD_RESOURCE("ManualText", CImage::CreateImage("Title/ManualText.png"));
			ADD_RESOURCE("RankingText", CImage::CreateImage("Title/RankingText.png"));

			//�t�B���^�[�摜�ǂݍ���
			ADD_RESOURCE("Filta", CImage::CreateImage("Filta/Filta.png"));
			
			//����X�e�[�W
			ADD_RESOURCE("Map", CModel::CreateModel("Field/Field/Map.obj", 7, 4,7));
			ADD_RESOURCE("MapCol", CModel::CreateModel("Field/Field/MapCol.obj", 7, 4, 7));

			ADD_RESOURCE("WallMap", CModel::CreateModel("Field/Field/WallMap.obj", 7, 4, 7));
			ADD_RESOURCE("WallMapCol", CModel::CreateModel("Field/Field/WallMapCol.obj", 7, 4, 7));
			
			new Filta();
			new Title();
		});

}


void Release()
{
	TaskManager::ClearInstance();
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//��ʉ𑜓x�ϓ�
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//��ʉ𑜓x�Œ�
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->Viewport(0, 0, w, h);
	CCamera::GetCurrent()->Perspective(DtoR(45.0), (float)w / (float)h, 1.0, 10000.0);
	
	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//�t���X�N���[��?�E�C���h�E���[�h�̐؂�ւ�
//Alt+Enter�Ő؂�ւ���
void CheckFullScreen() {
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv) {
	// ���������[�N���o
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(1);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);

	Init();
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();


		CInput::Update();
		//�e�o�b�t�@�[���N���A
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();


		glfwSwapBuffers(GL::window);


		CFPS::Wait();

		char title[32];
		sprintf_s(title, "math fps:%d dt:%.3f", CFPS::GetFPS(), CFPS::GetDeltaTime());
		glfwSetWindowTitle(GL::window, title);

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();




	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}
