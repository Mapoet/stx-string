// $Id$

#include <cppunit/extensions/HelperMacros.h>

#include <stx-string.h>

class SimpleTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SimpleTest );
    CPPUNIT_TEST(test_trim);
    CPPUNIT_TEST(test_toupperlower);
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

    void test_toupperlower()
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
};

CPPUNIT_TEST_SUITE_REGISTRATION( SimpleTest );
