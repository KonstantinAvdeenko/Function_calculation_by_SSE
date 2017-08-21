This program in the C++ programming language, finds the result of a function using SSE,
where four float32 numbers are stored in one SSE register, operations on which are carried out simultaneously,
using an array of random variables of the function and measures separately spent time on initializing the array
and separately spent time on finding the result of the function:

The main module VitheslenieZnatheniiSPrimeneniemTehnologiiSSE contains the main function int main -
in which the ability to work with the Russian language is connected, the number of array elements for
substituting them as function variables, are created and converted to 16-byte size arrays for
the possibility of working with them SSE means. Also, the main function measures separately spent time on
array initialization, getting data from the init method and separately spent time on finding the result
function, receiving data from the ComputeArrayCppSSE method, displays the results of the time spent on calculating
and before the end of the program, it clears the allocated memory blocks for the 16 byte arrays with which
operation by means of SSE.

Methods with which the main function works:
1) init method - initializes all array elements and returns data about the array to
main function int main;
2) ComputeArrayCppSSE method - performs finding the result of a function, displays the result and returns
the result in the main function int main to stop the time being traced for finding the result of the function.