#include "CppUnitTest.h"
#include "../4LAB_1/RB_Tree.h"
using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		RB_Tree<int> *rb_tree;
		// before each test
		TEST_METHOD_INITIALIZE(setUp)
		{
			rb_tree = new RB_Tree<int>();
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

		TEST_METHOD(insert_test_2)
		{
			rb_tree->insert(6, 10);
			rb_tree->insert(5, 2);
			rb_tree->insert(7, 4);
			list<int> keys = rb_tree->get_keys();
			Assert::AreEqual(6, keys.front());
			keys.pop_front();
			Assert::AreEqual(5, keys.front());
			keys.pop_front();
			Assert::AreEqual(7, keys.front());
			keys.pop_front();
			Assert::AreEqual(0, int(keys.size()));
		}

		TEST_METHOD(insert_test_3)
		{
			rb_tree->insert(6, 10);
			rb_tree->insert(5, 2);
			rb_tree->insert(7, 4);
			list<int> values = rb_tree->get_values();
			Assert::AreEqual(10, values.front());
			values.pop_front();
			Assert::AreEqual(2, values.front());
			values.pop_front();
			Assert::AreEqual(4, values.front());
			values.pop_front();
			Assert::AreEqual(0, int(values.size()));
		}

		TEST_METHOD(insert_color_test)
		{
			rb_tree->insert(6, 10);
			Assert::AreEqual('b', rb_tree->color(6));
		}

		TEST_METHOD(insert_color_test_2)
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

		TEST_METHOD(insert_color_test_3)
		{
			rb_tree->insert(33, 1);
			rb_tree->insert(13, 2);
			rb_tree->insert(53, 3);
			rb_tree->insert(11, 4);
			rb_tree->insert(21, 5);
			rb_tree->insert(41, 6);
			rb_tree->insert(61, 7);
			rb_tree->insert(15, 8);
			rb_tree->insert(31, 9);
			rb_tree->insert(20, 10);
			Assert::AreEqual('b', rb_tree->color(21));
			Assert::AreEqual('r', rb_tree->color(13));
			Assert::AreEqual('r', rb_tree->color(33));
			Assert::AreEqual('b', rb_tree->color(31));
		}

		TEST_METHOD(remove_test)
		{
			try {
				rb_tree->insert(55, 1);
				rb_tree->insert(40, 2);
				rb_tree->insert(65, 3);
				rb_tree->insert(60, 4);
				rb_tree->insert(75, 5);
				rb_tree->insert(57, 6);
				rb_tree->remove(40);
				rb_tree->find(40);
			}
			catch (char* e) {
				Assert::AreEqual("There is no such element!", e);
			}
		}

		TEST_METHOD(remove_color_test)
		{
			rb_tree->insert(55, 1);
			rb_tree->insert(40, 2);
			rb_tree->insert(65, 3);
			rb_tree->insert(60, 4);
			rb_tree->insert(75, 5);
			rb_tree->insert(57, 6);
			rb_tree->remove(40);
			Assert::AreEqual('b', rb_tree->color(65));
			Assert::AreEqual('r', rb_tree->color(57));
			Assert::AreEqual('b', rb_tree->color(55));
			Assert::AreEqual('b', rb_tree->color(60));
		}

		TEST_METHOD(remove_keys_test)
		{
			rb_tree->insert(55, 1);
			rb_tree->insert(40, 2);
			rb_tree->insert(65, 3);
			rb_tree->insert(60, 4);
			rb_tree->insert(75, 5);
			rb_tree->insert(57, 6);
			list<int> keys = rb_tree->get_keys();
			Assert::AreEqual(55, keys.front());
			keys.pop_front();
			Assert::AreEqual(40, keys.front());
			keys.pop_front();
			Assert::AreEqual(65, keys.front());
			keys.pop_front();
			Assert::AreEqual(60, keys.front());
			keys.pop_front();
			Assert::AreEqual(57, keys.front());
			keys.pop_front();
			Assert::AreEqual(75, keys.front());
			keys.pop_front();
			Assert::AreEqual(0, int(keys.size()));
		}

		TEST_METHOD(remove_values_test)
		{
			rb_tree->insert(55, 1);
			rb_tree->insert(40, 2);
			rb_tree->insert(65, 3);
			rb_tree->insert(60, 4);
			rb_tree->insert(75, 5);
			rb_tree->insert(57, 6);
			list<int> values = rb_tree->get_values();
			Assert::AreEqual(1, values.front());
			values.pop_front();
			Assert::AreEqual(2, values.front());
			values.pop_front();
			Assert::AreEqual(3, values.front());
			values.pop_front();
			Assert::AreEqual(4, values.front());
			values.pop_front();
			Assert::AreEqual(6, values.front());
			values.pop_front();
			Assert::AreEqual(5, values.front());
			values.pop_front();
			Assert::AreEqual(0, int(values.size()));
		}

		TEST_METHOD(find_test)
		{
			rb_tree->insert(33, 1);
			rb_tree->insert(13, 2);
			rb_tree->insert(53, 3);
			rb_tree->insert(11, 4);
			rb_tree->insert(21, 5);
			rb_tree->insert(41, 6);
			Assert::AreEqual(1, rb_tree->find(33));
			Assert::AreEqual(2, rb_tree->find(13));
			Assert::AreEqual(3, rb_tree->find(53));
			Assert::AreEqual(4, rb_tree->find(11));
			Assert::AreEqual(5, rb_tree->find(21));
			Assert::AreEqual(6, rb_tree->find(41));
		}

		TEST_METHOD(clear_test)
		{
			rb_tree->insert(33, 1);
			rb_tree->insert(13, 2);
			rb_tree->insert(53, 3);
			rb_tree->insert(11, 4);
			rb_tree->insert(21, 5);
			rb_tree->insert(41, 6);
			rb_tree->clear();
			list<int> keys = rb_tree->get_keys();
			Assert::AreEqual(0, int(keys.size()));
		}

		TEST_METHOD(get_keys_test)
		{
			rb_tree->insert(33, 1);
			rb_tree->insert(13, 2);
			rb_tree->insert(53, 3);
			rb_tree->insert(11, 4);
			rb_tree->insert(21, 5);
			rb_tree->insert(41, 6);
			list<int> keys = rb_tree->get_keys();
			Assert::AreEqual(33, keys.front());
			keys.pop_front();
			Assert::AreEqual(13, keys.front());
			keys.pop_front();
			Assert::AreEqual(11, keys.front());
			keys.pop_front();
			Assert::AreEqual(21, keys.front());
			keys.pop_front();
			Assert::AreEqual(53, keys.front());
			keys.pop_front();
			Assert::AreEqual(41, keys.front());
			keys.pop_front();
			Assert::AreEqual(0, int(keys.size()));
		}

		TEST_METHOD(get_keys_size_test)
		{
			rb_tree->insert(33, 1);
			rb_tree->insert(13, 2);
			rb_tree->insert(53, 3);
			rb_tree->insert(11, 4);
			rb_tree->insert(21, 5);
			rb_tree->insert(41, 6);
			list<int> keys = rb_tree->get_keys();
			Assert::AreEqual(6, int(keys.size()));
		}

		TEST_METHOD(get_values_test)
		{
			rb_tree->insert(33, 1);
			rb_tree->insert(13, 2);
			rb_tree->insert(53, 3);
			rb_tree->insert(11, 4);
			rb_tree->insert(21, 5);
			rb_tree->insert(41, 6);
			list<int> values = rb_tree->get_values();
			Assert::AreEqual(1, values.front());
			values.pop_front();
			Assert::AreEqual(2, values.front());
			values.pop_front();
			Assert::AreEqual(4, values.front());
			values.pop_front();
			Assert::AreEqual(5, values.front());
			values.pop_front();
			Assert::AreEqual(3, values.front());
			values.pop_front();
			Assert::AreEqual(6, values.front());
			values.pop_front();
			Assert::AreEqual(0, int(values.size()));
		}

		TEST_METHOD(get_values_size_test)
		{
			rb_tree->insert(33, 1);
			rb_tree->insert(13, 2);
			rb_tree->insert(53, 3);
			rb_tree->insert(11, 4);
			rb_tree->insert(21, 5);
			rb_tree->insert(41, 6);
			list<int> values = rb_tree->get_values();
			Assert::AreEqual(6, int(values.size()));
		}
	};
}
