// $Id$

#include <stx-string.h>
#include <stdlib.h>

#include <cppunit/extensions/HelperMacros.h>

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
    CPPUNIT_TEST(test_random);
    CPPUNIT_TEST(test_hexdump);
    CPPUNIT_TEST(test_base64);
    CPPUNIT_TEST(test_levenshtein);
    CPPUNIT_TEST_SUITE_END();

protected:

    void test_trim()
    {
	// string-copy functions
	CPPUNIT_ASSERT( stx::string("  abc  ").trim_left() == "abc  " );
	CPPUNIT_ASSERT( stx::string("abc  ").trim_left() == "abc  " );
	CPPUNIT_ASSERT( stx::string("  ").trim_left() == "" );

	CPPUNIT_ASSERT( stx::string("  abc  ").trim_right() == "  abc" );
	CPPUNIT_ASSERT( stx::string("  abc").trim_right() == "  abc" );
	CPPUNIT_ASSERT( stx::string("  ").trim_right() == "" );

	CPPUNIT_ASSERT( stx::string("  abc  ").trim() == "abc" );
	CPPUNIT_ASSERT( stx::string("abc  ").trim() == "abc" );
	CPPUNIT_ASSERT( stx::string("  abc").trim() == "abc" );
	CPPUNIT_ASSERT( stx::string("  ").trim() == "" );

	// in-place functions
	stx::string str1 = "  abc  ";
	stx::string str2 = "abc  ";
	stx::string str3 = "  ";

	CPPUNIT_ASSERT( str1.trim_left_inplace() == "abc  " );
	CPPUNIT_ASSERT( str2.trim_left_inplace() == "abc  " );
	CPPUNIT_ASSERT( str3.trim_left_inplace() == "" );

	str1 = "  abc  ";
	str2 = "  abc";
	str3 = "  ";


	CPPUNIT_ASSERT( str1.trim_right_inplace() == "  abc" );
	CPPUNIT_ASSERT( str2.trim_right_inplace() == "  abc" );
	CPPUNIT_ASSERT( str3.trim_right_inplace() == "" );

	str1 = "  abc  ";
	str2 = "  abc";
	str3 = "abc  ";
	stx::string str4 = "  ";

	CPPUNIT_ASSERT( str1.trim_inplace() == "abc" );
	CPPUNIT_ASSERT( str2.trim_inplace() == "abc" );
	CPPUNIT_ASSERT( str3.trim_inplace() == "abc" );
	CPPUNIT_ASSERT( str4.trim_inplace() == "" );
    }

    void test_toupper_tolower()
    {
	// string-copy functions
	CPPUNIT_ASSERT( stx::string(" aBc ").toupper() == " ABC " );
	CPPUNIT_ASSERT( stx::string(" AbCdEfG ").tolower() == " abcdefg " );

	// in-place functions
	stx::string str1 = "  aBc  ";
	stx::string str2 = "AbCdEfGh ";

	CPPUNIT_ASSERT( str1.toupper_inplace() == "  ABC  " );
	CPPUNIT_ASSERT( str2.tolower_inplace() == "abcdefgh " );
    }

    void test_compare_icase()
    {
	CPPUNIT_ASSERT( stx::string("ABC") != stx::string("abc") );

	CPPUNIT_ASSERT( stx::string("ABC").equal_icase("abc") );
	CPPUNIT_ASSERT( !stx::string("ABC").equal_icase("abd") );
	CPPUNIT_ASSERT( !stx::string("ABC").equal_icase("abcedf") );

	CPPUNIT_ASSERT( stx::string("ABC") < stx::string("abc") );
	CPPUNIT_ASSERT( !stx::string("ABC").less_icase("abc") );
	CPPUNIT_ASSERT( stx::string("abc").less_icase("abcdef") );
	CPPUNIT_ASSERT( !stx::string("abcdef").less_icase("abcd") );
    }

    void test_prefix_suffix()
    {
	CPPUNIT_ASSERT( stx::string("abcdef").is_prefix("abc") );
	CPPUNIT_ASSERT( ! stx::string("abcdef").is_prefix("def") );
	CPPUNIT_ASSERT( stx::string("abcdef").is_suffix("def") );
	CPPUNIT_ASSERT( ! stx::string("abcdef").is_suffix("abc") );

	CPPUNIT_ASSERT( ! stx::string("abcdef").is_prefix("ABC") );

	CPPUNIT_ASSERT( stx::string("abcdef").is_prefix_icase("ABC") );
	CPPUNIT_ASSERT( ! stx::string("abcdef").is_prefix_icase("DEF") );
	CPPUNIT_ASSERT( stx::string("abcdef").is_suffix_icase("DEF") );
	CPPUNIT_ASSERT( ! stx::string("abcdef").is_suffix_icase("ABC") );

	CPPUNIT_ASSERT( stx::string("abcdef").is_prefix("") );
	CPPUNIT_ASSERT( stx::string("abcdef").is_suffix("") );

	CPPUNIT_ASSERT( ! stx::string("").is_prefix("abc") );
	CPPUNIT_ASSERT( ! stx::string("").is_suffix("abc") );

	CPPUNIT_ASSERT( stx::string("").is_prefix("") );
	CPPUNIT_ASSERT( stx::string("").is_suffix("") );
    }

    void test_replace()
    {
	// copy variants
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first("abc", "a") == "adef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first("cba", "a") == "abcdef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all("abc", "a") == "adef adef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all("cba", "a") == "abcdef abcdef" );

	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first("a", "aaa") == "aaabcdef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all("a", "aaa") == "aaabcdef aaabcdef" );

	// in-place variants
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first_inplace("abc", "a") == "adef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first_inplace("cba", "a") == "abcdef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all_inplace("abc", "a") == "adef adef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all_inplace("cba", "a") == "abcdef abcdef" );

	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_first_inplace("a", "aaa") == "aaabcdef abcdef" );
	CPPUNIT_ASSERT( stx::string("abcdef abcdef").replace_all_inplace("a", "aaa") == "aaabcdef aaabcdef" );
    }

    void test_split_ws()
    {
	// simple whitespace split
	std::vector<std::string> sv = stx::string("  ab c df  fdlk f  ").split_ws();

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string("ab c df  fdlk f  ").split_ws();

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string("ab c df  fdlk f").split_ws();

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	sv = stx::string("").split_ws();
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string("    ").split_ws();
	CPPUNIT_ASSERT( sv.size() == 0 );

	// whitespace split with limit
	sv = stx::string("  ab c   df  fdlk f  ").split_ws(3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df  fdlk f  " );

	// whitespace split with some strange limits
	sv = stx::string("  ab c df  fdlk f  ").split_ws(0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string("  ab c df  fdlk f  ").split_ws(1);

	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "ab c df  fdlk f  " );

	// whitespace split with large limit
	sv = stx::string("  ab  c  df  fdlk f  ").split_ws(10);

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f" );

	// whitespace split with limit at exactly the end
	sv = stx::string("  ab  c  df  fdlk f  ").split_ws(5);

	CPPUNIT_ASSERT( sv.size() == 5 );
	CPPUNIT_ASSERT( sv[0] == "ab" && sv[1] == "c" && sv[2] == "df" && sv[3] == "fdlk" && sv[4] == "f  " );
    }

    void test_split()
    {
	// simple char split
	std::vector<std::string> sv = stx::string("/usr/bin/test").split('/');

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin" && sv[3] == "test" );

	sv = stx::string("/usr/bin/test").split('/', 3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin/test" );

	// char split with some strange limits
	sv = stx::string("/usr//bin/test").split('/', 0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string("/usr//bin/test").split('/', 1);
	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "/usr//bin/test" );

	// simple str split
	sv = stx::string("/usr/bin/test").split("/");

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin" && sv[3] == "test" );

	sv = stx::string("/usr/bin/test").split("/", 3);

	CPPUNIT_ASSERT( sv.size() == 3 );
	CPPUNIT_ASSERT( sv[0] == "" && sv[1] == "usr" && sv[2] == "bin/test" );

	// str split with some strange limits
	sv = stx::string("/usr//bin/test").split("/", 0);
	CPPUNIT_ASSERT( sv.size() == 0 );

	sv = stx::string("/usr//bin/test").split("/", 1);
	CPPUNIT_ASSERT( sv.size() == 1 );
	CPPUNIT_ASSERT( sv[0] == "/usr//bin/test" );

	sv = stx::string("/usr/bin/test").split("");
	CPPUNIT_ASSERT( sv.size() == 0 );

	// str split with parital needle at end
	sv = stx::string("testabcblahabcabcab").split("abc");

	CPPUNIT_ASSERT( sv.size() == 4 );
	CPPUNIT_ASSERT( sv[0] == "test" && sv[1] == "blah" && sv[2] == "" && sv[3] == "ab" );
    }

    void test_join()
    {
	// simple string split and join
	std::vector<std::string> sv = stx::string("/usr/bin/test").split('/');
	CPPUNIT_ASSERT( sv.size() == 4 );

	CPPUNIT_ASSERT( stx::string::join("--", sv) == "--usr--bin--test" );
	CPPUNIT_ASSERT( stx::string(";").join(sv) == ";usr;bin;test" );

	std::vector<stx::string> sv2;
	for(unsigned int i = 0; i < 6; ++i)
	    sv2.push_back("abc");

	CPPUNIT_ASSERT( stx::string(".").join(sv2) == "abc.abc.abc.abc.abc.abc" );
    }

    void test_random()
    {
	srand( time(NULL) );

	stx::string rand1 = stx::string::random_binary(42);
	stx::string rand2 = stx::string::random_alpha(42);
	stx::string rand3 = stx::string::random_alphanumeric(42);

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

	stx::string hexdata(hexdump, 8);
	stx::string hexstring = hexdata.hexdump();

	CPPUNIT_ASSERT( hexstring == "8DE285D4BF98E603" );

	stx::string hexparsed = hexstring.parse_hexdump();
	CPPUNIT_ASSERT( hexparsed == hexdata );

	// dump random binary string into hex and parse it back
	stx::string rand1 = stx::string::random_binary(42);
	CPPUNIT_ASSERT( rand1.hexdump().parse_hexdump() == rand1 );

	// take the first hex list and dump it into source code format, then
	// compare it with correct data (which was also dumped with
	// hexdump_sourcecode())
	stx::string hexsource = hexdata.hexdump_sourcecode("abc");

	const char hexsourcecmp[65] = {
	    0x63,0x6F,0x6E,0x73,0x74,0x20,0x63,0x68,0x61,0x72,0x20,0x61,0x62,0x63,0x5B,0x38,
	    0x5D,0x20,0x3D,0x20,0x7B,0x0A,0x30,0x78,0x38,0x44,0x2C,0x30,0x78,0x45,0x32,0x2C,
	    0x30,0x78,0x38,0x35,0x2C,0x30,0x78,0x44,0x34,0x2C,0x30,0x78,0x42,0x46,0x2C,0x30,
	    0x78,0x39,0x38,0x2C,0x30,0x78,0x45,0x36,0x2C,0x30,0x78,0x30,0x33,0x0A,0x7D,0x3B,
	    0x0A
	};

	CPPUNIT_ASSERT( hexsource == std::string(hexsourcecmp, sizeof(hexsourcecmp)) );

	// test parse_hexdump with illegal string
	stx::string s1;
	CPPUNIT_ASSERT_THROW( s1.parse_hexdump("illegal"), std::runtime_error);
    }

    void test_base64()
    {
	// take some static hex data and dump it using base64 encoding, then decode it again.
	const char rand1data[42] = {
	    0x16,0x35,0xCA,0x03,0x90,0x6B,0x47,0x11,0x85,0x02,0xE7,0x40,0x9E,0x3A,0xCE,0x43,
	    0x0C,0x57,0x3E,0x35,0xE7,0xA6,0xB2,0x37,0xEC,0x6D,0xF6,0x68,0xF6,0x0E,0x74,0x0C,
	    0x44,0x3F,0x0F,0xD4,0xAA,0x56,0xE5,0x2F,0x58,0xCC
	};

	stx::string rand1(rand1data, sizeof(rand1data));

	stx::string rand1base64 = rand1.base64_encode();

	CPPUNIT_ASSERT( rand1base64 == "FjXKA5BrRxGFAudAnjrOQwxXPjXnprI37G32aPYOdAxEPw/UqlblL1jM" );

	CPPUNIT_ASSERT( rand1base64.base64_decode(1) == rand1 );

	// check line-splitting
	stx::string rand1base64lines = rand1.base64_encode(16);

	CPPUNIT_ASSERT( rand1base64lines == "FjXKA5BrRxGFAudA\n" "njrOQwxXPjXnprI3\n" "7G32aPYOdAxEPw/U\n" "qlblL1jM" );

	// take three random binary data string with different sizes and run
	// the base64 encoding->decoding->checking drill.

	stx::string rand12 = stx::string::random_binary(12);
	CPPUNIT_ASSERT( rand12.base64_encode().base64_decode(1) == rand12 );

	stx::string rand13 = stx::string::random_binary(13);
	CPPUNIT_ASSERT( rand13.base64_encode().base64_decode(1) == rand13 );

	stx::string rand14 = stx::string::random_binary(14);
	CPPUNIT_ASSERT( rand14.base64_encode().base64_decode(1) == rand14 );

	// run a larger set of random tests
	for (unsigned int ti = 0; ti < 1000; ++ti)
	{
	    unsigned int randlen = ti; // rand() % 1000;
	    stx::string randstr = stx::string::random_binary(randlen);

	    CPPUNIT_ASSERT( randstr.base64_encode().base64_decode(1) == randstr );
	}

	CPPUNIT_ASSERT_THROW( stx::string("FjXKA5!!RxGFAudA").base64_decode(1), std::runtime_error );
    }

    void test_levenshtein()
    {
	CPPUNIT_ASSERT( stx::string::levenshtein("Demonstration", "Comparison") == 9 );
	CPPUNIT_ASSERT( stx::string::levenshtein("Levenshtein", "Distance") == 10 );
	CPPUNIT_ASSERT( stx::string::levenshtein("Distance", "Distance") == 0 );
	CPPUNIT_ASSERT( stx::string("Distance").levenshtein("LVDistance") == 2 );

	CPPUNIT_ASSERT( stx::string::levenshtein_icase("distance", "DISTANCE") == 0 );
	CPPUNIT_ASSERT( stx::string::levenshtein_icase("Levenshtein", "Distance") == 10 );

	CPPUNIT_ASSERT( stx::string("Test this distance").levenshtein_icase("to this one") == 9 );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( SimpleTest );
