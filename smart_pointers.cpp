#include <iostream>
#include <memory>

class Test {
   public:
    Test() { std::cout << "test const\n"; };
    void print() { std::cout << "hello\n"; };
    ~Test() { std::cout << "test dest\n"; };
};

int main() {
    auto x = 100;
    // int x = 10;
    int hello = 20;
    int testtesttest = 3000;
    {
        std::unique_ptr<Test> test = std::make_unique<Test>();
        // std::unique_ptr<Test> test(new Test);
        test->print();
    }
    std::weak_ptr<Test> wkTest;
    {
        // std::shared_ptr<Test> shTest = std::make_shared<Test>();
        std::shared_ptr<Test> shTest(new Test);
        shTest->print();
        std::shared_ptr<Test> shTest2 = shTest;
        shTest2->print();
        {
            std::shared_ptr<Test> shTest3 = shTest2;
            shTest3->print();
            wkTest = shTest2;
            if (!wkTest.expired())
                std::cout << "stil alive\n";
        }
    }
    if (wkTest.expired())
        std::cout << "dead\n";
}
