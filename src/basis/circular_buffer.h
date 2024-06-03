/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-03 10:16:49
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-03 10:17:17
 */
#pragma once

template <typename T>
class CircularBuffer
{
private:
	T *m_buffer;
	int m_head;
	int m_tail;
	int m_capacity;

public:
	CircularBuffer(int size)
		: m_capacity(size), m_head(0), m_tail(0)
	{
		m_buffer = new T[m_capacity];
	}
	~CircularBuffer()
	{
		delete[] m_buffer;
	}

	void Add(const T &value)
	{
		if ((m_tail + 1) % m_capacity == m_head)
		{
			m_head = (m_head + 1) % m_capacity;
		}
		m_buffer[m_tail] = value;
		m_tail = (m_tail + 1) % m_capacity;
	}
	const T &Get(int index) const
	{
		assert(index >= 0 && index < m_capacity);
		int trueIndex = (m_head + index) % m_capacity;
		return m_buffer[trueIndex];
	}

	std::vector<T> GetBufferArray()
	{
		std::vector<T> buff;
		for (int i = m_head; i != m_tail; i = (i + 1) % m_capacity)
		{
			buff.emplace_back(m_buffer[i]);
		}
		return buff;
	}
};