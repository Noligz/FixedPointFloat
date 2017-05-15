#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <vector>

#include "FixedPointFloat.h"
using namespace FixedPointMath;
using namespace std;

void PrecisionTest()
{
	printf("PrecisionTest begin\n");
	double precision = (double)1 / ((long long)1 << FRACTION_BITS);
	double testCase1[] = { 1.234, 2.5, 3.14159265, 1.5707963, 2.4585, 15.6842
		, 268.148, 842.36985
		//, 1024.7854, 1000.267 
		//, 2387.99, 6754.098
		//, 9999.547, 65535, 65536
};
	size_t testCase1Count = sizeof(testCase1) / sizeof(testCase1[0]);
	double testCase2[] = { 0.0078125, 0.5, 1, 0.9876, 0.5138223, 0.1, 0.77528 };
	size_t testCase2Count = sizeof(testCase2) / sizeof(testCase2[0]);

	vector<double> allNums;
	for (size_t i = 0; i < testCase1Count; i++)
	{
		allNums.push_back(testCase1[i]);
		allNums.push_back(-testCase1[i]);
	}
	for (size_t i = 0; i < testCase2Count; i++)
	{
		allNums.push_back(testCase2[i]);
		allNums.push_back(-testCase2[i]);
	}
	allNums.push_back(0);

	vector<double> sqrtNums;
	for (size_t i = 0; i < testCase1Count; i++)
		sqrtNums.push_back(testCase1[i]);
	for (size_t i = 0; i < testCase2Count; i++)
		sqrtNums.push_back(testCase2[i]);
	sqrtNums.push_back(0);

	vector<double> asinNums;
	for (size_t i = 0; i < testCase2Count; i++)
	{
		asinNums.push_back(testCase2[i]);
		asinNums.push_back(-testCase2[i]);
	}
	asinNums.push_back(0);

	//abs
	for (size_t i = 0; i < allNums.size(); i++)
	{
		double da = allNums[i];
		FixedPointFloat fpa = FixedPointFloat(da);

		double dabs = fabs(da);
		FixedPointFloat fpabs = abs(fpa);
		if (fabs(dabs - fpabs.ToFloat()) > precision)
			printf("\n abs(%f) \n result:\t %10.6f \n expected:\t %10.6f \n", da, fpabs.ToFloat(), dabs);
	}

	//+-*/
	precision = 0.01;
	for (size_t i = 0; i < allNums.size(); i++)
	{
		double da = allNums[i];
		FixedPointFloat fpa = FixedPointFloat(da);
		for (size_t j = 0; j < allNums.size(); j++)
		{
			double db = allNums[j];
			FixedPointFloat fpb = FixedPointFloat(db);

			double dadd = da + db;
			FixedPointFloat fpadd = fpa + fpb;
			if (fabs(dadd - fpadd.ToFloat()) > precision)
				printf("\n %f + %f \n result:\t %10.6f \n expected:\t %10.6f \n", da, db, fpadd.ToFloat(), dadd);
		
			double dmin = da - db;
			FixedPointFloat fpmin = fpa - fpb;
			if (fabs(dmin - fpmin.ToFloat()) > precision)
				printf("\n %f - %f \n result:\t %10.6f \n expected:\t %10.6f \n", da, db, fpmin.ToFloat(), dmin);

			double dmul = da * db;
			FixedPointFloat fpmul = fpa * fpb;
			if (fabs(dmul - fpmul.ToFloat()) > precision)
				printf("\n %f * %f \n result:\t %10.6f \n expected:\t %10.6f \n", da, db, fpmul.ToFloat(), dmul);

			if (fabs(db) < 0.000001)
				continue;
			double ddiv = da / db;
			FixedPointFloat fpdiv = fpa / fpb;
			if (fabs(ddiv - fpdiv.ToFloat()) > precision)
				printf("\n %f / %f \n result:\t %10.6f \n expected:\t %10.6f \n", da, db, fpdiv.ToFloat(), ddiv);
		}
	}

	//sqrt
	precision = 0.01;
	for (size_t i = 0; i < sqrtNums.size(); i++)
	{
		double da = sqrtNums[i];
		FixedPointFloat fpa = FixedPointFloat(da);

		double dsqrt = sqrt(da);
		FixedPointFloat fpsqrt = sqrt(fpa);
		if (fabs(dsqrt - fpsqrt.ToFloat()) > precision)
			printf("\n sqrt(%f) \n result:\t %10.6f \n expected:\t %10.6f \n", da, fpsqrt.ToFloat(), dsqrt);
	}

	//sin cos tan
	precision = 0.01;
	for (size_t i = 0; i < allNums.size(); i++)
	{
		double da = allNums[i];
		FixedPointFloat fpa = FixedPointFloat(da);

		double dsin = sin(da);
		FixedPointFloat fpsin = sin(fpa);
		if (fabs(dsin - fpsin.ToFloat()) > precision)
			printf("\n sin(%f) \n result:\t %10.6f \n expected:\t %10.6f \n", da, fpsin.ToFloat(), dsin);

		double dcos = cos(da);
		FixedPointFloat fpcos = cos(fpa);
		if (fabs(dcos - fpcos.ToFloat()) > precision)
			printf("\n cos(%f) \n result:\t %10.6f \n expected:\t %10.6f \n", da, fpcos.ToFloat(), dcos);

		if (fabs(dcos) < 0.000001)
			continue;
		double dtan = tan(da);
		FixedPointFloat fptan = tan(fpa);
		if (fabs(dtan - fptan.ToFloat()) > precision)
			printf("\n tan(%f) \n result:\t %10.6f \n expected:\t %10.6f \n", da, fptan.ToFloat(), dtan);
	}

	//asin acos
	precision = 0.01;
	for (size_t i = 0; i < asinNums.size(); i++)
	{
		double da = asinNums[i];
		FixedPointFloat fpa = FixedPointFloat(da);

		double dasin = asin(da);
		FixedPointFloat fpasin = asin(fpa);
		if (fabs(dasin - fpasin.ToFloat()) > precision)
			printf("\n asin(%f) \n result:\t %10.6f \n expected:\t %10.6f \n", da, fpasin.ToFloat(), dasin);

		double dacos = acos(da);
		FixedPointFloat fpacos = acos(fpa);
		if (fabs(dacos - fpacos.ToFloat()) > precision)
			printf("\n acos(%f) \n result:\t %10.6f \n expected:\t %10.6f \n", da, fpacos.ToFloat(), dacos);
	}

	//atan
	precision = 0.01;
	for (size_t i = 0; i < allNums.size(); i++)
	{
		double da = allNums[i];
		if (fabs(da) >= 65535) continue;
		FixedPointFloat fpa = FixedPointFloat(da);

		double datan = atan(da);
		FixedPointFloat fpatan = atan(fpa);
		if (fabs(datan - fpatan.ToFloat()) > precision)
			printf("\n atan(%f) \n result:\t %10.6f \n expected:\t %10.6f \n", da, fpatan.ToFloat(), datan);
	}

	printf("\nPrecisionTest end\n");
}


long DoubleTest(double a, double b, unsigned long long testCount)
{
	clock_t begin, end;
	long td;

	begin = clock();
	double x = 0;
	for (unsigned long long i = 0; i < testCount; i++)
	{
		x = x + b;
		x = x * b;
		x = x - b;
		x = x / b;
		x = fabs(x);
		x = sqrt(x);
		//x = sin(x);
		//x = cos(x);
		/*x -= tan(a);
		x -= asin(a);
		x -= acos(a);
		x -= atan(a);*/
		
		//a += 0.01;
		//b += 0.01;
	}
	end = clock();
	td = end - begin;
	printf("double time: %lu\t\t\t%f\n", td, x);
	return td;
}

long FixedPointFloatTest(FixedPointFloat fpa, FixedPointFloat fpb, unsigned long long testCount)
{
	clock_t begin, end;
	long tfp;

	begin = clock();
	FixedPointFloat d1 = FixedPointFloat(0.01);
	FixedPointFloat fpx(0);
	for (unsigned long long i = 0; i < testCount; i++)
	{
		fpx = fpx + fpb;
		fpx = fpx * fpb;
		fpx = fpx - fpb;
		fpx = fpx / fpb;
		fpx = abs(fpx);
		fpx = sqrt(fpx);
		//fpx = sin(fpx);
		//fpx = cos(fpx);
		//fpx -= tan(fpa);
		//fpx -= asin(fpa);
		//fpx -= acos(fpa);
		//fpx -= atan(fpa);

		//fpa += d1;
		//fpb += d1;
	}
	end = clock();
	tfp = end - begin;
	printf("FixedPointFloat time: %lu\t\t%f\n", tfp, fpx.ToFloat());

	return tfp;
}

void PerformanceTest()
{
	printf("PerformanceTest begin\n");

	double a = 123.4567;
	double b = 1.584;

	FixedPointFloat fpa = FixedPointFloat(a);
	FixedPointFloat fpb = FixedPointFloat(b);

	unsigned long long testCount = 4294967296;
	//testCount = 999999999999999999;
	testCount = 59496729;

	long td, tfp;

	td = DoubleTest(a, b, testCount);
	tfp = FixedPointFloatTest(fpa, fpb, testCount);

	if (td > 1)
		printf("%.1fx", (double)tfp / td);

	printf("\nPerformanceTest end\n");
}

int main()
{
	//PrecisionTest();
	PerformanceTest();

	system("pause");
	return 0;
}