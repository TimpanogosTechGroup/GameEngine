/*
 * Author: Jon Meilstrup
 *
 * This is supposed to be a preprocessor file that includes all the possible exceptions in any code files that might need it.
 * This way you don't have your file bogged down with tons of #include statements at the top, you only need to include this
 * file using #include "ExceptionInclude.cpp" at the top of your file, and the preprocessor will include all these files in
 * your file.
 *
 * There should be no functions in this file at all whatsoever. This is purely for preprocessor use only.
 */

#include "ExampleException.cpp"