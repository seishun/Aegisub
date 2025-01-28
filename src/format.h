// Copyright (c) 2014, Thomas Goyne <plorkyeran@aegisub.org>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// Aegisub Project http://www.aegisub.org/

#include <format>

#include <wx/string.h>
#include <wx/translation.h>

namespace agi {
template<typename... Args>
std::string format(wxString const& fmt, Args&&... args) {
	return std::format(std::runtime_format((const char *)fmt.utf8_str()), std::forward<Args>(args)...);
}

template<typename... Args>
wxString wxformat(wxString const& fmt, Args&&... args) {
	std::basic_string<wxStringCharType> out;
	std::format_to(std::back_inserter(out), std::runtime_format(fmt.wx_str()), std::forward<Args>(args)...);
	return out;
}

template<typename... Args>
wxString wxformat(const wxStringCharType *fmt, Args&&... args) {
	return format(fmt, std::forward<Args>(args)...);
}
}

#define fmt_wx(str, ...) std::format(str, __VA_ARGS__)
#define fmt_tl(str, ...) agi::format(wxGetTranslation(wxS(str)), __VA_ARGS__)
#define fmt_plural(n, sing, plural, ...) \
	agi::format(wxGetTranslation(wxS(sing), wxS(plural), (n)), __VA_ARGS__)
