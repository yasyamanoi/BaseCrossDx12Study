/*!
@file Velocity.cpp
@brief 速度コンポーネント
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#include "stdafx.h"

namespace basecross {


		Velocity::Velocity(const shared_ptr<GameObject>& gameObjectPtr)
			:
			Component(gameObjectPtr),
			m_velocity(0.0f),
			m_force(0.0f)
		{}

		Velocity::~Velocity() {}


		void Velocity::ForceInit() {
	//		m_force = Vec3(0.0f);
		}

		void Velocity::OnUpdate() {
		
			float elapsedTime = App::GetElapsedTime();
			m_velocity += m_force * elapsedTime;

			auto transPtr = GetGameObject()->GetComponent<Transform>();
			auto pos = transPtr->GetPosition();
			pos += m_velocity * elapsedTime;
			transPtr->SetPosition(pos);

		}


}
//end basecross
