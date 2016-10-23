# toolbelt

Collection of useful header-only util functions, written in C++14.

## Usage

Just pick whatever header file you need and drop it into your project.

## Content

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

## License

MIT
