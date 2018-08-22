// Capim - a modern C++ plotting library powered by gnuplot
// https://github.com/allanleal/capim
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018 Allan Leal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// Capim includes
#include <Capim/default.hpp>
#include <Capim/specs/textspecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The class used to specify options for titles.
template<typename derivedspecs>
class titlespecs : public textspecs<derivedspecs>
{
public:
    /// Construct a default titlespecs instance.
    titlespecs();

    /// Convert this titlespecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the text of the title.
    auto text(std::string title) -> derivedspecs& { m_title = "'" + title + "'"; return static_cast<derivedspecs&>(*this); }

    /// Set the offset of the title element.
    /// @param xval The offset along the x direction
    /// @param yval The offset along the y direction
    auto offset(int xval, int yval) -> derivedspecs& { m_offset = "offset " + str(xval) + "," + str(yval); return static_cast<derivedspecs&>(*this); }

    /// Set the rotation angle of the title element in degrees.
    auto rotate(double angle) -> derivedspecs& { m_rotate = "by " + str(angle); return static_cast<derivedspecs&>(*this); }

private:
    /// The title word.
    std::string m_title;

    /// The offset used to move the label around.
    std::string m_offset;

    /// The rotation command to rotate the label around.
    std::string m_rotate;
};

template<typename derivedspecs>
titlespecs<derivedspecs>::titlespecs()
{
    text("");
}

template<typename derivedspecs>
auto titlespecs<derivedspecs>::repr() const -> std::string
{
    std::stringstream ss;
    ss << m_title << " " << textspecs<derivedspecs>::repr() << " ";
    ss << optionstr(m_rotate) << optionstr(m_offset);
    return ss.str();
}

} // namespace internal
} // namespace Capim
