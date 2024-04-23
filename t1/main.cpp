#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Circle {
public:
    CircleShape shape;

    // 构造函数
    Circle(float radius) : shape(radius) {
        shape.setFillColor(Color::Yellow);  // 默认颜色为绿色
        std::cout << "Default constructor called!" << std::endl;

    }
    

    // 拷贝构造函数
    Circle(const Circle& other) : shape(other.shape) {
        std::cout << "Copy constructor called!" << std::endl;
    }

    // 移动构造函数
    Circle(Circle&& other) noexcept : shape(std::move(other.shape)) {
        std::cout << "Move constructor called!" << std::endl;
    }

    //移动赋值运算符
    Circle& operator=(Circle&& other) noexcept {//noexcept:函数不会抛出异常
        if(this!=&other)
        {
            this->shape = std::move(other.shape);
            std::cout << "Move assignment operator called!"<<std::endl;
        }
        return *this;
    }

    // 绘制函数
    void draw(RenderWindow& window) {
        window.draw(shape);
    }
    ~Circle() {std::cout<< "delete Circle()"<<std::endl;}
};

int main() {
    RenderWindow window(VideoMode(200, 200), "SFML with Custom Circle");
    Circle circle(50.f); 
    //拷贝构造
    Circle c2(circle);
    //隐式调用拷贝构造
    Circle c3 = circle;
    //移动构造
    Circle c4 = std::move(circle);
    //移动赋值运算符
    Circle c5(20.f);
    c5 = std::move(circle); 

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        // circle.draw(window); 
        // 使用Circle的方法绘制形状
        c2.draw(window);
        window.display();
    }

    return 0;
}
