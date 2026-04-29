void deserialize_public_signature(cbor_item_t* map, struct public_signature* s)
{
    s->name = copy_cbor_string(cbor_map_get(map, "name"));

    memcpy(s->sign_public,
        cbor_bytestring_handle(cbor_map_get(map, "sign_public")),
        crypto_sign_PUBLICKEYBYTES);

    memcpy(s->signature,
        cbor_bytestring_handle(cbor_map_get(map, "signature")),
        crypto_sign_SECRETKEYBYTES);
}

char* copy_cbor_string(cbor_item_t* item)
{
    size_t len = cbor_string_length(item);
    char* str = malloc(len + 1);

    memcpy(str, cbor_string_handle(item), len);
    str[len] = '\0';

    return str;
}

struct card_metadata* deserialize_card_metadata_array(
    cbor_item_t* array,
    uint32_t* out_count
)
{
    size_t count = cbor_array_size(array);
    *out_count = count;

    struct card_metadata* arr =
        malloc(sizeof(struct card_metadata) * count);

    for (size_t i = 0; i < count; i++)
    {
        cbor_item_t* item = cbor_array_get(array, i);
        deserialize_card_metadata(item, &arr[i]);
    }

    return arr;
}

void deserialize_card_info(cbor_item_t* map, struct card_info* ci)
{
    ci->region = cbor_get_uint8(cbor_map_get(map, "region"));
    ci->language = cbor_get_uint8(cbor_map_get(map, "language"));
    ci->series = cbor_get_uint16(cbor_map_get(map, "series"));
    ci->set = cbor_get_uint16(cbor_map_get(map, "set"));
    ci->card = cbor_get_uint16(cbor_map_get(map, "card"));
    ci->variant = cbor_get_uint64(cbor_map_get(map, "variant"));
    ci->extra = cbor_get_uint8(cbor_map_get(map, "extra"));
}

cbor_item_t* cbor_map_get(cbor_item_t* map, const char* key)
{
    struct cbor_pair* pairs = cbor_map_handle(map);
    size_t size = cbor_map_size(map);

    for (size_t i = 0; i < size; i++)
    {
        cbor_item_t* k = pairs[i].key;

        if (cbor_isa_string(k))
        {
            char* str = (char*)cbor_string_handle(k);

            if (strcmp(str, key) == 0)
                return pairs[i].value;
        }
    }

    return NULL;
}

cbor_item_t* load_cbor_from_file(const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    unsigned char* buffer = malloc(size);
    fread(buffer, 1, size, fp);
    fclose(fp);

    struct cbor_load_result result;
    cbor_item_t* item = cbor_load(buffer, size, &result);

    free(buffer);

    if (result.error.code != CBOR_ERR_NONE)
        return NULL;

    return item;
}
