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