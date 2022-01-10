#ifndef _MODERN_CPP_TIMER_H_
#define _MODERN_CPP_TIMER_H_

#include <chrono>
#include <mutex>
#include <future>
#include <condition_variable>


class ModernCppTimer
{
public:
	ModernCppTimer()
	{
	}

	ModernCppTimer(const ModernCppTimer& timer) = delete;

	~ModernCppTimer()
	{
		stop();
	}

	void start(int interval, std::function<void()> task)
	{
		if (!m_stop)
			return;
		m_stop = false;

		m_future = std::async(std::launch::async, [this, interval, task]()
		{
			while (!m_stop)
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				const auto status = m_cv.wait_for(lock, std::chrono::milliseconds(interval));
				if(status == std::cv_status::timeout)
					task();
			}
		});
	}

	void stop()
	{
		if (m_stop)
			return;

		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_stop = true;
		}
		m_cv.notify_one();
		m_future.wait();
	}

private:
	bool m_stop{ true };
	std::mutex m_mutex;
	std::condition_variable m_cv;
	std::future<void> m_future;
};

#endif // !_TIMER_H_
