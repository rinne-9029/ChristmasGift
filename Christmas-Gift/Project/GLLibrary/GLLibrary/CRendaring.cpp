#include "CRendaring.h"
CRendaring* CRendaring::m_instance = nullptr;
CRendaring::CRendaring(int screen_width, int screen_height,float focus): m_gbuffer(nullptr), m_tmp_buffer(nullptr), m_scene(nullptr),
m_blurtmp(nullptr), m_blur(nullptr), m_blur1(nullptr), m_blur2(nullptr),
m_focus(focus)
{

	GLenum formats[] = {
		GL_RGBA,
		GL_RGBA32F,
		GL_RGBA32F,
		GL_RGBA,
		GL_RGBA,
	};

	GLenum type[] = {
		GL_UNSIGNED_BYTE,
		GL_FLOAT,
		GL_FLOAT,
		GL_UNSIGNED_BYTE,
		GL_UNSIGNED_BYTE,
	};

	//描画先レンダーターゲット(色、法線、座標、シャドウマップ、その他)
	m_gbuffer = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0), 5, formats,type);
	m_ligting_buffer = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0),2);
	//グレア済み
	m_scene = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));


	m_tmp_buffer = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 1));

	//ブラー用
	m_blurtmp = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));
	m_blur = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));
	m_blur1 = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));
	m_blur2 = new CTextureFrame(screen_width, screen_height, CVector4D(0, 0, 0, 0));
}

CRendaring::~CRendaring()
{
	if (m_gbuffer) {delete m_gbuffer; m_gbuffer = nullptr;}
	if (m_scene) { delete m_scene; m_scene = nullptr; }
	if (m_blurtmp) { delete m_blurtmp; m_blurtmp = nullptr; }
	if (m_blur) { delete m_blur; m_blur = nullptr; }
	if (m_blur1) { delete m_blur1; m_blur1 = nullptr; }
	if (m_blur2) { delete m_blur2; m_blur2 = nullptr; }
}

CRendaring* CRendaring::GetInstance()
{
	return m_instance;
}

void CRendaring::ClearInstance()
{
	if (m_instance) delete m_instance;
	m_instance = nullptr;
}

void CRendaring::CreatInstance(int screen_width, int screen_height,float focus)
{

	if (!m_instance) m_instance = new CRendaring(screen_width, screen_height, focus);
}

//ポストエフェクトでよく使用するので関数化
//画面いっぱいに四角形として描画
void CRendaring::DrawFillQuad() {
	CVector3D vertices[] = {
		CVector3D(0,0,0),CVector3D(1,0,0),
		CVector3D(1,1,0),CVector3D(0,1,0)
	};
	glEnableVertexAttribArray(CShader::eVertexLocation);
	glVertexAttribPointer(CShader::eVertexLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(CShader::eVertexLocation);
}

/// <summary>
/// ブラー
/// </summary>
/// <param name="src">元画像</param>
/// <param name="tmp">一時結果用</param>
/// <param name="result">出力結果用</param>
/// <param name="pow">ブラー係数</param>
/// <param name="pix">ブラー範囲</param>
void CRendaring::Blur(CTexture* src, CTextureFrame* tmp, CTextureFrame* result, float pow, float pix) {
	//ブラーの度合
	float weight[10];
	float t = 0.0;
	float d = pow * pow / 100;
	for (int i = 0; i < 10; i++) {
		float r = 1.0 + 2.0 * i;
		float w = exp(-0.5 * (r * r) / d);
		weight[i] = w;
		if (i > 0) { w *= 2.0; }
		t += w;
	}
	for (int i = 0; i < 10; i++) {
		weight[i] /= t;
	}

	//ブラー用シェーダー
	CShader* s = CShader::GetInstance("GaussianBlur");
	s->Enable();

	//一回目（横ブラー）
	tmp->BeginDraw();
	//元画像をセット
	src->MapTexture();
	glUniform1i(glGetUniformLocation(s->GetProgram(), "texture"), 0);
	glUniform1fv(glGetUniformLocation(s->GetProgram(), "weight"), 10, weight);
	glUniform1i(glGetUniformLocation(s->GetProgram(), "horizontal"), 1);
	glUniform2f(glGetUniformLocation(s->GetProgram(), "scale"), 1.0f / src->m_width * pix, 1.0f / src->m_height * pix);
	//画面描画
	DrawFillQuad();
	src->UnmapTexture();
	tmp->EndDraw();

	//二回目（さらに縦ブラー）
	result->BeginDraw();
	tmp->GetTexture()->MapTexture();
	glUniform1i(glGetUniformLocation(s->GetProgram(), "texture"), 0);
	glUniform1fv(glGetUniformLocation(s->GetProgram(), "weight"), 10, weight);
	glUniform1i(glGetUniformLocation(s->GetProgram(), "horizontal"), 0);
	glUniform2f(glGetUniformLocation(s->GetProgram(), "scale"), 1.0f / src->m_width * pix, 1.0f / src->m_height * pix);
	DrawFillQuad();
	s->Disable();
	tmp->GetTexture()->UnmapTexture();
	result->EndDraw();

}

void CRendaring::Render(std::function<void()> render)
{


	//デプステストON
	glEnable(GL_DEPTH_TEST);
	//モデルの描画
	//A.影付き描画
	if (CShadow::GetInstance()) {
		CShadow::GetInstance()->Render(render,m_gbuffer);
	} else {
	//B.影無し描画
		m_gbuffer->BeginDraw();
		render();
		m_gbuffer->EndDraw();
	}
	//デプステストOFF
	glDisable(GL_DEPTH_TEST);
	{
		m_ligting_buffer->BeginDraw();
		//GBufferから描画
		static CShader* s = nullptr;
		if (!s)
			s = new CShader("Lighting");

		s->Enable();
		const char name[][32] = {
			"color_texture",
			"normal_texture",
			"worldpos_texture",
			"shadowmap_texture",
			"extra_texture",

		};
		glUniform3fv(glGetUniformLocation(s->GetProgram(), "lightPos"), CLight::LIGHT_MAX, (float*)CLight::GetPosPointer());
		glUniform3fv(glGetUniformLocation(s->GetProgram(), "lightDir"), CLight::LIGHT_MAX, (float*)CLight::GetDirPointer());
		glUniform3fv(glGetUniformLocation(s->GetProgram(), "lightAmbientColor"), CLight::LIGHT_MAX, (float*)CLight::GetAmbientColorPointer());
		glUniform3fv(glGetUniformLocation(s->GetProgram(), "lightDiffuseColor"), CLight::LIGHT_MAX, (float*)CLight::GetDiffuseColorPointer());
		glUniform1fv(glGetUniformLocation(s->GetProgram(), "lightRange"), CLight::LIGHT_MAX, (float*)CLight::GetRangePointer());
		glUniform1fv(glGetUniformLocation(s->GetProgram(), "lightRadiationAngle"), CLight::LIGHT_MAX, (float*)CLight::GetRadiationAnglePointer());
		glUniform1iv(glGetUniformLocation(s->GetProgram(), "lightType"), CLight::LIGHT_MAX, (int*)CLight::GetTypeColorPointer());
		CVector3D vec = CCamera::GetCurrent()->GetDir();
		glUniform3fv(glGetUniformLocation(s->GetProgram(), "eyeVec"), 1, (float*)&vec);
		CVector3D pos = CCamera::GetCurrent()->GetPos();
		glUniform3fv(glGetUniformLocation(s->GetProgram(), "eyePos"), 1, (float*)&pos);


		for (int i = 0; i < 5; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			m_gbuffer->GetTexture(i)->MapTexture();
			glUniform1i(glGetUniformLocation(s->GetProgram(), name[i]), i);
		}
		//操作スロットを0へ戻す
		glActiveTexture(GL_TEXTURE0);
		//画面描画
		DrawFillQuad();
		//シェーダ無効
		s->Disable();
		m_ligting_buffer->EndDraw();

	}
	CTexture* t = nullptr;
	//輪郭描画
	if(0){
		m_tmp_buffer->BeginDraw();
		CTextureFrame::Draw(0, 0, m_ligting_buffer->GetWidth(), m_ligting_buffer->GetHeight(), m_ligting_buffer->GetTexture());
		//デプステスト無効
		glDisable(GL_DEPTH_TEST);
		//輪郭描画用シェーダ(ここで輪郭を描画している)
		CShader* s = CShader::GetInstance("Edge");
		s->Enable();

		glActiveTexture(GL_TEXTURE0);
		//デプスバッファを描画で使用する
		m_gbuffer->GetDepthTexture()->MapTexture();
		glUniform1i(glGetUniformLocation(s->GetProgram(), "depth"), 0);
		//画面描画
		DrawFillQuad();
		m_gbuffer->GetDepthTexture()->UnmapTexture();
		s->Disable();
		m_tmp_buffer->EndDraw();
		t = m_tmp_buffer->GetTexture();
	} else {
		t = m_ligting_buffer->GetTexture();
	}

	//CTextureFrame::Draw(0, 0, m_gbuffer->GetWidth(), m_gbuffer->GetHeight(), m_gbuffer->GetTexture());
	//return;

	//グロー
	{
		//反射光にブラーをかける
		Blur(m_ligting_buffer->GetTexture(1), m_blurtmp, m_blur, 60.0f, 2.0f);

		m_scene->BeginDraw();
		//通常描画＋グレア
		static CShader* s = nullptr;
		if (!s)
			s = new CShader("GlareMix");
		s->Enable();
		//テクスチャー0のスロットへ通常
		glActiveTexture(GL_TEXTURE0);
		t->MapTexture();
		//テクスチャー1のスロットへグレア
		glActiveTexture(GL_TEXTURE1);
		m_blur->GetTexture()->MapTexture();
		//操作スロットを0へ戻す
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "texture1"), 0);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "texture2"), 1);
		//画面描画
		DrawFillQuad();
		//シェーダ無効
		s->Disable();
		m_scene->EndDraw();
	}

	//被写界深度
	{
		//ブラー弱
		Blur(m_scene->GetTexture(), m_blurtmp, m_blur1, 30.0f);
		//ブラー強
		Blur(m_scene->GetTexture(), m_blurtmp, m_blur2, 60.0f);

		//視界深度用シェーダー
		CShader* s = CShader::GetInstance("DepthOfField");
		s->Enable();
		//テクスチャー0のスロットへ深度バッファ
		glActiveTexture(GL_TEXTURE0);
		m_gbuffer->GetDepthTexture()->MapTexture();
		//テクスチャー1のスロットへ通常レンダリング画像
		glActiveTexture(GL_TEXTURE1);
		m_scene->GetTexture()->MapTexture();
		//テクスチャー2のスロットへブラー弱
		glActiveTexture(GL_TEXTURE2);
		m_blur1->GetTexture()->MapTexture();
		//テクスチャー3のスロットへブラー強
		glActiveTexture(GL_TEXTURE3);
		m_blur2->GetTexture()->MapTexture();
		//操作スロットを0へ戻す
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "depthTexture"), 0);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "sceneTexture"), 1);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "blurTexture1"), 2);
		glUniform1i(glGetUniformLocation(s->GetProgram(), "blurTexture2"), 3);
		glUniform1f(glGetUniformLocation(s->GetProgram(), "offset"), m_focus);
		//画面描画
		DrawFillQuad();
		//シェーダ無効
		s->Disable();
	}
	//デプステストON
	glEnable(GL_DEPTH_TEST);

}
