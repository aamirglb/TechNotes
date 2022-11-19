#include "spreedsheetcell.hpp"
#include "format"
#include <charconv>

SpreedsheetCell::SpreedsheetCell(double value) {
    setValue(value);
}

SpreedsheetCell::SpreedsheetCell(std::string_view value) {
    setString(value);
}

void SpreedsheetCell::setValue(double value) {
    m_value = value;
}

double SpreedsheetCell::getValue() const {
    return m_value;
}

void SpreedsheetCell::setString(std::string_view value) {
    m_value = stringToDouble(value);
}

std::string SpreedsheetCell::getString() const {
    return doubleToString(m_value);
}

std::string SpreedsheetCell::doubleToString(double value) const {
    return std::to_string(value);
}

double SpreedsheetCell::stringToDouble(std::string_view value) const {
    double number {};
    std::from_chars(value.data(), value.data()+value.size(), number);
    return number;
}

// SpreedsheetCell SpreedsheetCell::operator+(const SpreedsheetCell& rhs) const
// {
//     fmt::print("In class: {}\n", __func__);
//     return SpreedsheetCell { getValue() + rhs.getValue() };
// }

SpreedsheetCell& SpreedsheetCell::operator+=(const SpreedsheetCell& rhs)
{
    setValue(getValue() + rhs.getValue());
    return *this;
}

SpreedsheetCell& SpreedsheetCell::operator-=(const SpreedsheetCell& rhs)
{
    setValue(getValue() - rhs.getValue());
    return *this;
}

SpreedsheetCell& SpreedsheetCell::operator*=(const SpreedsheetCell& rhs)
{
    setValue(getValue() * rhs.getValue());
    return *this;
}

SpreedsheetCell& SpreedsheetCell::operator/=(const SpreedsheetCell& rhs)
{
    if(rhs.getValue() == 0) {
        throw std::invalid_argument{ "Divide by zero." };
    }
    setValue(getValue() / rhs.getValue());
    return *this;
}

// should be implemented in terms of shorthand version
SpreedsheetCell operator+(const SpreedsheetCell& lhs, const SpreedsheetCell& rhs)
{
    fmt::print("Global: {}\n", __func__);
    // return SpreedsheetCell{ lhs.getValue() + rhs.getValue() };
    auto result{lhs};
    result += rhs;
    return result;
}

SpreedsheetCell operator-(const SpreedsheetCell& lhs, const SpreedsheetCell& rhs)
{
    return SpreedsheetCell{ lhs.getValue() - rhs.getValue() };
}

SpreedsheetCell operator*(const SpreedsheetCell& lhs, const SpreedsheetCell& rhs)
{
    return SpreedsheetCell{ lhs.getValue() * rhs.getValue() };
}

SpreedsheetCell operator/(const SpreedsheetCell& lhs, const SpreedsheetCell& rhs)
{
    if(rhs.getValue() == 0) {
        throw std::invalid_argument{ "Divide by zero." };
    }
    return SpreedsheetCell{ lhs.getValue() / rhs.getValue() };
}