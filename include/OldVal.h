#include <vector>
#include <type_traits>
#include <string>

template<typename T>
struct Old
{
    struct OldWrapper
    {
        Old<T>* old;

        OldWrapper(Old<T>* old_) : old(old_)
        {
        }

        OldWrapper(const OldWrapper& rhs)
        {
            old = new Old(*rhs.old);
        }

        OldWrapper(OldWrapper&& rhs)
        {
            old = rhs.old;
            rhs.old = nullptr;
        }

        ~OldWrapper()
        {
            delete old;
        }
    };

    T& original;
    T current;
    T* assignment = nullptr;
    std::vector<OldWrapper> inherited;

    // Used as aliases for targeting the current object.
    // Can be used to make the usage more verbose
    Old& New = *this;
    Old& old = *this;

    Old(T& original_) : original(original_), current(original)
    {
    }

    Old(T& original_, T current_) : original(original_), current(current_)
    {
    }
    ~Old()
	{
		if (assignment != nullptr)
		{
			*assignment = current;
			assignment = nullptr;
		}
	}

    Old<T>& operator+(T rhs)
	{
		auto newOld = new Old<T>(this->original, this->current + rhs);
		this->inherited.emplace_back(newOld);
		return *newOld;
	}
	
    Old<T>& operator-(T rhs)
	{
		auto newOld = new Old<T>(this->original, this->current - rhs);
		this->inherited.emplace_back(newOld);
		return *newOld;
	}
	
    Old<T>& operator+=(T rhs)
	{
		current += rhs;
		return *this;
	}

    Old<T>& operator-=(T rhs)
	{
		current -= rhs;
		return *this;
	}
	

    operator T()
	{
		return current;
	}
	
    Old<T>& operator,(T& rhs)
	{
		this->assignment = &rhs;
		return *this;
	}
	
    Old<T>& operator,(Old& rhs)
	{
		this->assignment = &rhs.original;
		return *this;
	}
	
    Old<T>& operator=(Old& rhs)
	{
		rhs.assignment = &this->original;
		return rhs; 
	}
};

template<typename T>
Old<T>& operator+(T lhs, Old<T>& rhs)
{
    auto newOld = new Old<T>(rhs.original, lhs + rhs.current);
    rhs.inherited.emplace_back(newOld);
    return *newOld;
}
template<typename T, typename Q>
Old<T>& operator+(Q lhs, Old<T>& rhs)
{
    auto newOld = new Old<T>(rhs.original, lhs + rhs.current);
    rhs.inherited.emplace_back(newOld);
    return *newOld;
}
