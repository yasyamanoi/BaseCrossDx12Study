/*!
@file App.h
@brief �A�v���P�[�V�����N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�A�v���P�[�V�����N���X
	//--------------------------------------------------------------------------------------
	class App
	{
	public:
		static int Run(BaseDevice* pSample,BaseScene* pBaseScene, HINSTANCE hInstance, int nCmdShow);
		static HWND GetHwnd() { return m_hwnd; }
		static BaseScene* GetBaseScene() {return m_pBaseScene; }

		static DefaultDevice* GetDefaultDevice() {
			return reinterpret_cast<DefaultDevice*>(GetWindowLongPtr(App::GetHwnd(), GWLP_USERDATA));
		}
		static ComPtr<ID3D12Device> GetID3D12Device() {
			return GetDefaultDevice()->GetID3D12Device();
		}
		static double GetElapsedTime(){
			return GetDefaultDevice()->GetElapsedTime();
		}
		static const wstring& GetModulePath() { return m_wstrModulePath; }
		static const wstring& GetModuleDir() { return m_wstrDir; }
		static const wstring& GetDataPath() { return m_wstrDataPath; }
		static const wstring& GetShadersPath() { return m_wstrShadersPath; }
		static const wstring& GetRelativeDataPath() { return m_wstrRelativeDataPath; }
		static const wstring& GetRelativeShadersPath() { return m_wstrRelativeShadersPath; }
		static const wstring& GetRelativeAssetsPath() { return m_wstrRelativeAssetsPath; }
	protected:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		static void SetAssetsPath();

		static HWND m_hwnd;
		static BaseScene* m_pBaseScene;

		static wstring m_wstrModulePath;		///< ���W���[�����t���p�X
		static wstring m_wstrDir;				///< ���W���[��������f�B���N�g��
		static wstring m_wstrDataPath;			///< ��΃p�X�̃��f�B�A�f�B���N�g��
		static wstring m_wstrShadersPath;		///< ��΃p�X�̃V�F�[�_�f�B���N�g��
		static wstring m_wstrRelativeDataPath;	///< ���΃p�X�̃��f�B�A�f�B���N�g��
		static wstring m_wstrRelativeShadersPath;	///< ���΃p�X�̃V�F�[�_�f�B���N�g��
		static wstring	m_wstrRelativeAssetsPath;	///< ���΃p�X�̃A�Z�b�g�f�B���N�g��

	};
}
//end namespace basecross


