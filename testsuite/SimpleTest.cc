// $Id$

#include <cppunit/extensions/HelperMacros.h>

#include <stx-string.h>
#include <stdlib.h>

class SimpleTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SimpleTest );
    CPPUNIT_TEST(test_trim);
    CPPUNIT_TEST(test_toupper_tolower);
    CPPUNIT_TEST(test_compare_icase);
    CPPUNIT_TEST(test_prefix_suffix);
    CPPUNIT_TEST(test_replace);
    CPPUNIT_TEST(test_split_ws);
    CPPUNIT_TEST(test_split);
    CPPUNIT_TEST(test_join);
    CPPUNIT_TEST(test_contains);
    CPPUNIT_TEST(test_random);
    CPPUNIT_TEST(test_hexdump);
    CPPUNIT_TEST(test_base64);
    CPPUNIT_TEST(test_levenshtein);
    CPPUNIT_TEST_SUITE_END();

protected:

    void test_trim()
    {
	// string-copy functions
	CPPUNIT_ASSERT( stx::string::trim_left("  abc  ") == "abc  " );
	CPPUNIT_ASSERT( stx::string::trim_left("abc  ") == "abc  " );
	CPPUNIT_ASSERT( stx::string::trim_left("  ") == "" );

	CPPUNIT_ASSERT( stx::string::trim_right("  abc  ") == "  abc" );
	CPPUNIT_ASSERT( stx::string::trim_right("  abc") == "  abc" );
	CPPUNIT_ASSERT( stx::string::trim_right("  ") == "" );

	CPPUNIT_ASSERT( stx::string::trim("  abc  ") == "abc" );
	CPPUNIT_ASSERT( stx::string::trim("abc  ") == "abc" );
	CPPUNIT_ASSERT( stx::string::trim("  abc") == "abc" );
	CPPUNIT_ASSERT( stx::string::trim("  ") == "" );

	// in-place functions
	std::string str1 = "  abc  ";
	std::string str2 = "abc  ";
	std::string str3 = "  ";

	CPPUNIT_ASSERT( stx::string::trim_left_inplace(str1) == "abc  " );
	CPPUNIT_ASSERT( stx::string::trim_left_inplace(str2) == "abc  " );
	CPPUNIT_ASSERT( stx::string::trim_left_inplace(str3) == "" );

	str1 = "  abc  ";
	str2 = "  abc";
	str3 = "  ";

	CPPUNIT_ASSERT( stx::string::trim_right_inplace(str1) == "  abc" );
	CPPUNIT_ASSERT( stx::string::trim_right_inplace(str2) == "  abc" );
	CPPUNIT_ASSERT( stx::string::trim_right_inplace(str3) == "" );

	str1 = "  abc  ";
	str2 = "  abc";
	str3 = "abc  ";
	std::string str4 = "  ";

	CPPUNIT_ASSERT( stx::string::trim_inplace(str1) == "abc" );
	CPPUNIT_ASSERT( stx::string::trim_inplace(str2) == "abc" );
	CPPUNIT_ASSERT( stx::string::trim_inplace(str3) == "abc" );
	CPPUNIT_ASSERT( stx::string::trim_inplace(str4) == "" );
    }

    void test_toupper_tolower()
    {
	// string-copy functions
	CPPUNIT_ASSERT( stx::string::toupper(" aBc ") == " ABC " );
	CPPUNIT_ASSERT( stx::string::tolower(" AbCdEfG ") == " abcdefg " );

	// in-place functions
	std::string str1 = "  aBc  ";
	std::string str2 = "AbCdEfGh ";

	CPPUNIT_ASSERT( stx::string::toupper_inplace(str1) == "  ABC  " );
	CPPUNIT_ASSERT( stx::string::tolower_inplace(str2) == "abcdefgh " );
    }

    void test_compare_icase()
    {
	CPPUNIT_ASSERT( std::string("ABC") != std::string("abc") );

	CPPUNIT_ASSERT( stx::string::equal_icase("ABC", "abc") );
	CPPUNIT_ASSERT( !stx::string::equal_icase("ABC", "abd") );
	CPPUNIT_ASSERT( !stx::string::equal_icase("ABC", "abcedf") );

	CPPUNIT_ASSERT( std::string("ABC") < std::string("abc") );
	CPPUNIT_ASSERT( !stx::string::less_icase("ABC", "abc") );
	CPPUNIT_ASSERT( stx::string::less_icase("abc", "abcdef") );
	CPPUNIT_ASSERT( !stx::string::less_icase("abcdef", "abcd") );

	CPPUNIT_ASSERT( stx::string::compare_icase("ABC", "abc") == 0 );
	CPPUNIT_ASSERT( stx::string::compare_icase("ABC", "abd") < 0  );
	CPPUNIT_ASSERT( stx::string::compare_icase("ABC", "abb") > 0  );
    }

    void test_prefix_suffix()
    {
	CPPUNIT_ASSERT( stx::string::is_prefix("abcdef", "abc") );
	CPPUNIT_ASSERT( ! stx::string::is_prefix("abcdef", "def") );
	CPPUNIT_ASSERT( stx::string::is_suffix("abcdef", "def") );
	CPPUNIT_ASSERT( ! stx::string::is_suffix("abcdef", "abc") );

	CPPUNIT_ASSERT( ! stx::string::is_prefix("abcdef", "ABC") );

	CPPUNIT_ASSERT( stx::string::is_prefix_icase("abcdef", "ABC") );
	CPPUNIT_ASSERT( ! stx::string::is_prefix_icase("abcdef", "DEF") );
	CPPUNIT_ASSERT( stx::string::is_suffix_icase("abcdef", "DEF") );
	CPPUNIT_ASSERT( ! stx::string::is_suffix_icase("abcdef", "ABC") );

	CPPUNIT_ASSERT( stx::string::is_prefix("abcdef", "") );
	CPPUNIT_ASSERT( stx::string::is_suffix("abcdef", "") );

	CPPUNIT_ASSERT( ! stx::string::is_prefix("", "abc") );
	CPPUNIT_ASSERT( ! stx::string::is_suffix("", "abc") );

	CPPUNIT_ASSERT( stx::string::is_prefix("", "") );
	CPPUNIT_ASSERT( stx::string::is_suffix("", "") );
    }

    void test_replace()
    {
	// copy variants
	CPPUNIT_ASSERT( stx::string::replace_first("abcdef abcdef", "abc", "a") == "adef abcdef" );
	CPPUNIT_ASSERT( stx::string::replace_first("abcdef abcdef", "cba", "a") == "abcdef abcdef" );
	CPPUNIT_ASSERT( stx::string::replace_all("abcdef abcdef", "abc", "a") == "adef adef" );
	CPPUNIT_ASSERT( stx::string::replace_all("abcdef abcdef", "cba", "a") == "abcdef abcdef" );

	CPPUNIT_ASSERT( stx::string::replace_first("abcdef abcdef", "a", "aaa") == "aaabcdef abcdef" );
	CPPUNIT_ASSERT( stx::string::replace_all("abcdef abcdef", "a", "aaa") == "aaabcdef aaabcdef" );

	// in-place variants
	std::string str1 = "abcdef abcdef";
	std::string str2 = "abcdef abcdef";
	CPPUNIT_ASSERT( stx::string::replace_first_inplace(str1, "abc", "a") == "adef abcdef" );
	CPPUNIT_ASSERT( stx::string::replace_first_inplace(str2, "cba", "a") == "abcdef abcdef" );

	str1 = "abcdef abcdef";
	str2 = "abcdef abcdef";
	CPPUNIT_ASSERT( stx::string::replace_all_inplace(str1, "abc", "a") == "adef adef" );
	CPPUNIT_ASSERT( stx::string::replace_all_inplace(str2, "cba", "a") == "abcdef abcdef" );

	str1 = "abcdef abcdef";
	str2 = "abcdef abcdef";
	CPPUNIT_ASSERT( stx::string::replace_first_inplace(str1, "a", "aaa") == "aaabcdef abcdef" );
	CPPUNIT_ASSERT( stx::string::replace_all_inplace(str2, "a", "aaa") == "aaabcdef aaabcdef" );
    }

    void test_split_ws()
    {
	// simple whitespace split
	std::vector<std::string> sv = stx::string::split_ws("  ab c df  fdlk f  ");

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string::split_ws("ab c df  fdlk f  ");

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string::split_ws("ab c df  fdlk f");

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string::split_ws("");
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string::split_ws("    ");
	CPPUNIT_ASSERT( sv.size() == 0 );

	// whitespace split with limit
	sv = stx::string::split_ws("  ab c   df  fdlk f  ", 3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df  fdlk f  " );

	// whitespace split with some strange limits
	sv = stx::string::split_ws("  ab c df  fdlk f  ", 0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string::split_ws("  ab c df  fdlk f  ", 1);

	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "ab c df  fdlk f  " );

	// whitespace split with large limit
	sv = stx::string::split_ws("  ab  c  df  fdlk f  ", 10);

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	// whitespace split with limit at exactly the end
	sv = stx::string::split_ws("  ab  c  df  fdlk f  ", 5);

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f  " );
    }

    void test_split()
    {
	// simple char split
	std::vector<std::string> sv = stx::string::split("/usr/bin/test", '/');

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin" && sv[3] == "test" );

	sv = stx::string::split("/usr/bin/test", '/', 3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin/test" );

	// char split with some strange limits
	sv = stx::string::split("/usr//bin/test", '/', 0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string::split("/usr//bin/test", '/', 1);
	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "/usr//bin/test" );

	// simple str split
	sv = stx::string::split("/usr/bin/test", "/");

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin" && sv[3] == "test" );

	sv = stx::string::split("/usr/bin/test", "/", 3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin/test" );

	// str split with some strange limits
	sv = stx::string::split("/usr//bin/test", "/", 0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string::split("/usr//bin/test", "/", 1);
	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "/usr//bin/test" );

	sv = stx::string::split("/usr/bin/test", "");
	CPPUNIT_ASSERT( sv.size() == 0 );

	// str split with parital needle at end
	sv = stx::string::split("testabcblahabcabcab", "abc");

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "test" && sv[1] == "blah" && sv[2] == "" && sv[3] == "ab" );
    }

    void test_join()
    {
	// simple string split and join
	std::vector<std::string> sv = stx::string::split("/usr/bin/test", '/');
	CPPUNIT_ASSERT( sv.size() == 4 );

	CPPUNIT_ASSERT( stx::string::join("--", sv) == "--usr--bin--test" );
	CPPUNIT_ASSERT( stx::string::join(";", sv) == ";usr;bin;test" );

	std::vector<std::string> sv2;
	for(unsigned int i = 0; i < 6; ++i)
	    sv2.push_back("abc");

	CPPUNIT_ASSERT( stx::string::join(".", sv2) == "abc.abc.abc.abc.abc.abc" );
    }

    void test_contains()
    {
	std::string data = "test admin write readall read do";
	
	CPPUNIT_ASSERT( stx::string::contains_word(data, "test") );
	CPPUNIT_ASSERT( !stx::string::contains_word(data, "testit") );

	CPPUNIT_ASSERT( stx::string::contains_word(data, "read") );
	CPPUNIT_ASSERT( stx::string::contains_word(data, "readall") );

	CPPUNIT_ASSERT( !stx::string::contains_word(data, "doit") );
    }

    void test_random()
    {
	srand( time(NULL) );

	std::string rand1 = stx::string::random_binary(42);
	std::string rand2 = stx::string::random_alpha(42);
	std::string rand3 = stx::string::random_alphanumeric(42);

	CPPUNIT_ASSERT( rand1.size() == 42 );

	CPPUNIT_ASSERT( rand2.size() == 42 );
	for(unsigned int i = 0; i < rand2.size(); ++i) {
	    CPPUNIT_ASSERT( isalpha(rand2[i]) );
	}

	CPPUNIT_ASSERT( rand3.size() == 42 );
	for(unsigned int i = 0; i < rand3.size(); ++i) {
	    CPPUNIT_ASSERT( isalnum(rand3[i]) );
	}
    }

    void test_hexdump()
    {
	// take hex data and dump it into a string, then parse back into array
	const char hexdump[8] = { 0x8D,0xE2,0x85,0xD4,0xBF,0x98,0xE6,0x03 };

	std::string hexdata(hexdump, 8);
	std::string hexstring = stx::string::hexdump(hexdata);

	CPPUNIT_ASSERT( hexstring == "8DE285D4BF98E603" );

	std::string hexparsed = stx::string::parse_hexdump(hexstring);
	CPPUNIT_ASSERT( hexparsed == hexdata );

	// dump random binary string into hex and parse it back
	std::string rand1 = stx::string::random_binary(42);
	CPPUNIT_ASSERT( stx::string::parse_hexdump( stx::string::hexdump(rand1) ) == rand1 );

	// take the first hex list and dump it into source code format, then
	// compare it with correct data (which was also dumped with
	// hexdump_sourcecode())
	std::string hexsource = stx::string::hexdump_sourcecode(hexdata, "abc");

	const char hexsourcecmp[65] = {
	    0x63,0x6F,0x6E,0x73,0x74,0x20,0x63,0x68,0x61,0x72,0x20,0x61,0x62,0x63,0x5B,0x38,
	    0x5D,0x20,0x3D,0x20,0x7B,0x0A,0x30,0x78,0x38,0x44,0x2C,0x30,0x78,0x45,0x32,0x2C,
	    0x30,0x78,0x38,0x35,0x2C,0x30,0x78,0x44,0x34,0x2C,0x30,0x78,0x42,0x46,0x2C,0x30,
	    0x78,0x39,0x38,0x2C,0x30,0x78,0x45,0x36,0x2C,0x30,0x78,0x30,0x33,0x0A,0x7D,0x3B,
	    0x0A
	};

	CPPUNIT_ASSERT( hexsource == std::string(hexsourcecmp, sizeof(hexsourcecmp)) );

	// test parse_hexdump with illegal string
	CPPUNIT_ASSERT_THROW( stx::string::parse_hexdump("illegal"), std::runtime_error);
    }

    void test_base64()
    {
	// take some static hex data and dump it using base64 encoding, then decode it again.
	const char rand1data[42] = {
	    0x16,0x35,0xCA,0x03,0x90,0x6B,0x47,0x11,0x85,0x02,0xE7,0x40,0x9E,0x3A,0xCE,0x43,
	    0x0C,0x57,0x3E,0x35,0xE7,0xA6,0xB2,0x37,0xEC,0x6D,0xF6,0x68,0xF6,0x0E,0x74,0x0C,
	    0x44,0x3F,0x0F,0xD4,0xAA,0x56,0xE5,0x2F,0x58,0xCC
	};

	std::string rand1(rand1data, sizeof(rand1data));

	std::string rand1base64 = stx::string::base64_encode(rand1);

	CPPUNIT_ASSERT( rand1base64 == "FjXKA5BrRxGFAudAnjrOQwxXPjXnprI37G32aPYOdAxEPw/UqlblL1jM" );

	CPPUNIT_ASSERT( stx::string::base64_decode(rand1base64, 1) == rand1 );

	// check line-splitting
	std::string rand1base64lines = stx::string::base64_encode(rand1, 16);

	CPPUNIT_ASSERT( rand1base64lines == "FjXKA5BrRxGFAudA\n" "njrOQwxXPjXnprI3\n" "7G32aPYOdAxEPw/U\n" "qlblL1jM" );

	// take three random binary data string with different sizes and run
	// the base64 encoding->decoding->checking drill.

	std::string rand12 = stx::string::random_binary(12);
	CPPUNIT_ASSERT( stx::string::base64_decode( stx::string::base64_encode(rand12) , 1) == rand12 );

	std::string rand13 = stx::string::random_binary(13);
	CPPUNIT_ASSERT( stx::string::base64_decode( stx::string::base64_encode(rand13) , 1) == rand13 );

	std::string rand14 = stx::string::random_binary(14);
	CPPUNIT_ASSERT( stx::string::base64_decode( stx::string::base64_encode(rand14) , 1) == rand14 );

	// run a larger set of random tests
	for (unsigned int ti = 0; ti < 1000; ++ti)
	{
	    unsigned int randlen = ti; // rand() % 1000;
	    std::string randstr = stx::string::random_binary(randlen);

	    CPPUNIT_ASSERT( stx::string::base64_decode( stx::string::base64_encode(randstr) , 1) == randstr );
	}

	CPPUNIT_ASSERT_THROW( stx::string::base64_decode("FjXKA5!!RxGFAudA", 1), std::runtime_error );
    }

    void test_levenshtein()
    {
	CPPUNIT_ASSERT( stx::string::levenshtein("Demonstration", "Comparison") == 9 );
	CPPUNIT_ASSERT( stx::string::levenshtein("Levenshtein", "Distance") == 10 );
	CPPUNIT_ASSERT( stx::string::levenshtein("Distance", "Distance") == 0 );
	CPPUNIT_ASSERT( stx::string::levenshtein("Distance", "LVDistance") == 2 );

	CPPUNIT_ASSERT( stx::string::levenshtein_icase("distance", "DISTANCE") == 0 );
	CPPUNIT_ASSERT( stx::string::levenshtein_icase("Levenshtein", "Distance") == 10 );

	CPPUNIT_ASSERT( stx::string::levenshtein_icase("Test this distance", "to this one") == 9 );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( SimpleTest );
