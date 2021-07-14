/*!
@file Character.cpp
@brief キャラクタークラス
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void WallObject::OnInit() {
		auto transPtr = GetComponent<Transform>();
		transPtr->SetScale(Vec3(1.0f));
		transPtr->SetPosition(Vec3(0.5f));

		auto veloPtr = AddComponent<Velocity>();

		auto renderPtr = AddComponent<BcPNTStatic>();
		renderPtr->SetBaseMesh(App::GetBaseScene()->GetMesh(L"DEFAULT_CUBE"));
		renderPtr->SetBaseTexture(App::GetBaseScene()->GetTexture(L"WALL_TEX"));
	}

	void WallObject::OnKeyDown(UINT8 key) {
		auto veloPtr = GetComponent<Velocity>();
		if (key == VK_RIGHT) {
			veloPtr->SetForce(Vec3(1.0,0,0));
		}
		else if (key == VK_LEFT) {
			veloPtr->SetForce(Vec3(-1.0, 0, 0));
		}

	}

	void WallObject::OnUpdate() {
	}

	void WallObject::OnDestroy() {
	}


	void SkyObject::OnInit() {
		auto transPtr = GetComponent<Transform>();
		transPtr->SetScale(Vec3(20.0f, 1.0f, 20.0f));
		transPtr->SetPosition(Vec3(0, -0.5f, 0.0));

		auto renderPtr = AddComponent<BcPNTStatic>();
		renderPtr->SetBaseMesh(App::GetBaseScene()->GetMesh(L"DEFAULT_CUBE"));
		renderPtr->SetBaseTexture(App::GetBaseScene()->GetTexture(L"SKY_TEX"));


	}

	void SkyObject::OnUpdate() {
		//何もしない
	}

	void SkyObject::OnDestroy() {

	}


}
// end basecross
