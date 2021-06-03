/*!
@file Scene.cpp
@brief シーンクラス
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Scene::OnInit() {
		//親クラスの初期化
		BaseScene::OnInit();
		//カメラとライトの設定
		m_camera = Camera::CreateCamera<Camera>(Vec3(0, 5.0f, -10.0f), Vec3(0, 0, 0));
		m_lightSet = LightSet::CreateDefaultLights();
		//テクスチャ
		auto texFile = App::GetRelativeAssetsPath() + L"wall.jpg";
		auto texture = CreateTextureFlomFile(texFile);
		AddTexture(L"WALL_TEX", texture);
		texFile = App::GetRelativeAssetsPath() + L"sky.jpg";
		texture = CreateTextureFlomFile(texFile);
		AddTexture(L"SKY_TEX", texture);

		//配置するオブジェクトの初期化
		AddGameObject<WallObject>();
		AddGameObject<SkyObject>();
	}

	void Scene::OnKeyDown(UINT8 key) {
	}
	void Scene::OnKeyUp(UINT8 key) {

	}



}
// end basecross