# toolbelt [![Build Status](https://travis-ci.org/atomicptr/toolbelt.svg?branch=master)](https://travis-ci.org/atomicptr/toolbelt)

Collection of useful header-only util functions, written in C++14.

## Usage

Just pick whatever header files you need and drop them  into your project.

## Content

### crc32.hpp

Compile time CRC32.

```cpp
auto crc = toolbelt::crc32("Hello, World");
```

### format_time.hpp

Format std::chrono time strings.

```cpp
auto now = std::chrono::system_clock::now();
toolbelt::format_time(now, "Today is %A"); // Today is Friday

// NOTE: If you don't specify a chrono time point it's now by default:
toolbelt::format_time("Today is %A"); // Today is Friday
```

### logger.hpp

Simple extensible logger with log levels.

Dependencies: **format_time.hpp**

```cpp
toolbelt::logger logger;

std::string name = "World";

logger.log("Hello, ", name);
// [13:37:42][INFO] Hello, World

logger(toolbelt::log_level::WARNING).log("Oh something went wrong!");
// [02:03:04][WARNING] Oh something went wrong!
```

If you want to use your custom types, just overload ``std::ostream& operator<<(std::ostream&, YOUR_TYPE&)``

```cpp
struct vec2 {
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& os, const vec2& v) {
    os << "vec2 x: " << v.x << ", y: " << v.y;
    return os;
}

vec2 position = get_position();

logger.log("my position is: ", position);
```

### make_smart.hpp

Create a ``std::unique_ptr`` from C Constructor/Destructor pairs.

```cpp
// General usage
struct Type { ... };
Type* construct(...);
void destruct(Type*);

auto ptr = toolbelt::make_smart<Type>(construct, destruct, arg1, ...);

// Example using SDL2
...make_smart<SDL_Window>(SDL_CreateWindow, SDL_DestroyWindow, "Window Title!", ...);
```

### string.hpp

A few string utils.

```cpp

auto str = toolbelt::replace("Hello, Universe!", "Universe", "World"); // Hello, World!
auto parts = toolbelt::split("Good Evening", ' '); // ["Good", "Evening"]
auto str = toolbelt::to_lower("CAPSLOCK"); // capslock
auto str = toolbelt::to_upper("capslock");  // CAPSLOCK
auto str = toolbelt::trim("   I'M IN SPAAACE    "); // there is also ltrim and rtrim!
bool b = toolbelt::ends_with("Hello, World", "World"); // true
```

### unit_tests.hpp

Fairly simple way to do unit tests.

```cpp
toolbelt::test_suite suite;

suite.test("2 + 2 is 4", []() {
    return ExpectEquals(2 + 2, 4);
});

suite.test("true and true is true", []() {
    return ExpectTrue(true && true);
});

// runs the tests, returns true if ALL tests passed
auto result = suite.run_tests();
```

## License

MIT
