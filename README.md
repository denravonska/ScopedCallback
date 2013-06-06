ScopedCallback
==============

ScopedCallback is way of achieving self deregistering callback mechanisms without the use of new/delete or malloc/free.
This can be useful when data needs to be pushed from the lower layer of an application upwards, or when trying to
achieve event driven systems.

Example
-------
```C++
void PrintHello()
{
   std::cout << "PrintHello called." << std::endl;
}

int main(int argc, char** argv)
{
   Callback::Emitter emitter;

   // Attach a receptor to the emitter.
   Callback::Receptor receptor(std::bind(PrintHello));
   receptor.AttachTo(emitter);

   // Emit callback. This will print "PrintHello called" on the command line.
   emitter.Trigger();

   return 0;
}
```

Since both Emitter and Receptor keep track of their lifetime there is no need to manually detach from the emitter
other than when there is no longer an interest in the callback.

Design goals
------------
- Automatic deregistration if the callee _or_ the caller go out of scope.
- Low RAM footprint. Currently 64 bytes per emitter/receptor pair on 32bit systems.
- No dynamic memory allocation.

Limitations
-----------
- Only one receptor per emitter. This is intentional to keep the cost down.
- Data can't currently be passed as parameters in callbacks.
- Not header only.

License
-------
The software is licensed under the MIT license. Feel free to extend it or include it in your own projects.
