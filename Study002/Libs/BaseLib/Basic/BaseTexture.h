/*!
@file BaseTexture.h
@brief �e�N�X�`���N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�e�N�X�`���N���X
	//--------------------------------------------------------------------------------------
	class BaseTexture {
		ComPtr<ID3D12Resource> m_texture;
		ComPtr<ID3D12Resource> m_textureUploadHeap;
		DirectX::ScratchImage m_image;
		std::vector<D3D12_SUBRESOURCE_DATA> m_subresources;
		CD3DX12_CPU_DESCRIPTOR_HANDLE m_maphandle;
		UINT m_srvIndex;
		BaseTexture() {}
	public:
		~BaseTexture() {}
		ComPtr<ID3D12Resource> GetTexture() const {
			return m_texture;
		}
		ComPtr<ID3D12Resource> GetTextureUploadHeap() const {
			return m_textureUploadHeap;
		}
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetMapHandle() const {
			return m_maphandle;
		}
		void SetSrvIndex(UINT srvIndex) {
			m_srvIndex = srvIndex;
		}
		UINT GetSrvIndex() const {
			return m_srvIndex;
		}
		//�T�u���\�[�X�̃A�b�v�f�[�g�ƃV�F�[�_���\�[�X�r���[�̍쐬
		void UpdateSRAndCreateSRV(const ComPtr<ID3D12GraphicsCommandList>& commandList);
		//�t�@�C������e�X�N�`���쐬(SRV���쐬����)
		static shared_ptr<BaseTexture>
			CreateBaseTextureFromFile(const ComPtr<ID3D12GraphicsCommandList>& commandList,const wstring& fileName, const CD3DX12_CPU_DESCRIPTOR_HANDLE& mapHandle);

	};



}
//end basecross
