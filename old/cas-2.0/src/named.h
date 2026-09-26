typedef struct {
    char* name;
    void* ptr;
} Named;

extern Named null_named;

void* Named_get(Named*, char*);
int Named_len(Named*);
Named* Named_cat(Named*, Named*);

#define NULL_NAMED { 0, 0 }

#define NAMED_P(name) { #name, name }
#define NAMED_S(name) { #name, &name }
