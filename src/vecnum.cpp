#include "vecnum.h"

#include <ctime>
#include <vector>
#include <cstring>

using namespace std;

template <typename T, typename Enable>
vecnum<T, Enable>::vecnum(std::size_t size) : _size(size), _data(new T[size])
{
	srand(static_cast<uint32_t>(time(nullptr)));
	fill(static_cast<T>(0));
};

template <typename T, typename Enable>
vecnum<T, Enable>::vecnum(const vecnum<T>& src) : vecnum(src._size)
{
	std::copy(src._data, src._data + src._size, _data);
};

template <typename T, typename Enable>
vecnum<T, Enable>::vecnum(const T* src, std::size_t size) : vecnum(size)
{
	std::copy(src, src + size, _data);
};

template <typename T, typename Enable>
void vecnum<T, Enable>::create(std::size_t size)
{
	if(_data != nullptr)
	{
		delete[] _data;
	}
	_size = size;
	_data = new T[_size];
};

template <typename T, typename Enable>
T& vecnum<T, Enable>::operator[](std::size_t pos) const
{
	if(pos >= _size)
	{
        throw std::out_of_range("Índice fuera de rango");
	}
	return _data[pos];
};

template <typename T, typename Enable>
vecnum<T> vecnum<T, Enable>::operator=(const vecnum<T>& other)
{
	if(this != &other)
	{
		_size = other._size;
	    std::copy(other._data, other._data + other._size, _data);
	}
	return *this;
}

template <typename T, typename Enable>
bool vecnum<T, Enable>::operator==(const vecnum<T>& other) const
{
	if(this == &other)
	{
		return true;
	}
	for(std::size_t i = 0; i < _size; ++i)
	{
		if(_data[i] != other._data[i])
		{
			return false;
		}
	}
	return true;
}

template <typename T, typename Enable>
bool vecnum<T, Enable>::operator!=(const vecnum<T>& other) const
{
	if(this == &other)
	{
		return false;
	}
	for(std::size_t i = 0; i < _size; ++i)
	{
		if(_data[i] != other._data[i])
		{
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------

template <typename T, typename Enable>
vecnum<T>& vecnum<T, Enable>::operator+=(const vecnum<T> &other)
{
	if(other._size != _size)
	{
        throw std::length_error("Vectores de tamaños distintos");
	}
	__VECNUM_PROC func = [&other, this](std::size_t pos, T &value)
	{
		_data[pos] += other._data[pos];
	};
	procVec(func);

	return *this;
};

template <typename T, typename Enable>
vecnum<T>& vecnum<T, Enable>::operator-=(const vecnum<T> &other)
{
	if(other._size != _size)
	{
        throw std::length_error("Vectores de tamaños distintos");
	}
	__VECNUM_PROC func = [&other, this](std::size_t pos, T &value)
	{
		_data[pos] -= other._data[pos];
	};
	procVec(func);

	return *this;
};

template <typename T, typename Enable>
template <typename U>
vecnum<T>& vecnum<T, Enable>::operator*=(U num)
{
	__VECNUM_PROC func = [&num, this](std::size_t pos, T &value)
	{
		_data[pos] = static_cast<T>(value*num);
	};
	procVec(func);

	return *this;
};

template <typename T, typename Enable>
template <typename U>
vecnum<T>& vecnum<T, Enable>::operator/=(U num)
{
	__VECNUM_PROC func = [&num, this](std::size_t pos, T &value)
	{
		_data[pos] = static_cast<T>(value/num);
	};
	procVec(func);

	return *this;
};

//-------------------------------------------------------------------------------------------------

template <typename T, typename Enable>
vecnum<T> vecnum<T, Enable>::operator+(const vecnum<T> &other)
{
	if(other._size != _size)
	{
        throw std::length_error("Vectores de tamaños distintos");
	}
	vecnum<T> res(_size);

	__VECNUM_PROC func = [&res, &other](std::size_t pos, T &value)
	{
		res._data[pos] = value + other._data[pos];
	};
	procVec(func);

	return res;
};

template <typename T, typename Enable>
vecnum<T> vecnum<T, Enable>::operator-(const vecnum<T> &other)
{
	if(other._size != _size)
	{
        throw std::length_error("Vectores de tamaños distintos");
	}
	vecnum<T> res(_size);

	__VECNUM_PROC func = [&res, &other](std::size_t pos, T &value)
	{
		res._data[pos] = value - other._data[pos];
	};
	procVec(func);

	return res;
};

template <typename T, typename Enable>
T vecnum<T, Enable>::operator*(const vecnum<T>& other)
{
	if(other._size != _size)
	{
        throw std::length_error("Vectores de tamaños distintos");
	}
	T res = 0;

	__VECNUM_PROC func = [&res, &other](std::size_t pos, T &value)
	{
		res += value*other._data[pos];
	};
	procVec(func);

	return res;
};

template <typename T, typename Enable>
template <typename U>
vecnum<T> vecnum<T, Enable>::operator*(U num)
{
	if(!std::is_arithmetic<U>::value)
	{
        throw std::invalid_argument("Operador * no definido para el tipo dado");
	}
	vecnum<T> res(_size);

	__VECNUM_PROC func = [&res, &num](std::size_t pos, T &value)
	{
		res._data[pos] = static_cast<T>(value*num);
	};
	procVec(func);

	return res;
}

template <typename T, typename Enable>
template <typename U>
vecnum<T> vecnum<T, Enable>::operator/(U num)
{
	if(!std::is_arithmetic<U>::value)
	{
        throw std::invalid_argument("Operador * no definido para el tipo dado");
	}
	vecnum<T> res(_size);

	__VECNUM_PROC func = [&res, &num](std::size_t pos, T &value)
	{
		res._data[pos] = static_cast<T>(value/num);
	};
	procVec(func);

	return res;
}

//-------------------------------------------------------------------------------------------------

template <typename T, typename Enable>
void vecnum<T, Enable>::procVec(__VECNUM_PROC func)
{
	for(std::size_t i = 0; i < _size; ++i)
	{
		func(i, _data[i]);
	}
};

template <typename T, typename Enable>
void vecnum<T, Enable>::fill(T value)
{
	__VECNUM_PROC func = [value](std::size_t pos, T &v){ v = value; };

	procVec(func);
};

template <typename T, typename Enable>
void vecnum<T, Enable>::fillrnd()
{
	__VECNUM_PROC func = [](std::size_t pos, T &v)
	{
		double range = static_cast<double>(rand())/RAND_MAX;
		v = static_cast<T>(range*100);
	};

	procVec(func);
};

template <typename T, typename Enable>
std::string vecnum<T, Enable>::to_string() const
{
	std::string out;

	out.append(1, '{');
	for(std::size_t pos = 0; pos < _size; ++pos)
	{
		out.append(std::to_string(_data[pos]));
		if(pos == _size - 1)
		{
			out.append(1, '}');
		}
		else
		{
			out.append(", ");
		}
	}
	return out;
};

template <typename T, typename Enable>
vecnum<T, Enable>::~vecnum()
{
	delete[] _data;
};
