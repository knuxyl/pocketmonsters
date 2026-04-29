# Pocket Monters Card Game
# ポケットモンスターカードゲーム

![Alt text](https://github.com/knuxyl/pocketmonsters/blob/master/screenshot.png?raw=true "Screenshot")
*probably not current*

# Current information
- Still very early, this is my first C project.
- Title menu
	- Press C to see Base Set cards
		- Press Left/Right to cycle through cards
		- Terminal output shows card information (only Alakazam atm, was copied)
	- Press N/M to cycle through game audio
		- Press ,/. to cycle through songs
	- Click/select options to change language
- Most testing goes in src/test/test.c

# Notable competing project
This project uses Godot so will have much more rapid development and quick cross platform releases.
- Pokemon TCG Legacy
- https://github.com/APINKSHRIMP/Pokemon-TCG-Legacy

# Building
- See [BUILDING.MD](https://github.com/knuxyl/pocketmonsters/blob/master/BUILDING.MD)

# Progress
- [x] Controller and Mouse + Keyboard support
	- Supports up to 10 connected controllers
	- Background input (when window isn't focused, will be a option)
	- All controllers control game, no seperate player 1 and player 2
- [ ] User interface
	- [x] Menus
	- [ ] Boxed dialogue/questions
	- [ ] Onscreen Keyboard
		- Only English and Japanese (no Kanji)
- [x] Multilingual support
	- English, Japanese, German, French, Spanish, Italian, Korean, Chinese Simplified, and Chinese
	- Noto font used for each language.
- [ ] Themes
	- [x] Color schemes and custom mouse cursor
	- [ ] More custom mouse cursors
- [x] Responsive
	- Scales, positions, and aligns correctly on all aspect ratios
- [ ] Game sound/music
	- Working 95% of the time but something's wrong with the audio buffer. The current system is not stable enough.
	- Reripped gbs from the Japanese games because all sources online were corrupted and missing songs/sounds.
	- [x] Loads original GBC/GB music
- [ ] Options menu
- [ ] Data serialization
- [ ] Encryption and signatures
- [ ] Tilemap drawing
- [ ] Player Save Data
- [ ] Saving and Loading
	- [ ] Save game data
	- [ ] High resolution textures
- [ ] Expand UI to support boxed text, dialogues, etc
- [ ] Card battle scene
- [ ] Card database
	- Initial work has been done
	- [ ] International
		- [ ] Wizards of the Coast
			- [ ] Base Set
			- [ ] Base Set 2
			- [ ] Fossil
			- [ ] Jungle
			- [ ] Team Rocket
			- [ ] Gym Heroes
			- [ ] Gym Challenge
- [ ] Card Assets
	- I have a script for cleaning up cropped cards (gamma, rounded border, etc) but japanese cards are a pain because the borders aren't one color
- [ ] Story
- [ ] Offline trade and duel
	- [ ] QR Code generation
	- [ ] Wifi networking
- [ ] Static linking
	- [ ] Linux
		- I need to build against musl to get rid of anything that's left. Everything else is static
	- [ ] Windows
	- [ ] Mac
	- [ ] Android
	- I have no idea what to do about platforms other than Linux with this.
- [ ] Cross platform (x86_64 & arm64)
	- [x] Linux
	- [ ] Windows
	- [ ] Mac
	- [ ] Android
	- No other platform is planned
- [ ] Translations
	- [x] Pokemon Names
	- [ ] Dialogue
	- [ ] Cards
	- [ ] User interface
- [ ] Networking/Server play

# Primary libraries
- [raylib](https://github.com/raysan5/raylib) (game engine)
- [sdl3](https://github.com/libsdl-org/SDL) (backend for raylib)
- [libgcrypt](https://github.com/gpg/libgcrypt) (serpent encryption)
- [libsodium](https://github.com/jedisct1/libsodium) (x25519 assymetric key exchange)
- [libcbor](https://github.com/PJK/libcbor) (data serialization)
- [libgme](https://github.com/libgme/game-music-emu) (GBC & GB music player)
- [zint](https://github.com/zint/zint) (barcode encoding)
- [zxing](https://github.com/zxing/zxing) (barcode decoding)
- networking (TODO)
### Other static linked libraries
- [libusb](https://github.com/libusb/libusb)
- [libhidapi](https://github.com/libusb/hidapi)
- [libflac](https://github.com/xiph/flac)
- [libogg](https://github.com/gcp/libogg)
- [libopus](https://github.com/xiph/opus)
- [libopusfile](https://github.com/xiph/opusfile)
- [libdrm](https://gitlab.freedesktop.org/mesa/drm)

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
