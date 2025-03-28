## How is memory managed in C++?

Memory in C++ can be managed either automatically or manually.

Automatic memory management includes stack memory and static memory.
Stack variables are destroyed automatically when they go out of scope (for example, at the end of a function or method). This kind of memory is fast but limited in size (though still large enough in practice).
Static variables are initialized when the program starts (or sometimes lazily upon first use).

Manual memory management is when memory is allocated using new and deallocated using delete.
Previously, malloc and free were used (but those don’t call constructors or destructors, which goes against OOP principles).

Modern C++ uses smart pointers (I mentioned them during the first interview stage).
In short: std::shared_ptr uses reference counting (similar to Unreal Engine’s GarbageCollector that marks objects for deletion)
std::unique_ptr does not allow copy construction and uses move semantics only
std::weak_ptr doesn’t increase the reference count, but tracks the shared object; to access it, you must call .lock() to get a shared_ptr

## What is polymorphism? Types of polymorphism?

I would say polymorphism is a mechanism that allows the same function call to behave differently depending on the object.
It fits perfectly with the Strategy pattern. A common example from the game industry would be:

```
class Vampire : public Monster {};
class Zombie : public Monster {};
```
Monster* current_monster = SomeFactory(instructions);
current_monster->update();

There is also static polymorphism, but that refers more to “template magic” and is rarely mentioned in the context of basic overloading.

When I was studying at university, there was a joke:
A woman says to a programmer, “Tell me the three most important words!” (meaning: I love you),
and he replies: Encapsulation, Polymorphism, and Inheritance.

## What is a friend function?

A friend function is a function that is allowed to access the protected or private members of a class, even though it is not a member of that class.

There’s a joke that a friend gave me a C++ book, but the page with friend was missing.
Although using friend class is often considered bad practice, I’ve seen friend functions in real-world code.
Sometimes, when architecture is too rigid to handle a case cleanly, a programmer may resort to this kind of workaround.

## What is multithreading?

Multithreading is the ability to execute multiple operations in parallel.
It is important to distinguish between physical CPU threads and logical OS threads.
To avoid unnecessary overhead, it is recommended to use std::thread::hardware_concurrency() to get the number of concurrent threads supported by the system (a CPU may have 8 cores but 16 threads).

In C++, multithreading is done via std::thread (previously boost::thread) and is controlled using synchronization primitives like std::mutex, std::condition_variable.

It’s commonly used to improve performance, especially on multi-core systems.

## How can one optimise a C++ program?

First of all, you need to define what exactly you're optimizing, because sometimes we pay for speed with memory usage (e.g., complex data structures), sometimes we pay for compactness with slower computations — and often we trade all of that for code readability.

You should always start by identifying the bottleneck, and for that, profiling tools can help.
There are also compiler optimizations like -O2.
Inlining functions can also improve performance, but increases compilation unit size, so it’s better used for short functions.
When working with dynamic containers, it helps to preallocate memory using patterns like an object pool.

For networked or asynchronous functions, profiling is more complex, and you need to understand where the bottlenecks are likely to occur — typically in places where shared data is synchronized between threads or where we are waiting to some data(port listening and etc).
In these cases, lock-free algorithms and std::atomic can help.

In the game industry, the most optimized functions are always the ones called every tick or N times per second — such as rendering.
In those cases, it makes sense to update only the data that has changed.
That’s how most physics engines work — only objects affected by forces are updated.

You can also use mathematical optimizations, especially in graphics.
For example, I once wrote a mesh hit test algorithm:
Instead of checking every polygon, the mesh is first enclosed in a bounding sphere or AABB, and we check for intersection with that.
If the ray doesn’t hit the sphere, there’s no point in checking individual polygons — because it’s a necessary condition.

And there are many more techniques depending on the domain...

## What is the diamond problem?

The diamond problem occurs when two classes that share the same base are used as parents of a new derived class.
This creates ambiguity when calling functions from the shared base.

It can be resolved using virtual inheritance (preferred), or by explicitly calling the method:

```
class A { void print(); };
class B : public A {};
class C : public A {};
class D : public B, public C {};
```

D d;
d.B::print(); // OK but ugly
Very common interview question. In production code, it’s often found in the form of a mixed-in interface.
In post-Soviet countries, it’s even nicknamed rhomboid inheritance.