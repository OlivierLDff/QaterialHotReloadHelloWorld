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

#ifndef __HELLOWORLD_PROPERTY_HPP__
#define __HELLOWORLD_PROPERTY_HPP__

// ───────────────────────────────────────
//                INCLUDE
// ───────────────────────────────────────

#include <QQmlEngine>

// ───────────────────────────────────────
//              DECLARATION
// ───────────────────────────────────────

#define _HELLOWORLD_Q_PROPERTY(type, attribute, Attribute)                                                                                 \
protected:                                                                                                                                 \
    Q_PROPERTY(type attribute READ attribute WRITE set##Attribute RESET reset##Attribute NOTIFY attribute##Changed)                        \
private:

#define _HELLOWORLD_Q_PROPERTY_RO(type, attribute, Attribute)                                                                              \
protected:                                                                                                                                 \
    Q_PROPERTY(type attribute READ attribute NOTIFY attribute##Changed)                                                                    \
private:

#define _HELLOWORLD_Q_PROPERTY_CONST(type, attribute)                                                                                      \
protected:                                                                                                                                 \
    Q_PROPERTY(type attribute READ attribute CONSTANT)                                                                                     \
private:

#define _HELLOWORLD_PROPERTY_MEMBER(type, attribute, def)                                                                                  \
private:                                                                                                                                   \
    type _##attribute = def;                                                                                                               \
                                                                                                                                           \
private:

#define _HELLOWORLD_PROPERTY_MEMBER_NOD(type, attribute)                                                                                   \
private:                                                                                                                                   \
    type _##attribute;                                                                                                                     \
                                                                                                                                           \
private:

#define _HELLOWORLD_PROPERTY_GETTER(type, attribute, override)                                                                             \
public:                                                                                                                                    \
    type attribute() const override { return _##attribute; }                                                                               \
                                                                                                                                           \
private:

#define _HELLOWORLD_PROPERTY_GETTER_ABSTRACT(type, attribute)                                                                              \
public:                                                                                                                                    \
    virtual type attribute() const = 0;                                                                                                    \
                                                                                                                                           \
private:

#define _HELLOWORLD_PROPERTY_SETTER(type, attribute, Attribute, override)                                                                  \
public:                                                                                                                                    \
    virtual bool set##Attribute(const type& value) override                                                                                \
    {                                                                                                                                      \
        if(value != _##attribute)                                                                                                          \
        {                                                                                                                                  \
            _##attribute = value;                                                                                                          \
            Q_EMIT attribute##Changed(value);                                                                                              \
            return true;                                                                                                                   \
        }                                                                                                                                  \
        return false;                                                                                                                      \
    }                                                                                                                                      \
                                                                                                                                           \
private:

#define _HELLOWORLD_ATTRIBUTE_SETTER(type, attribute, Attribute, override)                                                                 \
public:                                                                                                                                    \
    virtual bool set##Attribute(const type& value) override                                                                                \
    {                                                                                                                                      \
        if(value != _##attribute)                                                                                                          \
        {                                                                                                                                  \
            _##attribute = value;                                                                                                          \
            return true;                                                                                                                   \
        }                                                                                                                                  \
        return false;                                                                                                                      \
    }                                                                                                                                      \
                                                                                                                                           \
private:

#define _HELLOWORLD_PROPERTY_SETTER_ABSTRACT(type, Attribute)                                                                              \
public:                                                                                                                                    \
    virtual bool set##Attribute(const type& value) = 0;                                                                                    \
                                                                                                                                           \
private:

#define _HELLOWORLD_PROPERTY_RESET(type, Attribute, def)                                                                                   \
public:                                                                                                                                    \
    void reset##Attribute() { set##Attribute(def); }                                                                                       \
                                                                                                                                           \
private:

#define _HELLOWORLD_PROPERTY_SIGNAL(type, attribute)                                                                                       \
Q_SIGNALS:                                                                                                                                 \
    void attribute##Changed(type attribute);                                                                                               \
                                                                                                                                           \
private:

#define _HELLOWORLD_ABSTRACT_PROPERTY_SHARED(type, attribute, Attribute, def)                                                              \
    _HELLOWORLD_PROPERTY_GETTER_ABSTRACT(type, attribute)                                                                                  \
    _HELLOWORLD_PROPERTY_SETTER_ABSTRACT(type, Attribute)                                                                                  \
    _HELLOWORLD_PROPERTY_RESET(type, Attribute, def)                                                                                       \
    _HELLOWORLD_PROPERTY_SIGNAL(type, attribute)

#define HELLOWORLD_ABSTRACT_PROPERTY_D(type, attribute, Attribute, def)                                                                    \
    _HELLOWORLD_Q_PROPERTY(type, attribute, Attribute)                                                                                     \
    _HELLOWORLD_ABSTRACT_PROPERTY_SHARED(type, attribute, Attribute, def)                                                                  \
private:

#define HELLOWORLD_ABSTRACT_PROPERTY(type, attribute, Attribute) HELLOWORLD_ABSTRACT_PROPERTY_D(type, attribute, Attribute, {})

#define HELLOWORLD_ABSTRACT_PROPERTY_RO_D(type, attribute, Attribute, def)                                                                 \
    _HELLOWORLD_Q_PROPERTY_RO(type, attribute, Attribute)                                                                                  \
    _HELLOWORLD_ABSTRACT_PROPERTY_SHARED(type, attribute, Attribute, def)                                                                  \
private:

#define HELLOWORLD_ABSTRACT_PROPERTY_RO(type, attribute, Attribute) HELLOWORLD_ABSTRACT_PROPERTY_RO_D(type, attribute, Attribute, {})

#define HELLOWORLD_IMPL_PROPERTY_D(type, attribute, Attribute, def)                                                                        \
    _HELLOWORLD_PROPERTY_MEMBER(type, attribute, def)                                                                                      \
    _HELLOWORLD_PROPERTY_GETTER(type, attribute, override)                                                                                 \
    _HELLOWORLD_PROPERTY_SETTER(type, attribute, Attribute, override)                                                                      \
private:

#define HELLOWORLD_IMPL_PROPERTY(type, attribute, Attribute) HELLOWORLD_IMPL_PROPERTY_D(type, attribute, Attribute, {})

#define _HELLOWORLD_PROPERTY_SHARED(type, attribute, Attribute, def)                                                                       \
    _HELLOWORLD_PROPERTY_MEMBER(type, attribute, def)                                                                                      \
    _HELLOWORLD_PROPERTY_GETTER(type, attribute, )                                                                                         \
    _HELLOWORLD_PROPERTY_SETTER(type, attribute, Attribute, )                                                                              \
    _HELLOWORLD_PROPERTY_RESET(type, Attribute, def)                                                                                       \
    _HELLOWORLD_PROPERTY_SIGNAL(type, attribute)

#define HELLOWORLD_PROPERTY_D(type, attribute, Attribute, def)                                                                             \
    _HELLOWORLD_Q_PROPERTY(type, attribute, Attribute)                                                                                     \
    _HELLOWORLD_PROPERTY_SHARED(type, attribute, Attribute, def)                                                                           \
private:

#define HELLOWORLD_PROPERTY(type, attribute, Attribute) HELLOWORLD_PROPERTY_D(type, attribute, Attribute, {})

#define HELLOWORLD_PROPERTY_RO_D(type, attribute, Attribute, def)                                                                          \
    _HELLOWORLD_Q_PROPERTY_RO(type, attribute, Attribute)                                                                                  \
    _HELLOWORLD_PROPERTY_SHARED(type, attribute, Attribute, def)                                                                           \
private:

#define HELLOWORLD_PROPERTY_RO(type, attribute, Attribute) HELLOWORLD_PROPERTY_RO_D(type, attribute, Attribute, {})

#define _HELLOWORLD_ATTRIBUTE_SHARED(type, attribute, Attribute, def)                                                                      \
    _HELLOWORLD_PROPERTY_MEMBER(type, attribute, def)                                                                                      \
    _HELLOWORLD_PROPERTY_GETTER(type, attribute, )                                                                                         \
    _HELLOWORLD_ATTRIBUTE_SETTER(type, attribute, Attribute, )

#define HELLOWORLD_PROPERTY_CONST_D(type, attribute, Attribute, def)                                                                       \
    _HELLOWORLD_Q_PROPERTY_CONST(type, attribute)                                                                                          \
    _HELLOWORLD_ATTRIBUTE_SHARED(type, attribute, Attribute, def)                                                                          \
private:

#define HELLOWORLD_PROPERTY_CONST(type, attribute, Attribute) HELLOWORLD_PROPERTY_CONST_D(type, attribute, Attribute, {})

#define HELLOWORLD_ATTRIBUTE_D(type, attribute, Attribute, def)                                                                            \
    _HELLOWORLD_ATTRIBUTE_SHARED(type, attribute, Attribute, def)                                                                          \
private:

#define HELLOWORLD_ATTRIBUTE(type, attribute, Attribute) HELLOWORLD_ATTRIBUTE_D(type, attribute, Attribute, {})

#define HELLOWORLD_ABSTRACT_ATTRIBUTE(type, attribute, Attribute)                                                                          \
    _HELLOWORLD_PROPERTY_GETTER_ABSTRACT(type, attribute)                                                                                  \
    _HELLOWORLD_PROPERTY_SETTER_ABSTRACT(type, Attribute)

#define HELLOWORLD_PROXY_IMPL(proxiedType, proxied, proxiedAttribute, ProxiedAttribute, type, attribute, Attribute, def)                   \
public:                                                                                                                                    \
    type attribute() const override final { return type(proxied ? type(proxied->proxiedAttribute()) : type(def)); }                        \
    bool set##Attribute(const type& value) override                                                                                        \
    {                                                                                                                                      \
        if(proxied)                                                                                                                        \
        {                                                                                                                                  \
            if(attribute() != value)                                                                                                       \
            {                                                                                                                              \
                proxied->set##ProxiedAttribute(proxiedType(value));                                                                        \
                Q_EMIT attribute##Changed(value);                                                                                          \
                return true;                                                                                                               \
            }                                                                                                                              \
            return false;                                                                                                                  \
        }                                                                                                                                  \
        return proxied;                                                                                                                    \
    }                                                                                                                                      \
                                                                                                                                           \
private:

#define _HELLOWORLD_PTR_GETTER(type, attribute, override)                                                                                  \
public:                                                                                                                                    \
    type* attribute() const override { return _##attribute; }

#define _HELLOWORLD_PTR_CONST_ONLY_GETTER(type, attribute, override)                                                                       \
public:                                                                                                                                    \
    const type* attribute() const override { return &_##attribute; }

#define _HELLOWORLD_PTR_CONST_GETTER(type, attribute, override)                                                                            \
public:                                                                                                                                    \
    _HELLOWORLD_PTR_CONST_ONLY_GETTER(type, attribute, override)                                                                           \
    type* attribute() override { return &_##attribute; }

#define _HELLOWORLD_PTR_SETTER(type, attribute, Attribute, override)                                                                       \
public:                                                                                                                                    \
    virtual bool set##Attribute(type* value) override                                                                                      \
    {                                                                                                                                      \
        if(value != _##attribute)                                                                                                          \
        {                                                                                                                                  \
            _##attribute = value;                                                                                                          \
            Q_EMIT attribute##Changed(value);                                                                                              \
            return true;                                                                                                                   \
        }                                                                                                                                  \
        return false;                                                                                                                      \
    }

#define _HELLOWORLD_ABSTRACT_PTR_GETTER(type, attribute)                                                                                   \
public:                                                                                                                                    \
    virtual type* attribute() const = 0;

#define _HELLOWORLD_ABSTRACT_PTR_SETTER(type, Attribute)                                                                                   \
public:                                                                                                                                    \
    virtual bool set##Attribute(type* value) = 0;

#define _HELLOWORLD_PTR_SIGNAL(type, attribute)                                                                                            \
Q_SIGNALS:                                                                                                                                 \
    void attribute##Changed(type* value);

#define HELLOWORLD_PTR(type, attribute, Attribute)                                                                                         \
    _HELLOWORLD_Q_PROPERTY(type*, attribute, Attribute)                                                                                    \
    _HELLOWORLD_PROPERTY_MEMBER(type*, attribute, nullptr)                                                                                 \
    _HELLOWORLD_PTR_GETTER(type, attribute, )                                                                                              \
    _HELLOWORLD_PTR_SETTER(type, attribute, Attribute, )                                                                                   \
    _HELLOWORLD_PROPERTY_RESET(type, Attribute, nullptr)                                                                                   \
    _HELLOWORLD_PTR_SIGNAL(type, attribute)                                                                                                \
private:

#define HELLOWORLD_PTR_RO(type, attribute, Attribute)                                                                                      \
    _HELLOWORLD_Q_PROPERTY_RO(type*, attribute, Attribute)                                                                                 \
    _HELLOWORLD_PROPERTY_MEMBER(type*, attribute, nullptr)                                                                                 \
    _HELLOWORLD_PTR_GETTER(type, attribute, )                                                                                              \
    _HELLOWORLD_PTR_SETTER(type, attribute, Attribute, )                                                                                   \
    _HELLOWORLD_PROPERTY_RESET(type, Attribute, nullptr)                                                                                   \
    _HELLOWORLD_PTR_SIGNAL(type, attribute)                                                                                                \
private:

#define HELLOWORLD_ABSTRACT_PTR(type, attribute, Attribute)                                                                                \
    _HELLOWORLD_Q_PROPERTY(type*, attribute, Attribute)                                                                                    \
    _HELLOWORLD_ABSTRACT_PTR_GETTER(type, attribute)                                                                                       \
    _HELLOWORLD_ABSTRACT_PTR_SETTER(type, Attribute)                                                                                       \
    _HELLOWORLD_PROPERTY_RESET(type, Attribute, nullptr)                                                                                   \
    _HELLOWORLD_PTR_SIGNAL(type, attribute)                                                                                                \
private:

#define HELLOWORLD_ABSTRACT_PTR_RO(type, attribute, Attribute)                                                                             \
    _HELLOWORLD_Q_PROPERTY_RO(type*, attribute, Attribute)                                                                                 \
    _HELLOWORLD_ABSTRACT_PTR_GETTER(type, attribute)                                                                                       \
    _HELLOWORLD_ABSTRACT_PTR_SETTER(type, Attribute)                                                                                       \
    _HELLOWORLD_PROPERTY_RESET(type, Attribute, nullptr)                                                                                   \
    _HELLOWORLD_PTR_SIGNAL(type, attribute)                                                                                                \
private:

#define HELLOWORLD_IMPL_PTR(type, attribute, Attribute)                                                                                    \
    _HELLOWORLD_PROPERTY_MEMBER(type*, attribute, nullptr)                                                                                 \
    _HELLOWORLD_PTR_GETTER(type, attribute, override)                                                                                      \
    _HELLOWORLD_PTR_SETTER(type, attribute, Attribute, override)                                                                           \
    _HELLOWORLD_PROPERTY_RESET(type, Attribute, nullptr)                                                                                   \
    _HELLOWORLD_PTR_SIGNAL(type, attribute)                                                                                                \
private:

#define HELLOWORLD_CONST_PTR(type, attribute, Attribute)                                                                                   \
    _HELLOWORLD_Q_PROPERTY_CONST(type*, attribute)                                                                                         \
    _HELLOWORLD_PROPERTY_MEMBER_NOD(type, attribute)                                                                                       \
    _HELLOWORLD_PTR_CONST_GETTER(type, attribute, )                                                                                        \
private:

#define HELLOWORLD_REGISTER_TO_QML(Type)                                                                                                   \
public:                                                                                                                                    \
    static void registerToQml(const char* uri = "HelloWorld",                                                                              \
        const int majorVersion = 1,                                                                                                        \
        const int minorVersion = 0,                                                                                                        \
        const char* name = #Type)                                                                                                          \
    {                                                                                                                                      \
        qmlRegisterType<Type>(uri, majorVersion, minorVersion, name);                                                                      \
    }

#define HELLOWORLD_REGISTER_UNCREATABLE_TO_QML(Type)                                                                                       \
public:                                                                                                                                    \
    static void registerToQml(const char* uri = "HelloWorld",                                                                              \
        const int majorVersion = 1,                                                                                                        \
        const int minorVersion = 0,                                                                                                        \
        const char* name = #Type)                                                                                                          \
    {                                                                                                                                      \
        qmlRegisterUncreatableType<Type>(uri, majorVersion, minorVersion, name, "");                                                       \
    }                                                                                                                                      \
                                                                                                                                           \
private:

#define HELLOWORLD_SINGLETON_IMPL(Class, name, Name)                                                                                       \
public:                                                                                                                                    \
    static Class& name()                                                                                                                   \
    {                                                                                                                                      \
        static Class ret;                                                                                                                  \
        return ret;                                                                                                                        \
    }                                                                                                                                      \
    static QObject* set##Name(QQmlEngine* qmlEngine, QJSEngine* jsEngine)                                                                  \
    {                                                                                                                                      \
        Q_UNUSED(jsEngine)                                                                                                                 \
        Q_UNUSED(qmlEngine)                                                                                                                \
        QObject* ret = &name();                                                                                                            \
        QQmlEngine::setObjectOwnership(ret, QQmlEngine::CppOwnership);                                                                     \
        return ret;                                                                                                                        \
    }                                                                                                                                      \
    static void registerSingleton(const char* uri = "HelloWorld",                                                                          \
        const int majorVersion = 1,                                                                                                        \
        const int minorVersion = 0,                                                                                                        \
        const char* n = #Class)                                                                                                            \
    {                                                                                                                                      \
        qmlRegisterSingletonType<Class>(uri, majorVersion, minorVersion, n, &Class::set##Name);                                            \
    }                                                                                                                                      \
                                                                                                                                           \
private:

#endif
