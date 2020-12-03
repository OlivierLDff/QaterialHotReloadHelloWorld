// MIT License
//
// Copyright (c) 2020 Olivier Le Doeuff
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __HELLOWORLD_HPP__
#define __HELLOWORLD_HPP__

#include <HelloWorld/Details/Property.hpp>
#include <QOlm/QOlm.hpp>
#include <QObject>

class Foo : public QObject
{
    Q_OBJECT
    HELLOWORLD_REGISTER_UNCREATABLE_TO_QML(Foo);

public:
    Foo(QObject* parent = nullptr) : QObject(parent) {}

    HELLOWORLD_PROPERTY(QString, bar, Bar);
    HELLOWORLD_PROPERTY(int, foo, Foo);
};

class FooList : public qolm::QOlm<Foo>
{
    Q_OBJECT
    HELLOWORLD_REGISTER_UNCREATABLE_TO_QML(FooList);

public:
    FooList(QObject* parent = nullptr) : qolm::QOlm<Foo>(parent) {}

public Q_SLOTS:
    void appendFoo(int foo, QString bar)
    {
        auto* obj = new Foo(this);

        obj->setFoo(foo);
        obj->setBar(bar);

        append(obj);
    }
};

class Bar : public QObject
{
    Q_OBJECT
    HELLOWORLD_REGISTER_TO_QML(Bar);

public:
    Bar(QObject* parent = nullptr) : QObject(parent) {}

    HELLOWORLD_PROPERTY(QString, bar, Bar);
    HELLOWORLD_PROPERTY(int, foo, Foo);
};

class FooBar : public QObject
{
    Q_OBJECT
    HELLOWORLD_REGISTER_UNCREATABLE_TO_QML(FooBar);

public:
    FooBar(QObject* parent = nullptr) : QObject(parent), _bar(new Bar(this)), _foo(new Foo(this)) {}

public:
    HELLOWORLD_PTR_RO(Bar, bar, Bar);
    HELLOWORLD_PTR_RO(Foo, foo, Foo);
};

class Application : public QObject
{
    Q_OBJECT
    HELLOWORLD_SINGLETON_IMPL(Application, instance, Instance);

public:
    Application(QObject* parent = nullptr) : QObject(parent), _fooBar(new FooBar(this)), _foos(new FooList(this)) {}

public:
    HELLOWORLD_PTR_RO(FooBar, fooBar, FooBar);
    HELLOWORLD_PTR_RO(FooList, foos, Foos);

public:
    void populateDemo()
    {
        foos()->append(new Foo(foos()));
        foos()->append(new Foo(foos()));

        foos()->at(0)->setFoo(12);
        foos()->at(0)->setBar("Foo 0");

        foos()->at(1)->setFoo(-123);
        foos()->at(1)->setBar("Foo 1");

        fooBar()->foo()->setFoo(9999);
        fooBar()->foo()->setBar("Foo from FooBar");

        fooBar()->bar()->setFoo(1);
        fooBar()->bar()->setBar("Bar from FooBar");
    }
};

inline void registerHelloWorldQmlTypes()
{
    Foo::registerToQml();
    FooList::registerToQml();
    Bar::registerToQml();
    FooBar::registerToQml();
    Application::registerSingleton();
}

#endif
