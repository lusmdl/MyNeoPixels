# Where is the main.cpp

I add the `main.cpp` file to .gitignore with `src/main.cpp`, because I use it for testing, uploading the examples to my test envirement.
This avoid that I always commit the `main.cpp` with all the other files. I do not want this behavior.

## Example `main.cpp`

```cpp
/**
 * @file main.cpp
 * @brief example
 * 
 * @date today
 * @author lusmdl
 */

#include <MyNeoPixels.hpp>

int main(int argc, char const *argv[]) {
  
  return 0;
}
```