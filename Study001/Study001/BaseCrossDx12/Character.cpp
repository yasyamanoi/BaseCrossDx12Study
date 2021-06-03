/*!
@file Character.cpp
@brief キャラクタークラス
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void WallObject::OnInit() {
		m_transform = {};
		m_transform.m_scale = Vec3(1.0f);
		m_transform.m_position = Vec3(0.0f);
	}

	ComPtr<ID3D12PipelineState> WallObject::OnGetPipelineState() {
		return m_pBaseScene->GetPipelineState(L"BcPNTStaticPL");
	}

	shared_ptr<BaseMesh> WallObject::OnGetMesh() {
		return m_pBaseScene->GetMesh(L"DEFAULT_CUBE");
	}

	shared_ptr<BaseTexture> WallObject::OnGetTexture() {
		return m_pBaseScene->GetTexture(L"WALL_TEX");
	}

	void WallObject::OnUpdate() {
		float elapsedTime = (float)App::GetElapsedTime();
		Quat qtspan(Vec3(0, 1, 1), -elapsedTime);
		m_transform.m_quaternion *= qtspan;
		m_transform.m_quaternion.normalize();
		m_transform.m_position.x += m_posSpan * elapsedTime;
		if (abs(m_transform.m_position.x) >= 5.0f) {
			m_posSpan *= -1.0f;
		}
	}

	void WallObject::OnDestroy() {

	}


	void SkyObject::OnInit() {
		m_transform = {};
		m_transform.m_scale = Vec3(5.0f, 1.0f, 5.0f);
		m_transform.m_position = Vec3(0, -0.5f, 0.0);
	}

	ComPtr<ID3D12PipelineState> SkyObject::OnGetPipelineState() {
		return m_pBaseScene->GetPipelineState(L"BcPNTStaticPL");
	}

	shared_ptr<BaseMesh> SkyObject::OnGetMesh() {
		return m_pBaseScene->GetMesh(L"DEFAULT_CUBE");
	}
	shared_ptr<BaseTexture> SkyObject::OnGetTexture() {
		return m_pBaseScene->GetTexture(L"SKY_TEX");
	}


	void SkyObject::OnUpdate() {
		//何もしない
	}

	void SkyObject::OnDestroy() {

	}


}
// end basecross
