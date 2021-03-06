/*!
@file App.h
@brief アプリケーションクラス
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	アプリケーションクラス
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
		static float GetElapsedTime(){
			return (float)GetDefaultDevice()->GetElapsedTime();
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

		static wstring m_wstrModulePath;		///< モジュール名フルパス
		static wstring m_wstrDir;				///< モジュールがあるディレクトリ
		static wstring m_wstrDataPath;			///< 絶対パスのメディアディレクトリ
		static wstring m_wstrShadersPath;		///< 絶対パスのシェーダディレクトリ
		static wstring m_wstrRelativeDataPath;	///< 相対パスのメディアディレクトリ
		static wstring m_wstrRelativeShadersPath;	///< 相対パスのシェーダディレクトリ
		static wstring	m_wstrRelativeAssetsPath;	///< 相対パスのアセットディレクトリ

	};
}
//end namespace basecross


