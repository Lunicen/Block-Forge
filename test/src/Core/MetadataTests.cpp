#include "../UnitTestsConfig.h"

// ReSharper disable once CppUnusedIncludeDirective
#include "Core/FileUtils.cpp"
#include "Core/Metadata.cpp"
#include "Core/Log.cpp"

namespace MetadataTests
{
	TEST(Metadata, Load_FileIsNotSpecified_FileIsNotLoaded)
	{
		auto metadata = Metadata();

		try
		{
	        metadata.Load();
	        FAIL() << "Expected UninitializedPropertyAccessException";
	    }
	    catch(const UninitializedPropertyAccessException& err)
		{
	        EXPECT_EQ(err.what(), std::string("File is not specified!"));
	    }
	    catch(...)
		{
	        FAIL() << "Expected UninitializedPropertyAccessException";
	    }
	}

	TEST(Metadata, Load_FileDoesNotExist_FileIsNotLoaded)
	{
		const std::string filename = "FileThatDefinitelyDoesNotExist.json";

		Metadata metadata(filename);

		try
		{
	        metadata.Load();
	        FAIL() << "Expected NotFoundException";
	    }
	    catch(const NotFoundException& err)
		{
	        EXPECT_EQ(err.what(), std::string("File " + filename + " doesn't exist!"));
	    }
	    catch(...)
		{
	        FAIL() << "Expected NotFoundException";
	    }
	}

	TEST(Metadata, Load_FileExist_Success)
	{
		const std::string filename = root + "mocks/metadata/example.json";

		Metadata metadata(filename);
		metadata.Load();

		try
		{
	        metadata.Load();
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
	        FAIL() << "Unexpected error.";
	    }
	}

	TEST(Metadata, Save_FileIsNotSpecified_Error)
	{
		const std::string filename;

		const Metadata metadata(filename);

		try
		{
	        metadata.Save();
	        FAIL() << "Expected UninitializedPropertyAccessException";
	    }
	    catch(const UninitializedPropertyAccessException& err)
		{
	        EXPECT_EQ(err.what(), std::string("File is not specified!"));
	    }
	    catch(...)
		{
	        FAIL() << "Expected UninitializedPropertyAccessException";
	    }
	}

	TEST(Metadata, IsNull_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);

		try
		{
	        metadata.Load();

			const auto result = metadata.IsNull("null");
			EXPECT_EQ(result, true);
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
	        FAIL() << "Unexpected error.";
	    }
	}

	TEST(Metadata, GetBool_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);

		try
		{
	        metadata.Load();

			const auto result = metadata.GetBool("bool");
			EXPECT_EQ(result, true);
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
	        FAIL() << "Unexpected error.";
	    }
	}

	TEST(Metadata, GetInt_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);
		
		try
		{
	        metadata.Load();
			
			const auto result = metadata.GetInt("int");
			EXPECT_EQ(result, 123);
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
	        FAIL() << "Unexpected error.";
	    }
	}

	TEST(Metadata, GetDouble_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);
		
		try
		{
	        metadata.Load();
			
			const auto result = metadata.GetDouble("double");
			EXPECT_EQ(result, 0.123);
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
	        FAIL() << "Unexpected error.";
	    }
	}

	TEST(Metadata, GetString_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";

		Metadata metadata(filename);
		
		try
		{
	        metadata.Load();
			
			const auto result = metadata.GetString("string");
			EXPECT_EQ(result, "example");
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
			FAIL() << "Unexpected error.";
		}
	}

	TEST(Metadata, SetNull_TheValueIsSetProperly_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_null";

		Metadata metadata(filename);

		try
		{
			metadata.Load();
			metadata.SetNull(key);
			metadata.Save();

			metadata.Load();
			const auto result = metadata.IsNull(key);
			EXPECT_EQ(result, true);

			metadata.SetInt(key, 0);
			metadata.Save();
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
			FAIL() << "Unexpected error.";
		}
	}

	TEST(Metadata, SetBool_TheValueIsSetProperly_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_bool";

		Metadata metadata(filename);

		try
		{
			metadata.Load();
			metadata.SetBool(key, true);
			metadata.Save();

			metadata.Load();
			const auto result = metadata.GetBool(key);
			EXPECT_EQ(result, true);

			metadata.SetNull(key);
			metadata.Save();
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
			FAIL() << "Unexpected error.";
		}
	}

	TEST(Metadata, SetInt_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_int";

		Metadata metadata(filename);
		
		try
		{
			metadata.Load();
			metadata.SetInt(key, 456);
			metadata.Save();

			metadata.Load();
			const auto result = metadata.GetInt(key);
			EXPECT_EQ(result, 456);

			metadata.SetNull(key);
			metadata.Save();
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
			FAIL() << "Unexpected error.";
		}
	}

	TEST(Metadata, SetDouble_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_double";

		Metadata metadata(filename);
		
		try
		{
			metadata.Load();
			metadata.SetDouble(key, 1.23);
			metadata.Save();

			metadata.Load();
			const auto result = metadata.GetDouble(key);
			EXPECT_EQ(result, 1.23);

			metadata.SetNull(key);
			metadata.Save();
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
			FAIL() << "Unexpected error.";
		}
	}

	TEST(Metadata, SetString_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";
		const std::string key = "set_string";

		Metadata metadata(filename);

		try
		{
			metadata.Load();
			metadata.SetString(key, "my test string");
			metadata.Save();

			metadata.Load();
			const auto result = metadata.GetString(key);
			EXPECT_EQ(result, "my test string");

			metadata.SetNull(key);
			metadata.Save();
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
			FAIL() << "Unexpected error.";
		}
	}

	TEST(Metadata, SetObject_ExistingValueIsLoaded_Success)
	{
		const std::string filename = root + "mocks/metadata/getters_and_setters.json";
		const std::string objectName = "set_object";

		nlohmann::json myTestObject;
		myTestObject["testBoolValue"] = true;
		myTestObject["testIntValue"] = 99;
		myTestObject["testNegativeIntValue"] = -1;
		myTestObject["testDoubleValue"] = 10.0001;

		Metadata metadata(filename);
		
		try
		{
			metadata.Load();
			metadata.SetJsonObject(objectName, myTestObject);
			metadata.Save();

			metadata.Load();
			const auto result = metadata.GetJsonObject(objectName);
			EXPECT_EQ(result, myTestObject);

			metadata.SetNull(objectName);
			metadata.Save();
	    }
	    catch(const EngineException& e)
		{
	        FAIL() << e.what();
	    }
		catch(...)
		{
			FAIL() << "Unexpected error.";
		}
		
	}
}
