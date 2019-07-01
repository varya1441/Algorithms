#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BHT
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int n = 5;
			long long  arr[] = { 1,2,3,4,5 };
			Assert::IsTrue(isHeap(arr,n));
		}

	};
}