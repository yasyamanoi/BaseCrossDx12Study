/*!
@file Velocity.h
@brief 速度コンポーネント
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#pragma once

namespace basecross {

	class GameObject;

	//--------------------------------------------------------------------------------------
	///	速度コンポーネント
	//--------------------------------------------------------------------------------------
	class Velocity : public Component {
		Vec3 m_velocity;
		Vec3 m_force;
	public:
		explicit Velocity(const shared_ptr<GameObject>& gameObjectPtr);
		virtual ~Velocity();
		//操作
		void ForceInit();
		void SetForce(const Vec3& v) {
			m_force = v;
		}
		virtual void OnInit()override {}
		virtual void OnUpdate()override;
		virtual void OnRender()override {}
		virtual void OnDestroy()override {}


	};
}
//end basecross

