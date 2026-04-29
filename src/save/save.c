//#include "save/save_data.c"
exe_path = GetApplicationDirectory();
save_file = TextFormat("%spmcg.sav", exe_path);

//static FILE *save_file;
struct save_game save_game;

bool save_exists() {
    //FILE *fp = fopen(filename, "rb");
    //if (fp) {
        //fclose(fp);
        //return true;
    //};
    //return false;
    if (FileExists(save_file)) {
    		return true;
    	}
    	return false;
};

void load_save() {

};
bool write_save(cbor_item_t *map) {
    unsigned char *buffer = NULL;
    size_t buffer_size = 0;
    cbor_serialize_alloc(map, &buffer, &buffer_size);
    if (SaveFileData(save_path, map, buffer_size) {
    		return true;
    	}
    	return false;
    //fwrite(buffer, 1, buffer_size, save_file);
    //free(buffer);
    //fclose(save_file);
    //return false;
};
void init_save() {
	//save_file = fopen(save_path, "wr");
    //write_save(serialize_slot(&current_save));
};
