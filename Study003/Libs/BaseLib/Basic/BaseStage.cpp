/*!
@file Stage.cpp
@brief �e�X�e�[�W�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�e�X�e�[�W
	//--------------------------------------------------------------------------------------
	void BaseStage::PushBackGameObject(const shared_ptr<GameObject>& Ptr) {
		//���̃X�e�[�W�̓N���G�C�g��ł���
		if (IsCreated()) {
			m_waitAddObjectVec.push_back(Ptr);
		}
		else {
			//�N���G�C�g�O
			m_gameObjectVec.push_back(Ptr);
		}
		Ptr->TransformInit();
	}

	//�폜�I�u�W�F�N�g�̐ݒ�
	void BaseStage::RemoveBackGameObject(const shared_ptr<GameObject>& Ptr) {
		m_waitRemoveObjectVec.push_back(Ptr);
	}

	void BaseStage::RemoveTargetGameObject(const shared_ptr<GameObject>& targetobj) {
		auto it = m_gameObjectVec.begin();
		while (it != m_gameObjectVec.end()) {
			if (*it == targetobj) {
				//�폜����邱�Ƃ��I�u�W�F�N�g�ɓ`����
				targetobj->ComponentDestroy();
				targetobj->OnDestroy();
				m_gameObjectVec.erase(it);
				return;
			}
			it++;
		}
	}


	void BaseStage::SetWaitToObjectVec() {
		if (!m_waitRemoveObjectVec.empty()) {
			for (auto Ptr : m_waitRemoveObjectVec) {
				RemoveTargetGameObject(Ptr);
			}
		}
		m_waitRemoveObjectVec.clear();
		if (!m_waitAddObjectVec.empty()) {
			for (auto Ptr : m_waitAddObjectVec) {
				m_gameObjectVec.push_back(Ptr);
			}
		}
		m_waitAddObjectVec.clear();
	}



	void BaseStage::OnInitFrame(FrameResource* pFrameResource) {
		for (auto& v : m_gameObjectVec) {
			v->OnInitFrame(pFrameResource);
		}
	}
	void BaseStage::WriteConstantBuffers(FrameResource* pFrameResource) {
		for (auto& v : m_gameObjectVec) {
			v->WriteConstantBuffers(pFrameResource);
		}
	}

	void BaseStage::UpdateGameObjects() {
		SetWaitToObjectVec();
		for (auto& v : m_gameObjectVec) {
			if (v->IsUpdateActive()) {
				auto v2 = v->GetComponent<Transform>();
				v2->SetToBefore();
			}
		}
		//�����I�u�W�F�N�g�̃t�H�[�X�̏�����
//		m_basePhysics.InitForce();
		for (auto& v : m_gameObjectVec) {
			if (v->IsUpdateActive()) {
				v->OnUpdate();
			}
		}
		//m_basePhysics.Update(false);
		for (auto& v : m_gameObjectVec) {
			if (v->IsUpdateActive()) {
				v->ComponentUpdate();
			}
		}
	}

	void BaseStage::OnRender() {
		for (auto& v : m_gameObjectVec) {
			if (v->IsRenderActive()) {
				v->OnRender();
			}
		}
	}


	void BaseStage::OnDestroy() {
		for (auto& v : m_gameObjectVec) {
			v->OnDestroy();
		}
	}


}
// end basecross