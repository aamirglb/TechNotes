#include <iostream>
#include <format>
#include <limits>
#include <string>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <future>
#include <atomic>

// puzzle_01 setup
struct Degrees
{
    Degrees() : degrees_(0) { std::cout << "Default constructed\n"; }
    Degrees(double deg) : degrees_(deg) { std::cout << "Constructed with " << degrees_ << '\n'; }
    double degrees_;
};

struct Position
{
    Position() : latitude_{1}
    {
        longitude_ = Degrees{2};
    }

    Degrees latitude_;
    Degrees longitude_;
};

void puzzle_1()
{
    Position position;
}

// puzzle_02 setup
void serialize(const void*) { std::cout << "const void*"; }
void serialize(const std::string&) { std::cout << "const string&"; }

void puzzle_2()
{
    serialize("hello world");
}

// puzzle_3 setup
int getUserId() { return 1220; }
void restrictedTask1() { 
    int id = getUserId();
    if(id == 1220) { std::cout << "did task 1\n"; }
}

void restrictedTask2() { 
    int id;
    if(id == 1220) { std::cout << "did task 2\n"; }
}

void puzzle_3() {
    restrictedTask1();
    restrictedTask2();
}

// puzzle_5 setup
struct Widget
{
    virtual void draw() { std::cout << "Widget draw\n"; }
    /*virtual*/ ~Widget() { std::cout << "Widget destructor\n"; }
};

struct Button : public Widget
{
    void draw() override { std::cout << "Button draw\n"; }
    ~Button() /*override*/ { std::cout << "Button destructor\n"; }
};

void puzzle_5()
{
    std::unique_ptr<Widget> widget = std::make_unique<Button>();
    widget->draw();
}

// puzzle_6 setup
struct Resource
{
    Resource() { std::cout << "Resource constructed\n"; }
    Resource(const Resource& res) { std::cout << "Resource copy constructor\n"; }
    Resource(Resource&& res) { std::cout << "Resource moved constructor\n"; }
    Resource& operator=(const Resource& res) { std::cout << "Copy assignment\n"; return *this; }
    Resource& operator=(Resource&& res) { std::cout << "Move assignment\n"; return *this; }
};

struct Consumer
{
    Consumer(const Resource& res) { std::cout << "Consumer Constructed\n"; }
};

struct Job
{
    Job() : resource_{}, consumer_{resource_} {}
    
    // this order matters, consumer_ will be initialized first then resource_
    Consumer consumer_;
    Resource resource_;
};

void puzzle_6()
{
    Job job;
}


// puzzle_7 setup
struct Connection
{
    Connection(const std::string& name) : name_{name} {
        std::cout << "Created " << name_ << '\n';
    }
    ~Connection() { std::cout << "Destroyed " << name_ << '\n'; }

    std::string name_;
};

Connection global{"global"};
Connection& get() { 
    static Connection localStatic{"local static"};
    return localStatic;
}

void puzzle_7()
{
    Connection local{"local"};
    Connection& tmp1 = get();
    Connection& tmp2 = get();
}


// puzzle_8 setup
struct Member{
    Member() { std::cout << "default ctor\n"; }
    Member(const Member& ) { std::cout << "copy ctor\n"; }
    Member(Member&&) { std::cout << "move ctor\n"; }
    Member& operator=(const Member&) { std::cout << "copy assignment"; return *this; }
    Member& operator=(Member&&) { std::cout << "move assignment"; return *this; }
};

struct WillItMove {
    WillItMove() = default;
    WillItMove(WillItMove&&) = default;
    const Member constMember_{};
};

void puzzle_8()
{
    WillItMove obj;
    WillItMove moved{std::move(obj)};
    std::cout << "It moved!\n";
}

// puzzle_9 setup
struct Res {
    Res() = default;
    Res(const Res&) { std::cout << "copy\n"; }
};
Res getRes() { return Res{}; }

void puzzle_9()
{
    Res res1 = getRes();
    Res res2{ res1 };
}

// puzzle_11 setup
struct MemoryArea {
    MemoryArea(int num) : number_(num) {}
    ~MemoryArea() { std::cout << "Freed memory area " << number_ << '\n'; }
    int number_;
};

MemoryArea getMemory(int num) { return MemoryArea{num}; }

struct DataSource
{
    DataSource(const MemoryArea& memArea) : memoryArea_(memArea) {}
    const MemoryArea& memoryArea_;
};

void puzzle_11()
{
    const auto& ref1 = getMemory(1);
    std::cout << "bound ref1\n";

    const auto& ref2 = getMemory(2).number_;
    std::cout << "bound ref2\n";

    const auto& ref3 = DataSource(getMemory(3));
    std::cout << "bound ref3\n";
}

// puzzle_12 setup
struct Engine
{
    ~Engine() { std::cout << "Engine stopped\n"; }
};

struct Machine {
    Machine() { throw std::runtime_error{"Failed to start machine"}; }
    ~Machine() { std::cout << "Machine stopped\n"; }
    Engine engine_;
};

void puzzle_12() 
{
    try {
        Machine machine;
    } catch(...) {

    }
}

// puzzle_13 setup
template <typename T>
void byValue(T t) { std::cout << std::is_const_v<T>; }

template <typename T>
void byReference(T& t) { std::cout << std::is_const_v<T>; }

void puzzle_13()
{
    int nonConstInt = 0;
    const int constInt = 0;

    byValue(nonConstInt);
    byValue(constInt);

    byReference(nonConstInt);
    byReference(constInt);
}


// puzzle_15 setup
void puzzle_15()
{
    std::atomic<char> counter = 0;
    auto future1 = std::async(std::launch::async, [&]() { counter++; });
    auto future2 = std::async(std::launch::async, [&]() { return counter.load(); });
    future1.wait();
    std::cout << static_cast<int>(future2.get()) << '\n';
    std::cout << counter.is_always_lock_free << '\n';
}

// puzzle 17 setup
struct Points
{
    Points(int value) : value_(value) {}
    int value_;
};

struct Player
{
    explicit Player(Points points) : points_(points) {}
    Points points_;
};

void puzzle_17()
{
    Player player(3);
    std::cout << player.points_.value_;
}

// puzzle_22 setup
/*
struct GameObject
{
    GameObject() { std::cout << "Created a " << getType() << '\n'; }
    void render() const { std::cout << "Rendered a " << getType() << '\n'; }
    virtual std::string getType() const { return "GameObject"; }
};

class Spaceship : public GameObject
{
    std::string getType() const override { return "Spaceship"; }
};

void display(const GameObject& gameObj) {
    gameObj.render();
}

void puzzle_22()
{
    GameObject gameObj;
    Spaceship spaceship;
    display(gameObj);
    display(spaceship);
}
*/

struct GameObject {
    virtual void render() const = 0;
};

template <typename Derived>
struct LoggingGameObject : public GameObject {
    LoggingGameObject() { std::cout << "Created a " << Derived::typeName << '\n'; }
    void render() const override { std::cout << "Rendered a " << Derived::typeName << '\n'; }
};

struct Spaceship : public LoggingGameObject<Spaceship> {
    static constexpr auto typeName = "Spaceship";
};

struct Tank : public LoggingGameObject<Tank> {
    static constexpr auto typeName = "Tank";
};

void display(const GameObject& gameObj) {
    gameObj.render();
}

void puzzle_22()
{
    Spaceship spaceship;
    Tank tank;
    display(spaceship);
    display(tank);
}

// puzzle_24 setup
template <typename T>
void serialize(T&) { std::cout << "template\n"; }

template<>
void serialize<>(const std::string&) { std::cout << "specialization\n";}

//void serialize(const std::string&) { std::cout << "normal function\n"; }

void puzzle_24()
{
    std::string h{"hello, world!"};
    serialize(h);
    serialize(std::string{"bye"});
}

// crtp example
template <typename Derived>
struct Shape { 
    void draw() { static_cast<Derived*>(this)->draw_impl(); }
};

struct Circle : public Shape<Circle> {
    void draw_impl() { std::cout << "Drawing circle\n"; }
};

struct Square : public Shape<Square> {
    void draw_impl() { std::cout << "drawing square\n"; }
};

void crtp_test()
{
    Circle c;
    c.draw();
    Square s;
    s.draw();
}

int main()
{
    // puzzle_1();
    // puzzle_2();
    // puzzle_3();   // undefined behavior, but output is intersting!!
    /* output 
    did task-1
    did task-2
    */

    //puzzle_5();
    /* output
    Button draw
    Button destructor
    Widget destructor
    */

    //puzzle_6();
    /* output
    Consumer constructed
    Resource constructed
    */
    
    //puzzle_7();
    /* output
    Created global
    Created local
    Created local static
    

    Destroyed local
    Destroyed local static
    Destroyed global
    */

    //puzzle_8();

    //puzzle_9();

    //puzzle_11();

    //puzzle_12();

    //puzzle_13();

    //puzzle_15();

    //puzzle_17();

    // puzzle_22();

    //puzzle_24();

    crtp_test();

    std::cout << +!!"";
}