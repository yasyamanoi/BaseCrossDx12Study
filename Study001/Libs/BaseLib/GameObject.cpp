/*!
@file GameObject.cpp
@brief ゲームオブジェクトクラス
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#include "stdafx.h"

namespace basecross {

	void GameObject::SetConstants(BasicConstants& constants, const Transform& transform) {
		//初期化
		constants = {};
		constants.activeFlg.x = 3;
		constants.activeFlg.y = 1;

		auto world = transform.GetWorldMatrix();
		auto view = m_pBaseScene->GetActiveCamera()->GetViewMatrix();
		auto proj = m_pBaseScene->GetActiveCamera()->GetProjectionMatrix();
		auto worldView = world * view;
		constants.worldViewProj = XMMatrixTranspose(XMMatrixMultiply(worldView, proj));
		constants.fogVector = g_XMZero;
		constants.fogColor = g_XMZero;
		//ライトの決定
		auto lightSet = m_pBaseScene->GetActiveLightSet();
		for (int i = 0; i < lightSet->GetNumLights(); i++) {
			constants.lightDirection[i] = lightSet->GetLight(i).m_directional;
			constants.lightDiffuseColor[i] = lightSet->GetLight(i).m_diffuseColor;
			constants.lightSpecularColor[i] = lightSet->GetLight(i).m_specularColor;
		}
		//ワールド行列
		constants.world = XMMatrixTranspose(world);

		XMMATRIX worldInverse = XMMatrixInverse(nullptr, world);
		constants.worldInverseTranspose[0] = worldInverse.r[0];
		constants.worldInverseTranspose[1] = worldInverse.r[1];
		constants.worldInverseTranspose[2] = worldInverse.r[2];

		XMMATRIX viewInverse = XMMatrixInverse(nullptr, view);
		constants.eyePosition = viewInverse.r[3];

		XMVECTOR diffuse = Col4(1.0f);
		XMVECTOR alphaVector = XMVectorReplicate(1.0);
		XMVECTOR emissiveColor = Col4(0.0f);
		XMVECTOR ambientLightColor = lightSet->GetAmbient();
		// emissive と ambientとライトをマージする
		constants.emissiveColor = (emissiveColor + ambientLightColor * diffuse) * alphaVector;
		constants.specularColorAndPower = Col4(0, 0, 0, 1);

		// xyz = diffuse * alpha, w = alpha.
		constants.diffuseColor = XMVectorSelect(alphaVector, diffuse * alphaVector, g_XMSelect1110);

	}

	void GameObject::WriteConstantBuffers(FrameResource* pFrameResource) {
		BasicConstants constants;
		SetConstants(constants, m_transform);
		memcpy(pFrameResource->m_frameParamVec[m_paramIndex].m_pConstantBuffer, &constants, sizeof(BasicConstants));
	}

	void GameObject::OnInitFrame(FrameResource* pFrameResource) {
		auto pDefaultDev = App::GetDefaultDevice();
		auto pDevice = App::GetID3D12Device();

		// コンスタントバッファのサイズは256バイト境界ごとに作成する
		UINT constsize = (sizeof(BasicConstants) + 255) & ~255;

		FrameParam param;
		// アップロードヒープ
		ThrowIfFailed(pDevice->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(constsize),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&param.m_cbvUploadHeap)));
		//マップ
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(param.m_cbvUploadHeap->Map(0, &readRange, reinterpret_cast<void**>(&param.m_pConstantBuffer)));
		//ハンドルの作成
		param.m_constBuffIndex = pDefaultDev->GetCbvSrvUavNextIndex();
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle(
			pDefaultDev->GetCbvSrvUavDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
			param.m_constBuffIndex,
			pDefaultDev->GetCbvSrvUavDescriptorHandleIncrementSize()
		);
		//コンスタントバッファビューの作成
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};
		cbvDesc.BufferLocation = param.m_cbvUploadHeap->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes = constsize;
		pDevice->CreateConstantBufferView(&cbvDesc, handle);
		m_paramIndex = pFrameResource->m_frameParamVec.size();
		pFrameResource->m_frameParamVec.push_back(param);
	}

	void GameObject::OnRender() {
		auto pDefaultDev = App::GetDefaultDevice();
		auto pFrame = pDefaultDev->GetCurrentFrameResource();
		PopulateCommandList(pFrame);
	}

	void GameObject::PopulateCommandList(FrameResource* pFrameResource) {
		auto pDevice = App::GetDefaultDevice();
		auto pCommandList = pDevice->GetComandList().Get();
		//Srv
		auto texture = OnGetTexture();
		CD3DX12_GPU_DESCRIPTOR_HANDLE srvHandle(
			pDevice->GetCbvSrvUavDescriptorHeap()->GetGPUDescriptorHandleForHeapStart(),
			texture->GetSrvIndex(),
			pDevice->GetCbvSrvUavDescriptorHandleIncrementSize()
		);
		pCommandList->SetGraphicsRootDescriptorTable(pDevice->GetGpuSlotID(L"t0"), srvHandle);

		//Sampler
		CD3DX12_GPU_DESCRIPTOR_HANDLE samplerHandle(
			pDevice->GetSamplerDescriptorHeap()->GetGPUDescriptorHandleForHeapStart(),
			0,
			0
		);
		auto pipeLine = OnGetPipelineState();
		pCommandList->SetGraphicsRootDescriptorTable(pDevice->GetGpuSlotID(L"s0"), samplerHandle);
		pCommandList->SetPipelineState(pipeLine.Get());
		pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//Cbv
		CD3DX12_GPU_DESCRIPTOR_HANDLE skyCbvHandle(
			pDevice->GetCbvSrvUavDescriptorHeap()->GetGPUDescriptorHandleForHeapStart(),
			pFrameResource->m_frameParamVec[m_paramIndex].m_constBuffIndex,
			pDevice->GetCbvSrvUavDescriptorHandleIncrementSize()
		);
		pCommandList->SetGraphicsRootDescriptorTable(pDevice->GetGpuSlotID(L"b0"), skyCbvHandle);

		auto mesh = OnGetMesh();
		pCommandList->IASetVertexBuffers(0, 1, &mesh->GetVertexBufferView());
		pCommandList->IASetIndexBuffer(&mesh->GetIndexBufferView());
		pCommandList->DrawIndexedInstanced(mesh->GetNumIndices(), 1, 0, 0, 0);
	}

}
//end basecross
