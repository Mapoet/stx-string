// $Id$

#ifndef _STX_STRING_H_ 
#define _STX_STRING_H_

#include <string>
#include <cctype>

namespace stx {

class string : public std::string
{
public:

    // ***                              ***
    // *** Constructors for stx::string ***
    // ***                              ***

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

    // ***                           ***
    // *** Whitespace Trim Functions ***
    // ***                           ***

    // *** generic std::string versions ***

    /** Trims the given string on the left and right. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of the
     * string.
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    static std::string trim(const std::string& str, const std::string& drop = " ")
    {
	std::string::size_type pos1 = str.find_first_not_of(drop);
	if (pos1 == std::string::npos) return std::string();

	std::string::size_type pos2 = str.find_last_not_of(drop);
	if (pos2 == std::string::npos) return std::string();

	return str.substr(pos1 == std::string::npos ? 0 : pos1,
			  pos2 == std::string::npos ? (str.size() - 1) : (pos2 - pos1 + 1));
    }

    /** Trims the given string only on the left. Removes all characters in the
     * given drop array, which defaults to " ". Returns a copy of the string.
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    static std::string trim_left(const std::string& str, const std::string& drop = " ")
    {
	std::string::size_type pos = str.find_first_not_of(drop);
	if (pos == std::string::npos) return std::string();

	return str.substr(pos, std::string::npos);
    }

    /** Trims the given string only on the right. Removes all characters in the
     * given drop array, which defaults to " ". Returns a copy of the string.
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return	new trimmed string
     */
    static std::string trim_right(const std::string& str, const std::string& drop = " ")
    {
	std::string::size_type pos = str.find_last_not_of(drop);
	if (pos == std::string::npos) return std::string();

	return str.substr(0, pos + 1);
    }

    /** Trims the given string in-place on the left and right. Removes all
     * characters in the given drop array, which defaults to " ".
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return	reference to the modified string
     */
    static std::string& trim_inplace(std::string& str, const std::string& drop = " ")
    {
	std::string::size_type pos = str.find_last_not_of(drop);
	if (pos != std::string::npos) {
	    str.erase(pos + 1);
	    pos = str.find_first_not_of(drop);
	    if (pos != std::string::npos) str.erase(0, pos);
	}
	else
	    str.erase(str.begin(), str.end());

	return str;
    }

    /** Trims the given string in-place only on the left. Removes all
     * characters in the given drop array, which defaults to " ".
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return	reference to the modified string
     */
    static std::string& trim_left_inplace(std::string& str, const std::string &drop = " ")
    {
	str.erase(0, str.find_first_not_of(drop));
	return str;
    }

    /** Trims the given string in-place only on the right. Removes all
     * characters in the given drop array, which defaults to " ".
     *
     * @param str	string to process
     * @param drop	remove these characters
     * @return	reference to the modified string
     */
    static std::string& trim_right_inplace(std::string &str, const std::string &drop = " ")
    {
	str.erase(str.find_last_not_of(drop) + 1, std::string::npos);
	return str;
    }

    // *** class stx::string methods versions ***

    /** Trims the contained string on the left and right. Removes all
     * characters in the given drop array, which defaults to " ". Returns a
     * copy of this string.
     *
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim(const string& drop = " ") const
    {
	return trim(*this, drop);
    }

    /** Trims the contained string only on the left. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of this
     * string.
     *
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim_left(const string& drop = " ") const
    {
	return trim_left(*this, drop);
    }

    /** Trims the contained string only on the right. Removes all characters in
     * the given drop array, which defaults to " ". Returns a copy of this
     * string.
     *
     * @param drop	remove these characters
     * @return		new trimmed string
     */
    string trim_right(const string& drop = " ") const
    {
	return trim_right(*this, drop);
    }

    /** Trims this string in-place on the left and right. Removes all
     * characters in the given drop array, which defaults to " ".
     *
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_inplace(const string& drop = " ")
    {
	trim_inplace(*this, drop);
	return *this;
    }

    /** Trims this string in-place only on the left. Removes all characters in
     * the given drop array, which defaults to " ".
     *
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_left_inplace(const string &drop = " ")
    {
	trim_left_inplace(*this, drop);
	return *this;
    }

    /** Trims this string in-place only on the right. Removes all characters in
     * the given drop array, which defaults to " ".
     *
     * @param drop	remove these characters
     * @return		reference to this string
     */
    string& trim_right_inplace(const string &drop = " ")
    {
	trim_right_inplace(*this, drop);
	return *this;
    }

    // ***                                 ***
    // ***  Upper and Lower Case Functions ***
    // ***                                 ***

    // *** functionals ***

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

    // *** generic std::string versions ***

    /** Returns a copy of the given string converted to uppercase.
     * @param str	string to process
     * @return		new string uppercased
     */
    static std::string toupper(const std::string& str)
    {
	std::string strcopy(str.size(), 0);
	std::transform(str.begin(), str.end(), strcopy.begin(), char_toupper_functional);
	return strcopy;
    }

    /** Returns a copy of the given string converted to lowercase.
     * @param str	string to process
     * @return		new string lowercased
     */
    static std::string tolower(const std::string& str)
    {
	std::string strcopy(str.size(), 0);
	std::transform(str.begin(), str.end(), strcopy.begin(), char_tolower_functional);
	return strcopy;
    }

    /** Transforms the enclosed string to uppercase and returns a reference to
     * this. */
    static std::string& toupper_inplace(std::string& str)
    {
	std::transform(str.begin(), str.end(), str.begin(), char_toupper_functional);
	return str;
    }

    /** Transforms the enclosed string to lowercase and returns a reference to
     * this. */
    static std::string& tolower_inplace(std::string& str)
    {
	std::transform(str.begin(), str.end(), str.begin(), char_tolower_functional);
	return str;
    }

    // *** class stx::string method versions ***

    /** Returns a copy of the enclosed string converted to uppercase.
     * @return		new string uppercased
     */
    string toupper() const
    {
	string strcopy(size(), 0);
	std::transform(begin(), end(), strcopy.begin(), char_toupper_functional);
	return strcopy;
    }

    /** Returns a copy of the enclosed string converted to lowercase.
     * @return		new string lowercased
     */
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

    // ***                              ***
    // *** Case-insensitive Comparision ***
    // ***                              ***

    // *** functional classes ***

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

    // *** std::string comparison operators ***

    /** Compare this string to the other case-insensitively. Return true if
     * they are equal. */
    static bool equal_icase(const std::string& a, const std::string& b)
    {
	if (a.size() != b.size()) return false;

	return std::equal( a.begin(), a.end(), b.begin(),
			   char_icase_equal() );
    }

    /** Compare this string to the other case-insensitively. Return true if
     * this one is less than the other. */
    static bool less_icase(const std::string& a, const std::string& b)
    {
	return std::lexicographical_compare( a.begin(), a.end(),
					     b.begin(), b.end(),
					     char_icase_less() );
    }

    // *** class stx::string method versions ***

    /** Compare this string to the other case-insensitively. Return true if
     * they are equal. */
    bool equal_icase(const string& other) const
    {
	return equal_icase(*this, other);
    }

    /** Compare this string to the other case-insensitively. Return true if
     * this one is less than the other. */
    bool less_icase(const string& other) const
    {
	return less_icase(*this, other);
    }

    // *** case-insenstive less-relation functional class for std::map ***
    
    /** Case-insensitive less order relation functional class for std::map. */
    struct order_less_icase {
	inline bool operator()(const std::string &a, const std::string &b) const {
	    return less_icase(a, b);
	}
    };

    // ***                             ***
    // *** Prefix and Suffix Functions ***
    // ***                             ***

    // *** static std::string functions ***

    /** Checks if the given match string is located at the start of this
     * string. */
    static bool is_prefix(const std::string& str, const std::string& match)
    {
	if (match.size() > str.size()) return false;
	return std::equal( match.begin(), match.end(), str.begin() );
    }

    /** Checks if the given match string is located at the end of this
     * string. */
    static bool is_suffix(const std::string& str, const std::string& match)
    {
	if (match.size() > str.size()) return false;
	return std::equal( match.begin(), match.end(),
			   str.end() - match.size() );
    }

    /** Checks if the given match string is located at the start of this
     * string. Compares the characters case-insensitively. */
    static bool is_prefix_icase(const std::string& str, const std::string& match)
    {
	if (match.size() > str.size()) return false;
	return std::equal( match.begin(), match.end(), str.begin(),
			   char_icase_equal() );
    }

    /** Checks if the given match string is located at the end of this
     * string. Compares the characters case-insensitively. */
    static bool is_suffix_icase(const std::string& str, const std::string& match)
    {
	if (match.size() > str.size()) return false;
	return std::equal( match.begin(), match.end(),
			   str.end() - match.size(),
			   char_icase_equal() );
    }

    // *** class stx::string method versions ***

    /** Checks if the given match string is located at the start of this
     * string. */
    bool is_prefix(const string& match) const
    {
	return is_prefix(*this, match);
    }

    /** Checks if the given match string is located at the end of this
     * string. */
    bool is_suffix(const string& match) const
    {
	return is_suffix(*this, match);
    }

    /** Checks if the given match string is located at the start of this
     * string. Compares the characters case-insensitively. */
    bool is_prefix_icase(const string& match) const
    {
	return is_prefix_icase(*this, match);
    }

    /** Checks if the given match string is located at the end of this
     * string. Compares the characters case-insensitively. */
    bool is_suffix_icase(const string& match) const
    {
	return is_suffix_icase(*this, match);
    }

    // ***                              ***
    // *** Search and Replace Functions ***
    // ***                              ***

    // *** static std::string functions ***

    /** Replace only the first occurrence of needle in str. The needle will be
     * replaced with instead, if found. Returns a copy of the string with the
     * possible replacement.
     *
     * @param str	the string to process
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		copy of string possibly with replacement
     */
    static std::string replace_first(const std::string& str, const std::string& needle, const std::string& instead)
    {
	std::string newstr = str;
	std::string::size_type firstpos = newstr.find(needle);

	if ( firstpos != std::string::npos)
	    newstr.replace(firstpos, needle.size(), instead);

	return newstr;
    }

    /** Replace all occurrences of needle in str. Each needle will be replaced
     * with instead, if found. Returns a copy of the string with possible
     * replacements.
     *
     * @param str	the string to process
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		copy of string possibly with replacements
     */
    static std::string replace_all(const std::string& str, const std::string& needle, const std::string& instead)
    {
	std::string newstr = str;
	std::string::size_type lastpos = 0, thispos;

	while ( (thispos = newstr.find(needle, lastpos)) != std::string::npos)
	{
	    newstr.replace(thispos, needle.size(), instead);
	    lastpos = thispos + instead.size();
	}
	return newstr;
    }

    /** Replace only the first occurrence of needle in str. The needle will be
     * replaced with instead, if found. The replacement is done in the given
     * string and a reference to the same is returned.
     *
     * @param str	the string to process
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		reference to str
     */
    static std::string& replace_first_inplace(std::string& str, const std::string& needle, const std::string& instead)
    {
	std::string::size_type firstpos = str.find(needle);

	if ( firstpos != std::string::npos)
	    str.replace(firstpos, needle.size(), instead);

	return str;
    }

    /** Replace all occurrences of needle in str. Each needle will be replaced
     * with instead, if found. The replacement is done in the given string and
     * a reference to the same is returned.
     *
     * @param str	the string to process
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		reference to str
     */
    static std::string& replace_all_inplace(std::string& str, const std::string& needle, const std::string& instead)
    {
	std::string::size_type lastpos = 0, thispos;

	while ( (thispos = str.find(needle, lastpos)) != std::string::npos)
	{
	    str.replace(thispos, needle.size(), instead);
	    lastpos = thispos + instead.size();
	}
	return str;
    }

    // *** class stx::string method versions ***

    /** Replace only the first occurrence of needle in the enclosed string. The
     * needle will be replaced with instead, if found. Returns a copy of this
     * string with the possible replacement.
     *
     * @param needle	string to search for
     * @param instead	replace needle with instead
     * @return		copy of this string possibly with replacement
     */
    string replace_first(const string& needle, const string& instead) const
    {
	return replace_first(*this, needle, instead);
    }
    
    /** Replace all occurrences of needle in the enclosed string. Each needle
     * will be replaced with instead, if found. Returns a copy of the string
     * with possible replacements.
     *
     * @param needle	string to search for
     * @param instead	replace needle with instead
     * @return		copy of this string possibly with replacements
     */
    string replace_all(const string& needle, const string& instead) const
    {
	return replace_all(*this, needle, instead);
    }

    /** Replace only the first occurrence of needle in the enclosed string. The
     * needle will be replaced with instead, if found. The replacement is done
     * in the enclosed string and a reference to this is returned.
     *
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		reference to this
     */
    string& replace_first_inplace(const string& needle, const string& instead)
    {
	replace_first_inplace(*this, needle, instead);
	return *this;
    }

    /** Replace all occurrences of needle in the enclosed string. Each needle
     * will be replaced with instead, if found. The replacement is done in the
     * enclosed string and a reference to this is returned.
     *
     * @param needle	string to search for in str
     * @param instead	replace needle with instead
     * @return		reference to this
     */
    string& replace_all_inplace(const string& needle, const string& instead)
    {
	replace_all_inplace(*this, needle, instead);
	return *this;
    }

    // ***                          ***
    // *** Split and Join Functions ***
    // ***                          ***

    // *** static std::string functions ***

    /** Split the given string by whitespaces into distinct words. Multiple
     * consecutive whitespaces are considered as one split point. Whitespaces
     * are space, tab, newline and carriage-return.
     *
     * @param str	string to split
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    static std::vector<std::string> split_ws(const std::string& str, std::string::size_type limit = std::string::npos)
    {
	std::vector<std::string> out;
	if (limit == 0) return out;

	std::string::const_iterator it = str.begin(), last = it;

	for (; it != str.end(); ++it)
	{
	    if (*it == ' ' || *it == '\n' || *it == '\t' || *it == '\r')
	    {
		if (it == last) { // skip over empty split substrings
		    last = it+1;
		    continue;
		}

		if (out.size() + 1 >= limit)
		{
		    out.push_back(std::string(last, str.end()));
		    return out;
		}

		out.push_back(std::string(last, it));
		last = it + 1;
	    }
	}

	if (last != it)
	    out.push_back(std::string(last, it));

	return out;
    }

    /** Split the given string at each separator character into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings.
     *
     * @param str	string to split
     * @param sep	separator character
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    static std::vector<std::string> split(const std::string& str, char sep, std::string::size_type limit = std::string::npos)
    {
	std::vector<std::string> out;
	if (limit == 0) return out;

	std::string::const_iterator it = str.begin(), last = it;

	for (; it != str.end(); ++it)
	{
	    if (*it == sep)
	    {
		if (out.size() + 1 >= limit)
		{
		    out.push_back(std::string(last, str.end()));
		    return out;
		}

		out.push_back(std::string(last, it));
		last = it + 1;
	    }
	}

	if (last != it)
	    out.push_back(std::string(last, it));

	return out;
    }

    /** Split the given string at each separator string into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings.
     *
     * @param str	string to split
     * @param sepstr	separator string
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    static std::vector<std::string> split(const std::string& str, const std::string& sepstr, std::string::size_type limit = std::string::npos)
    {
	std::vector<std::string> out;
	if (limit == 0) return out;
	if (sepstr.empty()) return out;

	std::string::const_iterator it = str.begin(), last = it;

	for (; it + sepstr.size() <= str.end(); ++it)
	{
	    if (std::equal(sepstr.begin(), sepstr.end(), it))
	    {
		if (out.size() + 1 >= limit)
		{
		    out.push_back(std::string(last, str.end()));
		    return out;
		}

		out.push_back(std::string(last, it));
		last = it + sepstr.size();
	    }
	}

	if (last != str.end())
	    out.push_back(std::string(last, str.end()));

	return out;
    }

    /** Join a sequence of strings by some glue string between each pair from
     * the sequence. The sequence in given as a range between two iterators.
     *
     * @param glue	string to glue
     * @param first	the beginning iterator of the range to join
     * @param last	the ending iterator of the range to join
     * @return		string constructed from the range with the glue between two strings.
     */
    template <typename input_iterator>
    static std::string join(const std::string& glue, input_iterator first, input_iterator last)
    {
	std::string out;
	if (first == last) return out;

	out.append(*first);
	++first;

	while( first != last )
	{
	    out.append(glue);
	    out.append(*first);
	    ++first;
	}

	return out;
    }

    /** Join a vector of strings by some glue string between each pair from
     * the sequence.
     *
     * @param glue	string to glue
     * @param parts	the vector of strings to join
     * @return		string constructed from the vector with the glue between two strings.
     */
    static std::string join(const std::string& glue, const std::vector<std::string>& parts)
    {
	return join(glue, parts.begin(), parts.end());
    }

    // *** class stx::string method versions ***

    /** Split the enclosed string by whitespaces into distinct words. Multiple
     * consecutive whitespaces are considered as one split point.
     *
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    std::vector<std::string> split_ws(size_type limit = npos) const
    {
	return split_ws(*this, limit);
    }

    /** Split the enclosed string at each separator character into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings.
     *
     * @param sep	separator character
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    std::vector<std::string> split(char sep, size_type limit = npos) const
    {
	return split(*this, sep, limit);
    }

    /** Split the enclosed string at each separator string into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings.
     *
     * @param sepstr	separator string
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    std::vector<std::string> split(const std::string& sepstr, size_type limit = npos) const
    {
	return split(*this, sepstr, limit);
    }

    /** Split the enclosed string at each separator string into distinct
     * substrings. Multiple consecutive separators are considered individually
     * and will result in empty split substrings. This function fixes ambiguous
     * calls with C-style strings.
     *
     * @param sepstr	separator C-style string
     * @param limit	maximum number of parts returned
     * @return		vector containing each split substring
     */
    std::vector<std::string> split(const char* sepstr, size_type limit = npos) const
    {
	return split(*this, std::string(sepstr), limit);
    }

    /** Join a sequence of strings by gluing each pair together with the
     * enclosed glue string. The sequence in given as a range between two
     * iterators.
     *
     * @param first	the beginning iterator of the range to join
     * @param last	the ending iterator of the range to join
     * @return		string constructed from the range with the glue between two strings.
     */
    template <typename input_iterator>
    stx::string join(input_iterator first, input_iterator last) const
    {
	return join(*this, first, last);
    }

    /** Join a vector of strings by gluing each pair together with the enclosed
     * glue string.
     *
     * @param parts	the vector of strings to join
     * @return		string constructed from the vector with the glue between two strings.
     */
    stx::string join(const std::vector<std::string>& parts) const
    {
	return join(*this, parts.begin(), parts.end());
    }

    /** Join a vector of strings by gluing each pair together with the enclosed
     * glue string.
     *
     * @param parts	the vector of strings to join
     * @return		string constructed from the vector with the glue between two strings.
     */
    stx::string join(const std::vector<stx::string>& parts) const
    {
	return join(*this, parts.begin(), parts.end());
    }

}; // class string

} // namespace stx

#endif // _STX_STRING_H_
