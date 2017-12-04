6e01 ; V[e] to 01
00e0 ; clear screen
6d01 ; V[d] = 01
6a01 ; V[a] = 01
6b01 ; V[b] = 01
8cd0 ; V[c] = V[d] 
8ce2 ; V[c] = V[c] & V[e]
4c00 ; if V[c] != 00 skip next instruction
1220 ; jump to adress 220
88d0 ; V[8] = V[d]
223e ; call subroutine at 23e (line 32)
3a40 ; if v[a] == 40 skip next instruction
1220 ; jump to adress 220
6a01 ; V[a] = 01
7b06 ; v[b] += 06
3c3f
7d01 ; v[d] += 01
3d3f ; if V[d] == 3f skip next instruction
120a ; jump to adress 20a
f00a ; wait for keypress and then store it in v[0]
4005
89e4
8ee4
3e40
1202 ; jump to adress 202
6a1c
6b0d
8890 ; v[8] = v[9]
00e0 ; clear screen
223e
123c ; jump to adress 23c
a294 ; set I to adress 294
f833 ; store BCD of V[x] at mem[I+0], mem[I+1], mem[I+2]
f265 ; reg_load(V[0..2], &I) (increase I as it goes)
2254 ; call subroutine at 254
dab5 ; draw(v[a], v[b], 5)
7a04 ; v[a] += 04
8120 ; v[1] = v[2]
2254
dab5 ; draw(v[a], v[b], 5)
7a05 ; v[a] += 05
00ee ; return from subroutine 
8310 ; V[3] = V[1]
8334 ; V[3] += V[3]
8334 ; V[3] += V[3]
8314 ; V[3] += V[1]
a262 ; set I to adress 262
f31e ; I += V[x]
00ee ; return from subroutine
e0a0
a0a0
e040
4040
4040
e020
e080
e0e0
20e0
20e0
a0a0
e020
20e0
80e0
20e0
e080
e0a0
e0e0
2020
2020
e0a0
e0a0
e0e0
a0e0
20e0
