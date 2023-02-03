#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
typedef long long ll;

class IntegerRange
{
public:
	IntegerRange(ll low, ll high) {
		this->low = low;
		this->high = high+1;
	};
	class Iterator
	{
	public:
		using iterator_category = random_access_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = ll;
		using pointer = ll*;
		using reference = ll&;

		Iterator(pointer ptr) {
			m_ptr = new ll;
			*m_ptr = *ptr;
		}
		Iterator(const Iterator& it)
		{
			m_ptr = new ll;
			*m_ptr = *it;
		}

		reference operator*() const { return *m_ptr; }

		friend bool operator== (const Iterator& a, const Iterator& b) { 
			return *a.m_ptr == *b.m_ptr; 
		};

		friend bool operator!= (const Iterator& a, const Iterator& b) { 
			return *a.m_ptr != *b.m_ptr; 
		};

		Iterator& operator++() {
			*m_ptr += 1;
			return *this; 
		}

		Iterator operator+(const difference_type delta) { 
			return Iterator(m_ptr + delta); 
		}

		Iterator& operator+=(const difference_type delta) { 
			*m_ptr+=delta; 
			return *this; 
		}

		Iterator operator-(const difference_type delta) { 
			return Iterator(m_ptr - delta); 
		}

		difference_type operator-(const Iterator& other) { 
			return *m_ptr - *other.m_ptr; 
		}

		reference operator[](size_t index) const { 
			ll x = *m_ptr + index;
			return x; 
		}
	private:
		pointer m_ptr;
	};
	Iterator begin() { return Iterator(&low); }
	Iterator end() { return Iterator(&high); }
private:
	ll low, high;
};
