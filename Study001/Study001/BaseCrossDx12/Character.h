/*!
@file Character.h
@brief キャラクタークラス
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class WallObject : public GameObject {
		float m_posSpan;
	public:
		WallObject(BaseScene* pBaseScene) :GameObject(pBaseScene), m_posSpan(1.0f) {}
		virtual ~WallObject() {}
		virtual void OnInit()override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;
		virtual ComPtr<ID3D12PipelineState> OnGetPipelineState() override;
		virtual shared_ptr<BaseMesh> OnGetMesh()override;
		virtual shared_ptr<BaseTexture> OnGetTexture()override;

	};

	class SkyObject : public GameObject {
	public:
		SkyObject(BaseScene* pBaseScene) :GameObject(pBaseScene) {}
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
