#include "format"
#include "spreedsheetcell.hpp"

int main() {
    SpreedsheetCell c1, c2;
    c1.setValue(61);
    c2.setString("3.1425");

    fmt::print("cell 1: {}\n", c1.getValue());
    fmt::print("cell 2: {}\n", c2.getValue());

    auto* c3 {new SpreedsheetCell{}};
    c3->setValue(4.25);
    fmt::print("cell 3: {}\n", c3->getValue());
    delete c3;
    c3 = nullptr;

    auto c4 {std::make_unique<SpreedsheetCell>() };
    c4->setValue(5.894);
    fmt::print("cell 4: {}\n", c4->getValue());

    SpreedsheetCell c5(1.25);
    SpreedsheetCell c6("8.45");
    fmt::print("cell 5: {}\n", c5.getValue());
    fmt::print("cell 6: {}\n", c6.getValue());

    SpreedsheetCell c7{c5 + c6};
    fmt::print("cell 7: {}\n", c7.getValue());

    c7 += 0.3;
    fmt::print("cell 7: {}\n", c7.getValue());
}