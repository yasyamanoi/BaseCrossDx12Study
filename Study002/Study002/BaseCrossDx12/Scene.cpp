/*!
@file Scene.cpp
@brief �V�[���N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Scene::OnInit() {
		//�e�N���X�̏�����
		BaseScene::OnInit();
		ResetActiveStage<GameStage>();
	}




}
// end basecross