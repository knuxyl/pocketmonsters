//#include "save/save_data.c"
exe_path = GetApplicationDirectory();
save_file = TextFormat("%spmcg.sav", exe_path);

//static FILE *save_file;
struct save_game save_game;



cbor_item_t* serialize_player_public(struct player_public *p) {
    cbor_item_t* map = cbor_new_definite_map(5);
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("name")),
            .value = cbor_build_string(p->name ? p->name : "")
        }
    );
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("public")),
            .value = cbor_build_bytestring(p->public, crypto_sign_PUBLICKEYBYTES)
        }
    );
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("encrypt_public")),
            .value = cbor_build_bytestring(p->encrypt_public, crypto_box_PUBLICKEYBYTES)
        }
    );
    return map;
};

cbor_item_t* serialize_player_public_array(struct player_public* arr, uint32_t count)
{
    cbor_item_t* array = cbor_new_definite_array(count);
    for (uint32_t i = 0; i < count; i++)
    {
        cbor_array_push(array,
            serialize_player_public(&arr[i])
        );
    }
    return array;
}




cbor_item_t* serialize_player_private(struct player_private *p) {
    cbor_item_t* map = cbor_new_definite_map(5);
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("name")),
            .value = cbor_build_string(p->name ? p->name : "")
        }
    );

    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("public")),
            .value = cbor_build_bytestring(p->public, crypto_sign_PUBLICKEYBYTES)
        }
    );

    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("private")),
            .value = cbor_build_bytestring(p->private, crypto_sign_SECRETKEYBYTES)
        }
    );

    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("encrypt_public")),
            .value = cbor_build_bytestring(p->encrypt_public, crypto_box_PUBLICKEYBYTES)
        }
    );

    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("encrypt_private")),
            .value = cbor_build_bytestring(p->encrypt_private, crypto_box_SECRETKEYBYTES)
        }
    );
    return map;
};
cbor_item_t* serialize_card_info(struct player_card_info* ci)
{
    cbor_item_t* map = cbor_new_definite_map(7);

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("region")),
        .value = cbor_build_uint8(ci->region)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("language")),
        .value = cbor_build_uint8(ci->language)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("series")),
        .value = cbor_build_uint16(ci->series)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("set")),
        .value = cbor_build_uint16(ci->set)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("card")),
        .value = cbor_build_uint16(ci->card)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("variant")),
        .value = cbor_build_uint64(ci->variant)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("extra")),
        .value = cbor_build_uint8(ci->extra)
    });

    return map;
}

cbor_item_t* serialize_obtained_from(struct player_obtained* o)
{
    cbor_item_t* map = cbor_new_definite_map(3);

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("date")),
        .value = cbor_build_uint64(o->date)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("method")),
        .value = cbor_build_uint8(o->method)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("player")),
        .value = serialize_player_public(&o->player)
    });

    return map;
}

cbor_item_t* serialize_card(struct player_card* c)
{
    cbor_item_t* map = cbor_new_definite_map(15);
    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("owners")),
        .value = cbor_build_uint32(c->owners)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("owner")),
        .value = serialize_player_public(&c->owner)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("owner_obtained")),
        .value = serialize_obtained_from(&c->owner_obtained)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("last_owner")),
        .value = serialize_player_public(&c->last_owner)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("last_obtained")),
        .value = serialize_obtained_from(&c->last_obtained)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("original_owner")),
        .value = serialize_player_public(&c->original_owner)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("original_obtained")),
        .value = serialize_obtained_from(&c->original_obtained)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("card")),
        .value = serialize_card_info(&c->card)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("condition")),
        .value = cbor_build_uint8(c->condition)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("won")),
        .value = cbor_build_uint16(c->won)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("lost")),
        .value = cbor_build_uint16(c->lost)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("knockouts")),
        .value = cbor_build_uint16(c->knockouts)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("knockedout")),
        .value = cbor_build_uint16(c->knockedout)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("achievements")),
        .value = cbor_build_uint64(c->achievements)
    });

    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("signature")),
        .value = serialize_player_public(&c->signature)
    });
    return map;
}

cbor_item_t* serialize_card_array(struct player_card* arr, uint32_t count)
{
    cbor_item_t* array = cbor_new_definite_array(count);
    for (uint32_t i = 0; i < count; i++)
    {
        cbor_array_push(array,
            serialize_card(&arr[i])
        );
    }
    return array;
}


cbor_item_t* serialize_deck(struct player_deck* d)
{
    cbor_item_t* map = cbor_new_definite_map(2);
    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("name")),
        .value = cbor_build_string(d->name ? d->name : "")
    });
    cbor_map_add(map, (struct cbor_pair){
        .key = cbor_move(cbor_build_string("cards")),
        .value = serialize_card(d->cards, d->card_count)
    });
    return map;
}


cbor_item_t* serialize_deck_array(struct player_deck* arr, uint32_t count)
{
    cbor_item_t* array = cbor_new_definite_array(count);
    for (uint32_t i = 0; i < count; i++)
    {
        cbor_array_push(array,
            serialize_deck(&arr[i])
        );
    }
    return array;
}

cbor_item_t* serialize_player_progress(struct player_progress *s) {
	cbor_item_t* map = cbor_new_definite_map(1);
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("stage")),
            .value = cbor_build_uint64((uint8_t) s->stage)
        }
    );
};

cbor_item_t* serialize_slot(struct player_slot *s) {
    cbor_item_t* map = cbor_new_definite_map(7);
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("progress")),
            .value = serialize_player_progress(s->progress)
        }
    );
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("player")),
            .value = serialize_player_private(&s->player)
        }
    );
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("friends")),
            .value = serialize_player_public_array(s->friends, s->friend_count)
        }
    );
    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("cards")),
            .value = serialize_card_array(s->cards, s->card_count)
        }
    );

    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("decks")),
            .value = serialize_deck_array(s->decks, s->deck_count)
        }
    );

    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("date_created")),
            .value = cbor_build_uint64((uint64_t) s->date_created)
        }
    );

    cbor_map_add(map, (struct cbor_pair) {
            .key = cbor_move(cbor_build_string("date_saved")),
            .value = cbor_build_uint64((uint64_t) s->date_saved)
        }
    );
    return map;
};



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
