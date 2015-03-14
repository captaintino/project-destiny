# Network File Format: #

The networking will be tournament style, where each user connects to the server and then plays their own single-player game. Each time the user finishes a level or ends their game, the client will send an update to the server with the user's new score as well as if he is alive or dead. The user will be able to access a screen which lists all of the current users and their scores. The user can press a refresh button which will send a request to the server to send an updated list to the client.



# Example: #
### Messages From Client: ###
  * UPDATE or REFRESH
  * Username
  * New Total Score
  * Completed Level or Died
  * Current Level

#### Example: ####
  * UPDATE AustinC ALIVE 27356 3

##### OR #####
  * Refresh - This will cause the server to respond with this:

### Messages From Server: ###
  * Number of Users
  * Username
  * Score
  * Still alive or dead
  * Level they are/were on
  * New Line

#### Example: ####
  1. 3
  1. AustinC 27356 A 3
  1. KonradW 18764 D 2
  1. IMultiThreadedQObjects -10254 A 1