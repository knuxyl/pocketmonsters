#include "music.c"
#define SAMPLE_RATE 44100
#define FRAMES 4096
#define BUFFER_SIZE (FRAMES * 2)
#define AUDIO_STREAMS 2

AudioStream music_stream;
AudioStream sound_stream;
bool music_playing;
bool sound_playing;
short int music_buffer[BUFFER_SIZE];
short int sound_buffer[BUFFER_SIZE];
Music_Emu* music_player;
Music_Emu* sound_player;

void pause_sound() {
	PauseAudioStream(sound_stream);
}

void resume_sound() {
	ResumeAudioStream(sound_stream);
}

void stop_sound() {
	if (sound_playing) {
		sound_playing = false;
		StopAudioStream(sound_stream);
		gme_delete(sound_player);
		UnloadAudioStream(sound_stream);
	}
}

void pause_music() {
	PauseAudioStream(music_stream);
}

void resume_music() {
	ResumeAudioStream(music_stream);
}

void stop_music() {
	if (music_playing) {
		music_playing = false;
		StopAudioStream(music_stream);
		gme_delete(music_player);
		UnloadAudioStream(music_stream);
	}
}


void play_sound(uint16_t track) {
	stop_sound();
	gme_open_data(embedded_music[config.game_audio].data, embedded_music[config.game_audio].len, &sound_player, SAMPLE_RATE);
	gme_start_track(sound_player, audio[config.game_audio][track]);
	sound_stream = LoadAudioStream(SAMPLE_RATE, 16, 2);
	PlayAudioStream(sound_stream);
	sound_playing = true;
	SetAudioStreamVolume(sound_stream, config.sound_volume * (!config.mute));
}

void play_music(uint16_t track) {
	stop_music();
	gme_open_data(embedded_music[config.game_audio].data, embedded_music[config.game_audio].len, &music_player, SAMPLE_RATE);
	gme_start_track(music_player, audio[config.game_audio][track]);
	music_stream = LoadAudioStream(SAMPLE_RATE, 16, 2);
	PlayAudioStream(music_stream);
	music_playing = true;
	SetAudioStreamVolume(music_stream, config.music_volume * (!config.mute));
}

void mute() {
	SetAudioStreamVolume(sound_stream, config.sound_volume * (config.mute));
	SetAudioStreamVolume(music_stream, config.music_volume * (config.mute));
	config.mute = !config.mute;
}

void init_audio() {
	InitAudioDevice();
	SetMasterVolume(1.0);
	SetAudioStreamBufferSizeDefault(FRAMES);
}

void loop_audio() {
	if (sound_playing) {
		while (IsAudioStreamProcessed(sound_stream)) {
			gme_play(sound_player, BUFFER_SIZE, sound_buffer);
			UpdateAudioStream(sound_stream, sound_buffer, FRAMES);
		}
	}
	if (music_playing) {
		while (IsAudioStreamProcessed(music_stream)) {
			gme_play(music_player, BUFFER_SIZE, music_buffer);
			UpdateAudioStream(music_stream, music_buffer, FRAMES);
		}
	}
}
