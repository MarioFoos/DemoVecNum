#ifndef SRC_VECNUM_H_
#define SRC_VECNUM_H_

#pragma once

#include <iostream>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <memory>

#define __VECNUM_PROC std::function<void(std::size_t _pos, T &_value)>

template <typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
class vecnum
{
	private:
		std::size_t _size;
		T *_data;

		void create(std::size_t size);
		void procVec(__VECNUM_PROC func);
	public:
		vecnum(std::size_t size);
		vecnum(std::size_t size, T init);
		virtual ~vecnum();

		// Acceso, asignación, comparación
		T& operator[](std::size_t _pos) const;
		vecnum<T>& operator=(const vecnum<T>& other);
		bool operator==(const vecnum<T>& other) const;
		bool operator!=(const vecnum<T>& other) const;

		// Aritméticos
		vecnum<T> operator+(const vecnum<T>& other);
		vecnum<T> operator-(const vecnum<T>& other);
		T operator*(const vecnum<T>& other);
		template <typename U> vecnum<T> operator*(U num);
		template <typename U> vecnum<T> operator/(U num);

		// Aritméticos y de asignación
		vecnum<T>& operator+=(const vecnum<T>& other);
		vecnum<T>& operator-=(const vecnum<T>& other);
		template <typename U> vecnum<T>& operator*=(U num);
		template <typename U> vecnum<T>& operator/=(U num);

		// Relleno
		void fill(T value);
		void fillrnd();
		void clear(){ fill(static_cast<T>(0)); };

		std::size_t size() const { return _size; }
		std::string to_string();
};

template <typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
std::ostream& operator<<(std::ostream& os, vecnum<T>& other)
{
	os << other.to_string();
	return os;
}

// Incluir la implementación al final del archivo de cabecera
#include "vecnum.cpp"

#endif /* SRC_VECNUM_H_ */
