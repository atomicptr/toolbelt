#ifndef __TESTS_MAKE_SMART_TEST_HPP__
#define __TESTS_MAKE_SMART_TEST_HPP__

#include <toolbelt/unit_tests.hpp>

#include <toolbelt/make_smart.hpp>

// cuz, if you don't know how to call something just call it widget
struct widget_t {
    std::string name;
    int x;
    int y;
};

widget_t* widget_construct(std::string name, int x, int y) {
    widget_t *w = new widget_t;

    w->name = name;
    w->x = x;
    w->y = y;

    return w;
}

void widget_destruct(widget_t *w) {
    delete w;
}


void add_make_smart_tests(toolbelt::test_suite& s) {
    s.test("can make C constructor/destructor functions smarter", []() {
        auto widget_ptr = toolbelt::make_smart<widget_t>(widget_construct, widget_destruct, "widget#1", 13, 37);

        return ExpectEquals(std::string{"widget#1"}, widget_ptr->name);
    });

    s.test("makes sure the destructor is called", []() {
        auto was_deleted = false;

        auto custom_destructor = [&was_deleted](widget_t* w) {
            was_deleted = true;
            delete w;
        };

        if(!was_deleted) {
            auto widget_ptr = toolbelt::make_smart<widget_t>(widget_construct, custom_destructor, "widget#2", 42, 42);
        }

        return ExpectTrue(was_deleted);
    });
}

#endif
