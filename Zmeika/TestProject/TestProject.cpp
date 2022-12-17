#include "pch.h"
#include "CppUnitTest.h"
#include "..\Zmeika\Zmeika.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestProject)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			head_x_position = 10;
			head_y_position = 5;
			move_snake(1, -1);
			Assert::AreEqual(11, head_x_position);
			Assert::AreEqual(4, head_y_position);

		}
	};
}
