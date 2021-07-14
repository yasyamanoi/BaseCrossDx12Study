/*!
@file StepTimer.h
@brief �X�e�b�v�^�C�}�[�N���X
@copyright Copyright (c) 2021 WiZ Tamura Hiroki,Yamanoi Yasushi.
*/

#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�X�e�b�v�^�C�}�[�N���X
	//--------------------------------------------------------------------------------------
	class StepTimer
	{
	public:
		StepTimer() :
			m_elapsedTicks(0),
			m_totalTicks(0),
			m_leftOverTicks(0),
			m_frameCount(0),
			m_framesPerSecond(0),
			m_framesThisSecond(0),
			m_qpcSecondCounter(0),
			m_isFixedTimeStep(false),
			m_targetElapsedTicks(TicksPerSecond / 60)
		{
			QueryPerformanceFrequency(&m_qpcFrequency);
			QueryPerformanceCounter(&m_qpcLastTime);

			m_qpcMaxDelta = m_qpcFrequency.QuadPart / 10;
		}

		UINT64 GetElapsedTicks() const { return m_elapsedTicks; }
		double GetElapsedSeconds() const { return TicksToSeconds(m_elapsedTicks); }

		UINT64 GetTotalTicks() const { return m_totalTicks; }
		double GetTotalSeconds() const { return TicksToSeconds(m_totalTicks); }

		UINT32 GetFrameCount() const { return m_frameCount; }

		UINT32 GetFramesPerSecond() const { return m_framesPerSecond; }

		void SetFixedTimeStep(bool isFixedTimestep) { m_isFixedTimeStep = isFixedTimestep; }

		void SetTargetElapsedTicks(UINT64 targetElapsed) { m_targetElapsedTicks = targetElapsed; }
		void SetTargetElapsedSeconds(double targetElapsed) { m_targetElapsedTicks = SecondsToTicks(targetElapsed); }

		static const UINT64 TicksPerSecond = 10000000;

		static double TicksToSeconds(UINT64 ticks) { return static_cast<double>(ticks) / TicksPerSecond; }
		static UINT64 SecondsToTicks(double seconds) { return static_cast<UINT64>(seconds * TicksPerSecond); }

		void ResetElapsedTime()
		{
			QueryPerformanceCounter(&m_qpcLastTime);

			m_leftOverTicks = 0;
			m_framesPerSecond = 0;
			m_framesThisSecond = 0;
			m_qpcSecondCounter = 0;
		}

		typedef void(*LPUPDATEFUNC) (void);

		void Tick(LPUPDATEFUNC update = nullptr)
		{
			// Query the current time.
			LARGE_INTEGER currentTime;

			QueryPerformanceCounter(&currentTime);

			UINT64 timeDelta = currentTime.QuadPart - m_qpcLastTime.QuadPart;

			m_qpcLastTime = currentTime;
			m_qpcSecondCounter += timeDelta;

			// Clamp excessively large time deltas (e.g. after paused in the debugger).
			if (timeDelta > m_qpcMaxDelta)
			{
				timeDelta = m_qpcMaxDelta;
			}

			timeDelta *= TicksPerSecond;
			timeDelta /= m_qpcFrequency.QuadPart;

			UINT32 lastFrameCount = m_frameCount;

			if (m_isFixedTimeStep)
			{

				if (abs(static_cast<int>(timeDelta - m_targetElapsedTicks)) < TicksPerSecond / 4000)
				{
					timeDelta = m_targetElapsedTicks;
				}

				m_leftOverTicks += timeDelta;

				while (m_leftOverTicks >= m_targetElapsedTicks)
				{
					m_elapsedTicks = m_targetElapsedTicks;
					m_totalTicks += m_targetElapsedTicks;
					m_leftOverTicks -= m_targetElapsedTicks;
					m_frameCount++;

					if (update)
					{
						update();
					}
				}
			}
			else
			{
				m_elapsedTicks = timeDelta;
				m_totalTicks += timeDelta;
				m_leftOverTicks = 0;
				m_frameCount++;

				if (update)
				{
					update();
				}
			}

			if (m_frameCount != lastFrameCount)
			{
				m_framesThisSecond++;
			}

			if (m_qpcSecondCounter >= static_cast<UINT64>(m_qpcFrequency.QuadPart))
			{
				m_framesPerSecond = m_framesThisSecond;
				m_framesThisSecond = 0;
				m_qpcSecondCounter %= m_qpcFrequency.QuadPart;
			}
		}

	private:
		LARGE_INTEGER m_qpcFrequency;
		LARGE_INTEGER m_qpcLastTime;
		UINT64 m_qpcMaxDelta;

		UINT64 m_elapsedTicks;
		UINT64 m_totalTicks;
		UINT64 m_leftOverTicks;

		UINT32 m_frameCount;
		UINT32 m_framesPerSecond;
		UINT32 m_framesThisSecond;
		UINT64 m_qpcSecondCounter;

		bool m_isFixedTimeStep;
		UINT64 m_targetElapsedTicks;
	};
}
// end namespace basecross


