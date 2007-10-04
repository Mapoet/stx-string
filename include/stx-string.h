// $Id$

#ifndef _STX_STRING_H_ 
#define _STX_STRING_H_

#include <string>
#include <cctype>

namespace stx {

class string : public std::string
{
public:

    /** Default constructor. Creates an empty string. */
    string()
	: std::string()
    {
    }

    /** Copy-Constructor. Duplicates the enclosed STL string. */
    string(const string &s)
	: std::string(s)
    {
    }

    /** Automatic Type-cast Constructor. Duplicates the given STL string. */
    string(const std::string &s)
	: std::string(s)
    {
    }

    /** Repeating constructor. Creates a string which contains the charater ch
     * repeated length times. */
    string(size_type length, const char& ch)
	: std::string(length, ch)
    {
    }

    /** C-style string constructor. Fills the new string with the given C-style
     * string. */
    string(const char* str)
	: std::string(str)
    {
    }

    /** C-style string constructor with length. Fills the new string with data
     * of length bytes. */
    string(const char* str, size_type length)
	: std::string(str, length)
    {
    }

    /** Substring constructor. Creates a new string containing the substring
     * specified by index and length. */
    string(const string& str, size_type index, size_type length)
	: std::string(str, index, length)
    {
    }
    
    /** Template-Iterator range constructor. Fills the new string with the
     * character in the start-end range. */
    template <typename input_iterator>
    string(input_iterator start, input_iterator end)
	: std::string(start, end)
    {
    }

    /*
     * --- Trim Functions ---
     */

    /** Trims the contained string on the left and right. Removes all
     * characters in the given drop array, which defaults to " ". Returns a
     * copy of this string.
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim(const string& drop = " ") const
    {
	size_type pos1 = find_first_not_of(drop);
	if (pos1 == npos) return string();

	size_type pos2 = find_last_not_of(drop);
	if (pos2 == npos) return string();

	return substr(pos1 == npos ? 0 : pos1,
		      pos2 == npos ? (size() - 1) : (pos2 - pos1 + 1));
    }

    /** Trims the contained string only on the left. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of this
     * string.
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim_left(const string& drop = " ") const
    {
	size_type pos = find_first_not_of(drop);
	if (pos == npos) return string();

	return substr(pos, npos);
    }

    /** Trims the contained string only on the right. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of this
     * string.
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim_right(const string& drop = " ") const
    {
	size_type pos = find_last_not_of(drop);
	if (pos == npos) return string();

	return substr(0, pos + 1);
    }

    /** Trims this string in-place on the left and right. Removes all
     * characters in the given drop array, which defaults to " ".
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_inplace(const string& drop = " ")
    {
	size_type pos = find_last_not_of(drop);
	if (pos != npos) {
	    erase(pos + 1);
	    pos = find_first_not_of(drop);
	    if (pos != npos) erase(0, pos);
	}
	else
	    erase(begin(), end());

	return *this;
    }

    /** Trims this string in-place only on the left. Removes all characters in
     * the given drop array, which defaults to " ".
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_left_inplace(const string &drop = " ")
    {
	erase(0, find_first_not_of(drop));
	return *this;
    }

    /** Trims this string in-place only on the right. Removes all characters in
     * the given drop array, which defaults to " ".
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_right_inplace(const string &drop = " ")
    {
	erase(find_last_not_of(drop) + 1, npos);
	return *this;
    }

    /*
     * --- Upper and Lower Case Functions ---
     */

    /** toupper() functional for std::transform with correct signature. */
    static char char_toupper_functional(char c)
    {
	return std::toupper(c);
    }

    /** tolower() functional for std::transform with correct signature. */
    static char char_tolower_functional(char c)
    {
	return std::tolower(c);
    }

    /** Returns a copy of the enclosed string converted to uppercase. */
    string toupper() const
    {
	string strcopy(size(), 0);
	std::transform(begin(), end(), strcopy.begin(), char_toupper_functional);
	return strcopy;
    }

    /** Returns a copy of the enclosed string converted to lowercase. */
    string tolower() const
    {
	string strcopy(size(), 0);
	std::transform(begin(), end(), strcopy.begin(), char_tolower_functional);
	return strcopy;
    }

    /** Transforms the enclosed string to uppercase and returns a reference to
     * this. */
    string& toupper_inplace()
    {
	std::transform(begin(), end(), begin(), char_toupper_functional);
	return *this;
    }

    /** Transforms the enclosed string to lowercase and returns a reference to
     * this. */
    string& tolower_inplace()
    {
	std::transform(begin(), end(), begin(), char_tolower_functional);
	return *this;
    }

    /*
     * --- Case-insensitive Comparision Functionals and Functions ---
     */

    /** Binary class functional which compares two characters
     * case-insensitively. Returns true if they are equal. */
    struct char_icase_equal : public std::binary_function<char, char, bool> 
    {
	bool operator() (const char& c1, const char& c2) const 
	{ return std::tolower(c1) == std::tolower(c2); }
    };

    /** Binary class functional which compares two characters
     * case-insensitively. Returns true if the first is less than the
     * second. */
    struct char_icase_less : public std::binary_function<char, char, bool> 
    {
	bool operator() (const char& c1, const char& c2) const 
	{ return std::tolower(c1) < std::tolower(c2); }
    };

    /** Compare this string to the other case-insensitively. Return true if
     * they are equal. */
    bool equal_icase(const string& other) const
    {
	if (size() != other.size()) return false;

	return std::equal( begin(), end(), other.begin(),
			   char_icase_equal() );
    }

    /** Compare this string to the other case-insensitively. Return true if
     * this one is less than the other. */
    bool less_icase(const string& other) const
    {
	return std::lexicographical_compare( begin(), end(),
					     other.begin(), other.end(),
					     char_icase_less() );
    }

    /*
     * --- Prefix and Suffix Functions ---
     */

    /** Checks if the given match string is located at the start of this
     * string. */
    bool is_prefix(const string& match) const
    {
	if (match.size() > size()) return false;
	return std::equal( match.begin(), match.end(), begin() );
    }

    /** Checks if the given match string is located at the end of this
     * string. */
    bool is_suffix(const string& match) const
    {
	if (match.size() > size()) return false;
	return std::equal( match.begin(), match.end(),
			   end() - match.size() );
    }

    /** Checks if the given match string is located at the start of this
     * string. Compares the characters case-insensitively. */
    bool is_prefix_icase(const string& match) const
    {
	if (match.size() > size()) return false;
	return std::equal( match.begin(), match.end(), begin(),
			   char_icase_equal() );
    }

    /** Checks if the given match string is located at the end of this
     * string. Compares the characters case-insensitively. */
    bool is_suffix_icase(const string& match) const
    {
	if (match.size() > size()) return false;
	return std::equal( match.begin(), match.end(),
			   end() - match.size(),
			   char_icase_equal() );
    }
};

} // namespace stx

#endif // _STX_STRING_H_
