typedef struct {
	uint8_t row[16];
} pattern;

typedef struct {
	uint8_t row[4];
} orderrow;

typedef struct {
	char title[16];
	char artist[16];
	char copyinfo[16];
	uint8_t speedlut[16];
	uint8_t volumelut[16];
	pattern patterns[128];
	orderrow orderrows[128];
} song_data;
