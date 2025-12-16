#include <iostream>

int main() {
    struct Point {
        int x;
        int y;
        ~Point() {
            std::cout << "Point is being destroyed" << std::endl;
        }
        int sum() {
            return x + y;
        }
        int diff() {
            return x - y;
        }
        int prod() {
            return x * y;
        }
        int quot() {
            return x / y;
        }
        void fourDirections(int distance) {
            std::cout << "Up: (" << x << ", " << y + distance << ")" << std::endl;
            std::cout << "Down: (" << x << ", " << y - distance << ")" << std::endl;
            std::cout << "Left: (" << x - distance << ", " << y << ")" << std::endl;
            std::cout << "Right: (" << x + distance << ", " << y << ")" << std::endl;
        }
    } p1;
    int x0, y0;
    for (x0 = 1; x0<=10; x0++) {
        y0 = x0 + 1; 
        p1 = {x0,y0};
        std::cout << "(" << p1.x << ", " << p1.y << ")" << std::endl;
        std::cout << " Sum: " << p1.sum() << std::endl;
        std::cout << " Diff: " << p1.diff() << std::endl;
        std::cout << " Prod: " << p1.prod() << std::endl;
        std::cout << " Quot: " << p1.quot() << std::endl;
        p1.fourDirections(3);
    }
}