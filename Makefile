all: a b OS_Project

a: regular_request_generator.c
    gcc -o a regular_request_generator.c

b: random_request_generator.c
    gcc -o b random_request_generator.c

OS_Project: OS_Project.c
    gcc -o OS_Project OS_Project.c

clean:
    rm -f a b OS_Project