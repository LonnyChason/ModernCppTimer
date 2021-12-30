# ModernCppTimer
A simple timer implemented using C++ 11

A cross-platform c++ timer using condition variable.

example:

```
  // A timer that wakes up every 5 seconds.
	Timer t;
	t.start(5 * 1000, []
	{
		std::cout << "Hello World!\n";
	});
```
