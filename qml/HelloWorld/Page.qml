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

import QtQuick 2.0
import QtQuick.Controls 2.0

import HelloWorld 1.0 as HW

Page
{
  id: root

  anchors.fill: parent

  // Application is coming from singleton registered from C++
  readonly property HW.Application application: HW.Application

  Column
  {
    anchors.centerIn: parent

    width: 500

    spacing: 8

    GroupBox
    {
      title: "Application Objects"

      width: parent.width

      Column
      {
        Label
        {
          text: `root.application: ${root.application}`
        }

        Label
        {
          text: `root.application.fooBar: ${root.application.fooBar}`
        }

        Label
        {
          text: `root.application.fooBar.bar: ${root.application.fooBar.bar}`
        }

        Label
        {
          text: `root.application.foos: ${root.application.foos}`
        }

        Label
        {
          text: `root.application.foos.count: ${root.application.foos.count}`
        }
      }
    }

    GroupBox
    {
      title: "FooList Objects"

      width: parent.width

      Column
      {
        ListView
        {
          width: contentItem.childrenRect.width
          height: contentItem.childrenRect.height
          interactive: false

          model: root.application.foos
          delegate: Row
          {
            id: _fooDelegate
            readonly property HW.Foo foo: model.qtObject

            Label
            {
              anchors.verticalCenter: parent.verticalCenter
              width: 230
              text: foo ? `${foo.foo}, "${foo.bar}", ${foo}` : ``
            }

            Button
            {
              width: 40
              text: "--"
              onClicked: () => --_fooDelegate.foo.foo
            }

            Button
            {
              width: 40
              text: "++"
              onClicked: () => ++_fooDelegate.foo.foo
            }

            Button
            {
              text: "Delete"
              onClicked: () => HW.Application.foos.remove(foo)
            }
          }
        }

        Button
        {
          text: "Add Foo"
          onClicked: () => HW.Application.foos.appendFoo(Math.random()*100, `Foo ${root.application.foos.count}`)
        }
      }
    }

    GroupBox
    {
      title: "Bar"

      width: parent.width

      HW.Bar
      {
        id: bar
        bar: "string"
        foo: 123
      }

      Column
      {
        Label
        {
          text: `bar ${bar}`
        }
        Label
        {
          text: `bar.string "${bar.bar}"`
        }
        Label
        {
          text: `bar.foo ${bar.foo}`
        }
      }
    }
  }
}
