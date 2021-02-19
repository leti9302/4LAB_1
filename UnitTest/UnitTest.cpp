#include "CppUnitTest.h"
#include "../4LAB_1/RB_Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		RB_Tree* rb_tree;
		// before each test
		TEST_METHOD_INITIALIZE(setUp)
		{
			rb_tree = new RB_Tree();
		}
		// after each test
		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete rb_tree;
		}

		TEST_METHOD(insert_test)
		{
			rb_tree->insert(6, 10);
			Assert::AreEqual(10, rb_tree->find(6));
		}
		TEST_METHOD(insert_color_test)
		{
			rb_tree->insert(13, 1);
			rb_tree->insert(8, 2);
			rb_tree->insert(17,3);
			rb_tree->insert(1, 4);
			rb_tree->insert(11, 5);
			rb_tree->insert(6, 6);
			rb_tree->insert(15, 7);
			rb_tree->insert(25, 8);
			rb_tree->insert(22, 9);
			rb_tree->insert(27, 10);
			Assert::AreEqual('b', rb_tree->color(13));
			Assert::AreEqual('r', rb_tree->color(8));
			Assert::AreEqual('r', rb_tree->color(17));
			Assert::AreEqual('b', rb_tree->color(1));
			Assert::AreEqual('b', rb_tree->color(11));
			Assert::AreEqual('b', rb_tree->color(15));
			Assert::AreEqual('b', rb_tree->color(25));
			Assert::AreEqual('r', rb_tree->color(6));
			Assert::AreEqual('r', rb_tree->color(22));
			Assert::AreEqual('r', rb_tree->color(27));
		}

		TEST_METHOD(remove_test)
		{
			rb_tree->insert(55, 1);
			rb_tree->insert(40, 2);
			rb_tree->insert(65, 3);
			rb_tree->insert(60, 4);
			rb_tree->insert(75, 3);
			rb_tree->insert(57, 3);
			rb_tree->remove(40);
			Assert::AreEqual('b', rb_tree->color(65));
		}
	};
}
