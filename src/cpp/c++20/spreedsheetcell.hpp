#pragma once
#include <string>
#include <string_view>

class SpreedsheetCell
{
public:
    SpreedsheetCell() = default;
    SpreedsheetCell(double value);
    SpreedsheetCell(std::string_view value);

public:
    void setValue(double value);
    double getValue() const;

    void setString(std::string_view value);
    std::string getString() const;

public:
    // SpreedsheetCell operator+(const SpreedsheetCell& rhs) const;
    SpreedsheetCell& operator+=(const SpreedsheetCell& rhs);
    SpreedsheetCell& operator-=(const SpreedsheetCell& rhs);
    SpreedsheetCell& operator*=(const SpreedsheetCell& rhs);
    SpreedsheetCell& operator/=(const SpreedsheetCell& rhs);

private:
    std::string doubleToString(double value) const;
    double stringToDouble(std::string_view value) const;
    double m_value;
};

SpreedsheetCell operator+(const SpreedsheetCell& lhs, const SpreedsheetCell& rhs);
SpreedsheetCell operator-(const SpreedsheetCell& lhs, const SpreedsheetCell& rhs);
SpreedsheetCell operator*(const SpreedsheetCell& lhs, const SpreedsheetCell& rhs);
SpreedsheetCell operator/(const SpreedsheetCell& lhs, const SpreedsheetCell& rhs);