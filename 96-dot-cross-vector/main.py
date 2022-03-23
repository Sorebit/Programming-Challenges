import re


# This method assumes valid vectors of the same length
def dot_product(a, b):
    return sum([i * j for (i, j) in zip(a, b)])


# This method assumes valid vectors of length 2
def cross_product_2(a, b):
    return cross_product_3(a + [0], b + [0])


# This method assumes valid vectors of length 3
def cross_product_3(a, b):
    return [
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    ]


# This method assumes same-length valid vectors of length 2 or 3
def cross_product(a, b):
    if len(a) == 2:
        return cross_product_2(a, b)
    return cross_product_3(a, b)


# Handle method input
def read_method():
    while True:
        print("Options:")
        print("- Cross product (cross/c) [Only 2 and 3 dimensional vectors]")
        print("-   Dot product (dot/d)")
        m = input("> ")

        if m == "cross" or m == "c":
            return "cross"
        elif m == "dot" or m == "d":
            return "dot"


# Handle vectors input
def read_vectors(method):
    while True:
        print("\nInput two vectors of the same length (ex. 1.0 2e3 4 then .5 6 7)")
        v = input("First> ")
        v = v.strip()
        a = re.split("\s+", v)

        v = input("Second> ")
        v = v.strip()
        b = re.split("\s+", v)

        if len(a) != len(b):
            continue
        # Only support 2 and 3 dim vectors for cross product
        if method == "cross" and not (len(a) == 2 or len(a) == 3):
            print("Error: Cross product only supports 2 and 3 dimensional vectors!")
            continue
        # Dimensions as expected
        a = [float(i) for i in a]
        b = [float(i) for i in b]
        return a, b


def main():
    print("Vector product calculator")

    method = read_method()
    a, b = read_vectors(method)

    if method == "dot":
        result = dot_product(a, b)
    else:
        result = cross_product(a, b)

    print("\n" + method.capitalize() + " product: " + str(result))


# Script execution
if __name__ == "__main__":
    main()
