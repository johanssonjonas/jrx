JRX: A Reactive Extensions Library for C++
======================================

[Reactive extensions (ReactiveX, or Rx)](https://en.wikipedia.org/wiki/Reactive_extensions) is a programming paradigm for working with sequences of data, whether synchronous or asynchronous. It enables unified handling of data sources like databases, REST APIs, and event streams, making it ideal for modern reactive systems.

This project is a Rx implementation in modern C++, centered around the Observable<Element> class and designed with an object-oriented approach. While it shares concepts and terminology with other Rx implementations, it is entirely independent, with no shared code or direct connection to any other framework.

## License

This implementation is available under the MIT License, a permissive open-source license. This means you are free to use, modify, and distribute the code, even in commercial projects, as long as you include attribution to the original source.

## Quick Start

Follow these steps to quickly get started with JRX:

1. **Clone the Repository**  
   Clone the repository to your local machine:
	`
	git clone https://github.com/johanssonjonas/jrx.git
	`  
	`
	cd jrx
	`
   
2. **Run the Sample Application**  
   Use the provided build.sh script to compile and run the included sample project:
   ```
   ./build.sh
   ```
   
3. **Integrate into Your Project**
Add the .h, .hpp, and .cpp files from the jrx folder to your project. Include the main header file in your source code:
		```
		#include "jrx.h"
		```

4. **Integrate into Your Project**
	
	Here’s a minimal example to combine two streams and log the output:
	
	```cpp
	// Quick Start Example
	#include "jrx.h"
	
	int main() {
	    // Create a BehaviorSubject seeded with an initial value
	    auto observable1 = BehaviorSubject<int>::seeded(5);
	    int value1 = 0;
	
	    // Subscribe to the observable
	    observable1->subscribe([&](int value) {
	        value1 = value;
	        std::cout << "Got value: " << value << "\n";
	    });
	
	    // BehaviorSubject immediately emits its current value
	    // Output: "Got value: 5"
	
	    // Create a PublishSubject
	    auto observable2 = PublishSubject<int>::create();
	    int value2 = 0;
	
	    // Map, filter, and subscribe to the observable
	    observable2
	        ->map<int>([](int value) { return value * 2; }) // Multiply by 2
	        ->filter([](int value) { return value > 10; })  // Only allow values > 10
	        ->subscribe([&](int value) {
	            value2 = value;
	            std::cout << "Got value: " << value << "\n";
	        });
	
	    // Emit values
	    observable2->onNext(5);  // Filtered out (10 is not > 10)
	    observable2->onNext(10); // Output: "Got value: 20"
	
	    return 0;
	}
	```
	
## Longer example

Let's say we're retrieving data (the name and the age of a person) from two sources and want to combine the result into a single model, Person, containing this data. This is an example: 

	// Longer Example
	// Create two observables that will serve the data
    auto observable1 = Observable<string>::just("David");
    auto observable2 = Observable<string>::just("Smith");
    auto observable3 = ReplaySubject<int>::create(); // let's say this value is delivered at some other point
    
    // Combining two streams into a new stream that contains the age and name of a person
    auto ptr = Observable<Person>::combineLatest({
        { observable1, &Person::firstName },
        { observable2, &Person::lastName },
        { observable3, &Person::age },
    })
    // Ensure we're only receiving signals where the age is above 5
    ->filter([](Person value) {
        return value.age > 5.0f;
    })
    // Convert the person into a string for display
    ->map<string>([](Person value){
        return value.firstName + value.lastName + string(", ") + to_string(value.age) + string(" years old");
    })
    ->subscribe([print](auto value) {
        if (print) {
            std::cout << "Got a person '" << value << "'\n";
        }
    });
    
    observable3->onNext(12);
    
The really interesting part about this design pattern above is that the Person will be delivered to the subscribe-lambda not until all values have been set, which happens first at this line: 

    observable3->onNext(12);


## What JRX ...

###### ... is

* A standalone object oriented implementation of Rx for C++
* OOP–oriented, with a focus on readability and simplicity
* Usable in most modern C++ project (see [requirements](Documentation/Requirements))
* Decent featured with several operators, tools and utils
* Open Source

###### ... is **not**

* An implementation supported, nor in any way connected to, [reactivex.io](http://reactivex.io)
* A [concept](https://en.wikipedia.org/wiki/Reactive_programming)  not developed by me
Feature-wise, not in pace with certain [other implementations such as RxCpp](https://github.com/Reactive-Extensions/RxCpp)
* Not fully compatible with the standard, so some operators and features might behave differently if you've used previous implementations. 



## Resources

###### ... third party concept links

* [ReactiveX.io Operators](http://reactivex.io/documentation/operators.html)

###### ... basic usage

* [example source code](examples/example_1.cpp)

###### ... extending

* Have a look at the [map operator](jrx/jrx_operator_map.h) operator as it show a simple operator (few lines of code) which integrates nicely with the concept. 

## Requirements

Used for development:

* C++ Language Dialect: C++17 [-std=c++17]
* C++ Standard Library: libc++ (LLVM C++ standard library with C++ 11 support)

Fully tested with:

* Xcode 9.0

Partial tested in:

* Visual Studio 2017

## Installation

You can start using the library in three different ways:

1. **Integrate into an Existing Project**  
   Import the `.h`, `.hpp`, and `.cpp` files into your project structure. Ensure your build system includes the files in the compilation process.

2. **Use the Xcode Workspace**  
   Open the provided Xcode workspace to build and run the sample application directly. This is the quickest way to see the library in action.

3. **Compile from the Terminal**  
   Use the included `build.sh` script to compile and run the sample project:
   ```bash
   ./build.sh
   ```

## Extending the Library

To extend the library, start by exploring the `jrx.h` file, which contains all the core declarations and serves as the entry point for the library's functionality.

A great way to begin adding functionality is by implementing new **operators**, as they form the backbone of most extensions. Operators allow you to transform, filter, and compose observables, making them the primary tool for extending the reactive capabilities of the library.

In `jrx.h`, you'll also find the `config` namespace, which includes useful settings for development. Notably, it allows you to disable automatic memory management (reference counting). This can be helpful when extending the library, but it’s recommended to keep automatic memory management enabled unless you have a specific reason to turn it off.

## Contributing

Contributions to the library are welcome and appreciated! Here are some guidelines to follow:

- **Core Functionality**: The core functionality of the library should not be changed unless you’ve identified an obvious bug. Stability and consistency are a priority for the core components.
  
- **New Operators**: Suggestions for new operators are highly encouraged. Operators are the main way to extend the library and improve its utility.

- **Bug Fixes**: Found a bug? Feel free to submit a fix! Please include a clear description of the issue and any relevant test cases.

- **Performance Improvements**: Contributions aimed at optimizing the performance of the library are always appreciated. Ensure that your changes do not compromise the library’s stability or readability.

When contributing, please submit a pull request with a clear description of your changes. Make sure your code adheres to the project’s style and includes any necessary tests.


## References

* [http://reactivex.io/](http://reactivex.io/)
* [Reactive Extensions GitHub (GitHub)](https://github.com/Reactive-Extensions)
