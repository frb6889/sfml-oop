#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Circle {
public:
    CircleShape shape;
    float radius;

    // 构造函数
    Circle(float radius) : shape(radius) {
        shape.setFillColor(Color::Yellow);  // 默认颜色为绿色
        std::cout << "Default constructor called!" << std::endl;

    }
    

    // 拷贝构造函数
    Circle(const Circle& other) : shape(other.shape) {
        std::cout << "Copy constructor called!" << std::endl;
    }

    // 移动构造函数 右值引用&&
    Circle(Circle&& other) noexcept : shape(std::move(other.shape)) {
        std::cout << "Move constructor called!" << std::endl;
    }

    //移动赋值运算符 右值引用&&
    Circle& operator=(Circle&& other) noexcept {//noexcept:函数不会抛出异常
        if(this!=&other)
        {
            this->shape = std::move(other.shape);
            std::cout << "Move assignment operator called!"<<std::endl;
        }
        return *this;
    }

    // 6.6 p51自动类型转换：方法1 在源类中定义“目标类型转换符”
    operator float() const {
        return radius;
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
    //6.2 拷贝构造
    Circle c2(circle);
    //6.2 隐式调用拷贝构造
    Circle c3 = circle;
    //6.4 移动构造
    Circle c4 = std::move(circle);
    //6.5 移动赋值运算符
    Circle c5(20.f);
    c5 = std::move(circle); 
    /* 
    这里的std::move(circle)将circle转换为一个右值，
    允许c4的移动构造函数和c5的移动赋值运算符被调用。
    std::move是一个将其参数转换为右值引用的函数模板，
    这是启用移动语义的关键 
    */
   

    float circleRadius = circle;  // 自动转换Circle到float
    std::cout << "The radius of the circle is: " << circleRadius << std::endl;


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
