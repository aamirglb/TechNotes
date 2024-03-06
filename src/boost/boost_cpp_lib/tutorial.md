# A guide to getting started with boost::asio

[Article Link](https://www.gamedev.net/blog/950/entry-2249317-a-guide-to-getting-started-with-boostasio/?pg=1)

boost::asio is "is a cross-platform C++ library for network and low-level I/O programming that provides developers with a consistent asynchronous model using a modern C++ approach." It currently has many users and is part of the boost family of libraries.

Before getting started, we will want to read over the boost::asio overview. It covers a lot of useful information that we should understand the basics of first. This guide is not meant to teach the complete ins and outs of boost::asio library; that is what the documentation is for! This guide will point us in a practical direction for learning the library and getting on our way to using it in our own applications.

In addition, we might also want to check out the blog of the boost::asio author as well. There is a plethora of tidbits of useful information there as well as many stream of conscious posts by the author. Another good site to reference is this one. It is actually a book that has been released online so consider supporting that author for their hard work!

At this time, the purpose of this guide needs to be explained. This guide is not going to teach any programming languages. The reader must already be comfortable with C++ to get the most out of the boost libraries, especially boost::asio. This guide is not going to teach network programming in general. The reader should already understand that topic. This guide will simply help get the reader started using the boost::asio library for practical network programming. In other words, this guide's goal is to direct the reader along a path of learning that is most useful for learning boost::asio. It is still up to the reader to spend the time reading the official docs and doing the other research required when using a new library for their projects.

Another thing to note is the examples were compiled only on Windows. While an effort has been made to make them mostly portable, there are a few that might need a few logic changes to compile on other platforms or using other compilers. All of the source examples have been zipped up and attached. No project files are included, only the actual source files. This is to make looking over the code more convenient if we do not want to copy and paste the examples. Boost must be properly setup and installed to use them though! We can refer to the main boost site for such instructions.

Lastly, this guide is written from my own personal opinions and experiences. While I work hard to make sure no misinformation is spread, sometimes mistakes are made. Please point out any errors or inconsistency if you are also experienced in this domain and I will be happy to correct them.

Without further adieu, let us get started!

1. The basics of io_service
2. Getting to know boost::bind
3. Giving io_service some work to do
4. Serializing our workload with strand
5. Error handling
6. Timers
7. Networking basics: connectors and acceptors (TCP)
8. Networking basics: binary protocol sending and receiving (TCP)
9. A boost::asio network wrapper (TCP)
10. The road ahead

[page]

## 1. The basics of io_service

The core object of boost::asio is io_service. This object is like the brain and the heart of the library. We will start out with a simple example to get acquainted with it. In this example, we will be calling the run member function. If we check the function's documentation, "the run() function blocks until all work has finished and there are no more handlers to be dispatched, or until the io_service has been stopped."

Example 1a
[spoiler]

```c++
#include
#include

int main( int argc, char * argv[] )
{
boost::asio::io_service io_service;

io_service.run();

std::cout << "Do you reckon this line displays?" << std::endl;

return 0;
}
```
[/spoiler]

Based on what the docs say, we should expect the line of text to be displayed, right? I mean we are not really giving it anything to do explicitly, so unless something goes on behind the scenes we do not know of, the function should not block. If we run the program, we get the expected results; we see the line of text.

This example might have already set alarms off for some readers. What if our program runs out of work? That is not useful at all; boost::asio is definitely not for me! Not so fast partner, let us not get ahead of ourselves so soon. The developers of boost::asio thought about this as well. To address this issue, they created a work class. The work class is a "class to inform the io_service when it has work to do." In other words, as long as an io_service has a work object associated with it, it will never run out of stuff to do. To test this, consider the next example.

Example 1b
[spoiler]

#include
#include

int main( int argc, char * argv[] )
{
boost::asio::io_service io_service;
boost::asio::io_service::work work( io_service );

io_service.run();

std::cout << "Do you reckon this line displays?" << std::endl;

return 0;
}

[/spoiler]

If we run the example, we will get the expected results once again. We do not see the text and the program does not quit. Unfortunately, we now have no way of performing a graceful exit with the tools we know of now. There are ways around this, but we will not cover them until later since we are only getting our feet wet for the moment.

From these examples, we can already see two different design approaches that are possible with boost::asio. There are many, many more! What if we do not like this idea of having to block a thread for doing work? What if we want the ability to do work whenever and wherever we want? Is this even possible? The answer is yes!

In the next example, we will simply simulate a loop and call the poll function of the io_service. The poll function "runs the io_service object's event processing loop to execute ready handlers."

Example 1c
[spoiler]

#include
#include

int main( int argc, char * argv[] )
{
boost::asio::io_service io_service;

for( int x = 0; x < 42; ++x )
{
io_service.poll();
std::cout << "Counter: " << x << std::endl;
}

return 0;
}

[/spoiler]

If we run the example, we will see 42 lines worth of text outputted to the console and then the program exits. What if we had a work object assigned to the io_service? Would the behavior change?

Example 1d
[spoiler]

#include
#include

int main( int argc, char * argv[] )
{
boost::asio::io_service io_service;
boost::asio::io_service::work work( io_service );

for( int x = 0; x < 42; ++x )
{
io_service.poll();
std::cout << "Counter: " << x << std::endl;
}

return 0;
}

[/spoiler]

When we run this program, we get the exact same output and results as before. This is because the poll function will not block while there is more work to do. It simply executes the current set of work and then returns. In a real program, the loop would be based on some other event, but for the sake of simplicity, we are just using a fixed one.

This example speaks volumes to how the work class operates under the hood. Imagine for a second if the work object supplied the io_service object with work in a manner that new work was added from inside the work handler invoked by the io_service. In that case, poll should never run out of work to do since new work would always be added. However, this is clearly not the case. The work is added outside the handler so everything will work as intended.

Great! We can now choose between using the run and poll functions depending on how we need our program setup. To add more flexibility, the run_one and poll_one functions were created. These allow programmers to fine tune their programs as needed. At this point we need to step back and consider what we know so far. To get the io_service working for us, we have to use the run or poll family of functions. Run will block and wait for work if we assign it a work object while the poll function does not. In essence, the names of the functions match their functionality.

There is one more little loose end we need to tie up. What if we want a work object removed from an io_service? Looking through the docs, there does not seem to be a function provided to do this. In order to achieve this functionality, we must make use of a pointer to a work object instead. Keeping with the boost library, we will use shared_ptr, a smart pointer class.

Example 1e
[spoiler]

#include
#include
#include

int main( int argc, char * argv[] )
{
boost::asio::io_service io_service;
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( io_service )
);

work.reset();

io_service.run();

std::cout << "Do you reckon this line displays?" << std::endl;

return 0;
}

[/spoiler]

If we run the program, we will see the line of text displayed. This effectively shows us how we can remove a work object from an io_service. This type of functionality is important in the case we want to gracefully finish all pending work but not stop it prematurely. There is a caveat to this that will be covered later though.

Now that we know how to drive the io_service with one thread, we need to figure out what would be required for more threads. The io_service docs page tell us that "multiple threads may call the run() function to set up a pool of threads from which the io_service may execute handlers. All threads that are waiting in the pool are equivalent and the io_service may choose any one of them to invoke a handler." Sounds easy enough right? Since the boost library also provides a thread library, we will make use of that for the next example.

Example 1f
[spoiler]

#include
#include
#include
#include

boost::asio::io_service io_service;

void WorkerThread()
{
std::cout << "Thread Start\n";
io_service.run();
std::cout << "Thread Finish\n";
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( io_service )
);

std::cout << "Press [return] to exit." << std::endl;

boost::thread_group worker_threads;
for( int x = 0; x < 4; ++x )
{
worker_threads.create_thread( WorkerThread );
}

std::cin.get();

io_service.stop();

worker_threads.join_all();

return 0;
}

[/spoiler]

This example introduces the stop member function. The stop function will signal the io_service that all work should be stopped, so after the current batch of work finishes, no more work will be done. Another change in this example is the io_service object has now been made global. This was only to keep things simple as more complex mechanisms have to be used otherwise. If we run the program, we get the 4 thread start messages on the console and after we hit return, we get the four thread finish messages, as expected.

What should really stand out is how simple and easy it is to make our threaded programs scale. By simply adding more worker threads, we can support more and more concurrency for processing work through the io_service object. As mentioned before, if we had associated a work object with the io_service and wanted to let all queued work finish, we would not call stop but rather destroy the work object. Care has to be taken though. If we want all work to finish but keep giving the io_service more things to do, then it will never exit! In that case, at some point, we would want to call the stop function to ensure the system actually stops.

Now that we have an idea of the different ways to drive the io_service object, we can move on to the next set of topics we have to learn before being able to actually do the real work.

[page]

## 2. Getting to know boost::bind

Before we look at how to give the io_service real work to do, we need to establish a basic understanding of another boost library, boost::bind. The first time I saw boost::bind I had no idea of what was going on with it and really had no idea why such a library would be needed. After using boost::asio though, I could easily see and appreciate how useful the library is. At this time, I would recommend the reader to read up on the boost::bind docs a little to have an idea of what the library does before moving on.

Wrapping a function invocation with boost::bind creates an object. Consider the following example.

Example 2a
[spoiler]

#include
#include

void F1()
{
std::cout << __FUNCTION__ << std::endl;
}

int main( int argc, char * argv[] )
{
boost::bind( &F1 );
return 0;
}

[/spoiler]

If we run the program, we would see no output. This is because we created a function invocation object, but did not actually call it. To call it, we simply use the () operator of the object.

Example 2b
[spoiler]
#include
#include

void F1()
{
std::cout << __FUNCTION__ << std::endl;
}

int main( int argc, char * argv[] )
{
boost::bind( &F1 )();
return 0;
}
[/spoiler]

Now when we run the example, we see the output! What if we had arguments to pass? Adding them is pretty easy as well.

Example 2c
[spoiler]
#include
#include

void F2( int i, float f )
{
std::cout << "i: " << i << std::endl;
std::cout << "f: " << f << std::endl;
}

int main( int argc, char * argv[] )
{
boost::bind( &F2, 42, 3.14f )();
return 0;
}
[/spoiler]

If we run the program, we will see the expected output. We could easily swap out the hard coded values with variables as well. There are a couple of important things here to notice as well. The parameters belong to the function object and are not passed through the calling operator! When we bind the parameters along with the function, we have to match the signature exactly or we will get a ton of hard to read errors that will be difficult to look through at first. When we get errors with boost::bind, we need to compare our function declarations and the parameters that are being used to check for any type mismatches.

The last example we have in our crash course to boost::bind will show using bind of a class member function. This example is similar to before, but there is one important difference.

Example 2d
[spoiler]
#include
#include

class MyClass
{
public:
void F3( int i, float f )
{
std::cout << "i: " << i << std::endl;
std::cout << "f: " << f << std::endl;
}
};

int main( int argc, char * argv[] )
{
MyClass c;
boost::bind( &MyClass::F3, &c, 42, 3.14f )();
return 0;
}
[/spoiler]

We must pass the address of the class object to invoke after the class function! If we were calling bind from inside the class, we could then use the this pointer or subsequently shared_from_this() if our class supported it. Please note in all these examples, we are simply using the () operator to call the object. In practice, we only do this if we are receiving a boost::bind object to actually invoke. Otherwise, we would just use normal semantics to call the function! Be sure to refer to the boost::bind documentation for more information and references.

Now that boost::bind has been quickly introduced, we must also go over another important concept. In the threaded boost::asio example, the io_service object as made global and moved to the top of the program. For any modular and reusable code this is not desired. However, if we were to try to use io_service with boost::bind, we would get a non-copyable error, since the io_service cannot be copied and that is what boost::bind does for us behind the scenes. To get around this, we must make use of shared_ptr again.

Rather than using a regular io_service object, we must use a shared_ptr object of io_service and pass that around. The shared_ptr is a reference counted smart pointer so it is copyable and thus compatible with boost::bind. The same applies for many other non-copyable objects as well; we have to wrap them in shared_ptrs to pass them if we need to. Let us revisit the threaded example using our newly learned concepts.

Example 2e
[spoiler]
#include
#include
#include
#include
#include

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
std::cout << "Thread Start\n";
io_service->run();
std::cout << "Thread Finish\n";
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

std::cout << "Press [return] to exit." << std::endl;

boost::thread_group worker_threads;
for( int x = 0; x < 4; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

std::cin.get();

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

Pretty cool, huh? We can use shared_ptr on the io_service to make it copyable so we can bind it to the worker thread function that we use as the thread handler. When we run the program, we should get the exact same behavior as before. At this point it is strongly advised to read up more on boost::bind, shared_ptr, and even the boost::asio topics already covered if they do not feel comfortably understood yet. We will be making heavy use of them all very soon!

When working with threaded programs, we must ensure that we synchronize access to any global data or shared data. Our previous thread example has a flaw that was hackishly worked around. Does it stand out? The std::cout object is a global object. Writing to it from different threads at once can cause output formatting issues. To ensure we do not run into such issues since they hamper debugging efforts, we will want to make use of a global mutex. The boost::thread library provides us with the classes we need to accomplish this.

The next example will make use of a mutex object. We should also read up on the synchronization topics as well. We will simply correct the previous example to handle the output as it should be handled now. In addition, we will also make use of the thread id functionality of boost::thread to identify our threads. More information about that feature can be found here in addition.

Example 2f
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id() <<
"] Thread Start" << std::endl;
global_stream_lock.unlock();

io_service->run();

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id() <<
"] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Press [return] to exit." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 4; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

std::cin.get();

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

It is important to understand the basics of the mutex object as well. If we lock once, we have to unlock as soon as it is done. We cannot recursively lock with this specific type of mutex, although there are other types that allow that. If we do, the thread will deadlock which is something we never want to happen. A lot of the benefits of concurrency are reduced when we have to wait on the global output lock, but for the sake of having correct multi-threaded code to work from, it is a must for now. Eventually, we will want to implement our own custom logging scheme that avoids such issues, but we can cover that issue later.

All of the prerequisites have been covered now. We will make use of the boost::bind library a lot in the future so be sure the concepts are comfortable before continuing on. For more interesting reading, check out How the Boost Bind Library Can Improve Your C++ Programs and Fast C++ Delegate: Boost.Function 'drop-in' replacement and multicast. Boost::bind certainly provides a great deal of flexibility, but at a cost the user should be aware of before using in production code.

[page]

## 3. Giving io_service some work to do

Now we can finally get to doing the real work! We will be reusing the previous example as our base, so our examples are multi-threaded ready. If the io_service is the brain and heart of the boost::asio library, the io_service member functions post and dispatch would be the arms and legs. The post function "is used to ask the io_service to execute the given handler, but without allowing the io_service to call the handler from inside this function." The dispatch function "guarantees that the handler will only be called in a thread in which the run(), run_one(), poll() or poll_one() member functions is currently being invoked. The handler may be executed inside this function if the guarantee can be met."

So the fundamental difference is that dispatch will execute the work right away if it can and queue it otherwise while post queues the work no matter what. Both of the functionality are really important as the function we will use will depend on the context that it is being used in. Remember earlier the remarks about how the internals of the work class worked? If the work class were to use dispatch over and over, it might be possible the work never finished for a poll call, but if the work called post, it could.

Let us get started! We will start out with a simple Fibonacci calculation. To make things more interesting we will add in some time delays to show the true nature of the power of boost::asio. We will also reduce the number of worker threads to just 2. The actual value that we will want to use in a multi-threaded program will vary depending on a number of factors, but that will be talked about later.

Example 3a
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

io_service->run();

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

size_t fib( size_t n )
{
if ( n <= 1 )
{
return n;
}
boost::this_thread::sleep(
boost::posix_time::milliseconds( 1000 )
);
return fib( n - 1 ) + fib( n - 2);
}

void CalculateFib( size_t n )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Now calculating fib( " << n << " ) " << std::endl;
global_stream_lock.unlock();

size_t f = fib( n );

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] fib( " << n << " ) = " << f << std::endl;
global_stream_lock.unlock();
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] The program will exit when all work has finished."
<< std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread(
boost::bind( &WorkerThread, io_service )
);
}

io_service->post( boost::bind( CalculateFib, 3 ) );
io_service->post( boost::bind( CalculateFib, 4 ) );
io_service->post( boost::bind( CalculateFib, 5 ) );

work.reset();

worker_threads.join_all();

return 0;
}
[/spoiler]

In this example, starting in main, we post 3 function objects to the io_service via the post function. In this particular case, since the current thread does no call the io_service run or poll function, dispatch would also call the post function and not execute the code right away. After we give the io_service work, through post, we reset the work object to signal once the work has been completed that we wish to exit. Finally, we wait on all the threads to finish as we have with the join_all function.

Our fib function simply calculates the sequence but we add in a time delay to slow things down to see our worker threads in action! We ultimate have to wrap the call with CalculateFib since we care about the return value and we want to see extra debugging information about when the function actually starts and completes.

Running the program, we should see the first two worker threads start on the first two units of work and once one worker thread has finished, it takes up the third unit of work. Once all work has been finished, the program exits.

Congratulations! We have now completed our first job! That was not so bad was it? Our program structure for working with boost::asio will be pretty generic overall. We can setup reusable worker threads to build up a pool of workers and when we send work to the io_service, it simply does it when it can. That is our basic example, let us consider another.

In this example, we show the difference between post and dispatch and how it can get us into trouble if we are not careful with what we do! We will use only one worker thread this time.

Example 3b
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

io_service->run();

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void Dispatch( int x )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id() << "] "
<< __FUNCTION__ << " x = " << x << std::endl;
global_stream_lock.unlock();
}

void Post( int x )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id() << "] "
<< __FUNCTION__ << " x = " << x << std::endl;
global_stream_lock.unlock();
}

void Run3( boost::shared_ptr< boost::asio::io_service > io_service )
{
for( int x = 0; x < 3; ++x )
{
io_service->dispatch( boost::bind( &Dispatch, x * 2 ) );
io_service->post( boost::bind( &Post, x * 2 + 1 ) );
boost::this_thread::sleep( boost::posix_time::milliseconds( 1000 ) );
}
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] The program will exit when all work has finished." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 1; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

io_service->post( boost::bind( &Run3, io_service ) );

work.reset();

worker_threads.join_all();

return 0;
}
[/spoiler]

If we run the program, we should see the problem here. We wanted an in order display of events, but instead it was out of order. This is because dispatch was used for some events and post for others. Dispatched events can execute from the current worker thread even if there are other pending events queued up. The posted events have to wait until the handler completes before being allowed to be executed. Keep this in mind when programming we can easily code ourselves into serious bugs if we depend on the order of such events!

It should also be noted that if we had more than one worker thread, we would actually get the expected results because of the sleep call, but the problem remains still. If we removed the sleep, we might get any order of output depending on who grabbed the lock mutex first. For example, running the program without the sleep one example output received was 0, 2, 1, 4, 3, 5. We have to be aware of such things when programming at this level so we do not get fooled by "correct" output that was simply a result of having setup our program in such a way that it was possible. These types of bugs are the hardest to track down once they happen so it is imperative we fully understand the API that we are using first before diving too deep in.

That pretty much wraps up, no pun intended, how we will pass our work to the io_service object. We simply setup our program to process the work via poll or run how we need and then we can call dispatch or post as needed. There is a lot of cool stuff we can do using these concepts now! At this point, we can now get into the other useful aspects of the boost::asio library.

[page]

## 4. Serializing our workload with strand

There will come a time when we will want to queue work to be done, but the order in which it is done is important. The strand class was created for such scenarios. The strand class "provides serialised handler execution." This means if we post work1 -> work2 -> work3 through a strand, no matter how many worker threads we have, it will be executed in that order. Neat!

With great power comes great responsibility though. We must understand the order of handler invocation for the strand class!

Order of handler invocation
Given:
a strand object s
an object a meeting completion handler requirements
an object a1 which is an arbitrary copy of a made by the implementation
an object b meeting completion handler requirements
an object b1 which is an arbitrary copy of b made by the implementation
if any of the following conditions are true:
s.post(a) happens-before s.post( b )
s.post(a) happens-before s.dispatch( b ), where the latter is performed outside the strand
s.dispatch(a) happens-before s.post( b ), where the former is performed outside the strand
s.dispatch(a) happens-before s.dispatch( b ), where both are performed outside the strand
then asio_handler_invoke(a1, &a1) happens-before asio_handler_invoke(b1, &b1).

Note that in the following case:

async_op_1(…, s.wrap( a ));
async_op_2(…, s.wrap( b ));
the completion of the first async operation will perform s.dispatch( a ), and the second will perform s.dispatch( b ), but the order in which those are performed is unspecified. That is, you cannot state whether one happens-before the other. Therefore none of the above conditions are met and no ordering guarantee is made.

It is absolutely imperative that we understand these conditions when using the strand class. If we do not, we can code a solution that has undefined behavior that might work most of the time, but every once in a while, it breaks down and it is extremely hard to figure out why! I have done this myself and learned quite a lot from it as a result.

Now we can consider an example where we do not use strand. We will remove the output locks on the std::cout object.

Example 4a
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

io_service->run();

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void PrintNum( int x )
{
std::cout << "[" << boost::this_thread::get_id()
<< "] x: " << x << std::endl;
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);
boost::asio::io_service::strand strand( *io_service );

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] The program will exit when all work has finished." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::this_thread::sleep( boost::posix_time::milliseconds( 1000 ) );

//strand.post( boost::bind( &PrintNum, 1 ) );
//strand.post( boost::bind( &PrintNum, 2 ) );
//strand.post( boost::bind( &PrintNum, 3 ) );
//strand.post( boost::bind( &PrintNum, 4 ) );
//strand.post( boost::bind( &PrintNum, 5 ) );

io_service->post( boost::bind( &PrintNum, 1 ) );
io_service->post( boost::bind( &PrintNum, 2 ) );
io_service->post( boost::bind( &PrintNum, 3 ) );
io_service->post( boost::bind( &PrintNum, 4 ) );
io_service->post( boost::bind( &PrintNum, 5 ) );

work.reset();

worker_threads.join_all();

return 0;
}

[/spoiler]

The output on my PC was as follows:
[spoiler]

[00154F88] The program will exit when all work has finished.
[001532B0] Thread Start
[00154FB0] Thread Start
[[001532B000154FB0] x: ] x: 21

[[001532B000154FB0] x: ] x: 34

[001532B0] x: 5
[00154FB0] Thread Finish
[001532B0] Thread Finish
Press any key to continue . . .
[/spoiler]

This is pretty much expected. Since we no longer lock the std::cout object and have multiple threads writing to it, the final output gets combined. Depending on how many worker threads we have and how many PC cores as well, the output might look a little different and even might show up correct! Conceptually though, we will know the correct output does not mean anything here since we are not properly synchronizing access to a global shared object!

Now, let us check out the next example, simply comment out all of the io_service->post and uncomment the strand.post function calls. Here is one output of the strand program.

[spoiler]
[00154F88] The program will exit when all work has finished.
[001532B0] Thread Start
[00154FB0] Thread Start
[001532B0] x: 1
[00154FB0] x: 2
[001532B0] x: 3
[00154FB0] x: 4
[001532B0] x: 5
[00154FB0] Thread Finish
[001532B0] Thread Finish
Press any key to continue . . .
[/spoiler]

No matter how many times we run the program, we should see a clean output each time for the x outputs. This is because the strand object is correctly serializing the event processing to only one thread at a time. It is very important that we notice that strand does not serialize work through only one thread either. If we check the previous output once again, more than one thread was used. So work will still execute serially, but it will execute through whichever worker thread is available at the time. We cannot program with the incorrect assumption the same thread will actually process all of the work! If we do, we will have bugs that will come back to bite us.

As mentioned before, in the past I had used strand the wrong way without realizing it and it caused all sorts of hard to find problems. Let us now take a look at such an example that is syntactically correct but logically incorrect as per our expectations.

Example 4b
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id() << "] Thread Start" << std::endl;
global_stream_lock.unlock();

io_service->run();

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void PrintNum( int x )
{
std::cout << "[" << boost::this_thread::get_id()
<< "] x: " << x << std::endl;
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);
boost::asio::io_service::strand strand( *io_service );

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] The program will exit when all work has finished." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 4; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::this_thread::sleep( boost::posix_time::milliseconds( 100 ) );
io_service->post( strand.wrap( boost::bind( &PrintNum, 1 ) ) );
io_service->post( strand.wrap( boost::bind( &PrintNum, 2 ) ) );

boost::this_thread::sleep( boost::posix_time::milliseconds( 100 ) );
io_service->post( strand.wrap( boost::bind( &PrintNum, 3 ) ) );
io_service->post( strand.wrap( boost::bind( &PrintNum, 4 ) ) );

boost::this_thread::sleep( boost::posix_time::milliseconds( 100 ) );
io_service->post( strand.wrap( boost::bind( &PrintNum, 5 ) ) );
io_service->post( strand.wrap( boost::bind( &PrintNum, 6 ) ) );

work.reset();

worker_threads.join_all();

return 0;
}
[/spoiler]

If we run this program quite a few times, we should see the expected 1, 2, 3, 4, 5, 6 output. However, every so often, we might see 2, 1, 3, 4, 5, 6 or some other variation where the events are switched. Sometimes we have to run a lot to get this to happen, while other times it might happen more frequently. The output remains clean though, but the order is just not as expected. This is because the work we are passing is guaranteed to be executed serially, but there is no guarantee to which the order of the work actually takes place as a result of the API functions we are using!

So if order is important, we have to go through the strand object API itself. If order is not important, then we can post across the io_service object and wrap our handler through the strand. It might seem obvious now, but if we were just getting started with this stuff on our own, it would be easy to misunderstand these basic concepts. The type of work we are posting will ultimately determine which interface we want to use as both are really useful. We will see more examples of the strand wrap member function being used in the future.

That pretty much covers the strand object. It is very powerful as it allows us to have synchronization without explicit locking. This is absolutely a must have feature when working with multi-threaded systems and maintaining efficiency across the board.

We almost have enough core concepts covered to move on into the networking aspect of the boost::asio library. The boost::asio library is huge with a ton of awesome features!

[page]

## 5. Error handling

The next concept we need to be aware of is error handling. In other words, what happens when our work function throws an exception? Boost::asio gives users two ways to handle this case. The errors are propagated through the handlers to the point where a thread calls a run or poll family of functions. The user can either handle the exception through a try/switch statement or they can opt to receive the exception through an error variable. For more information regarding boost, take a look at Error and Exception Handling. In addition, this Error Handling article covers some more useful points as well.

First, we will look at the exception method.

Example 5a
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

try
{
io_service->run();
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void RaiseAnException( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] " << __FUNCTION__ << std::endl;
global_stream_lock.unlock();

io_service->post( boost::bind( &RaiseAnException, io_service ) );

throw( std::runtime_error( "Oops!" ) );
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] The program will exit when all work has finished." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

io_service->post( boost::bind( &RaiseAnException, io_service ) );

worker_threads.join_all();

return 0;
}
[/spoiler]

In this example, we post work to the io_service that causes exceptions over and over. The work object is not destroyed either so the io_service should be kept busy. However, when we run the program, we see it exits. The reason is because the exception propagated through the run function, so the worker threads exited. Since all worker threads exited, the program is done since join_all returns. Immediately we can see how this could lead to problems if we are not careful since worker threads could be taken out one by one until the system has none left.

Now let us take a look at the error variable approach that is also possible.

Example 5b
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

boost::system::error_code ec;
io_service->run( ec );

if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ec << std::endl;
global_stream_lock.unlock();
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void RaiseAnException( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] " << __FUNCTION__ << std::endl;
global_stream_lock.unlock();

io_service->post( boost::bind( &RaiseAnException, io_service ) );

throw( std::runtime_error( "Oops!" ) );
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] The program will exit when all work has finished." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

io_service->post( boost::bind( &RaiseAnException, io_service ) );

worker_threads.join_all();

return 0;
}
[/spoiler]

Uh oh! When we run the program we get a crash. Through debugging, we can see that it is because the exception was not caught. This is because the error variable approach does not convert user exceptions to errors but rather boost::asio exceptions. This is very important to keep in mind! If we are passing our own work through an io_service, we have to keep true to C++ exception programming concepts. If the boost::asio library were to generate an error, it would either come as an exception if no error variable was used or it would be converted to an error variable. Depending on our application, we would choose the one that best fits what we need to do.

To further clarify once again if we are using the io_service for user work, we have to use exception handling if the work can generate exceptions. If we are using the io_service for boost::asio functions only, then we can use exception handling or the error variable as either will do. If we are using the io_service for both boost::asio functions and user work, then we can either use both methods or just the exception handling method, but not only the error variable if the work can generate an exception. That should be pretty straightforward to follow.

Now that we know of this little detail, we have to consider what should happen if an exception is actually generated. What we want to do also depends on the type of application we are developing. In other words, are exceptions system failures or context failures? If they are system failures, then we will want to call the stop member function of the io_service and make sure the work object is destroyed so our program gracefully exits. If exceptions are simply context failures, then we will want to setup the worker thread function to call the run function again so the worker thread does not die. Here is the previous example modified.

Example 5c
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

while( true )
{
try
{
boost::system::error_code ec;
io_service->run( ec );
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
break;
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void RaiseAnException( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] " << __FUNCTION__ << std::endl;
global_stream_lock.unlock();

io_service->post( boost::bind( &RaiseAnException, io_service ) );

throw( std::runtime_error( "Oops!" ) );
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] The program will exit when all work has finished." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

io_service->post( boost::bind( &RaiseAnException, io_service ) );

worker_threads.join_all();

return 0;
}
[/spoiler]

Now, when an exception occurs, it is outputted and the worker thread goes back to handling work. When the stop member function is called or the work object is destroyed, the run function no longer blocks as we have seen before, so the loop exits and then the thread finishes up. If we were to use this concept on the exception example, we would see an infinite output of the events since we are always posting new events to the queue. Obviously we would never want to have such a situation occur in a real program.

Most of the errors we will run into from the boost::asio library will come from the actual I/O interfaces such as sockets. We are not quite ready to dive into those yet. There are still more useful features of the boost::asio library we need to get exposed to first.

[page]

## 6. Timers

boost::asio provides a deadline_timer class that provides both synchronous and asynchronous interfaces. The docs page has a couple of good examples, so we can start right away with more advanced uses using what we already know about the boost::asio library.

In our first example, we will create a simple timer that expires in 5 seconds. There should be no surprises here as the docs go over this simple behavior.

Example 6a
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

while( true )
{
try
{
boost::system::error_code ec;
io_service->run( ec );
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
break;
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void TimerHandler( const boost::system::error_code & error )
{
if( error )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << error << std::endl;
global_stream_lock.unlock();
}
else
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] TimerHandler " << std::endl;
global_stream_lock.unlock();
}
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Press [return] to exit." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::asio::deadline_timer timer( *io_service );
timer.expires_from_now( boost::posix_time::seconds( 5 ) );
timer.async_wait( TimerHandler );

std::cin.get();

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

What if we want a recurring timer? We could have the timer object global, but that might introduce some issues down the line as shared objects are not thread safe. This is where boost::bind comes to rescue once again! By making a shared_ptr to the timer object, we can use boost::bind and pass the timer to its own handler so we can keep it recurring. Here is that example.

Example 6b
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

while( true )
{
try
{
boost::system::error_code ec;
io_service->run( ec );
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
break;
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void TimerHandler(
const boost::system::error_code & error,
boost::shared_ptr< boost::asio::deadline_timer > timer
)
{
if( error )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << error << std::endl;
global_stream_lock.unlock();
}
else
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] TimerHandler " << std::endl;
global_stream_lock.unlock();

timer->expires_from_now( boost::posix_time::seconds( 5 ) );
timer->async_wait( boost::bind( &TimerHandler, _1, timer ) );
}
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Press [return] to exit." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::shared_ptr< boost::asio::deadline_timer > timer(
new boost::asio::deadline_timer( *io_service )
);
timer->expires_from_now( boost::posix_time::seconds( 5 ) );
timer->async_wait( boost::bind( &TimerHandler, _1, timer ) );

std::cin.get();

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

As we can see, boost::bind allows us to do some pretty nifty things. The _1 parameter is an argument place holder. Since the TimerHandler function requires one parameter for the callback, we must reference this in the bind call. All in all, the _1 means "the first parameter, which will be supplied later". This blog has a nice post explaining this as well.

After running the program, we will see a timer that fires every 5 seconds. Great! Now we know how to make recurring timers in addition to the fire once type. Furthermore, we can utilize boost::bind to pass more parameters to the handler as needed. However, our timers will execute asynchronously so if we have more than one worker thread, it is possible that we execute a timer in one thread while we execute another event in another. Let us assume the timer handler and the work handler use the same shared object so we now have a non-thread safe design. How can we ensure a timer does not execute concurrently with a work handler?

The answer is with our friend strand. By using a strand object, we can post work through the strand as well as wrap the timer handler to be dispatched through it. As a result, we will get our serialized output and will not have to explicitly synchronize access to our shared object. Here is an example showing that.

Example 6c
[spoiler]
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

while( true )
{
try
{
boost::system::error_code ec;
io_service->run( ec );
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
break;
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void TimerHandler(
const boost::system::error_code & error,
boost::shared_ptr< boost::asio::deadline_timer > timer,
boost::shared_ptr< boost::asio::io_service::strand > strand
)
{
if( error )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << error << std::endl;
global_stream_lock.unlock();
}
else
{
std::cout << "[" << boost::this_thread::get_id()
<< "] TimerHandler " << std::endl;

timer->expires_from_now( boost::posix_time::seconds( 1 ) );
timer->async_wait(
strand->wrap( boost::bind( &TimerHandler, _1, timer, strand ) )
);
}
}

void PrintNum( int x )
{
std::cout << "[" << boost::this_thread::get_id()
<< "] x: " << x << std::endl;
boost::this_thread::sleep( boost::posix_time::milliseconds( 1000 ) );
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);
boost::shared_ptr< boost::asio::io_service::strand > strand(
new boost::asio::io_service::strand( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Press [return] to exit." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::this_thread::sleep( boost::posix_time::seconds( 1 ) );

strand->post( boost::bind( &PrintNum, 1 ) );
strand->post( boost::bind( &PrintNum, 2 ) );
strand->post( boost::bind( &PrintNum, 3 ) );
strand->post( boost::bind( &PrintNum, 4 ) );
strand->post( boost::bind( &PrintNum, 5 ) );

boost::shared_ptr< boost::asio::deadline_timer > timer(
new boost::asio::deadline_timer( *io_service )
);
timer->expires_from_now( boost::posix_time::seconds( 1 ) );
timer->async_wait(
strand->wrap( boost::bind( &TimerHandler, _1, timer, strand ) )
);

std::cin.get();

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

It is vital to note how we must wrap the timer handler through the strand everywhere and not just the first time. If we forget that, the timer would no longer execute through the strand object and bugs can result. Running the program, we should see our first five work objects execute and then the timer thread. Since everything is serialized, the work objects have to complete in order first before the timer event fires. If we were to remove the strand wrap calls, then we would see the timer executing normally but the output would be messed up since we did not lock the std::cout object, and thus that shows us we would have multi-threaded bugs! For more useful information regarding the timers, check out the Time Travel article the boost::asio author has written.

At this point, we can see how bind, strand, and shared_ptr are invaluable components when paired with the boost::asio library in giving us the power and flexibility we need to program with. We will be making use of all of these features in covering the next aspect of the boost::asio library, which is the networking system.

[page]

## 7. Networking basics: connectors and acceptors (TCP)

The first concepts of the boost::asio networking system we will cover will be TCP programming. The nice thing about the boost::asio library is consistency. Having covered the other aspects of the boost::asio library, we already know and understand the framework the network system uses. We just have to learn the specific networking API functions!

To get started, we will see how to connect synchronously to a host. Since our program will be acting as a client, we will be using the tcp::socket object now. There are different socket types for the different protocols available. As a result, we must make sure we use the correct objects and functions from the correct namespace. Before we can connect to a remote host, we must be able to get the address of the remote host. To do this, we will make use of tcp::resolver.

Example 7a
[spoiler]
#include
#include
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

while( true )
{
try
{
boost::system::error_code ec;
io_service->run( ec );
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
break;
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);
boost::shared_ptr< boost::asio::io_service::strand > strand(
new boost::asio::io_service::strand( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Press [return] to exit." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::asio::ip::tcp::socket sock( *io_service );

try
{
boost::asio::ip::tcp::resolver resolver( *io_service );
boost::asio::ip::tcp::resolver::query query(
"www.google.com",
boost::lexical_cast< std::string >( 80 )
);
boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
boost::asio::ip::tcp::endpoint endpoint = *iterator;

global_stream_lock.lock();
std::cout << "Connecting to: " << endpoint << std::endl;
global_stream_lock.unlock();

sock.connect( endpoint );
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}

std::cin.get();

boost::system::error_code ec;
sock.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
sock.close( ec );

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

This example will simply open a connection to Google. The program will tell us the actual IP and port it is attempting to connect to. If we open a command prompt and run the command "netstat -n", we should see a TCP connection of the program. In this example, we use the format for the query object to have reusable code. It might be common for the port to be an integer rather than a string, so we make use of lexical_cast to convert it to a string. While there are other methods to do this, boost makes it quick and easy. For another example, make sure to take a look at the Daytime.1 - A synchronous TCP daytime client tutorial on the boost site as well.

Sometimes we might not want to connect synchronously to a remote host. Imagine a GUI application where we want to start a connection via a button, but we do not want the GUI to freeze while the operation completes. Boost::asio provides a way to connect asynchronously through the socket as well. Using the techniques we have already learned, such as using boost::bind and boost::shared_ptr, we can setup our own connect handler that will be invoked.

Example 7b
[spoiler]
#include
#include
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

while( true )
{
try
{
boost::system::error_code ec;
io_service->run( ec );
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
break;
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void OnConnect( const boost::system::error_code & ec, boost::shared_ptr< boost::asio::ip::tcp::socket > sock )
{
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
else
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Connected!" << std::endl;
global_stream_lock.unlock();
}
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);
boost::shared_ptr< boost::asio::io_service::strand > strand(
new boost::asio::io_service::strand( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Press [return] to exit." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::shared_ptr< boost::asio::ip::tcp::socket > sock(
new boost::asio::ip::tcp::socket( *io_service )
);

try
{
boost::asio::ip::tcp::resolver resolver( *io_service );
boost::asio::ip::tcp::resolver::query query(
"www.google.com",
boost::lexical_cast< std::string >( 80 )
);
boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
boost::asio::ip::tcp::endpoint endpoint = *iterator;

global_stream_lock.lock();
std::cout << "Connecting to: " << endpoint << std::endl;
global_stream_lock.unlock();

sock->async_connect( endpoint, boost::bind( OnConnect, _1, sock ) );
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}

std::cin.get();

boost::system::error_code ec;
sock->shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
sock->close( ec );

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

Just to make sure we are still on the same page, figuratively speaking, we have to use a boost::shared_ptr with most boost::asio objects if we wish to pass them around. This is because the objects themselves are non-copyable and we have to ensure the object remains valid while the handler is waiting to be called. We use boost::bind to setup our own custom handler as well. This handler can have any number of parameters in addition to the default number it has to have. In this case, the async_connect handler is a ConnectHandler, which is simply a template parameter, but referring to the documentation we will see the signature it must have at minimal.

* @param handler The handler to be called when the connection operation
* completes. Copies will be made of the handler as required. The function
* signature of the handler must be:
* @code void handler(
* const boost::system::error_code& error // Result of operation
* ); @endcode
* Regardless of whether the asynchronous operation completes immediately or
* not, the handler will not be invoked from within this function. Invocation
* of the handler will be performed in a manner equivalent to using
* boost::asio::io_service::post().


One cool thing to note is that with boost::bind, we can rearrange the order of parameters as we desire! All that matters is that the parameter is physically there in the end. Hopefully now, the example makes sense as to why we do certain things. In this example as the last, we still resolve the remote address synchronously. We can change this to an asynchronous method by referring to the documentation if we wish. I prefer to keep it simple and just do the look-ups synchronously.

Now we have two different methods we can use to connect to remote hosts. What about letting remote hosts connect to us? To setup such a "server", we will make use of the tcp::acceptor object. While we covered both synchronous and asynchronous methods for connecting, we will just briefly cover the asynchronous method for the server. The reason is, the main goal to using the boost::asio library is asynchronicity, even though it does provide synchronous methods. We will see examples of more variations later but for now we will cover what will be used the most. Let us take a look at the start of the server.

Example 7c
[spoiler]
#include
#include
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

while( true )
{
try
{
boost::system::error_code ec;
io_service->run( ec );
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
break;
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void OnAccept( const boost::system::error_code & ec, boost::shared_ptr< boost::asio::ip::tcp::socket > sock )
{
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
else
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Accepted!" << std::endl;
global_stream_lock.unlock();
}
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);
boost::shared_ptr< boost::asio::io_service::strand > strand(
new boost::asio::io_service::strand( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Press [return] to exit." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::shared_ptr< boost::asio::ip::tcp::acceptor > acceptor(
new boost::asio::ip::tcp::acceptor( *io_service )
);
boost::shared_ptr< boost::asio::ip::tcp::socket > sock(
new boost::asio::ip::tcp::socket( *io_service )
);

try
{
boost::asio::ip::tcp::resolver resolver( *io_service );
boost::asio::ip::tcp::resolver::query query(
"127.0.0.1",
boost::lexical_cast< std::string >( 7777 )
);
boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );
acceptor->open( endpoint.protocol() );
acceptor->set_option( boost::asio::ip::tcp::acceptor::reuse_address( false ) );
acceptor->bind( endpoint );
acceptor->listen( boost::asio::socket_base::max_connections );
acceptor->async_accept( *sock, boost::bind( OnAccept, _1, sock ) );

global_stream_lock.lock();
std::cout << "Listening on: " << endpoint << std::endl;
global_stream_lock.unlock();
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}

std::cin.get();

boost::system::error_code ec;
acceptor->close( ec );

sock->shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
sock->close( ec );

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

This example looks pretty close to the previous. In fact, very little has changed! As mentioned before, this is one of the nice things about the boost::asio library. As we take the time to learn the different components, we began to be able to easily understand the others because of the dependency of the components on each other. Once we run the program, we have a server running on port 7777. We can run the command "telnet localhost 7777" to start a connection to the server and trigger the OnAccept function.

However, the server will not accept any more connections. This is because we only call async_accept once and only have one socket object. We will address the design strategies for servers later, as we are only getting started with the core API needed right now. At this time, we can also briefly mention the close and shutdown functions we have seen. In our examples, we have chosen to use the error_code variable version to ensure no exceptions are thrown. This is because sometimes shutdown might not be valid on a socket (if it was not connected or accepted) while close is. If we use exception handling, one of the functions might not get called as a result. So we will simply try to call both functions for sockets and ignore the errors.

The basics of connecting and accepting have been covered now. We now know how to connect to a remote host as well as accept an incoming connection. However, we have not yet covered reading and writing to sockets yet. That will be the next topic of our focus.

[page]

## 8. Networking basics: binary protocol sending and receiving (TCP)

To really get anything useful done with our sockets, we must be able to read and write to them. There are many different ways to go about this. Some protocols rely on text (ascii/unicode) while others require on binary. This chapter will just focus on smaller binary examples. For a more extensive set of examples, the boost::asio example page has a lot of useful reference material.

There are many types of functions for sending and receiving. Depending on our protocol, we will want to choose between them based on what best suites our application. Here is a list of relevant functions we need to be aware of:

basic_stream_socket:
[spoiler]
async_read_some - "This function is used to asynchronously read data from the stream socket. The function call always returns immediately."
async_receive - "This function is used to asynchronously receive data from the stream socket. The function call always returns immediately."
async_send - "This function is used to asynchronously send data on the stream socket. The function call always returns immediately."
async_write_some - "This function is used to asynchronously write data to the stream socket. The function call always returns immediately."
receive - "This function is used to receive data on the stream socket. The function call will block until one or more bytes of data has been received successfully, or until an error occurs."
read_some - "This function is used to read data from the stream socket. The function call will block until one or more bytes of data has been read successfully, or until an error occurs."
send - "This function is used to send data on the stream socket. The function call will block until one or more bytes of the data has been sent successfully, or an until error occurs."
write_some - "This function is used to write data to the stream socket. The function call will block until one or more bytes of the data has been written successfully, or until an error occurs."
[/spoiler]

boost::asio Free Functions
[spoiler]
async_read - "Start an asynchronous operation to read a certain amount of data from a stream."
async_read_at - "Start an asynchronous operation to read a certain amount of data at the specified offset."
async_read_until - "Start an asynchronous operation to read data into a streambuf until it contains a delimiter, matches a regular expression, or a function object indicates a match."
async_write - "Start an asynchronous operation to write a certain amount of data to a stream."
async_write_at - "Start an asynchronous operation to write a certain amount of data at the specified offset."
read - "Attempt to read a certain amount of data from a stream before returning."
read_at - "Attempt to read a certain amount of data at the specified offset before returning."
read_until - "Read data into a streambuf until it contains a delimiter, matches a regular expression, or a function object indicates a match."
write - "Write a certain amount of data to a stream before returning. "
write_at - "Write a certain amount of data at a specified offset before returning. "
[/spoiler]

Wow! That is a lot of functions. We should remember that boost::asio is more than just networking functions, so that is why there are so many of them. As we spend more time using the boost::asio library, we will be able to readily know which functions our application should be using. For this guide, we will make use of async_write and async_read_some. The reason we will use async_write is because the function will write all of the data for us, so we do not have to worry about partial sends. Likewise, we are using async_read_some as a generic function to read some data since we do not have a specific protocol we are using for receiving. We will go over this concept a bit later.

For now, let us take a look at a complete example of using our IO functions. We will be using a modified server example from Example 7C.

Example 8a
[spoiler]
#include
#include
#include
#include
#include
#include
#include
#include

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Start" << std::endl;
global_stream_lock.unlock();

while( true )
{
try
{
boost::system::error_code ec;
io_service->run( ec );
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
break;
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}
}

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Thread Finish" << std::endl;
global_stream_lock.unlock();
}

void OnAccept( const boost::system::error_code & ec, boost::shared_ptr< boost::asio::ip::tcp::socket > sock )
{
if( ec )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Error: " << ec << std::endl;
global_stream_lock.unlock();
}
else
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Accepted!" << std::endl;
global_stream_lock.unlock();
}
}

int main( int argc, char * argv[] )
{
boost::shared_ptr< boost::asio::io_service > io_service(
new boost::asio::io_service
);
boost::shared_ptr< boost::asio::io_service::work > work(
new boost::asio::io_service::work( *io_service )
);
boost::shared_ptr< boost::asio::io_service::strand > strand(
new boost::asio::io_service::strand( *io_service )
);

global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Press [return] to exit." << std::endl;
global_stream_lock.unlock();

boost::thread_group worker_threads;
for( int x = 0; x < 2; ++x )
{
worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
}

boost::shared_ptr< boost::asio::ip::tcp::acceptor > acceptor(
new boost::asio::ip::tcp::acceptor( *io_service )
);
boost::shared_ptr< boost::asio::ip::tcp::socket > sock(
new boost::asio::ip::tcp::socket( *io_service )
);

try
{
boost::asio::ip::tcp::resolver resolver( *io_service );
boost::asio::ip::tcp::resolver::query query(
"127.0.0.1",
boost::lexical_cast< std::string >( 7777 )
);
boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );
acceptor->open( endpoint.protocol() );
acceptor->set_option( boost::asio::ip::tcp::acceptor::reuse_address( false ) );
acceptor->bind( endpoint );
acceptor->listen( boost::asio::socket_base::max_connections );
acceptor->async_accept( *sock, boost::bind( OnAccept, _1, sock ) );

global_stream_lock.lock();
std::cout << "Listening on: " << endpoint << std::endl;
global_stream_lock.unlock();
}
catch( std::exception & ex )
{
global_stream_lock.lock();
std::cout << "[" << boost::this_thread::get_id()
<< "] Exception: " << ex.what() << std::endl;
global_stream_lock.unlock();
}

std::cin.get();

boost::system::error_code ec;
acceptor->close( ec );

sock->shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
sock->close( ec );

io_service->stop();

worker_threads.join_all();

return 0;
}
[/spoiler]

In this example, we add a ClientContext class that houses all of the context specific stuff for our incoming connections. This class wraps up the necessary IO functionality for sending and receiving. In this example, the server will send a message to the incoming connection in a format of (message size)[xx xx] (message payload)[ xx ... xx]. However, we do not have a client yet so to test we can simply telnet into the server to receive the data. Any data we send to the server will be dumped out on the console.

There are a couple of things we need to take away from the previous example. First, each connection we wish to service needs its own context. This context should contain the socket as well as the send/recv buffers as well as any other user data. Next, the example is not particularly thread safe per se, so we only limit it to one worker thread. We will cover this problem later. For now though, the concepts of reading and writing to the socket should be made clear. We simply choose the right API functions for our particular task and make sure to properly use them.

In order to properly use them, we must make sure the context and the buffers remain valid the entire duration of the function. In this case, we use a list of vectors for the sends and one vector to act as a common receive buffer. Depending on the protocol we have to implement, we might want to change a few things here and there. For example, let us say we want to process packets in our stream. In that case, we would want to use async_read with the size of the header followed by another call to async_read with the exact size of the payload. That way, we do not have to keep track of the stream position when using async_read_some.

The disadvantage of processing packets one at a time in the stream is that it is inefficient in larger scale programs. Imagine we had 100 3 byte messages in the stream. We would have to execute our "read one packet" logic 100 times! Compare that to if we used async_read_some, we would most likely get all of the data at once and the logically parse it. That is the preferred method, but it is also more complex. Depending on our application needs, we must decide which route we go. For some cases, we could not use either or though. For example, if we have a stream protocol, such as HTTP, then we cannot simply wait for an exact amount of bytes at a time but instead just receive as much as we can and then process it.

The code for a client would look similar as well. The only difference is that the connection context would connect to a remote host rather than be accepted. As a result, we can reuse a lot of the code. However, we will not dive into modifying the previous example to a client. The reason is because at this point of the guide, we have been exposed to all of the concepts we need to be aware of for using the boost::asio library for TCP programming. This means we can take a look at a full network wrapper and we should be able to understand all of the concepts that are used.

The reason we want to make a transition into the network wrapper is because we need reusable code to work from rather than recoding the same logic over and over as we have been. Another benefit of the wrapper is that it has been tested and should be relatively bug free. Having code that works to reference in the future can be a great help as we go on to write our own code. With that said, we will take a look at the network wrapper next.

[page]

## 9. A boost::asio network wrapper (TCP)

Now that we know the basics of using the boost::asio library and some simple TCP networking aspects, we can take a look at a network wrapper that takes care of the low level stuff. By using the wrapper, we can reuse it and always focus on the application logic rather than rewriting the network code ach time.

<span style="font-weight:bold;">IMPORTANT NOTE:</span> This code is purely for education purposes. Do not use it in production systems because there might be bugs. The code is designed to work a specific way and that might result in improper execution if you do not require such behavior. While I have tested and deployed the code for numerous projects, I am always finding small issues to fix.

In addition, the overhead of using such a network wrapper has to be taken into account. For example, there are tons of allocations behind the scenes from the vector and lists. In addition, the judicial use of shared_ptr along with boost::bind handlers does add quite a bit of overhead that might not be acceptable in some environments That is why this code is for educational use only!

network.h
[spoiler]
#pragma once

#ifndef NETWORK_H_
#define NETWORK_H_

//-----------------------------------------------------------------------------

#include
#include
#include
#include
#include
#include
#include
#include

//-----------------------------------------------------------------------------

using boost::uint64_t;
using boost::uint32_t;
using boost::uint16_t;
using boost::uint8_t;

using boost::int64_t;
using boost::int32_t;
using boost::int16_t;
using boost::int8_t;

//-----------------------------------------------------------------------------

class Hive;
class Acceptor;
class Connection;

//-----------------------------------------------------------------------------

class Connection : public boost::enable_shared_from_this< Connection >
{
friend class Acceptor;
friend class Hive;

private:
boost::shared_ptr< Hive > m_hive;
boost::asio::ip::tcp::socket m_socket;
boost::asio::strand m_io_strand;
boost::asio::deadline_timer m_timer;
boost::posix_time::ptime m_last_time;
std::vector< uint8_t > m_recv_buffer;
std::list< int32_t > m_pending_recvs;
std::list< std::vector< uint8_t > > m_pending_sends;
int32_t m_receive_buffer_size;
int32_t m_timer_interval;
volatile uint32_t m_error_state;

protected:
Connection( boost::shared_ptr< Hive > hive );
virtual ~Connection();

private:
Connection( const Connection & rhs );
Connection & operator =( const Connection & rhs );
void StartSend();
void StartRecv( int32_t total_bytes );
void StartTimer();
void StartError( const boost::system::error_code & error );
void DispatchSend( std::vector< uint8_t > buffer );
void DispatchRecv( int32_t total_bytes );
void DispatchTimer( const boost::system::error_code & error );
void HandleConnect( const boost::system::error_code & error );
void HandleSend( const boost::system::error_code & error, std::list< std::vector< uint8_t > >::iterator itr );
void HandleRecv( const boost::system::error_code & error, int32_t actual_bytes );
void HandleTimer( const boost::system::error_code & error );

private:
// Called when the connection has successfully connected to the local
// host.
virtual void OnAccept( const std::string & host, uint16_t port ) = 0;

// Called when the connection has successfully connected to the remote
// host.
virtual void OnConnect( const std::string & host, uint16_t port ) = 0;

// Called when data has been sent by the connection.
virtual void OnSend( const std::vector< uint8_t > & buffer ) = 0;

// Called when data has been received by the connection.
virtual void OnRecv( std::vector< uint8_t > & buffer ) = 0;

// Called on each timer event.
virtual void OnTimer( const boost::posix_time::time_duration & delta ) = 0;

// Called when an error is encountered.
virtual void OnError( const boost::system::error_code & error ) = 0;

public:
// Returns the Hive object.
boost::shared_ptr< Hive > GetHive();

// Returns the socket object.
boost::asio::ip::tcp::socket & GetSocket();

// Returns the strand object.
boost::asio::strand & GetStrand();

// Sets the application specific receive buffer size used. For stream
// based protocols such as HTTP, you want this to be pretty large, like
// 64kb. For packet based protocols, then it will be much smaller,
// usually 512b - 8kb depending on the protocol. The default value is
// 4kb.
void SetReceiveBufferSize( int32_t size );

// Returns the size of the receive buffer size of the current object.
int32_t GetReceiveBufferSize() const;

// Sets the timer interval of the object. The interval is changed after
// the next update is called.
void SetTimerInterval( int32_t timer_interval_ms );

// Returns the timer interval of the object.
int32_t GetTimerInterval() const;

// Returns true if this object has an error associated with it.
bool HasError();

// Binds the socket to the specified interface.
void Bind( const std::string & ip, uint16_t port );

// Starts an a/synchronous connect.
void Connect( const std::string & host, uint16_t port );

// Posts data to be sent to the connection.
void Send( const std::vector< uint8_t > & buffer );

// Posts a recv for the connection to process. If total_bytes is 0, then
// as many bytes as possible up to GetReceiveBufferSize() will be
// waited for. If Recv is not 0, then the connection will wait for exactly
// total_bytes before invoking OnRecv.
void Recv( int32_t total_bytes = 0 );

// Posts an asynchronous disconnect event for the object to process.
void Disconnect();
};

//-----------------------------------------------------------------------------

class Acceptor : public boost::enable_shared_from_this< Acceptor >
{
friend class Hive;

private:
boost::shared_ptr< Hive > m_hive;
boost::asio::ip::tcp::acceptor m_acceptor;
boost::asio::strand m_io_strand;
boost::asio::deadline_timer m_timer;
boost::posix_time::ptime m_last_time;
int32_t m_timer_interval;
volatile uint32_t m_error_state;

private:
Acceptor( const Acceptor & rhs );
Acceptor & operator =( const Acceptor & rhs );
void StartTimer();
void StartError( const boost::system::error_code & error );
void DispatchAccept( boost::shared_ptr< Connection > connection );
void HandleTimer( const boost::system::error_code & error );
void HandleAccept( const boost::system::error_code & error, boost::shared_ptr< Connection > connection );

protected:
Acceptor( boost::shared_ptr< Hive > hive );
virtual ~Acceptor();

private:
// Called when a connection has connected to the server. This function
// should return true to invoke the connection's OnAccept function if the
// connection will be kept. If the connection will not be kept, the
// connection's Disconnect function should be called and the function
// should return false.
virtual bool OnAccept( boost::shared_ptr< Connection > connection, const std::string & host, uint16_t port ) = 0;

// Called on each timer event.
virtual void OnTimer( const boost::posix_time::time_duration & delta ) = 0;

// Called when an error is encountered. Most typically, this is when the
// acceptor is being closed via the Stop function or if the Listen is
// called on an address that is not available.
virtual void OnError( const boost::system::error_code & error ) = 0;

public:
// Returns the Hive object.
boost::shared_ptr< Hive > GetHive();

// Returns the acceptor object.
boost::asio::ip::tcp::acceptor & GetAcceptor();

// Returns the strand object.
boost::asio::strand & GetStrand();

// Sets the timer interval of the object. The interval is changed after
// the next update is called. The default value is 1000 ms.
void SetTimerInterval( int32_t timer_interval_ms );

// Returns the timer interval of the object.
int32_t GetTimerInterval() const;

// Returns true if this object has an error associated with it.
bool HasError();

public:
// Begin listening on the specific network interface.
void Listen( const std::string & host, const uint16_t & port );

// Posts the connection to the listening interface. The next client that
// connections will be given this connection. If multiple calls to Accept
// are called at a time, then they are accepted in a FIFO order.
void Accept( boost::shared_ptr< Connection > connection );

// Stop the Acceptor from listening.
void Stop();
};

//-----------------------------------------------------------------------------

class Hive : public boost::enable_shared_from_this< Hive >
{
private:
boost::asio::io_service m_io_service;
boost::shared_ptr< boost::asio::io_service::work > m_work_ptr;
volatile uint32_t m_shutdown;

private:
Hive( const Hive & rhs );
Hive & operator =( const Hive & rhs );

public:
Hive();
virtual ~Hive();

// Returns the io_service of this object.
boost::asio::io_service & GetService();

// Returns true if the Stop function has been called.
bool HasStopped();

// Polls the networking subsystem once from the current thread and
// returns.
void Poll();

// Runs the networking system on the current thread. This function blocks
// until the networking system is stopped, so do not call on a single
// threaded application with no other means of being able to call Stop
// unless you code in such logic.
void Run();

// Stops the networking system. All work is finished and no more
// networking interactions will be possible afterwards until Reset is called.
void Stop();

// Restarts the networking system after Stop as been called. A new work
// object is created ad the shutdown flag is cleared.
void Reset();
};

//-----------------------------------------------------------------------------

#endif
[/spoiler]

network.cpp
[spoiler]
#include "network.h"
#include
#include
#include

//-----------------------------------------------------------------------------

Hive::Hive()
: m_work_ptr( new boost::asio::io_service::work( m_io_service ) ), m_shutdown( 0 )
{
}

Hive::~Hive()
{
}

boost::asio::io_service & Hive::GetService()
{
return m_io_service;
}

bool Hive::HasStopped()
{
return ( boost::interprocess::detail::atomic_cas32( &m_shutdown, 1, 1 ) == 1 );
}

void Hive::Poll()
{
m_io_service.poll();
}

void Hive::Run()
{
m_io_service.run();
}

void Hive::Stop()
{
if( boost::interprocess::detail::atomic_cas32( &m_shutdown, 1, 0 ) == 0 )
{
m_work_ptr.reset();
m_io_service.run();
m_io_service.stop();
}
}

void Hive::Reset()
{
if( boost::interprocess::detail::atomic_cas32( &m_shutdown, 0, 1 ) == 1 )
{
m_io_service.reset();
m_work_ptr.reset( new boost::asio::io_service::work( m_io_service ) );
}
}

//-----------------------------------------------------------------------------

Acceptor::Acceptor( boost::shared_ptr< Hive > hive )
: m_hive( hive ), m_acceptor( hive->GetService() ), m_io_strand( hive->GetService() ), m_timer( hive->GetService() ), m_timer_interval( 1000 ), m_error_state( 0 )
{
}

Acceptor::~Acceptor()
{
}

void Acceptor::StartTimer()
{
m_last_time = boost::posix_time::microsec_clock::local_time();
m_timer.expires_from_now( boost::posix_time::milliseconds( m_timer_interval ) );
m_timer.async_wait( m_io_strand.wrap( boost::bind( &Acceptor::HandleTimer, shared_from_this(), _1 ) ) );
}

void Acceptor::StartError( const boost::system::error_code & error )
{
if( boost::interprocess::detail::atomic_cas32( &m_error_state, 1, 0 ) == 0 )
{
boost::system::error_code ec;
m_acceptor.cancel( ec );
m_acceptor.close( ec );
m_timer.cancel( ec );
OnError( error );
}
}

void Acceptor::DispatchAccept( boost::shared_ptr< Connection > connection )
{
m_acceptor.async_accept( connection->GetSocket(), connection->GetStrand().wrap( boost::bind( &Acceptor::HandleAccept, shared_from_this(), _1, connection ) ) );
}

void Acceptor::HandleTimer( const boost::system::error_code & error )
{
if( error || HasError() || m_hive->HasStopped() )
{
StartError( error );
}
else
{
OnTimer( boost::posix_time::microsec_clock::local_time() - m_last_time );
StartTimer();
}
}

void Acceptor::HandleAccept( const boost::system::error_code & error, boost::shared_ptr< Connection > connection )
{
if( error || HasError() || m_hive->HasStopped() )
{
connection->StartError( error );
}
else
{
if( connection->GetSocket().is_open() )
{
connection->StartTimer();
if( OnAccept( connection, connection->GetSocket().remote_endpoint().address().to_string(), connection->GetSocket().remote_endpoint().port() ) )
{
connection->OnAccept( m_acceptor.local_endpoint().address().to_string(), m_acceptor.local_endpoint().port() );
}
}
else
{
StartError( error );
}
}
}

void Acceptor::Stop()
{
m_io_strand.post( boost::bind( &Acceptor::HandleTimer, shared_from_this(), boost::asio::error::connection_reset ) );
}

void Acceptor::Accept( boost::shared_ptr< Connection > connection )
{
m_io_strand.post( boost::bind( &Acceptor::DispatchAccept, shared_from_this(), connection ) );
}

void Acceptor::Listen( const std::string & host, const uint16_t & port )
{
boost::asio::ip::tcp::resolver resolver( m_hive->GetService() );
boost::asio::ip::tcp::resolver::query query( host, boost::lexical_cast< std::string >( port ) );
boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve( query );
m_acceptor.open( endpoint.protocol() );
m_acceptor.set_option( boost::asio::ip::tcp::acceptor::reuse_address( false ) );
m_acceptor.bind( endpoint );
m_acceptor.listen( boost::asio::socket_base::max_connections );
StartTimer();
}

boost::shared_ptr< Hive > Acceptor::GetHive()
{
return m_hive;
}

boost::asio::ip::tcp::acceptor & Acceptor::GetAcceptor()
{
return m_acceptor;
}

int32_t Acceptor::GetTimerInterval() const
{
return m_timer_interval;
}

void Acceptor::SetTimerInterval( int32_t timer_interval )
{
m_timer_interval = timer_interval;
}

bool Acceptor::HasError()
{
return ( boost::interprocess::detail::atomic_cas32( &m_error_state, 1, 1 ) == 1 );
}

//-----------------------------------------------------------------------------

Connection::Connection( boost::shared_ptr< Hive > hive )
: m_hive( hive ), m_socket( hive->GetService() ), m_io_strand( hive->GetService() ), m_timer( hive->GetService() ), m_receive_buffer_size( 4096 ), m_timer_interval( 1000 ), m_error_state( 0 )
{
}

Connection::~Connection()
{
}

void Connection::Bind( const std::string & ip, uint16_t port )
{
boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::address::from_string( ip ), port );
m_socket.open( endpoint.protocol() );
m_socket.set_option( boost::asio::ip::tcp::acceptor::reuse_address( false ) );
m_socket.bind( endpoint );
}

void Connection::StartSend()
{
if( !m_pending_sends.empty() )
{
boost::asio::async_write( m_socket, boost::asio::buffer( m_pending_sends.front() ), m_io_strand.wrap( boost::bind( &Connection::HandleSend, shared_from_this(), boost::asio::placeholders::error, m_pending_sends.begin() ) ) );
}
}

void Connection::StartRecv( int32_t total_bytes )
{
if( total_bytes > 0 )
{
m_recv_buffer.resize( total_bytes );
boost::asio::async_read( m_socket, boost::asio::buffer( m_recv_buffer ), m_io_strand.wrap( boost::bind( &Connection::HandleRecv, shared_from_this(), _1, _2 ) ) );
}
else
{
m_recv_buffer.resize( m_receive_buffer_size );
m_socket.async_read_some( boost::asio::buffer( m_recv_buffer ), m_io_strand.wrap( boost::bind( &Connection::HandleRecv, shared_from_this(), _1, _2 ) ) );
}
}

void Connection::StartTimer()
{
m_last_time = boost::posix_time::microsec_clock::local_time();
m_timer.expires_from_now( boost::posix_time::milliseconds( m_timer_interval ) );
m_timer.async_wait( m_io_strand.wrap( boost::bind( &Connection::DispatchTimer, shared_from_this(), _1 ) ) );
}

void Connection::StartError( const boost::system::error_code & error )
{
if( boost::interprocess::detail::atomic_cas32( &m_error_state, 1, 0 ) == 0 )
{
boost::system::error_code ec;
m_socket.shutdown( boost::asio::ip::tcp::socket::shutdown_both, ec );
m_socket.close( ec );
m_timer.cancel( ec );
OnError( error );
}
}

void Connection::HandleConnect( const boost::system::error_code & error )
{
if( error || HasError() || m_hive->HasStopped() )
{
StartError( error );
}
else
{
if( m_socket.is_open() )
{
OnConnect( m_socket.remote_endpoint().address().to_string(), m_socket.remote_endpoint().port() );
}
else
{
StartError( error );
}
}
}

void Connection::HandleSend( const boost::system::error_code & error, std::list< std::vector< uint8_t > >::iterator itr )
{
if( error || HasError() || m_hive->HasStopped() )
{
StartError( error );
}
else
{
OnSend( *itr );
m_pending_sends.erase( itr );
StartSend();
}
}

void Connection::HandleRecv( const boost::system::error_code & error, int32_t actual_bytes )
{
if( error || HasError() || m_hive->HasStopped() )
{
StartError( error );
}
else
{
m_recv_buffer.resize( actual_bytes );
OnRecv( m_recv_buffer );
m_pending_recvs.pop_front();
if( !m_pending_recvs.empty() )
{
StartRecv( m_pending_recvs.front() );
}
}
}

void Connection::HandleTimer( const boost::system::error_code & error )
{
if( error || HasError() || m_hive->HasStopped() )
{
StartError( error );
}
else
{
OnTimer( boost::posix_time::microsec_clock::local_time() - m_last_time );
StartTimer();
}
}

void Connection::DispatchSend( std::vector< uint8_t > buffer )
{
bool should_start_send = m_pending_sends.empty();
m_pending_sends.push_back( buffer );
if( should_start_send )
{
StartSend();
}
}

void Connection::DispatchRecv( int32_t total_bytes )
{
bool should_start_receive = m_pending_recvs.empty();
m_pending_recvs.push_back( total_bytes );
if( should_start_receive )
{
StartRecv( total_bytes );
}
}

void Connection::DispatchTimer( const boost::system::error_code & error )
{
m_io_strand.post( boost::bind( &Connection::HandleTimer, shared_from_this(), error ) );
}

void Connection::Connect( const std::string & host, uint16_t port)
{
boost::system::error_code ec;
boost::asio::ip::tcp::resolver resolver( m_hive->GetService() );
boost::asio::ip::tcp::resolver::query query( host, boost::lexical_cast< std::string >( port ) );
boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query );
m_socket.async_connect( *iterator, m_io_strand.wrap( boost::bind( &Connection::HandleConnect, shared_from_this(), _1 ) ) );
StartTimer();
}

void Connection::Disconnect()
{
m_io_strand.post( boost::bind( &Connection::HandleTimer, shared_from_this(), boost::asio::error::connection_reset ) );
}

void Connection::Recv( int32_t total_bytes )
{
m_io_strand.post( boost::bind( &Connection::DispatchRecv, shared_from_this(), total_bytes ) );
}

void Connection::Send( const std::vector< uint8_t > & buffer )
{
m_io_strand.post( boost::bind( &Connection::DispatchSend, shared_from_this(), buffer ) );
}

boost::asio::ip::tcp::socket & Connection::GetSocket()
{
return m_socket;
}

boost::asio::strand & Connection::GetStrand()
{
return m_io_strand;
}

boost::shared_ptr< Hive > Connection::GetHive()
{
return m_hive;
}

void Connection::SetReceiveBufferSize( int32_t size )
{
m_receive_buffer_size = size;
}

int32_t Connection::GetReceiveBufferSize() const
{
return m_receive_buffer_size;
}

int32_t Connection::GetTimerInterval() const
{
return m_timer_interval;
}

void Connection::SetTimerInterval( int32_t timer_interval )
{
m_timer_interval = timer_interval;
}

bool Connection::HasError()
{
return ( boost::interprocess::detail::atomic_cas32( &m_error_state, 1, 1 ) == 1 );
}

//-----------------------------------------------------------------------------

[/spoiler]

The networking library attempts to provide a thread safe scalable wrapper for easily implementing client and server applications. Users will derive their custom class from the base Connection, Acceptor, or Hive classes as needed. The following examples will show the basics of using the wrapper.

The first example we will look at is setting up a server using the wrapper. In this case, it is pretty similar to our previous examples. It simply echoes out all traffic sent or received. This server is a simple echo server this time around though.

Example 9a
[spoiler]
#include "network.h"
#include
#include

boost::mutex global_stream_lock;

class MyConnection : public Connection
{
private:

private:
void OnAccept( const std::string & host, uint16_t port )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
global_stream_lock.unlock();

// Start the next receive
Recv();
}

void OnConnect( const std::string & host, uint16_t port )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
global_stream_lock.unlock();

// Start the next receive
Recv();
}

void OnSend( const std::vector< uint8_t > & buffer )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
for( size_t x = 0; x < buffer.size(); ++x )
{
std::cout << std::hex << std::setfill( '0' ) <<
std::setw( 2 ) << (int)buffer[ x ] << " ";
if( ( x + 1 ) % 16 == 0 )
{
std::cout << std::endl;
}
}
std::cout << std::endl;
global_stream_lock.unlock();
}

void OnRecv( std::vector< uint8_t > & buffer )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
for( size_t x = 0; x < buffer.size(); ++x )
{
std::cout << std::hex << std::setfill( '0' ) <<
std::setw( 2 ) << (int)buffer[ x ] << " ";
if( ( x + 1 ) % 16 == 0 )
{
std::cout << std::endl;
}
}
std::cout << std::endl;
global_stream_lock.unlock();

// Start the next receive
Recv();

// Echo the data back
Send( buffer );
}

void OnTimer( const boost::posix_time::time_duration & delta )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
global_stream_lock.unlock();
}

void OnError( const boost::system::error_code & error )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
global_stream_lock.unlock();
}

public:
MyConnection( boost::shared_ptr< Hive > hive )
: Connection( hive )
{
}

~MyConnection()
{
}
};

class MyAcceptor : public Acceptor
{
private:

private:
bool OnAccept( boost::shared_ptr< Connection > connection, const std::string & host, uint16_t port )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
global_stream_lock.unlock();

return true;
}

void OnTimer( const boost::posix_time::time_duration & delta )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
global_stream_lock.unlock();
}

void OnError( const boost::system::error_code & error )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
global_stream_lock.unlock();
}

public:
MyAcceptor( boost::shared_ptr< Hive > hive )
: Acceptor( hive )
{
}

~MyAcceptor()
{
}
};

int main( int argc, char * argv[] )
{
boost::shared_ptr< Hive > hive( new Hive() );

boost::shared_ptr< MyAcceptor > acceptor( new MyAcceptor( hive ) );
acceptor->Listen( "127.0.0.1", 7777 );

boost::shared_ptr< MyConnection > connection( new MyConnection( hive ) );
acceptor->Accept( connection );

while( !_kbhit() )
{
hive->Poll();
Sleep( 1 );
}

hive->Stop();

return 0;
}
[/spoiler]

The code should be pretty straight forward. Since we are using the wrapper now, all of the details of the socket management are behind the scenes now so we can focus on application logic. In this example, we do not use any worker threads, but the same concepts apply as have been shown in previous examples. We now know what a server looks like, so let us take a look at a client.

Example 9b
[spoiler]
#include "network.h"
#include
#include

boost::mutex global_stream_lock;

class MyConnection : public Connection
{
private:

private:
void OnAccept( const std::string & host, uint16_t port )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
global_stream_lock.unlock();

// Start the next receive
Recv();
}

void OnConnect( const std::string & host, uint16_t port )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;
global_stream_lock.unlock();

// Start the next receive
Recv();

std::string str = "GET / HTTP/1.0\r\n\r\n";

std::vector< uint8_t > request;
std::copy( str.begin(), str.end(), std::back_inserter( request ) );
Send( request );
}

void OnSend( const std::vector< uint8_t > & buffer )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
for( size_t x = 0; x < buffer.size(); ++x )
{
std::cout << std::hex << std::setfill( '0' ) <<
std::setw( 2 ) << (int)buffer[ x ] << " ";
if( ( x + 1 ) % 16 == 0 )
{
std::cout << std::endl;
}
}
std::cout << std::endl;
global_stream_lock.unlock();
}

void OnRecv( std::vector< uint8_t > & buffer )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
for( size_t x = 0; x < buffer.size(); ++x )
{
std::cout << std::hex << std::setfill( '0' ) <<
std::setw( 2 ) << (int)buffer[ x ] << " ";
if( ( x + 1 ) % 16 == 0 )
{
std::cout << std::endl;
}
}
std::cout << std::endl;
global_stream_lock.unlock();

// Start the next receive
Recv();
}

void OnTimer( const boost::posix_time::time_duration & delta )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
global_stream_lock.unlock();
}

void OnError( const boost::system::error_code & error )
{
global_stream_lock.lock();
std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
global_stream_lock.unlock();
}

public:
MyConnection( boost::shared_ptr< Hive > hive )
: Connection( hive )
{
}

~MyConnection()
{
}
};

int main( int argc, char * argv[] )
{
boost::shared_ptr< Hive > hive( new Hive() );

boost::shared_ptr< MyConnection > connection( new MyConnection( hive ) );
connection->Connect( "www.google.com", 80 );

while( !_kbhit() )
{
hive->Poll();
Sleep( 1 );
}

hive->Stop();

return 0;
}
[/spoiler]

This client simply sends a HTTP GET to Google and then dumps the output in hex format to the console. The theme of reusability further shows itself in this example as the code in this example is not too different than the code of the server. This means our client and server programs are not going to be radically different. That is a good thing as it makes life easier for future maintenance.

With our networking wrapper, we can see how a lot of work is simplified for us. There are a lot of design implications to this particular networking wrapper that should be noticed. First, for "servers", there is no concept of storing each connection into a container for easy referencing. This is done because to add all connections into a container, the end user must lock the container to synchronize access to it or implement an async method of adding and removing connections. In short, this is behavior the end user has to implement if they need it. Not all networking applications have to be aware of all connections present at a time (HTTP servers for example) so the wrapper goes for the most generic approach beneficial to all.

Next, all connection interactions are done through a unique strand. As we covered already, the strand object allows events to be executed serially. As a result, we do not have to explicitly lock the connection each time an event happens because no events will ever happen concurrently no matter how many worker threads we have. Care has to be taken though because if the user adds any custom methods, then they would have to implement their logic following the same design to keep the class thread safe.

Simple send/recv buffer logic is implemented through vectors and lists. This obviously has serious memory implications in the long run. However, anyone who has custom memory needs will have their own unique system to work with, so they would modify the code as needed anyways. For most simple applications, the provided system is good enough and cross platform (standard C++ library containers) so no efforts have been made to complicate that aspect.

Finally, the specific design of the wrapper is not for everyone. This is just one example of what is possible with the boost::asio library. I prefer and use this wrapper myself, so that is why I am sharing it. Feel free to come up with your own and customize it as you need! The important part is getting familiar with the boost::asio library.

[page]

## 10. The road ahead

There are three basic things that need to happen now. We need to:
1. Continue to learn the ins and outs of the boost and boost::asio libraries to further extend our programs.
2. Write, test, and deploy a reusable wrapper for the base boost::asio networking stuff so we do not have to keep rewriting it.
3. Write our own networking library on top of the wrapper that handles the protocol specific tasks at hand.

In doing so, we will be able to finally harness the full potential of the boost::asio library. There are still a lot of aspects to the boost::asio library that has not been covered in this guide. That is because this guide was written to be a quick start guide. While this guide is certainly not short, it just goes to show how much is needed to really get into the boost::asio library. Hopefully, this guide will provide a good direction to learn the basics of boost::asio from. The biggest issue I have seen when trying to learn boost::asio is finding practical resources that really cover a lot of the bases of the library so the end user knows what they need to look into to get the most out of the library.

UDP is not quite as involved as TCP since it is connection-less. However, it is up to the programmer to implement their own layer on top of UDP specific to their application. As a consequence, no UDP topics are being covered at this time as using the UDP specific API is pretty straightforward after having looked at the TCP API. Most users might even consider using an existing UDP library as well. A lot of people do write their own TCP wrappers and then libraries while not many of them end up writing their own UDP simply based on their needs due to the nature of the protocol. Depending on one's application and networking experience, the decision will vary.

As part of goal #3, we will also want to write a custom "packet" class to use. Such a class was not included in these examples simply because of the added complexity. Ideally though, we want to have something reusable to build upon and reuse, but depending on the application this might not be possible. For example, larger scale applications might need code that uses custom memory allocation interfaces and as a result any code written before might be incompatible. These are important things to keep in mind when doing network programming!

Finally, we have to consider is boost::asio right for us. For some applications, it might be over kill. For others, we might decide we want to use another library. I myself have come to like the design of boost::asio and willing to accept the overhead incurred through boost::bind for the flexibility and power the library provides. While getting the "perfect" code takes a lot of work and testing, it is still doable. However, some other libraries might provide more features and an API set suitable for a task.

This guide to getting started with boost::asio is now concluded. Future guides will be written to cover even more topics. Please feel free to leave any feedback, corrections, or problems below.