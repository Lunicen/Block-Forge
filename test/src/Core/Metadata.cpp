#include "gtest/gtest.h"
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
	const std::string filename = "./mocks/example.json";

	Metadata metadata(filename);
	try
	{
		metadata.Load();
	}
	catch (...)
	{
		FAIL() << "Expected successful load!";
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
	const std::string filename = "./mocks/example.json";

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
	const std::string filename = "./mocks/example.json";

	const Metadata metadata(filename);
	try
	{
		metadata.Save(true);
	}
	catch (...)
	{
		FAIL() << "Expected successful save!";
	}
}