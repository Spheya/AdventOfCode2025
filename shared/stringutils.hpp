#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <limits>

template<typename S>
class BasicStringTokenizer {
public:
	using char_type = typename S::value_type;
	using string_type = S;
	using string_view_type = std::basic_string_view<char_type>;

public:
	BasicStringTokenizer(string_view_type string, string_type delimiter) :
		m_delimiter(std::move(delimiter)),
		m_string(string),
		m_start(0),
		m_end(nextIndex()),
		m_view(m_string.data() + m_start, m_end - m_start) {
	}

	BasicStringTokenizer<S>& operator++() {
		increment();
		return *this;
	}

	BasicStringTokenizer<S> operator++(int) {
		BasicStringTokenizer<S> tmp = *this;
		increment();
		return tmp;
	}

	const string_view_type& operator*() const noexcept { return m_view; }
	const string_view_type* operator->() const noexcept { return &m_view; }

	bool isFinished() const noexcept { return m_start >= m_string.size(); }
	operator bool() const noexcept { return !isFinished(); }

	bool operator==(BasicStringTokenizer<S>& other) const noexcept {
		return isFinished() == other.isFinished() ||
			(m_start == other.m_start && m_end == other.m_end && m_string.data() && other.m_string.data());
	}

	static BasicStringTokenizer<S> end() noexcept {
		return BasicStringTokenizer();
	}

private:
	BasicStringTokenizer() :
		m_delimiter(),
		m_string(),
		m_start(std::numeric_limits<size_t>::max()),
		m_end(std::numeric_limits<size_t>::max()),
		m_view() {
	}

	void increment() {
		m_start = m_end + m_delimiter.size();
		m_end = nextIndex();
		if (m_end == string_view_type::npos) m_end = m_string.size();
		m_view = string_view_type(m_string.data() + m_start, m_end - m_start);
	}

	size_t nextIndex() {
		size_t result = m_string.find(m_delimiter, m_start);
		if (result == string_type::npos) return m_string.size();
		return result;
	}

private:
	string_type m_delimiter;
	string_view_type m_string;
	size_t m_start;
	size_t m_end;
	string_view_type m_view;
};

constexpr std::string_view trimStr(std::string_view str, const char* characters = " \t\r\n") {
	size_t start = str.find_first_not_of(characters);
	if(start == std::string_view::npos) return std::string_view();
	return std::string_view(str.data() + start, str.find_last_not_of(characters) - start + 1);
}

using StringTokenizer = BasicStringTokenizer<std::string>;
