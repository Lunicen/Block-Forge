#include "../UnitTestsConfig.h"

#include "Core/Metadata.h"
#include "Core/Metadata.cpp"
#include "Core/Log.h"
#include "Core/Log.cpp"

TEST(Metadata, Load_FileIsNotSpecified_FileIsNotLoaded)
{
	auto metadata = Metadata();
	metadata.Load();

	EXPECT_EQ(metadata.IsLoaded(), false);
}

TEST(Metadata, Load_FileDoesNotExist_FileIsNotLoaded)
{
	const std::string filename = "FileThatDefinitelyDoesNotExist.json";

	Metadata metadata(filename);
	metadata.Load();

	EXPECT_EQ(metadata.IsLoaded(), false);
}

TEST(Metadata, Load_FileExist_Success)
{
	const std::string filename = root + "mocks/metadata/example.json";

	Metadata metadata(filename);
	metadata.Load();

	EXPECT_EQ(metadata.IsLoaded(), true);
}

TEST(Metadata, Save_FileIsNotSpecified_Error)
{
	/// TODO
	/// Add missing unit test
	FAIL() << "Unit test not implemented";
}

TEST(Metadata, Save_OverridingProtectedFile_ThrowException)
{
	/// TODO
	/// Add missing unit test
	FAIL() << "Unit test not implemented";
}

TEST(Metadata, IsNull_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";

	Metadata metadata(filename);
	metadata.Load();

	const auto result = metadata.IsNull("null");
	EXPECT_EQ(result, true);
}

TEST(Metadata, GetBool_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";

	Metadata metadata(filename);
	metadata.Load();

	const auto result = metadata.GetBool("bool");
	EXPECT_EQ(result, true);
}

TEST(Metadata, GetInt_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";

	Metadata metadata(filename);
	metadata.Load();

	const auto result = metadata.GetInt("int");
	EXPECT_EQ(result, 123);
}

TEST(Metadata, GetDouble_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";

	Metadata metadata(filename);
	metadata.Load();

	const auto result = metadata.GetDouble("double");
	EXPECT_EQ(result, 0.123);
}

TEST(Metadata, GetString_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";

	Metadata metadata(filename);
	metadata.Load();

	const auto result = metadata.GetString("string");
	EXPECT_EQ(result, "example");
}

TEST(Metadata, SetNull_TheValueIsSetProperly_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";
	const std::string key = "set_null";

	Metadata metadata(filename);

	metadata.Load();
	metadata.SetNull(key);
	metadata.Save();

	metadata.Load();
	const auto result = metadata.IsNull(key);
	EXPECT_EQ(result, true);

	metadata.SetInt(key, 0);
	metadata.Save();
}

TEST(Metadata, SetBool_TheValueIsSetProperly_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";
	const std::string key = "set_bool";

	Metadata metadata(filename);

	metadata.Load();
	metadata.SetBool(key, true);
	metadata.Save();

	metadata.Load();
	const auto result = metadata.GetBool(key);
	EXPECT_EQ(result, true);

	metadata.SetNull(key);
	metadata.Save();
}

TEST(Metadata, SetInt_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";
	const std::string key = "set_int";

	Metadata metadata(filename);

	metadata.Load();
	metadata.SetInt(key, 456);
	metadata.Save();

	metadata.Load();
	const auto result = metadata.GetInt(key);
	EXPECT_EQ(result, 456);

	metadata.SetNull(key);
	metadata.Save();
}

TEST(Metadata, SetDouble_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";
	const std::string key = "set_double";

	Metadata metadata(filename);

	metadata.Load();
	metadata.SetDouble(key, 1.23);
	metadata.Save();

	metadata.Load();
	const auto result = metadata.GetDouble(key);
	EXPECT_EQ(result, 1.23);

	metadata.SetNull(key);
	metadata.Save();
}

TEST(Metadata, SetString_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";
	const std::string key = "set_string";

	Metadata metadata(filename);

	metadata.Load();
	metadata.SetString(key, "my test string");
	metadata.Save();

	metadata.Load();
	const auto result = metadata.GetString(key);
	EXPECT_EQ(result, "my test string");

	metadata.SetNull(key);
	metadata.Save();
}

TEST(Metadata, SetObject_ExistingValueIsLoaded_Success)
{
	/// TODO
	/// Add missing unit test
	FAIL() << "Unit test not implemented";
}