# Pocket Monters Card Game
# ポケットモンスターカードゲーム

![Alt text](https://github.com/knuxyl/pocketmonsters/blob/master/screenshot.png?raw=true "Screenshot")
*probably not current*

# Current progress
- Still very early, this is my first C project
- Linux only but using cross platform libraries, just need cmake configuration for other platforms (windows, mac?, hopefully android)
	- I only have linux systems so this will be a while unless someone contributes
- Database design (will need to further test in battle later)
	- All base set cards are viewable by pressing c and cycling through up and down with keyboard or controller
- Controller support
	- Supports background input and up to 10 controllers
- Game audio support
	- All Pokemon GBC/GB game audio embedded and playable
	- "Original" audio format, infinite loop playback, tiny file size
	- There is something wrong with the buffer, I have no idea idea what. It sometimes messes up or something
- Color theme support
- Responsive design
- All pokemon names + translations
- Most future required libraries are being built and linked
	- Things like data serialization for saving, generating qrcodes, encryption, etc
	- I have yet to start even thinking about networking
- Statically linked

# Notable competing project
I started my project on March 22 and another project with almost the same goals started the day prior. I found out about it looking up information to get my project going. Very suspicious coincidence. His project uses Godot so will have much more rapid development and quick cross platform releases.
- Pokemon TCG Legacy
- https://github.com/APINKSHRIMP/Pokemon-TCG-Legacy

# Building
- See [BUILDING.MD](https://github.com/knuxyl/pocketmonsters/blob/master/BUILDING.MD)

# TODO
- Save data design
	- Waiting on starting map to know what data is to be stored
- Encryption design
	- I can generate keys but still deciding on what and where to encrypt
- Game Assets
	- English & Japanese Cards
	- I have a 300 MB Inkscape SVG for designing packs, I can't decide which design but it can be done in bulk in a day with how much progress I've made
	- Script to automatically format cards for game (WIP, looks great now but I keep changing my mind)
		- The script automatically pulls 8 pixels from various points around the border of cropped cards, averages them out, and generates a rounded border
		- Automatically resizes and limits colorspace and then optimizes with oxi-png so cards can be embedded
		- Generates all the c files for including
- Playable on a Raspberry Pi 2 and a Google Pixel (1)
	- I have yet to figure out how to build for android, this is for future
	- My arm64 system is complaining about not being able to initialize video device... It's a rock 5b on gentoo mainline linux, it should work.
- Tilemaps/Tilesets - haven't started
	- I can't seem to find a good 16x16 colored tileset for feudal Japan...
	- Will be using tiled
- Battling - haven't started
- Story Mode - haven't started

# Primary libraries
- raylib (game engine)
- sdl3 (backend for raylib)
- libgcrypt (serpent encryption)
- libsodium (x25519 assymetric key exchange)
- libcbor (data serialization)
- libgme (GBC & GB music player)
- zint (barcode encoding)
- zxing (barcode decoding)
- networking (TODO)
### Other static linked libraries
- libusb
- libhidapi
- libflac
- libogg, libopus, libopusfile
- libdrm (linux only)
### Linux libraries dynamically linked
- Most of these will be statically linked once I move the project to an Alpine machine
- linux-vdso
- libstdc++
- libm
- libc
- ld-linux-x86-64
- libgcc_s

# Engine Features
- Written in C
- Cmake build system
- Responsive layout
- Cross platform
- Multi-language support
- GPU and Software rendering
- Embedded assets + option to load high resolution
- Touch/Keyboard+Mouse/Controller support
- All assets embedded in binary
- Possibility for making this also a regular pokemon game as well in the future

# Game Features
- 2D tilemaps like the original games
- Offline gameplay
	- Infinite battle tournament system like the battle tower in emerald.
	- Story mode will probably follow the style of the GBC games.
	- Holiday and random events
	- Series progression system, start with Base set and work your way to Mega. (maybe)
- All cards from all regions
	- This will take a while, but once the database structure is finished then adding will just be trivial. Generic functions are easy to create and add.
- Every card has a unique id
	- Preserved throughout trading
- Custom card backs
- Private server with card signing (verification)
- Trading via Data Matrix or QRCodes (android only)
	- I think Data Matrix is actually more compact than QRCodes and each individual card stores a lot of data
	- This was the driving idea behind the entire game

# Server play
- Server can configure whether to allow cards from other servers (server signed) / offline play (player signed), independently. Can create a list of accepted public keys/uuids for acceptance.
- Server can configure whether to sign and encrypt cards to prevent offline play. Save data is still stored locally.
- Server ideas have not been decided on how to handle encryption and signing. Server play is about the last part of the game to be developed.

# Trading
- Data Matrix codes can be generated of a card to give to another player. The other player's UID (public key) must be known beforehand (added to friends list). Once the code is generated the card is deleted from the player's inventory. The Data Matrix is encrypted with serpent and can only be decrypted by the target player. Each Data Matrix will be hashed with blake3 and stored in list of scanned codes to prevent duplicating. The data in the code can also be serialized to an encrypted file and sent to a player. The file will actually be the card. The player who generated the card can decrypt it but not accept it, unless the target player was themselves.

# Security
- There are a lot of security mechanisms to be implemented to prevent cheating but this is an impossible task with this being open source and offline so the goal was really just to make it difficult and stable. It will be like the original pokemon, you can play vanilla or use gameshark. 

# Software used
- Gimp v3.2.2
- Inkscape v1.4.3
- GCC v15.2.1 / CMake v4.2.4
- Gnome Text Editor

# Music
- The internet available rips of the original GBC/GB Pokemon games were corrupted, especially for Pokemon TCG. I found the original developer of the gbs ripper's website and downloaded the latest tool to rerip all the games. This is the most complete set of ripped music for the Pokemon games in gbs format on the internet, albeit from the japanese versions. None of the tracks are corrupted like what is available on zophars domain or the like. 
