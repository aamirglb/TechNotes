class Foo {
    public:
    int baz() const { return 1;}
    protected:
    int i;
};

class Bar : public Foo {
    int i; // Triggers warning
    public:
    int baz() const { return 2;}
};

int main() {
    Bar b;
    Foo& f = b;
    return f.baz(); // returns 1
}