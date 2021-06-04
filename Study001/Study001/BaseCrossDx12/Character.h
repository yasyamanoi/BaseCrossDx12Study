/*!
@file Character.h
@brief �L�����N�^�[�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class WallObject : public GemeObject {
		float m_posSpan;
	public:
		WallObject(BaseScene* pBaseScene) :GemeObject(pBaseScene), m_posSpan(1.0f) {}
		virtual ~WallObject() {}
		virtual void OnInit()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
		virtual ComPtr<ID3D12PipelineState> OnGetPipelineState() override;
		virtual shared_ptr<BaseMesh> OnGetMesh()override;
		virtual shared_ptr<BaseTexture> OnGetTexture()override;

	};

	class SkyObject : public GemeObject {
	public:
		SkyObject(BaseScene* pBaseScene) :GemeObject(pBaseScene) {}
		virtual ~SkyObject() {}
		virtual void OnInit()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
		virtual ComPtr<ID3D12PipelineState> OnGetPipelineState() override;
		virtual shared_ptr<BaseMesh> OnGetMesh()override;
		virtual shared_ptr<BaseTexture> OnGetTexture()override;
	};


}
//end basecross
