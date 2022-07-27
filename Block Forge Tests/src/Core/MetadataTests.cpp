// ReSharper disable CppUnusedIncludeDirective
#include "pch.h"

#include "Core/FileUtils.cpp"
#include "Core/Metadata.cpp"
#include "Core/Log.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


TEST_CLASS(MetadataTests)
{
public:
	TEST_METHOD(Load_FileIsNotSpecified_FileIsNotLoaded)
	{
		auto metadata = Metadata();
		metadata.Load();

		Assert::IsFalse(metadata.IsLoaded());
	}

	TEST_METHOD(Load_FileDoesNotExist_FileIsNotLoaded)
	{
		const std::string filename = "FileThatDefinitelyDoesNotExist.json";

		Metadata metadata(filename);
		metadata.Load();

		Assert::IsFalse(metadata.IsLoaded());
	}
	TEST_METHOD(Load_FileExist_Success)
	{
		std::string filename = "mocks/metadata/example.json";

		Metadata metadata(filename);
		metadata.Load();

		Assert::IsTrue(metadata.IsLoaded());
	}

	TEST_METHOD(Save_FileIsNotSpecified_Error)
	{
		const std::string filename;

		Metadata metadata(filename);
		metadata.Save();

		Assert::IsFalse(metadata.IsSaved());
	}

	TEST_METHOD(IsNull_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);
		metadata.Load();

		const auto result = metadata.IsNull("null");
		Assert::IsTrue(result);
	}

	TEST_METHOD(GetBool_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);
		metadata.Load();

		const auto result = metadata.GetBool("bool");
		Assert::IsTrue(result);
	}

	TEST_METHOD(GetInt_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);
		metadata.Load();

		const auto result = metadata.GetInt("int");
		Assert::AreEqual(123, result);
	}

	TEST_METHOD(GetDouble_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);
		metadata.Load();

		const auto result = metadata.GetDouble("double");
		Assert::AreEqual(0.123, result);
	}

	TEST_METHOD(GetString_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);
		metadata.Load();

		const auto result = metadata.GetString("string");
		Assert::AreEqual("example", result.c_str());
	}

	TEST_METHOD(SetNull_TheValueIsSetProperly_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_null";

		Metadata metadata(filename);

		metadata.Load();
		metadata.SetNull(key);
		metadata.Save();

		metadata.Load();
		const auto result = metadata.IsNull(key);
		Assert::IsTrue(result);

		metadata.SetInt(key, 0);
		metadata.Save();
	}

	TEST_METHOD(SetBool_TheValueIsSetProperly_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_bool";

		Metadata metadata(filename);

		metadata.Load();
		metadata.SetBool(key, true);
		metadata.Save();

		metadata.Load();
		const auto result = metadata.GetBool(key);
		Assert::IsTrue(result);

		metadata.SetNull(key);
		metadata.Save();
	}

	TEST_METHOD(SetInt_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_int";

		Metadata metadata(filename);

		metadata.Load();
		metadata.SetInt(key, 456);
		metadata.Save();

		metadata.Load();
		const auto result = metadata.GetInt(key);
		Assert::AreEqual(456, result);

		metadata.SetNull(key);
		metadata.Save();
	}

	TEST_METHOD(SetDouble_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_double";

		Metadata metadata(filename);

		metadata.Load();
		metadata.SetDouble(key, 1.23);
		metadata.Save();

		metadata.Load();
		const auto result = metadata.GetDouble(key);
		Assert::AreEqual(1.23, result);

		metadata.SetNull(key);
		metadata.Save();
	}

	TEST_METHOD(SetString_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_string";

		Metadata metadata(filename);

		metadata.Load();
		metadata.SetString(key, "my test string");
		metadata.Save();

		metadata.Load();
		const auto result = metadata.GetString(key);
		Assert::AreEqual("my test string", result.c_str());

		metadata.SetNull(key);
		metadata.Save();
	}

	TEST_METHOD(SetObject_ExistingValueIsLoaded_Success)
	{
		const std::string filename = "mocks/metadata/getters_and_setters.json";
		const std::string objectName = "set_object";

		Metadata metadata(filename);

		nlohmann::json myTestObject;
		myTestObject["testBoolValue"] = true;
		myTestObject["testIntValue"] = 99;
		myTestObject["testNegativeIntValue"] = -1;
		myTestObject["testDoubleValue"] = 10.0001;

		metadata.Load();
		metadata.SetJsonObject(objectName, myTestObject);
		metadata.Save();

		metadata.Load();
		const auto result = metadata.GetJsonObject(objectName);

		Assert::IsTrue(result["testBoolValue"]);
		Assert::AreEqual(99, static_cast<int>(result["testIntValue"]));
		Assert::AreEqual(-1, static_cast<int>(result["testNegativeIntValue"]));
		Assert::AreEqual(10.0001, static_cast<double>(result["testDoubleValue"]));

		metadata.SetNull(objectName);
		metadata.Save();
	}
};
