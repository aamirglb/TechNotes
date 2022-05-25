#include <iostream>
#include <memory>

class CruiseControl
{
public:
    CruiseControl(int32_t speed = 15): _speed{speed} {
        std::cout << "CruiseControl object created. Initial Speed = " << _speed << std::endl;
    }

    ~CruiseControl() {
        std::cout << "CruiseControl object destroyed" << std::endl;
    }

    void increaseSpeedTo(int speed) {
        _speed += speed;
        std::cout << "Speed at " << _speed << std::endl;
    }

private:
    int32_t _speed;
};

int main()
{
    std::unique_ptr<CruiseControl> cruiseCtl = std::make_unique<CruiseControl>();
    cruiseCtl->increaseSpeedTo(5);

    std::unique_ptr<CruiseControl> cruiseCtl2 = std::make_unique<CruiseControl>(37);
    cruiseCtl2->increaseSpeedTo(13);

    std::unique_ptr<CruiseControl[]> cc = std::make_unique<CruiseControl[]>(3);
    cc[0].increaseSpeedTo(5);
    cc[1].increaseSpeedTo(15);
    cc[2].increaseSpeedTo(25);

    std::cout << "\n\n";

    // shared_ptr
    std::shared_ptr<CruiseControl> master(nullptr);
    {
        std::shared_ptr<CruiseControl> slave = std::make_shared<CruiseControl>(55);
        master = slave;
    }
    master->increaseSpeedTo(50);

}