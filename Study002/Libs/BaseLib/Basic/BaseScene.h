/*!
@file BaseScene.h
@brief �V�[���e�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	DECLARE_DX12SHADER(BcVSPNTStaticPL)
	DECLARE_DX12SHADER(BcPSPNTPL)


	//--------------------------------------------------------------------------------------
	///	�V�[���e�N���X
	//--------------------------------------------------------------------------------------
	class BaseScene {
		map<wstring, ComPtr<ID3D12PipelineState>> m_pipelineMap;
		void CreateDefaultPipelineStates();
		map<wstring, shared_ptr<BaseMesh>> m_meshMap;
		void CreateDefaultMeshes();
		map<wstring, shared_ptr<BaseTexture>> m_textureMap;
		shared_ptr<BaseStage> m_activeStage;
	protected:
		BaseScene() {}
		virtual ~BaseScene() {}
		vector<shared_ptr<GameObject>> m_GameObjectVec;
		shared_ptr<BaseStage> GetActiveStage(bool ExceptionActive = true) const {
			if (!m_activeStage) {
				//�A�N�e�B�u�ȃX�e�[�W�������Ȃ�
				if (ExceptionActive) {
					throw BaseException(
						L"�A�N�e�B�u�ȃX�e�[�W������܂���",
						L"if(!m_activeStage)",
						L"SceneEx::GetActiveStage()"
					);
				}
				else {
					return nullptr;
				}
			}
			return m_activeStage;
		}
		void SetActiveStage(const shared_ptr<BaseStage>& stage) {
			m_activeStage = stage;
		}
		//�A�N�e�B�u�X�e�[�W�̐ݒ�
		template<typename T, typename... Ts>
		shared_ptr<T> ResetActiveStage(Ts&&... params) {
			auto ActStagePtr = GetActiveStage(false);
			if (ActStagePtr) {
				//�j����`����
				ActStagePtr->OnDestroy();
			}
			auto Ptr = ObjectFactory::Create<T>(params...);
			auto StagePtr = dynamic_pointer_cast<BaseStage>(Ptr);
			if (!StagePtr) {
				throw BaseException(
					L"�ȉ���Stage�Ɍ^�L���X�g�ł��܂���B",
					Util::GetWSTypeName<T>(),
					L"SceneEx::ResetActiveStage<T>()"
				);
			}
			SetActiveStage(StagePtr);
			return Ptr;
		}

	public:
		void AddPipelineState(const wstring& key,const ComPtr<ID3D12PipelineState>& pipelineState, bool keyEnabled = false) {
			if (keyEnabled) {
				auto it = m_pipelineMap.find(key);
				if (it != m_pipelineMap.end()) {
					throw BaseException(
						L"�w��̃L�[�̃p�C�v���C�������łɑ��݂��܂�",
						key,
						L"BaseScene::AddPipelineState()"
					);
				}
			}
			m_pipelineMap[key] = pipelineState;
		}
		ComPtr<ID3D12PipelineState> GetPipelineState(const wstring& key) {
			auto it = m_pipelineMap.find(key);
			if (it != m_pipelineMap.end()) {
				return it->second;
			}
			else {
				throw BaseException(
					L"�w��̃L�[�̃p�C�v���C����������܂���",
					key,
					L"BaseScene::GetPipelineState()"
				);
			}
			return nullptr;
		}
		void AddMesh(const wstring& key, const shared_ptr<BaseMesh>& mesh,bool keyEnabled = false) {
			if (keyEnabled) {
				auto it = m_meshMap.find(key);
				if (it != m_meshMap.end()) {
					throw BaseException(
						L"�w��̃L�[�̃��b�V�������łɑ��݂��܂�",
						key,
						L"BaseScene::AddMesh()"
					);
				}
			}
			m_meshMap[key] = mesh;
		}
		shared_ptr<BaseMesh> GetMesh(const wstring& key) {
			auto it = m_meshMap.find(key);
			if (it != m_meshMap.end()) {
				return it->second;
			}
			else {
				throw BaseException(
					L"�w��̃L�[�̃��b�V����������܂���",
					key,
					L"BaseScene::GetMesh()"
				);
			}
			return nullptr;
		}
		void AddTexture(const wstring& key, const shared_ptr<BaseTexture>& texture, bool keyEnabled = false) {
			if (keyEnabled) {
				auto it = m_textureMap.find(key);
				if (it != m_textureMap.end()) {
					throw BaseException(
						L"�w��̃L�[�̃e�N�X�`�������łɑ��݂��܂�",
						key,
						L"BaseScene::AddTexture()"
					);
				}
			}
			m_textureMap[key] = texture;
		}
		shared_ptr<BaseTexture> GetTexture(const wstring& key) {
			auto it = m_textureMap.find(key);
			if (it != m_textureMap.end()) {
				return it->second;
			}
			else {
				throw BaseException(
					L"�w��̃L�[�̃e�N�X�`����������܂���",
					key,
					L"BaseScene::GetTexture()"
				);
			}
			return nullptr;
		}
		shared_ptr<BaseTexture> CreateTextureFlomFile(const wstring& falsename);
		template<typename T, typename... Ts>
		shared_ptr<T> AddGameObject(Ts&&... params) {
			try {
				auto ptr = ObjectFactory::Create<T>(this, params...);
				m_GameObjectVec.push_back(ptr);
				return ptr;
			}
			catch (...) {
				throw;
			}
		}
		vector<shared_ptr<GameObject>>& GetGameObjectVec() {
			return m_GameObjectVec;
		}
		virtual void OnInit();
		virtual void OnInitFrame(FrameResource* pFrameResource);
		virtual void WriteConstantBuffers(FrameResource* pFrameResource);
		virtual void OnUpdate();
		virtual void OnDestroy();
		virtual void OnKeyDown(UINT8 key);
		virtual void OnKeyUp(UINT8 key);

		virtual void PopulateCommandList(FrameResource* pFrameResource);

	};
}
// end basecross
