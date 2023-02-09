// kanas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <nlohmann/json.hpp>

struct example
{
public:
    void alloc(int a)
    {}

    void dealloc()
    {
    }

    static void shader_mapping()
    {
    }

    bool satisfy()
    {
        return false;
    }
};

template <>
struct std::hash<example> {
    _NODISCARD size_t operator()(const example& v) const noexcept {
        return 0; // map -0 to 0
    }
};

class example_non
{

};

template<typename T>
concept example_t = requires(T t, int a)
{
    T::shader_mapping();
    t.alloc(a);
    t.dealloc();
    { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};

template<example_t T>
void test(T t)
{
    std::vector<int> a;
    constexpr std::string_view sv("wait");
    constexpr std::string_view ssv("wait");
}

int main()
{
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
