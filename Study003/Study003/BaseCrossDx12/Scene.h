/*!
@file Scene.h
@brief �V�[���N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	// �V�[��
	//--------------------------------------------------------------------------------------
	class Scene :public BaseScene {
	public:
		Scene() : BaseScene() {}
		virtual ~Scene() {}
		virtual void OnInit() override;
	};

}
//end basecross


