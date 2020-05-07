#include "pch.h"
#include "CppUnitTest.h"
#include "../lab1sem4/Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace lab1sem4tests
{
	TEST_CLASS(lab1sem4tests)
	{
	public:
		
		TEST_METHOD(insert_one_element)
		{
			std::vector<std::string> keys{ "key0" };
			std::vector<int> values{ 0 };
			Map<std::string, int> map;
			map.insert("key0", 0);
			Assert::IsTrue(keys == map.get_keys() && values == map.get_values());
		}
		TEST_METHOD(insert_few_elements)
		{
			std::vector<std::string> keys{ "key0", "key1", "key2"};
			std::vector<int> values{ 0, 1, 2 };
			Map<std::string, int> map;
			map.insert("key0", 0);
			map.insert("key1", 1);
			map.insert("key2", 2);
			Assert::IsTrue(keys == map.get_keys() && values == map.get_values());
		}
		TEST_METHOD(remove_few_element)
		{

			std::vector<std::string> keys{ "key0", "key2", "key3" };
			std::vector<int> values{ 0, 2, 3 };
			Map<std::string, int> map;
			map.insert("key0", 0);
			map.insert("key1", 1);
			map.insert("key2", 2);
			map.insert("key3", 3);
			map.insert("key4", 4);
			map.remove("key1");
			map.remove("key4");
			Assert::IsTrue(keys == map.get_keys() && values == map.get_values());
		}
		TEST_METHOD(remove_one_element)
		{

			std::vector<std::string> keys{ };
			std::vector<int> values{ };
			Map<std::string, int> map;
			map.insert("key0", 0);
			map.remove("key0");
			Assert::IsTrue(keys == map.get_keys() && values == map.get_values());
		}
		TEST_METHOD(find)
		{
			Map<std::string, int> map;
			map.insert("key0", 0);
			map.insert("key1", 1);
			map.insert("key2", 2);
			Assert::IsTrue(map.find("key0", -1) == 0 && map.find("key1", -1) == 1 && map.find("key2", -1) == 2);
		}
		TEST_METHOD(find_not_exist)
		{
			Map<std::string, int> map;
			map.insert("key0", 0);
			map.insert("key1", 1);
			map.insert("key2", 2);
			Assert::IsTrue(map.find("key3", -1) == -1);
		}
		TEST_METHOD(clear)
		{

			std::vector<std::string> keys{ };
			std::vector<int> values{ };
			Map<std::string, int> map;
			map.insert("key0", 0);
			map.insert("key1", 1);
			map.insert("key2", 2);
			map.insert("key3", 3);
			map.insert("key4", 4);
			map.clear();
			Assert::IsTrue(keys == map.get_keys() && values == map.get_values());
		}
		TEST_METHOD(get_keys)
		{
			std::vector<std::string> keys{ "key0", "key1", "key2" };
			Map<std::string, int> map;
			map.insert("key0", 0);
			map.insert("key1", 1);
			map.insert("key2", 2);
			Assert::IsTrue(keys == map.get_keys());
		}
		TEST_METHOD(get_values)
		{
			std::vector<int> values{ 0, 1, 2 };
			Map<std::string, int> map;
			map.insert("key0", 0);
			map.insert("key1", 1);
			map.insert("key2", 2);
			Assert::IsTrue(values == map.get_values());
		}
	};
}
