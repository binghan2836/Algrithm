/*
 * File: RandomGenerator.h
 * Project: future stream
 * Created Date: Wednesday November 27th 2019
 * Author: DaGai  <binghan2836@163.com>
 * -----
 * Last Modified: Wednesday November 27th 2019 2:04:45 pm
 * Modified By:   the developer formerly known as DaGai
 * -----
 * MIT License
 * 
 * Copyright (c) 2019 binghan2836@163.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * -----
 * HISTORY:
 * Date          By    Comments
 * ----------    ---    ----------------------------------------------------------
 */
#ifndef FUTURE_STREAM_RANDOM_GENERATOR_H
#define FUTURE_STREAM_RANDOM_GENERATOR_H

#include <random>

struct OutputIntegerRandom {};
struct OutputDoubleRandom {};
struct OutputFloatRandom {};


template <class type>
class InnerRandomDevice;

template<class Dev,class Strategy>
class Distributes
{
	Dev      _dev;
	Strategy _gen;
public:
	Distributes():_gen(_dev()){}
	Strategy& operator()()
	{
		return _gen;
	}
};
template<>
class InnerRandomDevice<OutputIntegerRandom>
{
public:

	typedef int ReturnType;
	typedef int ParmType;
	ReturnType operator()()
	{
		Distributes<std::random_device, std::mt19937> gen;
		std::uniform_int_distribution<> dist;
		return dist(gen());
	}

	ReturnType operator()(ParmType from, ParmType end)
	{
		Distributes<std::random_device, std::mt19937> gen;
		std::uniform_int_distribution<> dist(from, end);
		return dist(gen());
	}
};

template<>
class InnerRandomDevice<OutputFloatRandom>
{
public:

	typedef float ReturnType;
	typedef float ParmType;
	ReturnType operator()()
	{
		Distributes<std::random_device, std::mt19937> gen;
		std::uniform_real_distribution<ParmType> dist;
		return dist(gen());
	}

	ReturnType operator()(ParmType from, ParmType end)
	{
		Distributes<std::random_device, std::mt19937> gen;
		std::uniform_real_distribution<ParmType> dist(from, end);
		return dist(gen());
	}
};

template<>
class InnerRandomDevice<OutputDoubleRandom>
{
public:

	typedef double ReturnType;
	typedef double ParmType;
	ReturnType operator()()
	{
		Distributes<std::random_device, std::mt19937> gen;
		std::uniform_real_distribution<ParmType> dist;
		return dist(gen());
	}

	ReturnType operator()(ParmType from, ParmType end)
	{
		Distributes<std::random_device, std::mt19937> gen;
		std::uniform_real_distribution<ParmType> dist(from, end);
		return dist(gen());
	}
};

template <class Ty>
typename InnerRandomDevice<Ty>::ReturnType GetRandomValue(Ty type)
{
	(void)(type);
	return InnerRandomDevice<Ty>()();
}

template <class Ty>
typename InnerRandomDevice<Ty>::ReturnType
GetRandomValue(Ty type, typename InnerRandomDevice<Ty>::ParmType from, 
	typename InnerRandomDevice<Ty>::ParmType end)
{
	(void)(type);
	return InnerRandomDevice<Ty>()(from, end);
}


#endif // !FUTURE_STREAM_RANDOM_GENERATOR_H
