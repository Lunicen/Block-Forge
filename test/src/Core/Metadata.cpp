#include "../UnitTestsConfig.h"
#include "Core/Metadata.h"
#include "Core/Metadata.cpp"

TEST(Metadata, Load_FileIsNotSpecified_ThrowException)
{
	auto metadata = Metadata();
	try
	{
		metadata.Load();
		FAIL() << "Expected std::invalid_argument";
	}
	catch(std::invalid_argument const& err)
	{
		EXPECT_EQ(err.what(), std::string("File is not specified!"));
	}
	catch(...)
	{
		FAIL() << "Expected std::invalid_argument";
	}
}

TEST(Metadata, Load_FileDoesNotExist_ThrowException)
{
	const std::string filename = "FileThatDefinitelyDoesNotExist.json";

	Metadata metadata(filename);
	try
	{
		metadata.Load();
		FAIL() << "Expected std::runtime_error";
	}
	catch(std::runtime_error const& err)
	{
		EXPECT_EQ(err.what(), std::string("File doesn't exist!"));
	}
	catch(...)
	{
		FAIL() << "Expected std::runtime_error";
	}
}

TEST(Metadata, Load_FileExist_Success)
{
	const std::string filename = root + "mocks/metadata/example.json";

	Metadata metadata(filename);
	try
	{
		metadata.Load();
	}
	catch (...)
	{
		char buffer[256];
		_getcwd(buffer, 256);

		FAIL() << "Expected successful load!\nFrom directory: " << buffer << "\nUnable to locate: " << filename;
	}
}

TEST(Metadata, Save_FileIsNotSpecified_ThrowException)
{
	const auto metadata = Metadata();
	try
	{
		metadata.Save();
		FAIL() << "Expected std::invalid_argument";
	}
	catch (std::invalid_argument const& err)
	{
		EXPECT_EQ(err.what(), std::string("File is not specified!"));
	}
	catch (...)
	{
		FAIL() << "Expected std::invalid_argument";
	}
}

TEST(Metadata, Save_OverridingProtectedFile_ThrowException)
{
	const std::string filename = root + "mocks/metadata/protected.json";
	
	const Metadata metadata(filename);
	try
	{
		metadata.Save(false);
		FAIL() << "Expected std::runtime_error";
	}
	catch (std::runtime_error const& err)
	{
		EXPECT_EQ(err.what(), std::string("An attempt of overriding protected file!"));
	}
	catch (...)
	{
		FAIL() << "Expected std::runtime_error";
	}
}

TEST(Metadata, Save_OverridingOverridableFile_Success)
{
	const std::string filename = root + "mocks/metadata/overridable.json";

	const Metadata metadata(filename);
	try
	{
		metadata.Save(true);
	}
	catch (...)
	{
		char buffer[256];
		_getcwd(buffer, 256);

		FAIL() << "Expected successful save!\nFrom directory: " << buffer << "\nUnable to locate: " << filename;
	}
}

TEST(Metadata, GetString_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";

	Metadata metadata(filename);
	metadata.Load();

	const auto result = metadata.GetString("string");
	EXPECT_EQ(result, "example");
}

TEST(Metadata, SetString_ExistingValueIsLoaded_Success)
{
	const std::string filename = root + "mocks/metadata/getters_and_setters.json";

	Metadata metadata(filename);

	metadata.Load();
	metadata.SetString("string", "unit_test");
	metadata.Save(true);

	metadata.Load();
	const auto result = metadata.GetString("string");
	EXPECT_EQ(result, "unit_test");

	metadata.SetString("string", "example");
	metadata.Save(true);
}