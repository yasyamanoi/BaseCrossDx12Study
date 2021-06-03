/*!
@file Scene.h
@brief シーンクラス
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// シーン
	//--------------------------------------------------------------------------------------
	class Scene :public BaseScene {
		//カメラ
		shared_ptr<Camera> m_camera;
		//ライト
		shared_ptr<LightSet> m_lightSet;
	public:
		Scene() : BaseScene() {}
		virtual ~Scene() {}
		shared_ptr<Camera> GetActiveCamera() const override{
			return m_camera;
		}
		shared_ptr<LightSet> GetActiveLightSet() const override{
			return m_lightSet;
		}
		virtual void OnInit() override;
		virtual void OnKeyDown(UINT8 key)override;
		virtual void OnKeyUp(UINT8 key)override;

	};

}
//end basecross


