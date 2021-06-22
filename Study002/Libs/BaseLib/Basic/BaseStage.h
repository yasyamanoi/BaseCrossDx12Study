/*!
@file Stage.h
@brief �e�X�e�[�W�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	// �e�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class BaseStage : public ObjectInterface {
		void PushBackGameObject(const shared_ptr<GameObject>& ptr);
		void RemoveBackGameObject(const shared_ptr<GameObject>& ptr);
		//�ǉ��E�폜�܂��I�u�W�F�N�g�̒ǉ��ƍ폜
		void RemoveTargetGameObject(const shared_ptr<GameObject>& targetobj);
		void SetWaitToObjectVec();
		vector<shared_ptr<GameObject>> m_waitAddObjectVec;
		vector<shared_ptr<GameObject>> m_waitRemoveObjectVec;
	protected:
		BaseStage() {}
		virtual ~BaseStage() {}
		vector<shared_ptr<GameObject>> m_gameObjectVec;
	public:
		template<typename T, typename... Ts>
		shared_ptr<T> AddGameObject(Ts&&... params) {
			try {
				auto Ptr = ObjectFactory::Create<T>(GetThis<BaseStage>(), params...);
				PushBackGameObject(Ptr);
				return Ptr;
			}
			catch (...) {
				throw;
			}
		}
		vector<shared_ptr<GameObject>>& GetGameObjectVec() {
			return m_gameObjectVec;
		}
		virtual shared_ptr<Camera> GetActiveCamera() const = 0;
		virtual shared_ptr<LightSet> GetActiveLightSet() const = 0;

		virtual void OnInitFrame(FrameResource* pFrameResource);
		virtual void WriteConstantBuffers(FrameResource* pFrameResource);
		virtual void UpdateGameObjects();
		virtual void OnUpdate()override {}
		virtual void OnRender()override;
		virtual void OnDestroy()override;



	};

}
// end basecross
