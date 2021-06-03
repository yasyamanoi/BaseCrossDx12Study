/*!
@file GameObject.h
@brief �Q�[���I�u�W�F�N�g�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/


#pragma once
#include "stdafx.h"

namespace basecross {

	class BaseScene;

	struct Transform {
		Vec3 m_scale;
		Vec3 m_pivot;
		Quat m_quaternion;
		Vec3 m_position;
		Mat4x4 GetWorldMatrix() const {
			Mat4x4 ret;
			ret.affineTransformation(
				m_scale,
				m_pivot,
				m_quaternion,
				m_position
			);
			return ret;
		}

	};

	//--------------------------------------------------------------------------------------
	// �z�u�����I�u�W�F�N�g
	//--------------------------------------------------------------------------------------
	class GemaObject : public ObjectInterface {
	protected:
		GemaObject(BaseScene* pBaseScene) :m_pBaseScene(pBaseScene) {}
		virtual ~GemaObject() {}
		//�t���[������CBV�֘A�p�����[�^�̃C���f�b�N�X
		size_t m_paramIndex;
		Transform m_transform;
		//�V�[���e�̃|�C���^
		BaseScene* m_pBaseScene;
		//�R���X�^���g�o�b�t�@�̓o�^
		void SetConstants(BasicConstants& constants, const Transform& transform);
	public:
		virtual void OnRender();
		virtual void OnInitFrame(FrameResource* pFrameResource);
		virtual void WriteConstantBuffers(FrameResource* pFrameResource);
		virtual void PopulateCommandList(FrameResource* pFrameResource);
		virtual ComPtr<ID3D12PipelineState> OnGetPipelineState() = 0;
		virtual shared_ptr<BaseMesh> OnGetMesh() = 0;
		virtual shared_ptr<BaseTexture> OnGetTexture() = 0;
	};

}
//end basecross
