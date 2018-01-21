JRX: A Reactive Extensions Library for C++17
======================================

[Reactive extensions (ReactiveX, or Rx)](https://en.wikipedia.org/wiki/Reactive_extensions) is an development concept that operate on sequences of data regardless of whether the data is synchronous or asynchronous, thus suitable for modern development projects with several data sources such as databases, REST APIs, etc. 

Rx is expressed through the `Observable<Element>` class.

This is **one** Rx implementation in C++, targeting modern versions of the language, with an object oriented approach. 

The port includes many concepts and terminologies as other implementations, but share no code nor is it connected in any other way. 


## What JRX ...

###### ... is

* A standalone object oriented implementation of Rx for C++
* Usable in most modern C++ project (see [requirements](Documentation/Requirements))
* Decent featured with several operators, tools and utils
* Open Source

###### ... is **not**

* An implementation supported, nor in any way connected to, [reactivex.io](http://reactivex.io)
* A [concept](https://en.wikipedia.org/wiki/Reactive_programming)  not developed by me
* Featured wise not in pace with certain [other implementations such as RxCpp](https://github.com/Reactive-Extensions/RxCpp)
* Below the surface technically equivalent with other Rx library – so functionality and behaviour might differ.



## Resources

###### ... third party concept links

* [ReactiveX.io Operators](http://reactivex.io/documentation/operators.html)

###### ... basic ussage

* with the example app. [Running Example App](Documentation/ExampleApp.md)
* with operators in playgrounds. [Playgrounds](Documentation/Playgrounds.md)
* [Online documentation](./docs/html/index.html)

###### ... extending

## Requirements

Used for development:

* C++ Language Dialect: C++17 [-std=c++17]
* C++ Standard Library: libc++ (LLVM C++ standard library with C++ 11 support)

Fully tested with:

* Xcode 9.0

Partial tested in:

* Visual Studio 2017

## Installation

Include all the source files into your project. 

Header files: `.h``.hpp`<br>
Source files: `.cpp`


## References

* [http://reactivex.io/](http://reactivex.io/)
* [Reactive Extensions GitHub (GitHub)](https://github.com/Reactive-Extensions)