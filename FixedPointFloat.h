//#pragma once
#ifndef __FIXEDPOINTFLOAT_H__
#define __FIXEDPOINTFLOAT_H__

#include <stdint.h>

namespace FixedPointMath
{
	class FixedPointFloat
	{
#define FRACTION_BITS 16
#define INTEGER_BITS 32

		typedef int64_t StorageType;
		typedef uint64_t CalcType;

	private:
		StorageType _num;
		const static CalcType c_one;
		const static CalcType c_intMask;
		const static CalcType c_fracMask;

	private:
		typedef unsigned short TableType;
		const static TableType c_sinTableCount;
		const static TableType c_sinTable[];
		const static TableType c_asinTableCount;
		const static TableType c_asinTable[];

	public:
		FixedPointFloat();
		FixedPointFloat(double);
		FixedPointFloat(int);
		FixedPointFloat(const FixedPointFloat&);

	private:
		FixedPointFloat(StorageType);

	public:
		friend FixedPointFloat operator + (const FixedPointFloat&, const FixedPointFloat&);
		FixedPointFloat& operator += (const FixedPointFloat&);

		friend FixedPointFloat operator - (const FixedPointFloat&, const FixedPointFloat&);
		FixedPointFloat& operator -= (const FixedPointFloat&);

		friend FixedPointFloat operator * (const FixedPointFloat&, const FixedPointFloat&);
		FixedPointFloat& operator *= (const FixedPointFloat&);

		friend FixedPointFloat operator / (const FixedPointFloat&, const FixedPointFloat&);
		FixedPointFloat& operator /= (const FixedPointFloat&);

		friend bool operator == (const FixedPointFloat&, const FixedPointFloat&);
		friend bool operator != (const FixedPointFloat&, const FixedPointFloat&);
		friend bool operator > (const FixedPointFloat&, const FixedPointFloat&);
		friend bool operator >= (const FixedPointFloat&, const FixedPointFloat&);
		friend bool operator < (const FixedPointFloat&, const FixedPointFloat&);
		friend bool operator <= (const FixedPointFloat&, const FixedPointFloat&);

		FixedPointFloat& operator ++ ();
		FixedPointFloat& operator -- ();

		FixedPointFloat Sqrt() const;
		FixedPointFloat Abs() const;
		FixedPointFloat Sin() const;
		FixedPointFloat Asin() const;
		FixedPointFloat Atan() const;

	public:
		double ToFloat() const;

	private:
		static CalcType GetIntPart(CalcType);
		static CalcType GetFracPart(CalcType);
	};

	FixedPointFloat abs(const FixedPointFloat& x) ;
	FixedPointFloat sqrt(const FixedPointFloat& x);
	FixedPointFloat sin(const FixedPointFloat& x) ;
	FixedPointFloat cos(const FixedPointFloat& x) ;
	FixedPointFloat tan(const FixedPointFloat& x) ;
	FixedPointFloat asin(const FixedPointFloat& x);
	FixedPointFloat acos(const FixedPointFloat& x);
	FixedPointFloat atan(const FixedPointFloat& x);
}
#endif // !__FIXEDPOINTFLOAT_H__
