/*!
@file GameStage.h
@brief �Q�[���X�e�[�W�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/
#pragma once
#include "stdafx.h"

namespace basecross {

	class GameStage : public BaseStage {
		//�J����
		shared_ptr<Camera> m_camera;
		//���C�g
		shared_ptr<LightSet> m_lightSet;
	public:
		GameStage() :BaseStage() {}
		virtual ~GameStage() {}
		virtual shared_ptr<Camera> GetActiveCamera() const override {
			return m_camera;
		}
		virtual shared_ptr<LightSet> GetActiveLightSet() const override {
			return m_lightSet;
		}
		virtual void OnInit()override;
		virtual void OnKeyDown(UINT8 key)override;
		virtual void OnKeyUp(UINT8 key) override;

	};

}
//end basedx12
