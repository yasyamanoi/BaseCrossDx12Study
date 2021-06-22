/*!
@file RenderComponents.h
@brief �`��R���|�[�l���g
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�`��R���|�[�l���g�e
	//--------------------------------------------------------------------------------------
	class RenderComponent : public Component {
	protected:
		explicit RenderComponent(const shared_ptr<GameObject>& gameObjectPtr);
		virtual ~RenderComponent() {}
		ComPtr<ID3D12PipelineState> m_pipelineState;
		shared_ptr<BaseMesh> m_baseMesh;
		shared_ptr<BaseTexture> m_baseTexture;
		void SetPipelineState(const ComPtr<ID3D12PipelineState>& pipelineState) {
			m_pipelineState = pipelineState;
		}
		virtual void PopulateCommandList(FrameResource* pFrameResource) = 0;
	public:
		void SetBaseMesh(const shared_ptr<BaseMesh>& baseMesh) {
			m_baseMesh = baseMesh;
		}
		void SetBaseTexture(const shared_ptr<BaseTexture>& baseTexture) {
			m_baseTexture = baseTexture;
		}
	};




	//--------------------------------------------------------------------------------------
	///	BcPNTStatic�`��R���|�[�l���g
	//--------------------------------------------------------------------------------------
	class BcPNTStatic : public RenderComponent {
	protected:
		virtual void PopulateCommandList(FrameResource* pFrameResource)override;
	public:
		explicit BcPNTStatic(const shared_ptr<GameObject>& gameObjectPtr);
		virtual ~BcPNTStatic() {}
		//����
		virtual void OnInit()override;
		virtual void OnUpdate()override {}
		virtual void OnRender()override;
		virtual void OnDestroy()override {}


	};


}
//end basecross
