#pragma once

namespace Hazel {

	class Timestep
	{
	public:
		Timestep(float time)
			: m_Time(time)
		{
			
		}

		//现在，class Timestep 可以自动转换为float类型
		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }


	private:
		float m_Time;
	};
}