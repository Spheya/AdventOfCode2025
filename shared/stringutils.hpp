#pragma once

#include <string>
#include <string_view>

template<typename S>
class BasicSubStringIterator {
public:
	using char_type = typename S::value_type;
	using string_type = S;
	using string_view_type = std::basic_string_view<char_type>;

public:
	BasicSubStringIterator(string_view_type string, string_type delimiter) :
		m_delimiter(std::move(delimiter)),
		m_string(string),
		m_start(0),
		m_end(m_string.find(m_delimiter)),
		m_view(m_string.data() + m_start, m_string.data() + m_end)
	{}

	BasicSubStringIterator& operator++() {
		increment();
		return *this;
	}

	BasicSubStringIterator& operator++(int) {
		BasicSubStringIterator tmp = *this;
		increment();
		return tmp;
	}

	const string_view_type& operator*() const noexcept { return m_view; }
	const string_view_type* operator->() const noexcept { return &m_view; }

	operator bool() const noexcept { return m_start < m_string.size(); }

private:
	void increment() {
		m_start = m_end + m_delimiter.size();
		m_end = m_string.find(m_delimiter, m_start);
		if(m_end == string_view_type::npos) m_end = m_string.size();
		m_view = string_view_type(m_string.data() + m_start, m_string.data() + m_end);
	}

private:
	string_type m_delimiter;
	string_view_type m_string;
	size_t m_start;
	size_t m_end;
	string_view_type m_view;
};

using SubStringIterator = BasicSubStringIterator<std::string>;