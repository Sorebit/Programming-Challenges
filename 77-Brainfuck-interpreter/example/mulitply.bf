Multiply two digits
Probably badly written by Sorebit

++++++                            set (0) to 6 so we can then subtract 48 from numbers
>,>>>,                            input (1) and (4)
<<<<[>-------->>>--------<<<<-]   subtract 48 from both
>>>>                              go to (4)
[                                 while (4) is not 0
	<<<                           move to (1)
	[->+>+<<]>>[-<<+>>]<<         copy (1) to (2)
	>>>-                          move to (4) and decrease it by 1
]                                 end loop
                                  now the value of a*b is located at (2)
<                                 move to (3) 
++++++                            and add 6 so we can add 48 to (2) (DELETE THESE LINES TO NOT ADD 48)
[<++++++++>-]                     add 48 to (2)                     (DELETE THESE LINES TO NOT ADD 48)
<.                                print the answer