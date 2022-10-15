#pragma once
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

namespace nm
{
	class string
	{
		inline static const short minimumCapacity = 5;
		char* text;
		size_t length;
		size_t capacity;

		void reallocate(const size_t size)
		{
			if (size < length)
				length = size;
			char* txt = DBG_NEW char[length + 1];
			for (size_t i = 0; i < length; i++)
				txt[i] = text[i];
			txt[length] = '\0';
			capacity = size;
			delete[] text;
			text = nullptr;
			text = DBG_NEW char[size];
			capacity = size;
			for (size_t i = 0; i <= length; i++)
				text[i] = txt[i];
			delete[] txt;
			txt = nullptr;
		}

		void ShouldReallocate(size_t size = 0)
		{
			if (size == 0) size = capacity;
			if (length > capacity * 0.8) reallocate(size * 1.5);
			else if (length < capacity * 0.3) reallocate(size * 0.5);
		}

	public:
		inline static const size_t npos = SIZE_MAX;

		string() : capacity(minimumCapacity), length(0)
		{
			text = DBG_NEW char[minimumCapacity];
			text[0] = '\0';						
		}
		string(const string& str) : capacity(str.capacity), length(0)
		{
			this->text = DBG_NEW char[capacity];
			for (; length < strlen(str.text) + 1; length++)
				text[length] = str.text[length];
			--length;
		}

		string& operator=(const string& str)
		{			
			capacity = str.capacity;
			length = 0;
			this->text = DBG_NEW char[capacity];
			for (; length < strlen(str.text) + 1; length++)
				text[length] = str.text[length];
			--length;
			return* this;
		}

		string& operator=(const char c)
		{			
			capacity = minimumCapacity;
			length = 0;
			text = DBG_NEW char[minimumCapacity];
			text[0] = c;
			text[1] = '\0';
			return *this;

		}

		explicit string(const char c) : capacity(minimumCapacity), length(1)
		{
			text = DBG_NEW char[minimumCapacity];
			text[0] = c;
			text[1] = '\0';
		}

		string(const char* c) : length(0)
		{
			capacity = strlen(c) + 2;
			text = DBG_NEW char[capacity];
			for (; length < strlen(c) + 1; length++)
				text[length] = c[length];
			--length;
		}

		string& operator=(const char* c)
		{
			if (text)
			{
				delete[] text;
				text = nullptr;
			}
			capacity = strlen(c) + 2;
			text = DBG_NEW char[capacity];
			for (; length < strlen(c) + 1; length++)
				text[length] = c[length];
			--length;
			return *this;
		}

		char& operator[](const size_t index)
		{
			if (index < 0 || index >= length) throw std::exception("index out of range : operator[]");
			return text[index];
		}

		const char& operator[](const size_t index)	const
		{
			if (index < 0 || index >= length) throw std::exception("index out of range : operator[]");
			return text[index];
		}

		string(const size_t number) { *this = ToString(number); }
		string(const long long& number) { *this = ToString(number); }
		string(const long& number) { *this = ToString(number); }
		string(const int& number) { *this = ToString(number); }
		string(const short& number) { *this = ToString(number); }

		static string ToString(size_t t)
		{
			char* num = DBG_NEW char[23];
			short index = 22;
			do
			{
				--index;
				num[index] = '0' + t % 10;
				t /= 10;
			} while (t != 0);
			num[22] = '\0';
			string ret = &num[index];
			delete[] num;
			num = nullptr;
			return ret;
		}

		~string()
		{
			if (!text) return;
			delete[] text;
			text = nullptr;
		}

		const size_t size() const
		{
			return length;
		}

		const size_t max_capacity() const
		{
			return capacity;
		}

		bool empty() const
		{
			return length == 0;
		}

		void reserve(const size_t size)
		{
			if (size < length) return;
			reallocate(size);
		}

		void resize(const size_t size)
		{
			if (size < length) return;
			reallocate(size);
			for (; length < size - 1; length++)
				text[length] = ' ';
			text[length] = '\0';
			--length;
		}

		size_t erase(const size_t pos)
		{
			if (pos < 0 || pos >= length) return npos;
			for (size_t i = pos; i < length; i++)
				text[i] = text[i + 1];
			--length;
			ShouldReallocate();
			return pos;
		}

		void insert(const char* c, const size_t pos)
		{
			if (pos > length || pos < 0) return;
			auto len = strlen(c);
			size_t oldLength = length;
			length += len;
			ShouldReallocate(length * 1.5);
			text[oldLength] = 'q';
			for (size_t i = pos; i < pos + len; i++)
				text[i + len] = text[i];
			for (size_t i = 0; i < len; i++)
				text[pos + i] = c[i];
			text[length] = '\0';
		}

		void insert(const char& c, const size_t pos)
		{
			const char str[] = { c, '\0' };
			insert(str, pos);
		}

		void insert(const string& str, const size_t pos)
		{
			insert(str.text, pos);
		}

		void insert(const char& c, const size_t pos, const long& amount)
		{
			char* str = DBG_NEW char[amount + 1];
			for (long i = 0; i < amount; i++)
				str[i] = c;
			str[amount] = '\0';
			insert(str, pos);
			delete[] str;
			str = nullptr;
		}

		void push_back(const char& c)
		{
			const char str[] = { c, '\0' };
			insert(str, length);
		}

		void push_back(const char* c)
		{
			insert(c, length);
		}

		void push_back(const string& str)
		{
			insert(str.text, length);
		}

		char pop_back()
		{
			if (empty()) return '\0';
			char c = back();
			erase(length - 1);
			return c;
		}

		const char* c_str()
		{
			if (empty()) return "";
			return text;
		}

		char& back()
		{
			return text[length - 1];
		}

		const char back() const
		{
			return text[length - 1];
		}

		char& front()
		{
			return text[0];
		}

		const char front() const
		{
			return text[0];
		}

		string substr(size_t start, size_t len)	const
		{
			if (start + len > length) len = length - start;
			char* str = DBG_NEW char[len + 1];
			size_t i = 0;
			for (; i < len; i++)
				str[i] = text[start + i];
			str[i] = '\0';
			string ret = str;
			delete[] str;
			str = nullptr;
			return ret;
		}

		void clear()
		{
			if (!text) return;
			delete[] text;
			text = nullptr;
			text = DBG_NEW char[capacity];
			length = 0;
		}

		void shrink_to_fit()
		{
			const size_t len = strlen(text);
			char* str = DBG_NEW char[len + 1];
			for (size_t i = 0; i < len; i++)
				str[i] = text[i];
			str[len] = '\0';
			length = len;
			this->text = str;
			reallocate(length * 1.5);
			str = nullptr;
		}

		size_t find(const char& c) const
		{
			if (empty()) return npos;
			for (size_t i = 0; i < length; i++)
				if (this->text[i] == c) return i;
			return npos;
		}

		size_t find(const string& str) const
		{
			if (length == 1) return find(str.text[0]);
			return this->find(str.text);
		}

		size_t find(const char* c) const
		{
			if (empty()) return npos;
			size_t len = strlen(c);
			
			for (size_t i = 0; i < length - len; i++)
				if (this->substr(i, len) == c) return i;
			return npos;
		}

		size_t find_first_of(const char* c)
		{
			size_t len = strlen(c);
			for (size_t i = 0; i < length; i++)
				for (size_t j = 0; j < len; j++)
					if (text[i] == c[j]) return i;
			return npos;
		}

		size_t find_first_of(const char& c)
		{
			return find(c);
		}

		size_t find_first_of(const string& str)
		{
			if (str.length == 1) return find(str[0]);
			return find_first_of(str.text);
		}

		template<typename CMP = std::less<char>>
		constexpr void sort(size_t begin = 0, size_t end = 0) noexcept
		{
			if (end == 0) end = length;
			if (begin < 0 || end > length || begin > end) return;
			CMP cmp;
			bool swap = true;
			while (swap)
			{
				swap = false;
				for (size_t i = begin; i < end - 1; i++)
				{
					if (cmp(text[i], text[i + 1]))
					{
						swap = true;
						char temp = text[i + 1];
						text[i + 1] = text[i];
						text[i] = temp;
					}
				}
			}
		}

		friend std::ostream& operator<< (std::ostream& os, const string& str)
		{
			for (size_t i = 0; i < strlen(str.text); i++)
				std::cout << str.text[i];
			return os;
		}

		friend std::istream& operator>>(std::istream& is, string& str)
		{
			str.clear();
			is.seekg(0, is.beg);
			str.reserve(120);			
			is.get(str.text, 120, '\n');
			str.shrink_to_fit();
			return is;
		}

		bool operator<(const string& str) const
		{
			return *this < str.text;
		}

		bool operator<(const char* c) const
		{
			return strcmp(this->text, c) < 0;
		}

		bool operator>(const string& str) const
		{
			return *this > str.text;
		}

		bool operator>(const char* c) const
		{
			return strcmp(this->text, c) > 0;
		}

		bool operator<=(const string& str) const
		{
			return *this <= str.text;
		}

		bool operator<=(const char* c) const
		{
			return strcmp(this->text, c) <= 0;
		}

		bool operator>=(const string& str) const
		{
			return *this >= str.text;
		}

		bool operator>=(const char* c) const
		{
			return strcmp(this->text, c) >= 0;
		}

		bool operator==(const string& str) const
		{
			return *this == str.text;
		}

		bool operator==(const char* c) const
		{
			return strcmp(this->text, c) == 0;
		}

		void operator+=(const char* c)
		{
			this->push_back(c);
		}

		void operator+=(const char& c)
		{
			const char str[] = { c, '\n' };
			this->push_back(str);
		}

		void operator+=(const string& str)
		{
			this->push_back(str);
		}

		string operator+(const char* c) const
		{
			string str(text);
			str.push_back(c);
			return str;
		}

		string operator+(const char& c) const
		{
			const char str[] = { c, '\0' };
			return *this + str;
		}

		string operator+(const string& str)	const
		{
			return *this + str.text;
		}
	};
}
