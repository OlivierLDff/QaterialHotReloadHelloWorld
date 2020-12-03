# QaterialHotReload HelloWorld

Minimal project that integrate QaterialHotReload demo. 
The goal of this project is to demonstrate persistance of state (stored in C++) when hot reloading and the minimal step required to integrate [Qaterial::HotReload](https://github.com/OlivierLDff/QaterialHotReload) in your project as an external dependency.

* HelloWorldCore in `lib` stores the state of the application.
* HelloWorldUi in `qml` stores qml files in qrc.
* HelloWorld in `app` is the final app.
* HelloWorldHotReload in `app` in hold the state in C++, and can hot reload qml file.

![image](https://user-images.githubusercontent.com/17255804/101096958-a0a39480-35c0-11eb-9c5c-31c238de6d24.png)

## How to build

```bash
#Configure
mkdir build && cd build
cmake ..

# Compile
cmake --build .

# Run App
./HelloWorld

# Run HotReload
./HelloWorldHotReload
```

## Author

[Olivier Le Doeuff](olivier.ldff@gmail.com)

## License

Licensed under MIT.
