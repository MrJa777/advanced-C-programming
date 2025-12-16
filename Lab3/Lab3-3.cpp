#include <iostream>



int main() {
    struct Point {
        int x;
        int y;
    };
Point p1;

Point* p2 =&p1;
Point* p3 =new Point;

p1 = {1,2};
p1.x = 5;


std::cout << (*p2).x << "." << (*p2).y << std::endl;
(*p3).x = 10; (*p3).y = 20;

std::cout << (*p3).x << "." << (*p3).y << std::endl;
    

}
