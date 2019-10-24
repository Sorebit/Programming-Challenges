# 06 - Rock, paper, scissors (lizard, spock)
Wikipedia: https://en.wikipedia.org/wiki/Rock%E2%80%93paper%E2%80%93scissors

## Concept 
- Server accepts tcp connections (so that telnet works and I don't have to write a custom client)
- Server holds rooms (max number is setup in config)
- Room:
  - Created by clients, deleted after all clients leave
  - `room create` - creates a room from the pool and gives back its number
  - `room join 1337` - joins room
  - `room list` - lists open rooms
  - While in room:
    - `ready` - marks player as ready
    - `nick Username` - sets nick to "Username"
    - `leave` - leave room
- Game:
  - Ready when number of players is met and all of them are ready
  - `rock`/`paper`/`scissors` and abbreviations - make moves
- Additional commands:
  - `help` - lists available commands (in lobby and in room)

### Example game setup
*Client #1* after connection:
```
# room create
>> You can now connect to room #1337
# room join 1337
[#1337]>> Joined room #1337
[#1337]>> Waiting for other players...
```
*Client #2* connects:
```
# room list
>> Open rooms:
>> - #1337 (1/2 players)
# room join 1337
>> Joined room #1337
[#1337]# nick Lizardo
[#1337]>> Username set to "Lizardo"
[#1337]# ready
[#1337]>> Lizardo is ready (1 player(s) not ready)
```

Meanwhile *Client #1* receives notifications:
```
[#1337]>> Player #2 connected
[#1337]>> Player #2 is now known as "Lizardo"
[#1337]>> Lizardo is ready (1 player(s) not ready)
[#1337]# ready
>> Game ready
```

### Example game
*Client #1*:
```
[#1337]# rock
[#1337]>> ...
```
*Client #2*:
```
[#1337]# scissors
[#1337]>> Player #1 played rock. You lose. (0 : 1)
```
*Client #1*:
```
[#1337]>> Lizardo played scissors. You win! (1 : 0)
```
