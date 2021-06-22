/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void GameStage::OnInit() {
		auto pBaseScene = App::GetBaseScene();


		//�J�����ƃ��C�g�̐ݒ�
		m_camera = Camera::CreateCamera<Camera>(Vec3(0, 5.0f, -10.0f), Vec3(0, 0, 0));
		m_lightSet = LightSet::CreateDefaultLights();

		//�e�N�X�`��
		auto texFile = App::GetRelativeAssetsPath() + L"wall.jpg";
		auto texture = pBaseScene->CreateTextureFlomFile(texFile);
		pBaseScene->AddTexture(L"WALL_TEX", texture);
		texFile = App::GetRelativeAssetsPath() + L"sky.jpg";
		texture = pBaseScene->CreateTextureFlomFile(texFile);
		pBaseScene->AddTexture(L"SKY_TEX", texture);

		//�z�u����I�u�W�F�N�g�̏�����
		AddGameObject<WallObject>();
		AddGameObject<SkyObject>();


	}


	void GameStage::OnKeyDown(UINT8 key) {
	}
	void GameStage::OnKeyUp(UINT8 key) {

	}


}
//end basecross
