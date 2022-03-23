c = 34
l = [
    "c = 34",
    "l = [",
    "]",
    "for i in range(0, 1):",
    "    print(l[i])",
    "for i in range(1, len(l)):",
    "    print('    ' + chr(c) + l[i] + chr(c) + ',')",
    "for in in range(6, len(l)):",
    "    print(l[i])",
    "",
]
for i in range(0, 2):
    print(l[i])
for i in range(0, len(l)):
    print('   ' + chr(c) + l[i] + chr(c) + ',')
for i in range(3, len(l)):
    print(l[i])

# Quine ends above this line
# TODO: write a quine that produces a quine in another language which in turn produces the first one
# As in Python -> C++ -> C# -> back to Python
# (A quine-relay or ouroboros program)
