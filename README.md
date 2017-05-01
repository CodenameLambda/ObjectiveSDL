# ObjectiveSDL

## This project is unstable, untested, and the API will likely change in the future!

This is a wrapper around SDL, that allows for object oriented programming.

The goal of this project is to be able to use every feature of SDL, but in an object oriented manner. As said goal is very ambitious, because the whole SDL library is *huge*, this will take a while to get to the point where it is ready for usage.

# Contributing

You can contribute via pull requests, and contact me under dodo2998@gmail.com if you want to get part of the main developers of this project.

# Unstable, untested

I am pretty sure that I have made some mistakes, like destructors that free resources that are still needed because the data behind it was copied.

And there are some bits that don't even allow you to copy a data structure, because the destructor would pose a problem otherwise.
But this wont change in the future (probably), but I'll add some structures that do the same thing, but with std::shared_ptr or something like that.

If you find mistakes or bits where you can do better, please improve!
