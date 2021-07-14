/*!
@file GameObject.h
@brief �Q�[���I�u�W�F�N�g�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	class BaseScene;
	class BaseStage;

	//--------------------------------------------------------------------------------------
	// �z�u�����I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class GameObject : public ObjectInterface {
		bool m_UpdateActive;	//update���邩�ǂ���
		bool m_renderActive;		//Render���邩�ǂ���
		bool m_AlphaActive;		//�������ǂ���

		map<type_index, shared_ptr<Component> > m_compMap;
		list<type_index> m_compOrder;	//�R���|�[�l���g���s����

		template<typename T>
		shared_ptr<T> SearchDynamicComponent()const {
			auto it = m_compMap.begin();
			while (it != m_compMap.end()) {
				auto ptr = dynamic_pointer_cast<T>(it->second);
				if (ptr) {
					return ptr;
				}
				it++;
			}
			return nullptr;
		}

	protected:
		explicit GameObject(const shared_ptr<BaseStage>& stage);
		virtual ~GameObject();
		//�t���[������CBV�֘A�p�����[�^�̃C���f�b�N�X
		size_t m_paramIndex;
		//�X�e�[�W�e�̃|�C���^
		weak_ptr<BaseStage> m_stage;
		//�R���X�^���g�o�b�t�@�̓o�^
		void SetConstants(BasicConstants& constants, const shared_ptr<Transform>& transform);
	public:
		bool IsUpdateActive() const {
			return m_UpdateActive;
		}
		void SetUpdateActive(bool b) {
			m_UpdateActive = b;
		}
		bool IsRenderActive() const {
			return m_renderActive;
		}
		void SetRenderActive(bool b) {
			m_renderActive = b;
		}
		bool IsAlphaActive() const {
			return m_AlphaActive;
		}
		void SetAlphaActive(bool b) {
			m_AlphaActive = b;
		}
		size_t GetParamIndex() const {
			return m_paramIndex;
		}
		shared_ptr<BaseStage> GetBaseStage(bool exceptionActive = true) const;
		template<typename T, typename... Ts>
		shared_ptr<T> AddComponent(Ts&&... params) {
			type_index t_index = type_index(typeid(T));
			auto ptr = SearchDynamicComponent<T>();
			//�w��̌^�̃R���|�[�l���g����������
			if (ptr) {
				auto retPtr = dynamic_pointer_cast<T>(ptr);
				if (retPtr) {
					return retPtr;
				}
				else {
					throw BaseException(
						L"���łɃR���|�[�l���g������܂������A�^�L���X�g�ł��܂���",
						Util::GetWSTypeName<T>(),
						L"GameObject::AddComponent<T>()"
					);
				}
			}
			else {
				//������Ȃ��B�V���ɍ쐬����
				shared_ptr<T> newPtr = ObjectFactory::Create<T>(GetThis<GameObject>(), params...);
				//���̃R���|�[�l���g���܂��Ȃ���ΐV�K�o�^
				m_compOrder.push_back(t_index);
				//map�ɒǉ��������͍X�V
				m_compMap[t_index] = newPtr;
				newPtr->AttachGameObject(GetThis<GameObject>());
				return newPtr;
			}
		}


		template <typename T>
		shared_ptr<T> GetComponent(bool exceptionActive = true)const {
			auto Ptr = SearchDynamicComponent<T>();
			if (Ptr) {
				//�w��̌^�̃R���|�[�l���g����������
				return Ptr;
			}
			else {
				if (exceptionActive) {
					throw BaseException(
						L"�R���|�[�l���g��������܂���",
						Util::GetWSTypeName<T>(),
						L"GameObject::GetComponent<T>()"
					);
				}
			}
			return nullptr;
		}

		template <typename T>
		void RemoveComponent() {
			auto typeIndex = type_index(typeid(T));
			//���ԃ��X�g�����؂��č폜
			auto it = m_compOrder.begin();
			while (it != m_compOrder.end()) {
				if (*it == typeIndex) {
					auto it2 = m_compMap.find(*it);
					if (it2 != m_compMap.end()) {
						//�w��̌^�̃R���|�[�l���g����������
						//map�f�[�^���폜
						m_compMap.erase(it2);
					}
					m_compOrder.erase(it);
					return;
				}
				it++;
			}
		}


		void TransformInit();
		void ComponentUpdate();
		void ComponentRender();
		void ComponentDestroy();

		virtual void OnPreInit() override;
		virtual void OnRender()override;
		virtual void OnInitFrame(FrameResource* pFrameResource);
		virtual void WriteConstantBuffers(FrameResource* pFrameResource);
	};

}
//end basecross
